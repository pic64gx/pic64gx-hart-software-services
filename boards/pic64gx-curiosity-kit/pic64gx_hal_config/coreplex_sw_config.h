#ifndef MSS_SW_CONFIG_H_
#define MSS_SW_CONFIG_H_

/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HAL Embedded Software
 *
 */

/*******************************************************************************
 *
 * Platform definitions
 * Version based on requirements of PIC64GX MSS
 *
 */
 /*========================================================================*//**
  @mainpage Sample file detailing how mss_sw_config.h should be constructed for
    the PIC64GX MSS

    @section intro_sec Introduction
    The mss_sw_config.h has the default software configuration settings for the
    PIC64GX HAL and will be located at
    <Project-Name>/src/platform/platform_config_reference folder of the bare
    metal SoftConsole project. The platform_config_reference is provided as a
    default reference configuration.
    When you want to configure the PIC64GX HAL with required configuration for
    your project, the mss_sw_config.h must be edited and be placed in the
    following project directory:
    <Project-Name>/src/boards/<your-board>/platform_config/pic64gx_hal_config/

    @section

*//*==========================================================================*/

/*
 * Include any driver setup/over-rides you may require.
 */
#include "drivers/coreplex/coreplex_ihc/coreplex_ihc_defines.h"
#include "drivers_config/coreplex/coreplex_ihc/coreplex_ihc_config.h"

#define PIC64GX_HAL_FIRST_HART  1
#define PIC64GX_HAL_LAST_HART   4

#define IMAGE_LOADED_BY_BOOTLOADER 0
#if (IMAGE_LOADED_BY_BOOTLOADER == 0)
#define PIC64GX_HAL_HW_CONFIG
#endif

/*------------------------------------------------------------------------------
 * Markers used to indicate startup status of hart
 */
#define HLS_DATA_IN_WFI                     0x12345678U
#define HLS_DATA_PASSED_WFI                 0x87654321U

/*
 * If you are using common memory for sharing across harts,
 * uncomment #define PIC64GX_HAL_SHARED_MEM_ENABLED
 * make sure common memory is allocated in the linker script
 * See app_hart_common mem section in the example platform
 * linker scripts.
 */

//#define PIC64GX_HAL_SHARED_MEM_ENABLED


/* define the required tick rate in Milliseconds */
/* if this program is running on one hart only, only that particular hart value
 * will be used */
#define HART0_TICK_RATE_MS  5UL
#define HART1_TICK_RATE_MS  5UL
#define HART2_TICK_RATE_MS  5UL
#define HART3_TICK_RATE_MS  5UL
#define HART4_TICK_RATE_MS  5UL

/*
 * Define the size of the Hart Local Storage (HLS).
 * In the PIC64GX HAL, we are using HLS for debug data storage during the initial
 * boot phase.
 * This includes the flags which indicate the hart state regarding boot state.
 * The HLS will take memory from top of each stack allocated at boot time.
 *
 */
#define HLS_DEBUG_AREA_SIZE     64

/*
 * Bus Error Unit (BEU) configurations
 * BEU_ENABLE => Configures the events that the BEU can report. bit value
 *               1= enabled, 0 = disabled.
 * BEU_PLIC_INT => Configures which accrued events should generate an
 *                 interrupt to the PLIC.
 * BEU_LOCAL_INT => Configures which accrued events should generate a
 *                 local interrupt to the hart on which the event accrued.
 */
#define BEU_ENABLE                  0x0ULL
#define BEU_PLIC_INT                0x0ULL
#define BEU_LOCAL_INT               0x0ULL

/*
 * Clear memory on startup
 * 0 => do not clear DTIM and L2
 * 1 => Clears memory
 * Note: If you are the zero stage bootloader, set this to one.
 */
#ifndef PIC64GX_HAL_CLEAR_MEMORY
#define PIC64GX_HAL_CLEAR_MEMORY  0
#endif

/*
 * Comment out the lines to disable the corresponding hardware support not required
 * in your application.
 * This is not necessary from an operational point of view as operation dictated
 * by MSS configurator settings, and items are enabled/disabled by this method.
 * The reason you may want to use below is to save code space.
 */
#define SGMII_SUPPORT
#define DDR_SUPPORT
#define MSSIO_SUPPORT

/*
 * Debugging IHC. This placed memory map in volatile memory and uses software
 * state machine
 */
#define LIBERO_SETTING_CONTEXT_A_HART_EN    0x0000000EUL    /* harts 1 to 3 */
#define LIBERO_SETTING_CONTEXT_B_HART_EN    0x00000010UL    /* hart 4 */

/*
 * DDR software options
 */

/*
 * SDIO register address location in fabric
 */
/*
 * We want the Kconfig-generated config.h file to get the SDIO Register Address,
 * but it defines CONFIG_OPENSBI...
 *
 * OpenSBI type definitions conflict with pic64gx_hal
 * so we need to undefine CONFIG_OPENSBI after including config.h
 */
#include "config.h"
#undef CONFIG_OPENSBI

#ifdef CONFIG_SERVICE_MMC_FABRIC_SD_EMMC_DEMUX_SELECT_ADDRESS
#  undef LIBERO_SETTING_SWITCH_ADDRESS
#  define LIBERO_SETTING_SWITCH_ADDRESS CONFIG_SERVICE_MMC_FABRIC_SD_EMMC_DEMUX_SELECT_ADDRESS
#else
#  ifndef LIBERO_SETTING_SWITCH_ADDRESS
#    define LIBERO_SETTING_SWITCH_ADDRESS 0x4fffff00
#  endif
#endif

#endif /* USER_CONFIG_MSS_USER_CONFIG_H_ */

