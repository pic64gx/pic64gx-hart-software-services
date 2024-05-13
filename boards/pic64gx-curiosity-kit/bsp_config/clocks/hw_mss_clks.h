/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_MSS_CLKS_H_
#define HW_MSS_CLKS_H_

#if !defined (BSP_SETTING_MSS_CLKS_VERSION)
/*This version incrments when change to format of this file */
#define BSP_SETTING_MSS_CLKS_VERSION    1
    /* VERSION                           [0:32]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_MSS_EXT_SGMII_REF_CLK)
/*Ref Clock rate in Hz */
#define BSP_SETTING_MSS_EXT_SGMII_REF_CLK    125000000
    /* MSS_EXT_SGMII_REF_CLK             [0:32]  RW value= 125000000 */
#endif
#if !defined (BSP_SETTING_MSS_COREPLEX_CPU_CLK)
/*CPU Clock rate in Hz */
#define BSP_SETTING_MSS_COREPLEX_CPU_CLK    600000000
    /* MSS_COREPLEX_CPU_CLK              [0:32]  RW value= 600000000 */
#endif
#if !defined (BSP_SETTING_MSS_SYSTEM_CLK)
/*System Clock rate in Hz static power. */
#define BSP_SETTING_MSS_SYSTEM_CLK    600000000
    /* MSS_SYSTEM_CLK                    [0:32]  RW value= 600000000 */
#endif
#if !defined (BSP_SETTING_MSS_RTC_TOGGLE_CLK)
/*RTC toggle Clock rate in Hz static power. */
#define BSP_SETTING_MSS_RTC_TOGGLE_CLK    1000000
    /* MSS_RTC_TOGGLE_CLK                [0:32]  RW value= 1000000 */
#endif
#if !defined (BSP_SETTING_MSS_AXI_CLK)
/*AXI Clock rate in Hz static power. */
#define BSP_SETTING_MSS_AXI_CLK    300000000
    /* MSS_AXI_CLK                       [0:32]  RW value= 300000000 */
#endif
#if !defined (BSP_SETTING_MSS_APB_AHB_CLK)
/*AXI Clock rate in Hz static power. */
#define BSP_SETTING_MSS_APB_AHB_CLK    150000000
    /* MSS_APB_AHB_CLK                   [0:32]  RW value= 150000000 */
#endif
#if !defined (BSP_SETTING_DDR_CLK)
/*DDR clock rate in Hz (clk rate x 2) */
#define BSP_SETTING_DDR_CLK    1600000000
    /* DDR_CLK                           [0:32]  RW value= 1600000000 */
#endif

#endif /* #ifdef HW_MSS_CLKS_H_ */

