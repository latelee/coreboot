/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2000,2007 Ronald G. Minnich <rminnich@gmail.com>
 * Copyright (C) 2007-2008 coresystems GmbH
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

#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/post_code.h>
#include <cbmem.h>

#define CACHE_AS_RAM_SIZE 0x10000
#define CACHE_AS_RAM_BASE 0xd0000

#define CPU_PHYSMASK_HI  (1 << (CONFIG_CPU_ADDR_BITS - 32) - 1)

	/* Save the BIST result. */
	movl	%eax, %ebp

cache_as_ram:
	post_code(0x20)
       /* Clear the cache memory region. This will also fill up the cache */
	movl	$CACHE_AS_RAM_BASE, %esi
	movl	%esi, %edi
	movl	$(CACHE_AS_RAM_SIZE >> 2), %ecx
	// movl	$0x23322332, %eax
	xorl	%eax, %eax
	/* 使用 EAX 填写位于 ESI:EDI 的 ECX 个双字 */
	/* 将CACHE_AS_RAM_BASE地址的大小为CACHE_AS_RAM_SIZE区域初始化为0 */
	rep	stosl

	post_code(0x21)
	/* Set up the stack pointer. */
	movl	$(CACHE_AS_RAM_SIZE + CACHE_AS_RAM_BASE - 4), %eax
	movl	%eax, %esp

	/* Restore the BIST result. */
	movl	%ebp, %eax
	movl	%esp, %ebp
	/* eax为BIST值，将其压栈，作为main的参数，然后调用main函数 */
	pushl	%eax
	/*测试 pushl $0xdeadbeaf*/

before_romstage:
	post_code(0x29)
	/* 跳转到romstage的主函数 */
	/* Call romstage.c main function. */
	call	main

	post_code(0x30)

 /* 调用完main后，就到了copy_and_run，即ramstage阶段了 */
__main:
	post_code(POST_PREPARE_RAMSTAGE)
	cld			/* Clear direction flag. */

	movl	$CONFIG_RAMTOP, %esp
	movl	%esp, %ebp
	/* 此处为调试用
	movl $9, %eax
	pushl	%eax
	*/
	/* 调用copy_and_run */
	call	copy_and_run

.Lhlt:
	post_code(POST_DEAD_CODE)
	hlt
	jmp	.Lhlt
