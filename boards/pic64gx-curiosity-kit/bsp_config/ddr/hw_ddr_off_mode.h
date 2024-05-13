/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_DDR_OFF_MODE_H_
#define HW_DDR_OFF_MODE_H_

#if !defined (BSP_SETTING_DDRPHY_MODE_OFF)
/*DDRPHY MODE Register, ddr off */
#define BSP_SETTING_DDRPHY_MODE_OFF    0x00000000UL
    /* DDRMODE                           [0:3]   RW value= 0x0 */
    /* ECC                               [3:1]   RW value= 0x0 */
    /* CRC                               [4:1]   RW value= 0x0 */
    /* BUS_WIDTH                         [5:3]   RW value= 0x0 */
    /* DMI_DBI                           [8:1]   RW value= 0x0 */
    /* DQ_DRIVE                          [9:2]   RW value= 0x0 */
    /* DQS_DRIVE                         [11:2]  RW value= 0x0 */
    /* ADD_CMD_DRIVE                     [13:2]  RW value= 0x0 */
    /* CLOCK_OUT_DRIVE                   [15:2]  RW value= 0x0 */
    /* DQ_TERMINATION                    [17:2]  RW value= 0x0 */
    /* DQS_TERMINATION                   [19:2]  RW value= 0x0 */
    /* ADD_CMD_INPUT_PIN_TERMINATION     [21:2]  RW value= 0x0 */
    /* PRESET_ODT_CLK                    [23:2]  RW value= 0x0 */
    /* POWER_DOWN                        [25:1]  RW value= 0x0 */
    /* RANK                              [26:1]  RW value= 0x0 */
    /* RESERVED                          [27:5]  RSVD */
#endif
#if !defined (BSP_SETTING_DPC_BITS_OFF_MODE)
/*DPC Bits Register off mode */
#define BSP_SETTING_DPC_BITS_OFF_MODE    0x00000000UL
    /* DPC_VS                            [0:4]   RW value= 0x0 */
    /* DPC_VRGEN_H                       [4:6]   RW value= 0x0 */
    /* DPC_VRGEN_EN_H                    [10:1]  RW value= 0x0 */
    /* DPC_MOVE_EN_H                     [11:1]  RW value= 0x0 */
    /* DPC_VRGEN_V                       [12:6]  RW value= 0x0 */
    /* DPC_VRGEN_EN_V                    [18:1]  RW value= 0x0 */
    /* DPC_MOVE_EN_V                     [19:1]  RW value= 0x0 */
    /* RESERVE01                         [20:12] RSVD */
#endif

#endif /* #ifdef HW_DDR_OFF_MODE_H_ */

