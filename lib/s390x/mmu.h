/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * s390x mmu functions
 *
 * Copyright (c) 2018 IBM Corp
 *
 * Authors:
 *	Janosch Frank <frankja@de.ibm.com>
 */
#ifndef _ASMS390X_MMU_H_
#define _ASMS390X_MMU_H_

void protect_page(void *vaddr, unsigned long prot);
void protect_range(void *start, unsigned long len, unsigned long prot);
void unprotect_page(void *vaddr, unsigned long prot);
void unprotect_range(void *start, unsigned long len, unsigned long prot);

#endif /* _ASMS390X_MMU_H_ */
