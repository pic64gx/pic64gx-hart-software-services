/*******************************************************************************
 * Copyright 2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file Reboot Handling
 * \brief Handling of reboot requests
 */
#include "config.h"
#include "hss_types.h"
#include "hss_state_machine.h"
#include "hss_debug.h"
#include "hss_clock.h"

#include <assert.h>

#include "hss_boot_service.h"
#include "opensbi_service.h"
#include "reboot_service.h"
#include "wdog_service.h"
#include "csr_helper.h"

#include "sbi/riscv_encoding.h"
#include "sbi/sbi_ecall_interface.h"

#include "coreplex_watchdog.h"
#include "mss_sysreg.h"
#include "mss_sys_services.h"

static void __attribute__((__noreturn__, unused)) do_srst_ecall(void)
{
    register uintptr_t a7 asm ("a7") = SBI_EXT_SRST;
    register uintptr_t a6 asm ("a6") = SBI_EXT_SRST_RESET;
    register uintptr_t a0 asm ("a0") = SBI_SRST_RESET_TYPE_WARM_REBOOT;
    register uintptr_t a1 asm ("a1") = SBI_SRST_RESET_REASON_NONE;
    asm volatile ("ecall" : "+r" (a0), "+r" (a1) : "r" (a6), "r" (a7) : "memory");

    csr_write(CSR_MIE, MIP_MSIP);
    while (1) { asm("wfi"); }
}

static void HSS_reboot_cold_all(void)
{
    SYSREG->MSS_RESET_CR = 0xDEAD;
}

void HSS_reboot_cold(enum HSSHartId target)
{
    switch (target) {
    case HSS_HART_E51:
        MSS_WD_force_reset(MSS_WDOG0_LO);
        break;

    case HSS_HART_U54_1:
        MSS_WD_force_reset(MSS_WDOG1_LO);
        break;

    case HSS_HART_U54_2:
        MSS_WD_force_reset(MSS_WDOG2_LO);
        break;

    case HSS_HART_U54_3:
        MSS_WD_force_reset(MSS_WDOG3_LO);
        break;

    case HSS_HART_U54_4:
        MSS_WD_force_reset(MSS_WDOG4_LO);
        break;

    case HSS_HART_ALL:
        HSS_reboot_cold_all();

        while (1) { ; }

        break;

    default:
        assert(1 == 0); // should never reach here!! LCOV_EXCL_LINE
        break;
    }
}

void HSS_reboot(uint32_t wdog_status)
{
    uint32_t restart_mask = 0u;

    if (IS_ENABLED(CONFIG_ALLOW_COLDREBOOT_ALWAYS))
        HSS_reboot_cold(HSS_HART_ALL);

    // watchdog timer has triggered for a monitored hart.
    // ensure OpenSBI housekeeping is in order for requesting reboots.
    // if any of these harts are allowed permission to force a cold reboot
    // it will happen here also...

    for (enum HSSHartId source = HSS_HART_U54_1; source < HSS_HART_NUM_PEERS; source++) {
        if (!(wdog_status & (1u << source)))
            continue;

        mHSS_DEBUG_PRINTF(LOG_ERROR, "u54_%d: Watchdog has fired\n", source);

        if (IS_ENABLED(CONFIG_ALLOW_COLDREBOOT) && pic64gx_is_cold_reboot_allowed(source)) {
            HSS_reboot_cold(HSS_HART_ALL);
        }

        // a cold reboot is not possible, treat it as a warm reboot now
        // potentially add a check for pic64gx_is_warm_reboot_allowed(source) here
        restart_mask |= (1 << source);

        for (enum HSSHartId peer = HSS_HART_U54_1; peer < HSS_HART_NUM_PEERS; peer++) {
            if (peer == source)
                continue;

            if (pic64gx_are_harts_in_same_domain(peer, source)) {
                restart_mask |= (1 << peer);
            }
        }
    }

    // if we reached here, nobody triggered a cold reboot, so
    // now trigger warm restarts as needed...
    if (restart_mask) {
        mHSS_DEBUG_PRINTF(LOG_NORMAL, "reboot: Watchdog triggering reboot of ");
        for (enum HSSHartId peer = HSS_HART_U54_1; peer < HSS_HART_NUM_PEERS; peer++) {
            if (!(restart_mask & (1u << peer)))
                    continue;

            mHSS_DEBUG_PRINTF_EX("[u54_%d] ", peer);

#if         IS_ENABLED(CONFIG_SERVICE_BOOT)
                // Restart core using SRST mechanism
                IPI_Send(peer, IPI_MSG_GOTO, 0u, PRV_M, do_srst_ecall, NULL);
                HSS_Wdog_Init_Time(peer);
                HSS_SpinDelay_MilliSecs(50u);
#else
                mHSS_DEBUG_PRINTF(LOG_ERROR,
                                  "reboot: warm reboot requested without SERVICE_BOOT enabled\n");
                assert(1 == 0);
#endif
        }
        mHSS_DEBUG_PUTS("\n");

    }
}
