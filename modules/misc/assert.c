/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file assert implementation
 * \brrief Local assert
 */

#include "config.h"
#include "hss_types.h"
#include "hss_debug.h"

#include <stdlib.h>


/*!
 * \brief Local implemention of assert fail
 */

__attribute__ ((__noreturn__)) void __assert_func(const char *__file, unsigned int __line,
        const char *__function, const char *__assertion);
__attribute__ ((__noreturn__)) void __assert_func(const char *__file, unsigned int __line,
        const char *__function, const char *__assertion)
{
    mHSS_DEBUG_PRINTF(LOG_ERROR, "%s:%d: %s() Assertion failed:\n\t%s\n",
        __file, __line, __function, __assertion);

#ifndef __riscv
    exit(1);
#else
    while(1);
#endif
}

__attribute__ ((__noreturn__)) void __assert_fail(const char *__file, unsigned int __line,
        const char *__function, const char *__assertion);
__attribute__ ((__noreturn__)) void __assert_fail(const char *__file, unsigned int __line,
        const char *__function, const char *__assertion)
{
   __assert_func(__file, __line, __function, __assertion);
}

