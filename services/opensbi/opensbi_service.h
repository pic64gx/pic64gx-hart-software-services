#ifndef HSS_OPENSBI_SERVICE_H
#define HSS_OPENSBI_SERVICE_H

/*******************************************************************************
 * Copyright 2019-2021 Microchip Technology Inc.
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
 * Hart Software Services - OpenSBI API Handler
 *
 */

/*!
 * \file Virtual OPENSBI API
 * \brief OPENSBI Driver State Machine API function declarations
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ssmb_ipi.h"
#include "hss_state_machine.h"
#include "hss_debug.h"

enum IPIStatusCode HSS_OpenSBI_IPIHandler(TxId_t transaction_id, enum HSSHartId source,
    uint32_t immediate_arg, void *p_extended_buffer_in_ddr, void *p_ancilliary_buffer_in_ddr);
void HSS_OpenSBI_Setup(void);
void HSS_OpenSBI_Reboot(void);

void pic64gx_domains_register_hart(int hartid, int boot_hartid);
void pic64gx_domains_deregister_hart(int hartid);

void pic64gx_domains_register_boot_hart(char *pName, u32 hartMask, int boot_hartid,
    u32 privMode, void * entryPoint, void * pArg1, bool allow_cold_reboot, bool allow_warm_reboot);
void pic64gx_mark_hart_as_booted(int hartid);
bool pic64gx_is_last_hart_ready(void);
bool pic64gx_is_hart_using_opensbi(int hartid);
bool pic64gx_are_harts_in_same_domain(int hartid1, int hartid2);
bool pic64gx_is_cold_reboot_allowed(int hartid);
bool pic64gx_is_warm_reboot_allowed(int hartid);
void pic64gx_uart_surrender(void);

extern struct StateMachine opensbi_service;

#ifdef __cplusplus
}
#endif

#endif
