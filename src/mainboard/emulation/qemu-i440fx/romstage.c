/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2004 Stefan Reinauer
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

#include <stdint.h>
#include <device/pci_def.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <device/pnp_def.h>
#include <pc80/mc146818rtc.h>
#include <console/console.h>
#include <cpu/x86/bist.h>
#include <timestamp.h>
#include <delay.h>
#include <cpu/x86/lapic.h>

#include "memory.c"

#include <cpu/intel/romstage.h>

// bist为blockboot传递的参数，intel在启动时会进行自检，正常情况下bist为0
// 在cache_as_ram.inc中会调用到此处的main
void main(unsigned long bist)
{
	int cbmem_was_initted;

	/* init_timer(); */
	post_code(0x05);

	console_init();

	ll_printk("qemu-i440fx romstage --BIST: 0x%x\n", (unsigned int)bist);
	/* Halt if there was a built in self test failure */
	report_bist_failure(bist);

	//print_pci_devices();
	//dump_pci_devices();

	cbmem_was_initted = !cbmem_recovery(0);

	timestamp_init(timestamp_get());
	timestamp_add_now(TS_START_ROMSTAGE);

}
