#ifndef HSS_BOOT_SECURE_H
#define HSS_BOOT_SECURE_H

/*******************************************************************************
 * Copyright 2021 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file  Boot Service - Code Signing
 * \brief Boot Service - Code Signing
 */


bool HSS_Boot_Secure_CheckCodeSigning(struct HSS_BootImage *pBootImage) __attribute__((nonnull));

#endif
