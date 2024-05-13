/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_DDR_MODE_H_
#define HW_DDR_MODE_H_

#if !defined (BSP_SETTING_DDRPHY_MODE)
/*DDRPHY MODE (binary)- 000 ddr3, 001 ddr33L, 010 ddr4, 011 LPDDR3, 100 LPDDR4,
111 OFF_MODE */
#define BSP_SETTING_DDRPHY_MODE    0x00002102UL
    /* DDRMODE                           [0:3]   RW value= 0x2 */
    /* ECC                               [3:1]   RW value= 0x0 */
    /* CRC                               [4:1]   RW value= 0x0 */
    /* BUS_WIDTH                         [5:3]   RW value= 0x0 */
    /* DMI_DBI                           [8:1]   RW value= 0x1 */
    /* DQ_DRIVE                          [9:2]   RW value= 0x0 */
    /* DQS_DRIVE                         [11:2]  RW value= 0x0 */
    /* ADD_CMD_DRIVE                     [13:2]  RW value= 0x1 */
    /* CLOCK_OUT_DRIVE                   [15:2]  RW value= 0x0 */
    /* DQ_TERMINATION                    [17:2]  RW value= 0x0 */
    /* DQS_TERMINATION                   [19:2]  RW value= 0x0 */
    /* ADD_CMD_INPUT_PIN_TERMINATION     [21:2]  RW value= 0x0 */
    /* PRESET_ODT_CLK                    [23:2]  RW value= 0x0 */
    /* POWER_DOWN                        [25:1]  RW value= 0x0 */
    /* RANK                              [26:1]  RW value= 0x0 */
    /* RESERVED                          [27:5]  RSVD */
#endif
#if !defined (BSP_SETTING_DATA_LANES_USED)
/*number of lanes used for data- does not include ECC, infer from mode register
*/
#define BSP_SETTING_DATA_LANES_USED    0x00000002UL
    /* DATA_LANES                        [0:3]   RW value= 0x2 */
#endif

#endif /* #ifdef HW_DDR_MODE_H_ */

