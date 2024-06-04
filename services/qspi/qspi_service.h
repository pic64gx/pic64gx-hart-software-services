#ifndef HSS_QSPI_DRIVER_H
#define HSS_QSPI_DRIVER_H


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
 * Hart Software Services - QSPI Initialization
 *
 */

/*!
 * \file QSPI API
 * \brief QSPI (null) Service API
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "hss_types.h"

bool HSS_QSPIInit(void);
bool HSS_QSPI_ReadBlock(void *pDest, size_t srcOffset, size_t byteCount);
bool HSS_QSPI_WriteBlock(size_t dstOffset, void *pSrc, size_t byteCount);
void HSS_QSPI_GetInfo(uint32_t *pBlockSize, uint32_t *pEraseSize, uint32_t *pBlockCount);
void HSS_QSPI_FlushWriteBuffer(void);

void HSS_QSPI_FlashChipErase(void);
void HSS_QSPI_BadBlocksInfo(void);

bool HSS_CachedQSPIInit(void);
bool HSS_CachedQSPI_ReadBlock(void *pDest, size_t srcOffset, size_t byteCount);
bool HSS_CachedQSPI_WriteBlock(size_t dstOffset, void *pSrc, size_t byteCount);
void HSS_CachedQSPI_GetInfo(uint32_t *pBlockSize, uint32_t *pEraseSize, uint32_t *pBlockCount);
void HSS_CachedQSPI_FlushWriteBuffer(void);

#ifdef __cplusplus
}
#endif

#endif
