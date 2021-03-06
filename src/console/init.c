/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2003 Eric Biederman
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <console/uart.h>
#include <console/streams.h>
#include <device/pci.h>
#include <option.h>
#include <rules.h>
#include <version.h>

/* While in romstage, console loglevel is built-time constant. */
static ROMSTAGE_CONST int console_loglevel = CONFIG_DEFAULT_CONSOLE_LOGLEVEL;

// do_printk用到此函数判断是否输出信息
int console_log_level(int msg_level)
{
	return (console_loglevel >= msg_level);
}

// tocheck 到底在哪里调用此函数？
// 是否在romstage.c的main函数中调用呢？
void console_init(void)
{
#if !defined(__PRE_RAM__)
	console_loglevel = CONFIG_DEFAULT_CONSOLE_LOGLEVEL;
	get_option(&console_loglevel, "debug_level");
#endif

#if CONFIG_EARLY_PCI_BRIDGE && !defined(__SMM__)
	pci_early_bridge_init();
#endif

	console_hw_init();
	// 打印版本信息及编译时间 首先打印此信息
	printk(BIOS_INFO, "\n\ncoreboot-%s%s %s by Jim Kent " ENV_STRING " starting...\n",
	       coreboot_version, coreboot_extra_version, coreboot_build);
}
