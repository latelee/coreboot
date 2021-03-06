/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Google Inc.
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
#include <bootmode.h>
#include <arch/io.h>
#include <device/device.h>
#include <device/pci.h>
#include <soc/gpio.h>

/* Compile-time settings for developer and recovery mode. */
#define DEV_MODE_SETTING 1
#define REC_MODE_SETTING 0

#ifndef __PRE_RAM__
#include <boot/coreboot_tables.h>

void fill_lb_gpios(struct lb_gpios *gpios)
{
	struct lb_gpio chromeos_gpios[] = {
		{-1, ACTIVE_HIGH, 0, "write protect"},
		{-1, ACTIVE_HIGH, REC_MODE_SETTING, "recovery"},
		{-1, ACTIVE_HIGH, DEV_MODE_SETTING, "developer"},
		{-1, ACTIVE_HIGH, 1, "lid"}, // force open
		{-1, ACTIVE_HIGH, 0, "power"},
		{-1, ACTIVE_HIGH, gfx_get_init_done(), "oprom"},
	};
	lb_add_gpios(gpios, chromeos_gpios, ARRAY_SIZE(chromeos_gpios));
}
#endif

int get_developer_mode_switch(void)
{
	return DEV_MODE_SETTING;
}

int get_recovery_mode_switch(void)
{
	return REC_MODE_SETTING;
}

int get_write_protect_state(void)
{
	return 0;
}
