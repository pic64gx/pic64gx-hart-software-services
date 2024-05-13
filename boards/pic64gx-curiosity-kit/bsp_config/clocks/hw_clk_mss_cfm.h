/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_CLK_MSS_CFM_H_
#define HW_CLK_MSS_CFM_H_

#if !defined (BSP_SETTING_MSS_BCLKMUX)
/*Input mux selections */
#define BSP_SETTING_MSS_BCLKMUX    0x00000208UL
    /* BCLK0_SEL                         [0:5]   RW value= 0x8 */
    /* BCLK1_SEL                         [5:5]   RW value= 0x10 */
    /* BCLK2_SEL                         [10:5]  RW value= 0x0 */
    /* BCLK3_SEL                         [15:5]  RW value= 0x0 */
    /* BCLK4_SEL                         [20:5]  RW value= 0x0 */
    /* BCLK5_SEL                         [25:5]  RW value= 0x0 */
    /* RESERVED                          [30:2]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_MSS_PLL_CKMUX)
/*Input mux selections */
#define BSP_SETTING_MSS_PLL_CKMUX    0x00000155UL
    /* CLK_IN_MAC_TSU_SEL                [0:2]   RW value= 0x1 */
    /* PLL0_RFCLK0_SEL                   [2:2]   RW value= 0x1 */
    /* PLL0_RFCLK1_SEL                   [4:2]   RW value= 0x1 */
    /* PLL1_RFCLK0_SEL                   [6:2]   RW value= 0x1 */
    /* PLL1_RFCLK1_SEL                   [8:2]   RW value= 0x1 */
    /* PLL1_FDR_SEL                      [10:5]  RW value= 0x0 */
    /* RESERVED                          [15:17] RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_MSS_MSSCLKMUX)
/*MSS Clock mux selections */
#define BSP_SETTING_MSS_MSSCLKMUX    0x00000003UL
    /* MSSCLK_MUX_SEL                    [0:2]   RW value= 0x3 */
    /* MSSCLK_MUX_MD                     [2:2]   RW value= 0x0 */
    /* CLK_STANDBY_SEL                   [4:1]   RW value= 0x0 */
    /* RESERVED                          [5:27]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_MSS_SPARE0)
/*spare logic */
#define BSP_SETTING_MSS_SPARE0    0x00000000UL
    /* SPARE0                            [0:32]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_MSS_FMETER_ADDR)
/*Frequency_meter_address_selections */
#define BSP_SETTING_MSS_FMETER_ADDR    0x00000000UL
    /* ADDR10                            [0:2]   RSVD */
    /* ADDR                              [2:4]   RW value= 0x0 */
    /* RESERVE18                         [6:26]  RSVD */
#endif
#if !defined (BSP_SETTING_MSS_FMETER_DATAW)
/*Frequency_meter_data_write */
#define BSP_SETTING_MSS_FMETER_DATAW    0x00000000UL
    /* DATA                              [0:24]  RW value= 0x0 */
    /* STROBE                            [24:1]  W1P */
    /* RESERVE19                         [25:7]  RSVD */
#endif
#if !defined (BSP_SETTING_MSS_FMETER_DATAR)
/*Frequency_meter_data_read */
#define BSP_SETTING_MSS_FMETER_DATAR    0x00000000UL
    /* DATA                              [0:24]  RO */
    /* RESERVE20                         [24:8]  RSVD */
#endif
#if !defined (BSP_SETTING_MSS_IMIRROR_TRIM)
/*Imirror TRIM Bits */
#define BSP_SETTING_MSS_IMIRROR_TRIM    0x00000000UL
    /* BG_CODE                           [0:3]   RW value= 0x0 */
    /* CC_CODE                           [3:8]   RW value= 0x0 */
    /* RESERVE21                         [11:21] RSVD */
#endif
#if !defined (BSP_SETTING_MSS_TEST_CTRL)
/*Test MUX Controls */
#define BSP_SETTING_MSS_TEST_CTRL    0x00000000UL
    /* OSC_ENABLE                        [0:4]   RW value= 0x0 */
    /* ATEST_EN                          [4:1]   RW value= 0x0 */
    /* ATEST_SEL                         [5:5]   RW value= 0x0 */
    /* DTEST_EN                          [10:1]  RW value= 0x0 */
    /* DTEST_SEL                         [11:5]  RW value= 0x0 */
    /* RESERVE22                         [16:16] RSVD */
#endif

#endif /* #ifdef HW_CLK_MSS_CFM_H_ */

