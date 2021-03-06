/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2015-2016 Intel Corporation.
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

#ifndef _QUARK_IOMAP_H_
#define _QUARK_IOMAP_H_

/*
 * Memory Mapped IO base addresses.
 */

/* UART MMIO */
#define UART_BASE_ADDRESS		CONFIG_TTYS0_BASE

/* I2C/GPIO Controller */
#define I2C_GPIO_BASE_ADDRESS		0xa0020000

/*
 * I/O port address space
 */
#define ACPI_BASE_ADDRESS		0x1000
#define ACPI_BASE_SIZE			0x100

#define LEGACY_GPIO_BASE_ADDRESS	0x1080
#define LEGACY_GPIO_SIZE		0x80

#define IO_ADDRESS_VALID		0x80000000

#endif /* _QUARK_IOMAP_H_ */
