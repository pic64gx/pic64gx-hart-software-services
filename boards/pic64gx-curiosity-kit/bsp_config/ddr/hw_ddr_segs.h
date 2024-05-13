/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_DDR_SEGS_H_
#define HW_DDR_SEGS_H_

#if !defined (BSP_SETTING_SEG0_0)
/*Cached access at 0x00_8000_0000 (-0x80+0x00) */
#define BSP_SETTING_SEG0_0    0x80007F80UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x7F80 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG0_1)
/*Cached access at 0x10_0000_000 */
#define BSP_SETTING_SEG0_1    0x80007000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x7000 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG0_2)
/*not used */
#define BSP_SETTING_SEG0_2    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG0_3)
/*not used */
#define BSP_SETTING_SEG0_3    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG0_4)
/*not used */
#define BSP_SETTING_SEG0_4    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG0_5)
/*not used */
#define BSP_SETTING_SEG0_5    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:6]  RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG0_6)
/*not used */
#define BSP_SETTING_SEG0_6    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG0_7)
/*not used */
#define BSP_SETTING_SEG0_7    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG1_0)
/*not used */
#define BSP_SETTING_SEG1_0    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG1_1)
/*not used */
#define BSP_SETTING_SEG1_1    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG1_2)
/*Non-Cached access at 0x00_c000_0000 */
#define BSP_SETTING_SEG1_2    0x80007F40UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x7F40 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG1_3)
/*Non-Cached access at 0x14_0000_0000 */
#define BSP_SETTING_SEG1_3    0x80006C00UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x6C00 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG1_4)
/*Non-Cached WCB access at 0x00_d000_0000 */
#define BSP_SETTING_SEG1_4    0x80007F30UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x7F30 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG1_5)
/*Non-Cached WCB 0x18_0000_0000 */
#define BSP_SETTING_SEG1_5    0x80006800UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x6800 */
    /* RESERVED                          [15:6]  RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_SEG1_6)
/*Trace - Trace not in use here so can be left as 0 */
#define BSP_SETTING_SEG1_6    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_SEG1_7)
/*not used */
#define BSP_SETTING_SEG1_7    0x00000000UL
    /* ADDRESS_OFFSET                    [0:15]  RW value= 0x0 */
    /* RESERVED                          [15:16] RW value= 0x0 */
    /* LOCKED                            [31:1]  RW value= 0x0 */
#endif

#endif /* #ifdef HW_DDR_SEGS_H_ */

