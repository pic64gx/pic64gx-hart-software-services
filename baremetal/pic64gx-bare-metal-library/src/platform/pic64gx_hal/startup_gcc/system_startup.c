/******************************************************************************************
 * Copyright 2019-2023 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/***************************************************************************
 * @file system_startup.c
 * @author Microchip Technology Inc
 * @brief first C code called on startup. Will call user code created outside
 * the HAL.
 */
#include <stddef.h>
#include <stdbool.h>
#include "pic64gx_hal/mss_hal.h"
#ifdef  MPFS_HAL_HW_CONFIG
#include "../common/nwc/mss_nwc_init.h"
#endif
#include "system_startup_defs.h"


 /*-----------------------------------------------------------------------------
  * _start() function called invoked
  * This function is called on power up and warm reset.
  */
 __attribute__((weak)) void init_memory(void)
 {
    copy_section(&__text_load, &__text_start, &__text_end);
    copy_section(&__sdata_load, &__sdata_start, &__sdata_end);
    copy_section(&__data_load, &__data_start, &__data_end);

    zero_section(&__sbss_start, &__sbss_end);
    zero_section(&__bss_start, &__bss_end);

    __disable_all_irqs();      /* disables local and global interrupt enable */
 }

 /*-----------------------------------------------------------------------------
   * _start() function called invoked
   * This function is called on power up and warm reset.
   */
  __attribute__((weak)) void init_ddr(void)
  {
    if ((LIBERO_SETTING_DDRPHY_MODE & DDRPHY_MODE_MASK) != DDR_OFF_MODE) {
#ifdef DDR_SUPPORT
        uint64_t end_address;

#if 0 /* enable to init cache to zero using 64 bit writes */
        end_address = LIBERO_SETTING_DDR_64_NON_CACHE + LIBERO_SETTING_CFG_AXI_END_ADDRESS_AXI2_0 + LIBERO_SETTING_CFG_AXI_END_ADDRESS_AXI2_1;
        zero_section((uint64_t *)LIBERO_SETTING_DDR_64_NON_CACHE, (uint64_t *)end_address);
#endif

        end_address = LIBERO_SETTING_DDR_64_CACHE + LIBERO_SETTING_CFG_AXI_END_ADDRESS_AXI1_0 + LIBERO_SETTING_CFG_AXI_END_ADDRESS_AXI1_1;
        zero_section((uint64_t *)LIBERO_SETTING_DDR_64_CACHE, (uint64_t *)end_address);
#endif
    }
  }

/**
 * init_mem_protection_unit(void)
 * add this function to you code and configure as required
 * @return
 */
__attribute__((weak)) uint8_t init_mem_protection_unit(void)
{
    mpu_configure();
    return (0U);
}

/**
 * init_pmp(void)
 * add this function to you code and configure as required
 * @return
 */
__attribute__((weak)) uint8_t init_pmp(uint8_t hart_id)
{
    pmp_configure(hart_id);
    return (0U);
}


