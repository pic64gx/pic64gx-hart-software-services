/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * This file contains system specific definitions for the PIC64GX MSS
 * Ethernet MAC device driver.
 *
 * SVN $Revision$
 * SVN $Date$
 *
 */

#ifndef MICROSEMI__FIRMWARE__POLARFIRE_SOC_MSS_ETHERNET_MAC_DRIVER__1_5_101_CONFIGURATION_HEADER
#define MICROSEMI__FIRMWARE__POLARFIRE_SOC_MSS_ETHERNET_MAC_DRIVER__1_5_101_CONFIGURATION_HEADER

#define CORE_VENDOR "Microsemi"
#define CORE_LIBRARY "Firmware"
#define CORE_NAME "PIC64GX_SoC_MSS_Ethernet_MAC_Driver"
#define CORE_VERSION "1.5.101"

/*
 * Defines for OS and network stack specific support
 * Un-comment as necessary or define in project properties etc.
 */

/* #define USING_FREERTOS */
/* #define USING_LWIP */

/* Allowed PHY interface types: */

#define NULL_PHY                        (0x0001U) /* No PHY in connection, for example GEM0 and GEM1 connected via fabric */
#define GMII                            (0x0002U) /* Currently only on Aloe board */
#define TBI                             (0x0004U) /* G5 SoC Emulation Platform designs with TBI */
#define GMII_SGMII                      (0x0008U) /* G5 SoC Emulation Platform designs with SGMII to GMII conversion */
#define BASEX1000                       (0x0010U) /* Not currently available */
#define RGMII                           (0x0020U) /* Not currently available */
#define RMII                            (0x0040U) /* Not currently available */
#define SGMII                           (0x0080U) /* Not currently available */

/* Allowed PHY models: */

#define MSS_MAC_DEV_PHY_NULL            (0x0001U)
#define MSS_MAC_DEV_PHY_VSC8575         (0x0002U) /* Uses full VTSS API */
#define MSS_MAC_DEV_PHY_VSC8541         (0x0004U)
#define MSS_MAC_DEV_PHY_DP83867         (0x0008U)
#define MSS_MAC_DEV_PHY_VSC8575_LITE    (0x0010U) /* Uses Lite VTSS API */


/*
 * Defines for the different hardware configurations on the G5 SoC Emulation
 * Platform etc.
 *
 * Used to allow software configure GPIO etc, to support the appropriate
 * hardware configuration. Not strictly part of the driver but we manage them
 * here to keep things tidy.
 */

#define MSS_MAC_PHYS (MSS_MAC_DEV_PHY_NULL | MSS_MAC_DEV_PHY_VSC8575_LITE | MSS_MAC_DEV_PHY_DP83867)

#define MSS_MAC_HW_PLATFORM MSS_MAC_DESIGN_EMUL_DUAL_EXTERNAL

//#define MSS_MAC_RX_RING_SIZE (16U)
#define MSS_MAC_RX_RING_SIZE (9U)
#define MSS_MAC_TX_RING_SIZE (4U) /* PMCS should be 2 but want to be able to force duplicate
                                  * tx to stuff multiple packets into FIFO for testing */

#define MSS_MAC_USE_PHY_VSC8575      (0U != (MSS_MAC_PHYS & MSS_MAC_DEV_PHY_VSC8575))
#define MSS_MAC_USE_PHY_VSC8575_LITE (0U != (MSS_MAC_PHYS & MSS_MAC_DEV_PHY_VSC8575_LITE))
#define MSS_MAC_USE_PHY_VSC8541      (0U != (MSS_MAC_PHYS & MSS_MAC_DEV_PHY_VSC8541))
#define MSS_MAC_USE_PHY_DP83867      (0U != (MSS_MAC_PHYS & MSS_MAC_DEV_PHY_DP83867))
#define MSS_MAC_USE_PHY_NULL         (0U != (MSS_MAC_PHYS & MSS_MAC_DEV_PHY_NULL))

#define MSS_MAC_TIME_STAMPED_MODE      (0) /* Enable time stamp support */ 

/*
 * Defines for different memory areas. Set the macro MSS_MAC_USE_DDR to one of
 * these values to select the area of memory and buffer sizes to use when
 * testing for non LIM based areas of memory.
 */

#define MSS_MAC_MEM_DDR    (0)
#define MSS_MAC_MEM_FIC0   (1)
#define MSS_MAC_MEM_FIC1   (2)
#define MSS_MAC_MEM_CRYPTO (3)

/*
 * Number of additional queues for PMAC.
 *
 * Note. We explicitly set the number of queues in the MAC structure as we have
 * to indicate the Interrupt Number so this is slightly artificial...
 */
#if defined(TARGET_ALOE)
#define MSS_MAC_QUEUE_COUNT (1)
#else
#define MSS_MAC_QUEUE_COUNT (4)
#endif


/*
 * Number of Type 1 and 2 screeners
 */

#define MSS_MAC_TYPE_1_SCREENERS  (4U)
#define MSS_MAC_TYPE_2_SCREENERS  (4U)
#define MSS_MAC_TYPE_2_ETHERTYPES (4U)
#define MSS_MAC_TYPE_2_COMPARERS  (4U)

/* These are hard coded and not user selectable */
#define MSS_MAC_EMAC_TYPE_2_SCREENERS  (2U)
#define MSS_MAC_EMAC_TYPE_2_COMPARERS  (6U)

#endif /* MICROSEMI__FIRMWARE__POLARFIRE_SOC_MSS_ETHERNET_MAC_DRIVER__1_5_101_CONFIGURATION_HEADER */

