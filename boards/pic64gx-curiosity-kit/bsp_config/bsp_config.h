/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef BSP_CONFIG_H_
#define BSP_CONFIG_H_

#include "memory_map/hw_memory.h"
#include "memory_map/hw_apb_split.h"
#include "memory_map/hw_cache.h"
#include "memory_map/hw_pmp_hart0.h"
#include "memory_map/hw_pmp_hart1.h"
#include "memory_map/hw_pmp_hart2.h"
#include "memory_map/hw_pmp_hart3.h"
#include "memory_map/hw_pmp_hart4.h"
#include "memory_map/hw_mpu_fic0.h"
#include "memory_map/hw_mpu_fic1.h"
#include "memory_map/hw_mpu_fic2.h"
#include "memory_map/hw_mpu_crypto.h"
#include "memory_map/hw_mpu_gem0.h"
#include "memory_map/hw_mpu_gem1.h"
#include "memory_map/hw_mpu_usb.h"
#include "memory_map/hw_mpu_mmc.h"
#include "memory_map/hw_mpu_scb.h"
#include "memory_map/hw_mpu_trace.h"
#include "memory_map/hw_nvm_map.h"
#include "io/hw_mssio_mux.h"
#include "io/hw_mssio_mux_alternate.h"
#include "io/hw_hsio_mux.h"
#include "sgmii/hw_sgmii_tip.h"
#include "ddr/hw_ddr_options.h"
#include "ddr/hw_ddr_io_bank.h"
#include "ddr/hw_ddr_mode.h"
#include "ddr/hw_ddr_off_mode.h"
#include "ddr/hw_ddr_segs.h"
#include "ddr/hw_ddrc.h"
#include "clocks/hw_mss_clks.h"
#include "clocks/hw_clk_sysreg.h"
#include "clocks/hw_clk_mss_pll.h"
#include "clocks/hw_clk_sgmii_pll.h"
#include "clocks/hw_clk_ddr_pll.h"
#include "clocks/hw_clk_mss_cfm.h"
#include "clocks/hw_clk_sgmii_cfm.h"
#include "general/hw_gen_peripherals.h"
/* No content in this file, used for referencing header */

#endif /* #ifdef BSP_CONFIG_H_ */

