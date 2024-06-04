#ifndef HSS_WDOG_SERVICE_H
#define HSS_WDOG_SERVICE_H

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
 * Hart Software Services - Virtual Watchdog Service
 *
 */


/*!
 * \file Watchdog Driver State Machine
 * \brief Virtualised Watchdog Service
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "hss_state_machine.h"
#include "hss_debug.h"
#include "ssmb_ipi.h"
#include "mpfs_reg_map.h"

void HSS_Wdog_MonitorHart(enum HSSHartId target);
void HSS_Wdog_DumpStats(void);
void HSS_Wdog_Init_Time(enum HSSHartId hart_id);
void HSS_Wdog_E51_Tickle(void);


extern struct StateMachine wdog_service;

#ifdef __cplusplus
}
#endif

#endif
