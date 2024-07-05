/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/**
 * \file HSS PCIe Initalization
 * \brief PCIe Initialization
 */

#include "config.h"
#include "hss_types.h"

#include "hss_init.h"
#include "hss_debug.h"

#include <assert.h>
#include "csr_helper.h"

#include "mss_plic.h"
#include "pic64gx_reg_map.h"

// Register Defintions
#define PCIE_IRQn				(PLIC_F2M_1_INT_OFFSET)

//
// Will constrain base addr of PCIe to 0x43000000u
// and constrain to use Bridge and Ctrl [1]
#define PCIE_BASE_ADDR				(uintptr_t)0x43000000u

#define PCIE1_BRIDGE_BASE_ADDR			(PCIE_BASE_ADDR + 0x00008000u)
#define PCIE1_BRIDGE_IMASK_LOCAL_OFFSET		0x180u
#define PCIE1_BRIDGE_ISTATUS_LOCAL_OFFSET	0x184u
#define PCIE1_BRIDGE_IMASK_HOST_OFFSET		0x188u
#define PCIE1_BRIDGE_ISTATUS_HOST_OFFSET	0x18Cu

#define PCIE1_CTRL_BASE_ADDR			(PCIE_BASE_ADDR + 0x0000A000u)
#define PCIE1_CTRL_SEC_ERROR_INT_OFFSET		0x28u
#define PCIE1_CTRL_SEC_ERROR_INT_MASK_OFFSET	0x2Cu
#define PCIE1_CTRL_DED_ERROR_INT_OFFSET		0x30u
#define PCIE1_CTRL_DED_ERROR_INT_MASK_OFFSET	0x34u
#define PCIE1_CTRL_PCIE_EVENT_INT_OFFSET	0x14c

#define PCIE0_BRIDGE_BASE_ADDR			(PCIE_BASE_ADDR + 0x00004000u)
#define PCIE0_BRIDGE_IMASK_LOCAL_OFFSET		0x180u
#define PCIE0_BRIDGE_ISTATUS_LOCAL_OFFSET	0x184u
#define PCIE0_BRIDGE_IMASK_HOST_OFFSET		0x188u
#define PCIE0_BRIDGE_ISTATUS_HOST_OFFSET	0x18Cu

#define PCIE0_CTRL_BASE_ADDR			(PCIE_BASE_ADDR + 0x00006000u)
#define PCIE0_CTRL_SEC_ERROR_INT_OFFSET		0x28u
#define PCIE0_CTRL_SEC_ERROR_INT_MASK_OFFSET	0x2Cu
#define PCIE0_CTRL_DED_ERROR_INT_OFFSET		0x30u
#define PCIE0_CTRL_DED_ERROR_INT_MASK_OFFSET	0x34u
#define PCIE0_CTRL_PCIE_EVENT_INT_OFFSET	0x14c

#define MAX_RETRY_COUNT				255u

