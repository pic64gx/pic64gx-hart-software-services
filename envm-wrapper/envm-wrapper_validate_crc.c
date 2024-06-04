/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * Implementation of validate_crc() for envm-wrapper.
 */

#include "hss_types.h"

#include <assert.h>

#include "hss_debug.h"

#include <mss_uart.h>
#include <string.h>
#include <stdint.h>

#include "uart_helper.h"
#include "hss_sys_setup.h"
#include "hss_crc32.h"

bool validate_crc(void);
bool validate_crc(void)
{
    extern const struct HSS_CompressedImage hss_l2scratch_lz;
    extern const unsigned char __l2_start;
    uint32_t crc32 = CRC32_calculate(&__l2_start, hss_l2scratch_lz.originalImageLen);
    bool result = 0;

    if (hss_l2scratch_lz.originalCrc == crc32) {
       result = 1;
    }

    return result;
}
