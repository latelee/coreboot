/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016 Intel Corp.
 * (Written by Lance Zhao <lijian.zhao@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SOC_INT_DEFINE_ASL_
#define _SOC_INT_DEFINE_ASL_

#define SDCARD_INT	3	/* Need to be shared by PMC and SCC only*/
#define UART0_INT	4	/* Need to be shared by PMC and SCC only*/
#define UART1_INT	5	/* Need to be shared by PMC and SCC only*/
#define UART2_INT	6	/* Need to be shared by PMC and SCC only*/
#define UART3_INT	7	/* Need to be shared by PMC and SCC only*/
#define XDCI_INT	13	/* Need to be shared by PMC and SCC only*/
#define GPIO_BANK_INT	16
#define NPK_INT		16
#define PIRQA_INT	16
#define PIRQB_INT	17
#define PIRQC_INT	18
#define SATA_INT	19
#define GEN_INT		19
#define PIRQD_INT	19
#define XHCI_INT	17	/* Need to be shared by PMC and SCC only*/
#define SMBUS_INT	20	/* PIRQE */
#define CSE_INT		20	/* PIRQE */
#define IUNIT_INT	21	/* PIRQF */
#define PUNIT_INT	24
#define AUDIO_INT	25
#define ISH_INT		26
#define I2C0_INT	27
#define I2C1_INT	28
#define I2C2_INT	29
#define I2C3_INT	30
#define I2C4_INT	31
#define I2C5_INT	32
#define I2C6_INT	33
#define I2C7_INT	34
#define SPI0_INT	35
#define SPI1_INT	36
#define SPI2_INT	37
#define UFS_INT		38
#define EMMC_INT	39
#define PMC_INT		40
#define SDIO_INT	42

#endif	/* _SOC_INT_DEFINE_ASL_ */
