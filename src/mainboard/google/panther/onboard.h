/*
 * This file is part of the coreboot project.
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

#ifndef __MAINBOARD_ONBOARD_H
#define __MAINBOARD_ONBOARD_H

/* defines for programming the MAC address */
#define PANTHER_NIC_VENDOR_ID		0x10EC
#define PANTHER_NIC_DEVICE_ID		0x8168

/* 0x00: White LINK LED and Amber ACTIVE LED */
#define PANTHER_NIC_LED_MODE		0x00

/* NIC wake is GPIO 8 */
#define PANTHER_NIC_WAKE_GPIO		8

/* WLAN wake is GPIO 10 */
#define PANTHER_WLAN_WAKE_GPIO		10

#ifndef __ACPI__
void lan_init(void);
#endif

#endif /* __MAINBOARD_ONBOARD_H */
