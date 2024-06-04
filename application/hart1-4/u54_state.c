/*******************************************************************************
 * Copyright 2019-2021 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file U54 States
 * \brief U54 States
 */

#include "config.h"
#include "hss_types.h"
#include "hss_debug.h"

#include <assert.h>

#include "csr_helper.h"
#include "u54_state.h"
#include "wdog_service.h"
#include "reboot_service.h"

static enum HSSHartState_t hartStates[HSS_HART_NUM_PEERS] = { 0u, };

void HSS_U54_SetState(int state)
{
    int const myHartId = current_hartid();

    switch (myHartId) {
    case HSS_HART_U54_1 ... HSS_HART_U54_4:
        //mHSS_DEBUG_PRINTF(LOG_STATE_TRANSITION, "u54_%d :: [%s] -> [%s]\n", myHartId,
        //    HSS_U54_GetStateName(HSS_U54_GetState_Ex(myHartId)), HSS_U54_GetStateName(state));
        HSS_U54_SetState_Ex(myHartId, state);
        break;

    default:
        // out of bounds
        assert((myHartId >= HSS_HART_U54_1) && (myHartId <= HSS_HART_U54_4));
        break;
    }
}

int HSS_U54_GetState(void)
{
    int result = HSS_State_Idle;
    int const myHartId = current_hartid();

    switch (myHartId) {
    case HSS_HART_U54_1 ... HSS_HART_U54_4:
        result = HSS_U54_GetState_Ex(myHartId);
        break;

    default:
        // out of bounds
        assert((myHartId >= HSS_HART_U54_1) && (myHartId <= HSS_HART_U54_4));
        break;
    }

    return result;
}

int HSS_U54_GetState_Ex(int hartId)
{
    int result;

    __atomic_load(&(hartStates[hartId]), &result, __ATOMIC_RELAXED);
    return result;
}

static char const * const hartStateNames[] = {
    [ HSS_State_Idle ]               = "Idle",
    [ HSS_State_Booting ]            = "Booting",
    [ HSS_State_SBIHartInit ]        = "SBIHartInit",
    [ HSS_State_SBIWaitForColdboot ] = "SBIWaitForColdboot",
    [ HSS_State_Running ]             = "Running",
    [ HSS_State_Trap ]	             = "Trap",
    [ HSS_State_Fatal ]	             = "Fatal",
};

char const * HSS_U54_GetStateName(int state)
{
    char const * result = NULL;

    if ((state >= HSS_State_Idle) && (state <= HSS_State_Fatal)) {
        result = hartStateNames[state];
    }

    return result;
}

static long reportingFlag = 0u;

void HSS_U54_SetState_Ex(int hartId, int state)
{
    switch (hartId) {
    case HSS_HART_U54_1 ... HSS_HART_U54_4:
	__atomic_store(&(hartStates[hartId]), &state, __ATOMIC_RELAXED);
        hartStates[hartId] = state;
        __atomic_store_n(&reportingFlag, 1, __ATOMIC_RELAXED);
        break;

    default:
        // out of bounds
        assert((hartId >= HSS_HART_U54_1) && (hartId <= HSS_HART_U54_4));
        break;
    }

#if IS_ENABLED(CONFIG_SERVICE_REBOOT) && IS_ENABLED(CONFIG_ALLOW_COLDREBOOT_ON_OPENSBI_FAULT)
    if (state == HSS_State_Fatal) {
        mHSS_DEBUG_PRINTF(LOG_ERROR, "***** u54_%d State Change to [%s] => forcing reboot *****",
            hartId, HSS_U54_GetStateName(HSS_State_Fatal));
        HSS_SpinDelay_Secs(CONFIG_COLDREBOOT_ON_OPENSBI_FAULT_DELAY);
        HSS_reboot_cold(HSS_HART_ALL);
    }
#endif
}

void HSS_U54_DumpStatesIfChanged(void)
{
    long retval = 0u;
    __atomic_load(&reportingFlag, &retval, __ATOMIC_RELAXED);
    if (retval) {
        mHSS_DEBUG_PRINTF(LOG_STATE_TRANSITION, "u54 State Change: ");
        HSS_Debug_Highlight(HSS_DEBUG_LOG_STATE_TRANSITION); \
        for (int i = HSS_HART_U54_1; i < HSS_HART_NUM_PEERS; i++) {
            mHSS_DEBUG_PRINTF_EX(" [%s]", HSS_U54_GetStateName(HSS_U54_GetState_Ex(i)));
        }
        HSS_Debug_Highlight(HSS_DEBUG_LOG_NORMAL);
        mHSS_DEBUG_PRINTF_EX("\n");

        __atomic_store_n(&reportingFlag, 0, __ATOMIC_RELAXED);
    }
}

void HSS_U54_DumpStates(void)
{
    for (int i = HSS_HART_U54_1; i < HSS_HART_NUM_PEERS; i++) {
        mHSS_DEBUG_PRINTF(LOG_NORMAL, "u54_%d :: [%s]\n", i, HSS_U54_GetStateName(HSS_U54_GetState_Ex(i)));
    }
}
