/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Timothy Pearson <tpearson@raptorengineeringinc.com>,
 *	 Raptor Engineering
 * Copyright (C) 2012 ChromeOS Authors
 * 2005.6 by yhlu
 * 2006.3 yhlu add copy data from CAR to ram
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <string.h>
#include <arch/stages.h>
#include <arch/early_variables.h>
#include <cpu/x86/mtrr.h>
#include <cpu/amd/mtrr.h>
#include <cpu/amd/car.h>
#include <arch/acpi.h>
#include <romstage_handoff.h>
#include "cbmem.h"
#include "cpu/amd/car/disable_cache_as_ram.c"

#if CONFIG_RAMTOP <= 0x100000
	#error "You need to set CONFIG_RAMTOP greater than 1M"
#endif

#if IS_ENABLED(CONFIG_DEBUG_CAR)
#define print_car_debug(format, arg...) printk(BIOS_DEBUG, "%s: " format, __func__, ##arg)
#else
#define print_car_debug(format, arg...)
#endif

static size_t backup_size(void)
{
	size_t car_size = car_data_size();
	return ALIGN(car_size + 1024, 1024);
}

static void memcpy_(void *d, const void *s, size_t len)
{
	print_car_debug(" Copy [%08x-%08x] to [%08x - %08x] ...",
		(uint32_t) s, (uint32_t) (s + len - 1), (uint32_t) d, (uint32_t) (d + len - 1));
	memcpy(d, s, len);
}

static void memset_(void *d, int val, size_t len)
{
	print_car_debug(" Fill [%08x-%08x] ...", (uint32_t) d, (uint32_t) (d + len - 1));
	memset(d, val, len);
}

static int memcmp_(void *d, const void *s, size_t len)
{
	print_car_debug(" Compare [%08x-%08x] with [%08x - %08x] ...",
		(uint32_t) s, (uint32_t) (s + len - 1), (uint32_t) d, (uint32_t) (d + len - 1));
	return memcmp(d, s, len);
}

static void prepare_romstage_ramstack(void *resume_backup_memory)
{
	size_t backup_top = backup_size();
	print_car_debug("Prepare CAR migration and stack regions...");

	if (resume_backup_memory) {
		memcpy_(resume_backup_memory + HIGH_MEMORY_SAVE - backup_top,
			(void *)(CONFIG_RAMTOP - backup_top), backup_top);
	}
	memset_((void *)(CONFIG_RAMTOP - backup_top), 0, backup_top);

	print_car_debug(" Done\n");
}

static void prepare_ramstage_region(void *resume_backup_memory)
{
	size_t backup_top = backup_size();
	print_car_debug("Prepare ramstage memory region...");

	if (resume_backup_memory) {
		memcpy_(resume_backup_memory, (void *) CONFIG_RAMBASE, HIGH_MEMORY_SAVE - backup_top);
		memset_((void*) CONFIG_RAMBASE, 0, HIGH_MEMORY_SAVE - backup_top);
	} else {
		memset_((void*)0, 0, CONFIG_RAMTOP - backup_top);
	}

#if IS_ENABLED(CONFIG_HAVE_ROMSTAGE_CONSOLE_SPINLOCK)
	initialize_romstage_console_lock();
#endif
#if IS_ENABLED(CONFIG_HAVE_ROMSTAGE_NVRAM_CBFS_SPINLOCK)
	initialize_romstage_nvram_cbfs_lock();
#endif

	print_car_debug(" Done\n");
}

/* Disable Erratum 343 Workaround, see RevGuide for Fam10h, Pub#41322 Rev 3.33
 * and RevGuide for Fam12h, Pub#44739 Rev 3.10
 */

static void vErrata343(void)
{
	msr_t msr;
	unsigned int uiMask = 0xFFFFFFF7;

	msr = rdmsr(BU_CFG2_MSR);
	msr.hi &= uiMask;	// IcDisSpecTlbWr (bit 35) = 0
	wrmsr(BU_CFG2_MSR, msr);
}

void post_cache_as_ram(void)
{
	void *resume_backup_memory = NULL;
	uint32_t family = amd_fam1x_cpu_family();

	/* Verify that the BSP didn't overrun the lower stack
	 * boundary during romstage execution
	 */
	volatile uint32_t *lower_stack_boundary;
	lower_stack_boundary = (void *)((CONFIG_DCACHE_RAM_BASE + CONFIG_DCACHE_RAM_SIZE) - CONFIG_DCACHE_BSP_STACK_SIZE);
	if ((*lower_stack_boundary) != 0xdeadbeef)
		printk(BIOS_WARNING, "BSP overran lower stack boundary.  Undefined behaviour may result!\n");

	struct romstage_handoff *handoff;
	handoff = romstage_handoff_find_or_add();
	if (handoff != NULL)
		handoff->s3_resume = acpi_is_wakeup_s3();
	else
		printk(BIOS_DEBUG, "Romstage handoff structure not added!\n");

	int s3resume = acpi_is_wakeup_s3();
	if (s3resume) {
		cbmem_recovery(s3resume);
		resume_backup_memory = cbmem_find(CBMEM_ID_RESUME);
	}
	prepare_romstage_ramstack(resume_backup_memory);

	/* from here don't store more data in CAR */
	if (family >= 0x1f && family <= 0x3f) {
		/* Family 10h and 12h, 11h until shown otherwise */
		vErrata343();
	}

	size_t car_size = car_data_size();
	void *migrated_car = (void *)(CONFIG_RAMTOP - car_size);

	print_car_debug("Copying data from cache to RAM...");
	memcpy_(migrated_car, _car_relocatable_data_start, car_size);
	print_car_debug(" Done\n");

	print_car_debug("Verifying data integrity in RAM...");
	if (memcmp_(migrated_car, _car_relocatable_data_start, car_size) == 0)
		print_car_debug(" Done\n");
	else
		print_car_debug(" FAILED\n");

	/* New stack grows right below migrated_car. */
	print_car_debug("Switching to use RAM as stack...");
	cache_as_ram_switch_stack(migrated_car);

	/* We do not come back. */
}

void cache_as_ram_new_stack (void)
{
	void *resume_backup_memory = NULL;

	print_car_debug("Top about %08x ... Done\n", (uint32_t) &resume_backup_memory);
	print_car_debug("Disabling cache as ram now\n");
	disable_cache_as_ram_bsp();

	disable_cache();
	/* Enable cached access to RAM in the range 1M to CONFIG_RAMTOP */
	set_var_mtrr(0, 0x00000000, CONFIG_RAMTOP, MTRR_TYPE_WRBACK);
	enable_cache();

	if (acpi_is_wakeup_s3()) {
		resume_backup_memory = cbmem_find(CBMEM_ID_RESUME);
		print_car_debug("Resume backup memory location: %p\n", resume_backup_memory);
	}
	prepare_ramstage_region(resume_backup_memory);

	set_sysinfo_in_ram(1); // So other core0 could start to train mem

	/*copy and execute ramstage */
	copy_and_run();
	/* We will not return */

	print_car_debug("should not be here -\n");
}
