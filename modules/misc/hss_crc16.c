/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/**
 * \file CRC16 calculation
 * \brief CRC16 calculation
 */

#include "config.h"
#include "hss_types.h"

#include "hss_debug.h"
#include "hss_crc16.h"

uint16_t CRC16_calculate(const uint8_t *pInput, size_t numBytes)
{
    uint16_t result = 0u;
    int i;

    while (numBytes--) {
        result = result ^ (*pInput << 8);
        pInput++;

        for (i = 0; i < 8; i++) {
            if (result & 0x8000u) {
                result = (result << 1) ^ 0x1021u;
            } else {
               result = result << 1;
            }
        }
    }

    return result;
}
