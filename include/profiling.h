#ifndef HSS_PROFILING_H
#define HSS_PROFILING_H

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
 * Hart Software Services - Function Profiling (Debug) Support
 *
 */


/**
 * \file Profiling Support
 * \brief Profiling Support
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "hss_types.h"
#include "hss_debug.h"

void __cyg_profile_func_enter (void *pFunc, void *pCaller) __attribute__((no_instrument_function));
void __cyg_profile_func_exit (void *pFunc, void *pCaller) __attribute__((no_instrument_function));
void HSS_Profile_DumpAll(void) __attribute__((no_instrument_function));

#ifdef __cplusplus
}
#endif

#endif
