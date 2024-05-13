/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/**
 * \file HSS PDMA Initalization
 * \brief PDMA Initialization
 */

#include "config.h"
#include "hss_types.h"

#include "hss_init.h"

#include <assert.h>

#include "hss_debug.h"

#if IS_ENABLED(CONFIG_USE_PDMA)
#  include "drivers/mss/mss_pdma/mss_pdma.h"
#endif

bool HSS_PDMAInit(void)
{
#if IS_ENABLED(CONFIG_USE_PDMA)
    // initialise PDMA
    MSS_PDMA_init();
#endif

    return true;
}
