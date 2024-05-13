/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HAL Embedded Software
 *
 *
 * @file mss_plic.c
 * @author Microchip Technology Inc
 * @brief PIC64GX MSS PLIC and PRCI access data structures and functions.
 *
 * PLIC related data which cannot be placed in mss_plic.h
 *
 */
#include "pic64gx_hal/mss_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

const unsigned long plic_hart_lookup[5U] = {0U, 1U, 3U, 5U, 7U};

#ifdef __cplusplus
}
#endif
