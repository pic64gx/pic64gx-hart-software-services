/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_GEN_PERIPHERALS_H_
#define HW_GEN_PERIPHERALS_H_

#if !defined (BSP_SETTING_GPIO_CR)
/*GPIO Blocks reset control- (soft_reset options chossen in Libero confgurator)
*/
#define BSP_SETTING_GPIO_CR    0x000F0703UL
    /* GPIO0_SOFT_RESET_SELECT           [0:2]   RW value= 0x3 */
    /* GPIO0_DEFAULT                     [4:2]   RW value= 0x0 */
    /* GPIO1_SOFT_RESET_SELECT           [8:3]   RW value= 0x7 */
    /* GPIO1_DEFAULT                     [12:3]  RW value= 0x0 */
    /* GPIO2_SOFT_RESET_SELECT           [16:4]  RW value= 0xF */
    /* GPIO2_DEFAULT                     [20:4]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_CRYPTO_CR_INFO)
/*Information on how Crypto setup on this MPFS */
#define BSP_SETTING_CRYPTO_CR_INFO    0x00000000UL
    /* MSS_MODE                          [0:2]   RO */
    /* RESERVED                          [2:1]   RO */
    /* STREAM_ENABLE                     [3:1]   RO */
    /* RESERVED1                         [4:28]  RO */
#endif
#if !defined (BSP_SETTING_CONFIGURED_PERIPHERALS)
/*MSS peripherals configured in this instance of MSS Configurator generated
output. 1 implies it has been configured, 0 it has not been configured. */
#define BSP_SETTING_CONFIGURED_PERIPHERALS    0x000FFFF9UL
    /* EMMC                              [0:1]   RW value= 0x1 */
    /* SD_SDIO                           [1:1]   RW value= 0x0 */
    /* USB                               [2:1]   RW value= 0x0 */
    /* MAC0                              [3:1]   RW value= 0x1 */
    /* MAC1                              [4:1]   RW value= 0x1 */
    /* QSPI                              [5:1]   RW value= 0x1 */
    /* SPI0                              [6:1]   RW value= 0x1 */
    /* SPI1                              [7:1]   RW value= 0x1 */
    /* MMUART0                           [8:1]   RW value= 0x1 */
    /* MMUART1                           [9:1]   RW value= 0x1 */
    /* MMUART2                           [10:1]  RW value= 0x1 */
    /* MMUART3                           [11:1]  RW value= 0x1 */
    /* MMUART4                           [12:1]  RW value= 0x1 */
    /* I2C0                              [13:1]  RW value= 0x1 */
    /* I2C1                              [14:1]  RW value= 0x1 */
    /* CAN0                              [15:1]  RW value= 0x1 */
    /* CAN1                              [16:1]  RW value= 0x1 */
    /* GPIO0                             [17:1]  RW value= 0x1 */
    /* GPIO1                             [18:1]  RW value= 0x1 */
    /* GPIO2                             [19:1]  RW value= 0x1 */
#endif

#endif /* #ifdef HW_GEN_PERIPHERALS_H_ */

