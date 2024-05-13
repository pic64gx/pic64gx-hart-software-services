/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_HSIO_MUX_H_
#define HW_HSIO_MUX_H_

#if !defined (BSP_SETTING_TRIM_OPTIONS)
/*User trim options- set option to 1 to use */
#define BSP_SETTING_TRIM_OPTIONS    0x00000000UL
    /* TRIM_DDR_OPTION                   [0:1]    */
    /* TRIM_SGMII_OPTION                 [1:1]    */
#endif
#if !defined (BSP_SETTING_DDR_IOC_REG0)
/*Manual trim values */
#define BSP_SETTING_DDR_IOC_REG0    0x00000000UL
    /* BANK_PCODE                        [0:6]   RW value= 0x0 */
    /* BANK_NCODE                        [6:6]   RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SGMII_IOC_REG0)
/*Manual trim values */
#define BSP_SETTING_SGMII_IOC_REG0    0x00000000UL
    /* BANK_PCODE                        [0:6]   RW value= 0x0 */
    /* BANK_NCODE                        [6:6]   RW value= 0x0 */
#endif

#endif /* #ifdef HW_HSIO_MUX_H_ */

