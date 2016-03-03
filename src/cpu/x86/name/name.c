/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
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
#include <device/device.h>
#include <cpu/cpu.h>
#include <cpu/x86/name.h>

void fill_processor_name(char *processor_name
{
	struct cpuid_result regs;
	char temp_processor_name[49];
	char *processor_name_start;
	unsigned int *name_as_ints = (unsigned int *)temp_processor_name;
	int i;

	/* 
	用cpuid指令，eax传入0x80000002/0x80000003/0x80000004，
	共3个，每个4个寄存器，每个寄存器4字节，故一共48字节。
	参考IA32开发手册第2卷第3章。
	*/
	for (i = 0; i < 3; i++) {
		regs = cpuid(0x80000002 + i);
		name_as_ints[i * 4 + 0] = regs.eax;
		name_as_ints[i * 4 + 1] = regs.ebx;
		name_as_ints[i * 4 + 2] = regs.ecx;
		name_as_ints[i * 4 + 3] = regs.edx;
	}

	temp_processor_name[48] = 0; // 最后的字节为0，结束

	/* Skip leading spaces. */
	processor_name_start = temp_processor_name;
	while (*processor_name_start == ' ')
		processor_name_start++;

	memset(processor_name, 0, 49);
	strcpy(processor_name, processor_name_start);
}
