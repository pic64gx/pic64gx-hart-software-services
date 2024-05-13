/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_CLK_SGMII_CFM_H_
#define HW_CLK_SGMII_CFM_H_

#if !defined (BSP_SETTING_SGMII_REFCLKMUX)
/*Input mux selections */
#define BSP_SETTING_SGMII_REFCLKMUX    0x00000005UL
    /* PLL0_RFCLK0_SEL                   [0:2]   RW value= 0x1 */
    /* PLL0_RFCLK1_SEL                   [2:2]   RW value= 0x1 */
    /* RESERVED                          [4:28]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SGMII_SGMII_CLKMUX)
/*sgmii clk mux */
#define BSP_SETTING_SGMII_SGMII_CLKMUX    0x00000005UL
    /* SGMII_CLKMUX                      [0:32]  RW value= 0x5 */
#endif
#if !defined (BSP_SETTING_SGMII_SPARE0)
/*spare logic */
#define BSP_SETTING_SGMII_SPARE0    0x00000000UL
    /* RESERVED                          [0:32]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SGMII_CLK_XCVR)
/*Clock_Receiver */
#define BSP_SETTING_SGMII_CLK_XCVR    0x00002C30UL
    /* EN_UDRIVE_P                       [0:1]   RW value= 0x0 */
    /* EN_INS_HYST_P                     [1:1]   RW value= 0x0 */
    /* EN_TERM_P                         [2:2]   RW value= 0x0 */
    /* EN_RXMODE_P                       [4:2]   RW value= 0x3 */
    /* EN_UDRIVE_N                       [6:1]   RW value= 0x0 */
    /* EN_INS_HYST_N                     [7:1]   RW value= 0x0 */
    /* EN_TERM_N                         [8:2]   RW value= 0x0 */
    /* EN_RXMODE_N                       [10:2]  RW value= 0x3 */
    /* CLKBUF_EN_PULLUP                  [12:1]  RW value= 0x0 */
    /* EN_RDIFF                          [13:1]  RW value= 0x1 */
    /* RESERVED                          [14:18] RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SGMII_TEST_CTRL)
/*Test MUX Controls */
#define BSP_SETTING_SGMII_TEST_CTRL    0x00000000UL
    /* OSC_ENABLE                        [0:4]   RW value= 0x0 */
    /* ATEST_EN                          [4:1]   RW value= 0x0 */
    /* ATEST_SEL                         [5:5]   RW value= 0x0 */
    /* DTEST_EN                          [10:1]  RW value= 0x0 */
    /* DTEST_SEL                         [11:5]  RW value= 0x0 */
    /* RESERVE22                         [16:16] RSVD */
#endif

#endif /* #ifdef HW_CLK_SGMII_CFM_H_ */

