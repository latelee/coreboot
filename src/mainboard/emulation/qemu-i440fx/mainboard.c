/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2004 Stefan Reinauer <stefan.reinauer@coreboot.org>
 * Copyright (C) 2010 Kevin O'Connor <kevin@koconnor.net>
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

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <pc80/keyboard.h>
#include <arch/io.h>
#include <console/console.h>

static const unsigned char qemu_i440fx_irqs[] = {
	11, 10, 10, 11,
	11, 10, 10, 11,
};

static void qemu_nb_init(device_t dev)
{
	/* Map memory at 0xc0000 - 0xfffff */
	int i;
	uint8_t v = pci_read_config8(dev, 0x59);
	v |= 0x30;
	pci_write_config8(dev, 0x59, v);
	for (i=0; i<6; i++)
	pci_write_config8(dev, 0x5a + i, 0x33);

	/* This sneaked in here, because Qemu does not
	 * emulate a SuperIO chip
	 */
	pc_keyboard_init(NO_AUX_DEVICE);

	/* setup IRQ routing */
	for (i = 0; i < 32; i++)
		pci_assign_irqs(0, i, qemu_i440fx_irqs + (i % 4));
}

static struct device_operations nb_operations = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = qemu_nb_init,
	.ops_pci          = 0,
};

static const struct pci_driver nb_driver __pci_driver = {
	.ops = &nb_operations,
	.vendor = 0x8086,
	.device = 0x1237,
};

//////////////////////
// 下面是chip_operations的测试，主要是演示在枚举设备前的芯片级别的初始化
// 在util/sconfig(coreboot设备树编译器工具)中生成static.c文件，将chip_operations赋值，如果不定义，则使用弱链接

static void mainboard_i440fx_enable(device_t dev)
{
    ll_printk("in %s()...\n", __func__);
}

static void mainboard_i440fx_chip_init(void *chip_info)
{
    ll_printk("in %s()...\n", __func__);
}

// 从static.c文件看，这个是root设备
struct chip_operations mainboard_ops = {
	CHIP_NAME("Late Lee qemu i440fx soc")
	.enable_dev = mainboard_i440fx_enable, // 在dev_enumerate函数中调用
	.init = mainboard_i440fx_chip_init, // 在dev_initialize_chips函数中调用
};