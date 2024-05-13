/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_NVM_MAP_H_
#define HW_NVM_MAP_H_

#if !defined (BSP_SETTING_SNVM_MSS_START_PAGE)
/*Page offset to start page of sNVM available to MSS. Each SNVM module may be
stored in any of the following formats, Non-authenticated plaintext,
Authenticated plaintext, Authenticated ciphertext. When the data is
authenticated 236 bytes of storage per page is available. When the data is not
authenticated 252 bytes may be stored. (Note: Value in decimal) */
#define BSP_SETTING_SNVM_MSS_START_PAGE    0
    /* START_PAGE_OFFSET                 [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_SNVM_MSS_END_PAGE)
/*Page offset to end page of sNVM available to MSS (Note: Value in decimal) */
#define BSP_SETTING_SNVM_MSS_END_PAGE    220
    /* END_PAGE_OFFSET                   [0:32]  RW value= 220 */
#endif
#if !defined (BSP_SETTING_ENVM_MSS_START_PAGE)
/*Page offset to start page of sNVM available to MSS (Note: Value in decimal)
*/
#define BSP_SETTING_ENVM_MSS_START_PAGE    0
    /* START_PAGE_OFFSET                 [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ENVM_MSS_END_PAGE)
/*Page offset to end page of sNVM available to MSS (Note: Value in decimal) */
#define BSP_SETTING_ENVM_MSS_END_PAGE    511
    /* END_PAGE_OFFSET                   [0:32]  RW value= 511 */
#endif

#endif /* #ifdef HW_NVM_MAP_H_ */