bool HSS_PCIeInit(void)
{
    // Set a priority for pcie hwirq
    // Set a context threshold for hart 0
    // enable PCIe interrupt
    PLIC_SetPriority(PCIE_IRQn, 1u);
    PLIC_SetPriority_Threshold(1u);
    PLIC_EnableIRQ(PCIE_IRQn);

    // check if an interrupt is pending
    // if so, attempt to clear (with timeout)
    uint32_t claim = PLIC_ClaimIRQ();
    uint32_t retryCount = 0u;

    while (claim != 0u) {
        uint32_t status = 0;
        (void)status;

#if IS_ENABLED(CONFIG_ENABLE_PCIE_CTRL_0)

        // turn off SEC - on ctrl0
        // clear out stragglers
        mHSS_WriteRegU32(PCIE0_CTRL, SEC_ERROR_INT_MASK, 0xFFFFu);
        status = mHSS_ReadRegU32(PCIE0_CTRL, SEC_ERROR_INT);
        if (status) {
            mHSS_WriteRegU32(PCIE0_CTRL, SEC_ERROR_INT, status);
        }

        // turn off DED - on ctrl0
        mHSS_WriteRegU32(PCIE0_CTRL, DED_ERROR_INT_MASK, 0xFFFFu);
        status = mHSS_ReadRegU32(PCIE0_CTRL, DED_ERROR_INT);
        if (status) {
            mHSS_WriteRegU32(PCIE0_CTRL, DED_ERROR_INT, status);
        }

        // turn of PCIe EVENTs - on ctrl0
        // Clear outstanding and disable future PCIE_EVENT_INTS
        status = mHSS_ReadRegU32(PCIE0_CTRL, PCIE_EVENT_INT);
        if (status & 0x7) {
            mHSS_WriteRegU32(PCIE0_CTRL, PCIE_EVENT_INT, 0x0070007u);
        }

        // turn off LOCAL interrupts - on bridge0
        mHSS_WriteRegU32(PCIE0_BRIDGE, IMASK_LOCAL, 0u);
        status = mHSS_ReadRegU32(PCIE0_BRIDGE, ISTATUS_LOCAL);
        if (status) {
            mHSS_WriteRegU32(PCIE0_BRIDGE, ISTATUS_LOCAL, status);
        }

        // turn off HOST interrupts - on bridge0
        mHSS_WriteRegU32(PCIE0_BRIDGE, IMASK_HOST, 0u);
        status = mHSS_ReadRegU32(PCIE0_BRIDGE, ISTATUS_HOST);
        if (status) {
            mHSS_WriteRegU32(PCIE0_BRIDGE, ISTATUS_HOST, status);
        }
#endif

#if IS_ENABLED(CONFIG_ENABLE_PCIE_CTRL_1)

        // turn off SEC - on ctrl1
        // clear out stragglers
        mHSS_WriteRegU32(PCIE1_CTRL, SEC_ERROR_INT_MASK, 0xFFFFu);
        status = mHSS_ReadRegU32(PCIE1_CTRL, SEC_ERROR_INT);
        if (status) {
            mHSS_WriteRegU32(PCIE1_CTRL, SEC_ERROR_INT, status);
        }

        // turn off DED - on ctrl1
        mHSS_WriteRegU32(PCIE1_CTRL, DED_ERROR_INT_MASK, 0xFFFFu);
        status = mHSS_ReadRegU32(PCIE1_CTRL, DED_ERROR_INT);
        if (status) {
            mHSS_WriteRegU32(PCIE1_CTRL, DED_ERROR_INT, status);
        }

        // turn of PCIe EVENTs - on ctrl1
        // Clear outstanding and disable future PCIE_EVENT_INTS
        status = mHSS_ReadRegU32(PCIE1_CTRL, PCIE_EVENT_INT);
        if (status & 0x7) {
            mHSS_WriteRegU32(PCIE1_CTRL, PCIE_EVENT_INT, 0x0070007u);
        }

        // turn off LOCAL interrupts - on bridge1
        mHSS_WriteRegU32(PCIE1_BRIDGE, IMASK_LOCAL, 0u);
        status = mHSS_ReadRegU32(PCIE1_BRIDGE, ISTATUS_LOCAL);
        if (status) {
            mHSS_WriteRegU32(PCIE1_BRIDGE, ISTATUS_LOCAL, status);
        }

        // turn off HOST interrupts - on bridge1
        mHSS_WriteRegU32(PCIE1_BRIDGE, IMASK_HOST, 0u);
        status = mHSS_ReadRegU32(PCIE1_BRIDGE, ISTATUS_HOST);
        if (status) {
            mHSS_WriteRegU32(PCIE1_BRIDGE, ISTATUS_HOST, status);
        }
#endif

        PLIC_CompleteIRQ(claim);

        if (retryCount < MAX_RETRY_COUNT) {
            retryCount++;
        } else {
            // don't hang around forever - if an interrupt is stubborn - signal failure
            break;
        }

        // check that no further interrupts pending
        claim = PLIC_ClaimIRQ();
    }

    // disable pcie hwirq
    // Set a context threshold for hart 0 back to 0
    // Set priority for pcie hwirq back to 0
    PLIC_DisableIRQ(PCIE_IRQn);
    PLIC_SetPriority_Threshold(0u);
    PLIC_SetPriority(PCIE_IRQn, 0u);

    return (claim == 0u);
}
