/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_PMP_HART0_H_
#define HW_PMP_HART0_H_

#if !defined (BSP_SETTING_HART0_CSR_PMPCFG0)
/*PMP configuration for 8 adress regions, bit 0 read, bit 1 write, bit 2
execute, bit 7 disable, bits 3,4 address format (0x18 => NAPOT) */
#define BSP_SETTING_HART0_CSR_PMPCFG0    0x0000000000000000ULL
    /* PMP0CFG                           [0:8]   RW value= 0x00 */
    /* PMP1CFG                           [8:8]   RW value= 0x0 */
    /* PMP2CFG                           [16:8]  RW value= 0x00 */
    /* PMP3CFG                           [24:8]  RW value= 0x00 */
    /* PMP4CFG                           [32:8]  RW value= 0x00 */
    /* PMP5CFG                           [40:8]  RW value= 0x00 */
    /* PMP6CFG                           [48:8]  RW value= 0x00 */
    /* PMP7CFG                           [56:8]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPCFG2)
/*PMP configuration for 8 address regions, bit 0 read, bit 1 write, bit 2
execute, bit 7 disable, bits 3,4 address format (0x18 => NAPOT) */
#define BSP_SETTING_HART0_CSR_PMPCFG2    0x0000000000000000ULL
    /* PMP8CFG                           [0:8]   RW value= 0x00 */
    /* PMP9CFG                           [8:8]   RW value= 0x00 */
    /* PMP10CFG                          [16:8]  RW value= 0x00 */
    /* PMP11CFG                          [24:8]  RW value= 0x00 */
    /* PMP12CFG                          [32:8]  RW value= 0x00 */
    /* PMP13CFG                          [40:8]  RW value= 0x00 */
    /* PMP14CFG                          [48:8]  RW value= 0x00 */
    /* PMP15CFG                          [56:8]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR0)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR0    0x0000000000000000ULL
    /* CSR_PMPADDR0                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR1)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR1    0x0000000000000000ULL
    /* CSR_PMPADDR1                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR2)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR2    0x0000000000000000ULL
    /* CSR_PMPADDR2                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR3)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR3    0x0000000000000000ULL
    /* CSR_PMPADDR3                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR4)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR4    0x0000000000000000ULL
    /* CSR_PMPADDR4                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR5)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR5    0x0000000000000000ULL
    /* CSR_PMPADDR5                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR6)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR6    0x0000000000000000ULL
    /* CSR_PMPADDR6                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR7)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR7    0x0000000000000000ULL
    /* CSR_PMPADDR7                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR8)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR8    0x0000000000000000ULL
    /* CSR_PMPADDR8                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR9)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR9    0x0000000000000000ULL
    /* CSR_PMPADDR9                      [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR10)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR10    0x0000000000000000ULL
    /* CSR_PMPADDR10                     [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR11)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR11    0x0000000000000000ULL
    /* CSR_PMPADDR11                     [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR12)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR12    0x0000000000000000ULL
    /* CSR_PMPADDR12                     [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR13)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR13    0x0000000000000000ULL
    /* CSR_PMPADDR13                     [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR14)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR14    0x0000000000000000ULL
    /* CSR_PMPADDR14                     [0:64]  RW value= 0x00 */
#endif
#if !defined (BSP_SETTING_HART0_CSR_PMPADDR15)
/*PMP ADRESS and size, format determined from bit 3 and 4 of configuration byte
in CSR_PMPCFGx */
#define BSP_SETTING_HART0_CSR_PMPADDR15    0x0000000000000000ULL
    /* CSR_PMPADDR15                     [0:64]  RW value= 0x00 */
#endif

#endif /* #ifdef HW_PMP_HART0_H_ */

