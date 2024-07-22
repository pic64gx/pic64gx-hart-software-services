/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file  System Setup Functions
 * \brief Functions for setting up the PMP, MPU, PLIC, IOMUX, PAD I/O, L2 Cache. Clocks
 *
 * These functions are used by the boot service, but they can be replaced by
 * auto-generated code from an external tool, e.g. Libero.
 *
 * What needs to be implemented are the following functions:
 *     bool HSS_Setup_PLIC(void);
 *     bool HSS_Setup_MPU(void);
 *     bool HSS_Setup_L2Cache(void);
 *     bool HSS_Setup_Clocks(void);
 *     bool HSS_Setup_PMP(void);
 */

#include "config.h"
#include "hss_types.h"

#include "hss_init.h"
#include "hss_debug.h"

#include <assert.h>
#include <string.h>

#include "hss_clock.h"
#include "hss_state_machine.h"

#include "csr_helper.h"

#define RISCV_CSR_ENCODING_H
#define RISCV_ENCODING_H
#include "mss_sysreg.h"
#include "mss_plic.h"
#include "mss_util.h"
#include "mss_mpu.h"
#include "mss_l2_cache.h"
#include "nwc/mss_io_config.h"
#include "system_startup.h"
#include "hss_memcpy_via_pdma.h"

#include "pic64gx_reg_map.h"
#include "hss_sys_setup.h"

#include "mss_beu_def.h"
#include "mss_beu.h"
#include "mss_peripherals.h"

/******************************************************************************/



/****************************************************************************/

//
// Setup Functions
//

/*!
 * \brief PLIC Setup and Configuration
 *
 * The RISC-V Platform-Level Interrupt Controller (PLIC) allows
 * broadcasting of interrupts to one  or more Harts within a Core Complex.
 *
 * The operation of the PLIC is suited to SMP operation: An interrupt
 * source occurs to PLIC and then any available processor can conceivable
 * claim it unless its configuration is locked down.
 *
 * This obviously doesn't work well if the processors are in AMP
 * configuration and we are trying to * maintain hardware separation.
 * Therefore, PIC64GX can secure PLIC configuration through the
 * use of RISC-V PMP registers.
 *
 * Furthermore, MPRs allow assignment of each of 160 interrupts going to
 * the PLIC to one of two hardware contexts. This assignment can be
 * configured by E51 at boot time and is then locked until subsequent
 * reset.
 */
bool HSS_Setup_PLIC(void)
{
    __disable_all_irqs();
    PLIC_init_on_reset();

    return true;
}

/*!
 * \brief MPU Setup and Configuration
 *
 * The E51 ensures that hardware separate is ensured before the U54 code starts running.
 * To do this, it needs to partition memory and peripheral access, based on configuration
 * information provided at build time.
 *
 * The MSS MPUs are memory mapped and can be setup once by the E51. They are then locked
 * until subsequent system reboot. The MPRs allow assignment of peripheral resources to
 * one of two separate hardware contexts.
 */
bool HSS_Setup_MPU(void)
{
    mpu_configure();

    return true;
}



/*!
 * \brief L2Cache and Scratchpad Setup
 *
 * The E51 is responsible for configuring the cache controller, including locking of ways and
 * configuring between L2 Cache and Scratchpad for real-time AMP needs, based on configuration
 * information provided as a Libero output.
 */
bool HSS_Setup_L2Cache(void)
{
    config_l2_cache();

    return true;
}

/*!
 * \brief Clock Configuration
 *
 * Setup clock enables and soft resets
 *
 */
bool HSS_Setup_Clocks(void)
{
    static const uint32_t hss_subblk_clock_Config = 0xFFFFFFFFu;
    const uint32_t hss_soft_reset_Config = SYSREG->SOFT_RESET_CR &
        ~(
           SOFT_RESET_CR_SGMII_MASK    |
           SOFT_RESET_CR_CFM_MASK      |
           SOFT_RESET_CR_ATHENA_MASK   |
           SOFT_RESET_CR_FIC3_MASK     |
           SOFT_RESET_CR_FIC2_MASK     |
           SOFT_RESET_CR_FIC1_MASK     |
           SOFT_RESET_CR_FIC0_MASK     |
           SOFT_RESET_CR_DDRC_MASK     |
           SOFT_RESET_CR_GPIO2_MASK    |
           SOFT_RESET_CR_GPIO1_MASK    |
           SOFT_RESET_CR_GPIO0_MASK    |
           SOFT_RESET_CR_QSPI_MASK     |
           SOFT_RESET_CR_RTC_MASK      |
           SOFT_RESET_CR_COREPLEX_MASK |
           SOFT_RESET_CR_USB_MASK      |
           SOFT_RESET_CR_CAN1_MASK     |
           SOFT_RESET_CR_CAN0_MASK     |
           SOFT_RESET_CR_I2C1_MASK     |
           SOFT_RESET_CR_I2C0_MASK     |
           SOFT_RESET_CR_SPI1_MASK     |
           SOFT_RESET_CR_SPI0_MASK     |
           SOFT_RESET_CR_MMUART4_MASK  |
           SOFT_RESET_CR_MMUART3_MASK  |
           SOFT_RESET_CR_MMUART2_MASK  |
           SOFT_RESET_CR_MMUART1_MASK  |
           SOFT_RESET_CR_MMUART0_MASK  |
           SOFT_RESET_CR_TIMER_MASK    |
           SOFT_RESET_CR_MMC_MASK      |
           SOFT_RESET_CR_MAC1_MASK     |
           SOFT_RESET_CR_MAC0_MASK     |
           SOFT_RESET_CR_ENVM_MASK);

    SYSREG->SOFT_RESET_CR = 0x3FFFFFFEu; // everything but ENVM
    SYSREG->SOFT_RESET_CR = hss_soft_reset_Config;
    SYSREG->SUBBLK_CLOCK_CR = hss_subblk_clock_Config;

    SYSREG->FABRIC_RESET_CR = FABRIC_RESET_CR_ENABLE_MASK;

    /*
     * Turn on FIC interfaces by default. Drivers will turn on/off other MSS
     * peripherals as required.
     */
    (void)mss_config_clk_rst(MSS_PERIPH_FIC0, (uint8_t)0u, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_FIC1, (uint8_t)0u, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_FIC2, (uint8_t)0u, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_FIC3, (uint8_t)0u, PERIPHERAL_ON);

    return true;
}

/*!
 * \brief Bus Error Unit
 *
 * Setup bus error unit
 */
bool HSS_Setup_BusErrorUnit(void)
{
    (void)init_bus_error_unit();

    return true;
}
