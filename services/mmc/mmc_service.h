#ifndef HSS_MMC_SERVICE_H
#define HSS_MMC_SERVICE_H


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
 * Hart Software Services - EMMC Initialization
 *
 */

/*!
 * \file MMC API
 * \brief MMC (null) Service API
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "hss_types.h"

bool HSS_MMCInit(void);
bool HSS_MMC_ReadBlock(void *pDest, size_t srcOffset, size_t byteCount);
bool HSS_MMC_WriteBlock(size_t dstOffset, void *pSrc, size_t byteCount);
bool HSS_MMC_WriteBlockSDMA(size_t dstOffset, void *pSrc, size_t byteCount);
void HSS_MMC_GetInfo(uint32_t *pBlockSize, uint32_t *pEraseSize, uint32_t *pBlockCount);
void HSS_MMC_SelectSDCARD(void);
void HSS_MMC_SelectMMC(void);
void HSS_MMC_SelectEMMC(void);

#ifdef __cplusplus
}
#endif

#endif
