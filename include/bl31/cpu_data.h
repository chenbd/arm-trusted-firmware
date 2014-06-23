/*
 * Copyright (c) 2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CPU_DATA_H__
#define __CPU_DATA_H__

/* Offsets for the cpu_data structure */
#define CPU_DATA_CRASH_STACK_OFFSET	0x0
#define CPU_DATA_LOG2SIZE		6

#ifndef __ASSEMBLY__

#include <arch_helpers.h>
#include <platform_def.h>
#include <stdint.h>

/*******************************************************************************
 * Function & variable prototypes
 ******************************************************************************/

/*******************************************************************************
 * Cache of frequently used per-cpu data:
 *   Address of the crash stack
 * It is aligned to the cache line boundary to allow efficient concurrent
 * manipulation of these pointers on different cpus
 *
 * TODO: Add other commonly used variables to this (tf_issues#90)
 *
 * The data structure and the _cpu_data accessors should not be used directly
 * by components that have per-cpu members. The member access macros should be
 * used for this.
 ******************************************************************************/

typedef struct cpu_data {
	uint64_t crash_stack;
} __aligned(CACHE_WRITEBACK_GRANULE) cpu_data_t;

struct cpu_data *_cpu_data_by_index(uint32_t cpu_index);
struct cpu_data *_cpu_data_by_mpidr(uint64_t mpidr);

/* Return the cpu_data structure for the current CPU. */
static inline struct cpu_data *_cpu_data(void)
{
	return (cpu_data_t *)read_tpidr_el3();
}


/**************************************************************************
 * APIs for initialising and accessing per-cpu data
 *************************************************************************/

void init_cpu_data_ptr(void);

#define get_cpu_data(_m)		   _cpu_data()->_m
#define set_cpu_data(_m, _v)		   _cpu_data()->_m = _v
#define get_cpu_data_by_index(_ix, _m)	   _cpu_data_by_index(_ix)->_m
#define set_cpu_data_by_index(_ix, _m, _v) _cpu_data_by_index(_ix)->_m = _v
#define get_cpu_data_by_mpidr(_id, _m)	   _cpu_data_by_mpidr(_id)->_m
#define set_cpu_data_by_mpidr(_id, _m, _v) _cpu_data_by_mpidr(_id)->_m = _v


#endif /* __ASSEMBLY__ */
#endif /* __CPU_DATA_H__ */
