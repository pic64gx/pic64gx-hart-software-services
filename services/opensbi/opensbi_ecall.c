/*******************************************************************************
 * Copyright 2019-2021 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX Embedded Software
 *
 */


#include "config.h"
#include "hss_types.h"

#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>


#include "opensbi_service.h"
#include "opensbi_ecall.h"

#if !IS_ENABLED(CONFIG_OPENSBI)
#  error OPENSBI needed for this module
#endif

#if IS_ENABLED(CONFIG_USE_IHC) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_IPC)
#  include "miv_ihc.h"
#  include "opensbi_ipc_ecall.h"
#endif

#if IS_ENABLED(CONFIG_USE_IHC) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_RPROC)
#  include "opensbi_rproc_ecall.h"
#endif

#if IS_ENABLED(CONFIG_USE_USER_CRYPTO) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_CRYPTO)
#  include "opensbi_crypto_ecall.h"
#endif

#include "opensbi_suspend_ecall.h"

#include "hss_boot_service.h"

int HSS_SBI_ECALL_Handler(long extid, long funcid,
    const struct sbi_trap_regs *regs, unsigned long *out_val, struct sbi_trap_info *out_trap)
{
    int result = SBI_ERR_FAILED;

    switch (funcid) {
        //
        // IPC Functions
        case SBI_EXT_IPC_PROBE:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_IPC_CH_INIT:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_IPC_SEND:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_IPC_RECEIVE:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_IPC_STATUS:
#if IS_ENABLED(CONFIG_USE_IHC) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_IPC)
            result = sbi_ecall_ipc_handler(extid, funcid, regs, out_val, out_trap);
#endif
            break;

        //
        // RemoteProc
        case SBI_EXT_RPROC_STATE:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_RPROC_START:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_RPROC_STOP:
#if IS_ENABLED(CONFIG_USE_IHC) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_RPROC)
            result = sbi_ecall_rproc_handler(extid, funcid, regs, out_val, out_trap);
#endif
            break;

#if IS_ENABLED(CONFIG_USE_USER_CRYPTO) && IS_ENABLED(CONFIG_SERVICE_OPENSBI_CRYPTO)
        //
        // User Crypto
        case SBI_EXT_CRYPTO_INIT:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_CRYPTO_SERVICES_PROBE:
            __attribute__((fallthrough)); // deliberate fallthrough
        case SBI_EXT_CRYPTO_SERVICES:
            result = sbi_ecall_crypto_handler(extid, funcid, regs, out_val, out_trap);
            break;
#endif

        //
        // HSS functions
        case SBI_EXT_HSS_REBOOT:
            result = HSS_OpenSBI_Reboot();
            break;

        //
        default:
            result = SBI_ENOTSUPP;
    };

    return result;
}

int HSS_SBI_Vendor_Ext_Check(long extid)
{
    return (SBI_EXT_MICROCHIP_TECHNOLOGY == extid);
}
