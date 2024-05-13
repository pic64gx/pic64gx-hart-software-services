/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HAL Embedded Software
 *
 */

/*******************************************************************************
 * @file mss_hal.h
 * @author Microchip Technology Inc
 * @brief PIC64GX HAL include file. This is the file intended for application to
 * include so that all the other PIC64GX files are then accessible to it.
 *
 */

#ifndef MSS_HAL_H
#define MSS_HAL_H

#ifndef CONFIG_OPENSBI
#  include <stddef.h>  // for size_t
#  include <stdbool.h> // for bool, true, false
#  include <stdint.h>
#ifndef ssize_t
typedef long            ssize_t;
#endif
#endif

#include "common/mss_assert.h"
#include "common/mss_legacy_defines.h"
#include "common/mss_beu_def.h"
#include "common/nwc/mss_ddr_defs.h"
#include "common/nwc/mss_ddr_sgmii_regs.h"
#include "common/nwc/mss_io_config.h"
#include "common/nwc/mss_pll.h"
#include "common/nwc/mss_scb_nwc_regs.h"
#include "common/nwc/mss_scb_nwc_regs.h"
/*
 */
#include "pic64gx_hal_config/coreplex_sw_config.h"
#include "common/atomic.h"
#include "common/bits.h"
#include "common/encoding.h"
#include "bsp_config/bsp_config.h"
#include "common/nwc/mss_ddr.h"
#include "common/mss_clint.h"
#include "common/mss_h2f.h"
#include "common/mss_hart_ints.h"
#include "common/mss_beu.h"
#include "common/mss_mpu.h"
#include "common/mss_pmp.h"
#include "common/mss_plic.h"
#include "common/mss_seg.h"
#include "common/mss_sysreg.h"
#include "common/mss_util.h"
#include "common/mss_mtrap.h"
#include "common/mss_l2_cache.h"
#include "common/mss_axiswitch.h"
#include "common/mss_peripherals.h"
#include "common/nwc/mss_cfm.h"
#include "common/nwc/mss_ddr.h"
#include "common/nwc/mss_sgmii.h"
#include "startup_gcc/system_startup.h"
#include "common/nwc/mss_ddr_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* MSS_HAL_H */
