/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_MEMORY_H_
#define HW_MEMORY_H_

#if !defined (BSP_SETTING_RESET_VECTOR_HART0)
/*Reset vector hart0 */
#define BSP_SETTING_RESET_VECTOR_HART0    0x20220000
#define BSP_SETTING_RESET_VECTOR_HART0_SIZE    0x4    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESET_VECTOR_HART1)
/*Reset vector hart1 */
#define BSP_SETTING_RESET_VECTOR_HART1    0x20220000
#define BSP_SETTING_RESET_VECTOR_HART1_SIZE    0x4    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESET_VECTOR_HART2)
/*Reset vector hart2 */
#define BSP_SETTING_RESET_VECTOR_HART2    0x20220000
#define BSP_SETTING_RESET_VECTOR_HART2_SIZE    0x4    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESET_VECTOR_HART3)
/*Reset vector hart3 */
#define BSP_SETTING_RESET_VECTOR_HART3    0x20220000
#define BSP_SETTING_RESET_VECTOR_HART3_SIZE    0x4    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESET_VECTOR_HART4)
/*Reset vector hart4 */
#define BSP_SETTING_RESET_VECTOR_HART4    0x20220000
#define BSP_SETTING_RESET_VECTOR_HART4_SIZE    0x4    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_32_CACHE)
/*example instance of memory */
#define BSP_SETTING_DDR_32_CACHE    0x80000000
#define BSP_SETTING_DDR_32_CACHE_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_32_NON_CACHE)
/*example instance */
#define BSP_SETTING_DDR_32_NON_CACHE    0xC0000000
#define BSP_SETTING_DDR_32_NON_CACHE_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_64_CACHE)
/*64 bit address  */
#define BSP_SETTING_DDR_64_CACHE    0x1000000000
#define BSP_SETTING_DDR_64_CACHE_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_64_NON_CACHE)
/*64 bit address  */
#define BSP_SETTING_DDR_64_NON_CACHE    0x1400000000
#define BSP_SETTING_DDR_64_NON_CACHE_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_32_WCB)
/*example instance */
#define BSP_SETTING_DDR_32_WCB    0xD0000000
#define BSP_SETTING_DDR_32_WCB_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_DDR_64_WCB)
/*64 bit address  */
#define BSP_SETTING_DDR_64_WCB    0x1800000000
#define BSP_SETTING_DDR_64_WCB_SIZE    0x100000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESERVED_SNVM)
/*Offset and size of reserved sNVM. (Not available to MSS) */
#define BSP_SETTING_RESERVED_SNVM    0x00000000
#define BSP_SETTING_RESERVED_SNVM_SIZE    0x00000000    /* Length of memory block*/
#endif
#if !defined (BSP_SETTING_RESERVED_ENVM)
/*Offset and size of reserved eNVM  (Not available to MSS) */
#define BSP_SETTING_RESERVED_ENVM    0x00000000
#define BSP_SETTING_RESERVED_ENVM_SIZE    0x00000000    /* Length of memory block*/
#endif

#endif /* #ifdef HW_MEMORY_H_ */

