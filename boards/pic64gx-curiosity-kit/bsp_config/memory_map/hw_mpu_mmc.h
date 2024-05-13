/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_MPU_MMC_H_
#define HW_MPU_MMC_H_

#if !defined (BSP_SETTING_MMC_MPU_CFG_PMP0)
/*mpu setup register, 64 bits */
#define BSP_SETTING_MMC_MPU_CFG_PMP0    0x1F00000FFFFFFFFFULL
    /* PMP                               [0:38]  RW value= 0xFFFFFFFFF */
    /* RESERVED                          [38:18] RW value= 0x0 */
    /* MODE                              [56:8]  RW value= 0x1F */
#endif
#if !defined (BSP_SETTING_MMC_MPU_CFG_PMP1)
/*mpu setup register, 64 bits */
#define BSP_SETTING_MMC_MPU_CFG_PMP1    0x1F00000FFFFFFFFFULL
    /* PMP                               [0:38]  RW value= 0xFFFFFFFFF */
    /* RESERVED                          [38:18] RW value= 0x0 */
    /* MODE                              [56:8]  RW value= 0x1F */
#endif
#if !defined (BSP_SETTING_MMC_MPU_CFG_PMP2)
/*pmp setup register, 64 bits */
#define BSP_SETTING_MMC_MPU_CFG_PMP2    0x1F00000FFFFFFFFFULL
    /* PMP                               [0:38]  RW value= 0xFFFFFFFFF */
    /* RESERVED                          [38:18] RW value= 0x0 */
    /* MODE                              [56:8]  RW value= 0x1F */
#endif
#if !defined (BSP_SETTING_MMC_MPU_CFG_PMP3)
/*pmp setup register, 64 bits */
#define BSP_SETTING_MMC_MPU_CFG_PMP3    0x1F00000FFFFFFFFFULL
    /* PMP                               [0:38]  RW value= 0xFFFFFFFFF */
    /* RESERVED                          [38:18] RW value= 0x0 */
    /* MODE                              [56:8]  RW value= 0x1F */
#endif

#endif /* #ifdef HW_MPU_MMC_H_ */

