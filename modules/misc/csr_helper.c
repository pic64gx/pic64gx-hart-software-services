/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/**
 * \file CSR Helper
 * \brief CSR Helper
 */

#include "config.h"
#include "hss_types.h"

#include "csr_helper.h"
#include "ssmb_ipi.h"
#include "hss_debug.h"

#include "mpfs_reg_map.h"


#include <assert.h>

HSSTicks_t CSR_GetTickCount(void)
{
    HSSTicks_t tickCount;

    tickCount = csr_read(mcycle);

    return tickCount;
}

HSSTicks_t CSR_GetTime(void)
{
    HSSTicks_t time;

    time = mHSS_ReadRegU64(CLINT, MTIME);

    return time;
}

void CSR_ClearMSIP(void)
{
    int hartid = current_hartid();

    switch (hartid) {
    case HSS_HART_U54_1:
        mHSS_WriteRegU32(CLINT, MSIP_U54_1, 0u);
        break;

    case HSS_HART_U54_2:
        mHSS_WriteRegU32(CLINT, MSIP_U54_2, 0u);
        break;

    case HSS_HART_U54_3:
        mHSS_WriteRegU32(CLINT, MSIP_U54_3, 0u);
        break;

    case HSS_HART_U54_4:
        mHSS_WriteRegU32(CLINT, MSIP_U54_4, 0u);
        break;

    default:
        mHSS_DEBUG_PRINTF(LOG_NORMAL, "Unknown hart ID %u\n", hartid);
        assert(0 == 1);
        break;
    }
}
