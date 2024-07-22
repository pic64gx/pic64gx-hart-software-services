/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/**
 * \file Access Local Tick Information
 * \brief Get acccess to tick counts from processor
 */

#include "config.h"
#include "hss_types.h"

#include "hss_debug.h"
#include "hss_clock.h"
#include "csr_helper.h"

/**
 * \brief Get acccess to tick counts from processor
 */

HSSTicks_t HSS_GetTime(void)
{
    HSSTicks_t tickCount;

    tickCount = CSR_GetTime();
    return tickCount;
}

HSSTicks_t HSS_GetTickCount(void)
{
    HSSTicks_t tickCount;

    tickCount = CSR_GetTickCount();
    return tickCount;
}

bool HSS_Timer_IsElapsed(HSSTicks_t startTick, HSSTicks_t durationInTicks)
{
    return (HSS_GetTime() > (startTick + durationInTicks));
}

void HSS_SpinDelay_MilliSecs(uint32_t milliseconds)
{
    HSSTicks_t delayTick = HSS_GetTime();
    while (!HSS_Timer_IsElapsed(delayTick, ONE_MILLISEC * milliseconds)) { ; }
}

void HSS_SpinDelay_Secs(uint32_t seconds)
{
    HSSTicks_t delayTick = HSS_GetTime();
    while (!HSS_Timer_IsElapsed(delayTick, ONE_SEC * seconds)) { ; }
}
