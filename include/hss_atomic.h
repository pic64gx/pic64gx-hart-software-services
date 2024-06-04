#ifndef HSS_ATOMIC_H
#define HSS_ATOMIC_H

/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *
 * Hart Software Services - HSS Atomic Fences
 *
 */

/**
 * \file Hart Software Services - Atomic Fences
 * \brief Hart Software Services - Atomic Fences
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "hss_atomic.h"

#ifndef mb
#    define mb() asm volatile ("fence" ::: "memory")
#endif
#ifndef mb_i
#    define mb_i() asm volatile ("fence.i" ::: "memory")
#endif

#ifdef __cplusplus
}
#endif

#endif
