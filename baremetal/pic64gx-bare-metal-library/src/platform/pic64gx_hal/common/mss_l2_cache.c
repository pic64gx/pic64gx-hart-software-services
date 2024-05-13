/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HAL Embedded Software
 *
 * @file mss_l2_cache.c
 * @author Microchip Technology Inc
 * @brief The code in this file is executed before any code/data sections are
 * copied. This code must not rely sdata/data section content. Hence, global
 * variables should not be used unless they are constants.
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pic64gx_hal/mss_hal.h"
#include "mss_l2_cache.h"

/*==============================================================================
 * Local defines
 */
#if (BSP_SETTING_NUM_SCRATCH_PAD_WAYS != 0)
static const uint64_t g_init_marker = INIT_MARKER;
#endif

/*==============================================================================
 * Local functions.
 */
static void check_config_l2_scratchpad(void);

/***************************************************************************//**
 * See hw_l2_scratch.h for details of how to use this function.
 */
__attribute__((weak)) uint64_t end_l2_scratchpad_address(void)
{
   return (uint64_t)(ZERO_DEVICE_BOTTOM + (BSP_SETTING_NUM_SCRATCH_PAD_WAYS
           * WAY_BYTE_LENGTH));
}

/***************************************************************************//**
 * See hw_l2_scratch.h for details of how to use this function.
 */
__attribute__((weak)) uint32_t num_cache_ways(void)
{
   static_assert(BSP_SETTING_WAY_ENABLE >
                 BSP_SETTING_NUM_SCRATCH_PAD_WAYS,
                 "Invalid way configuration");
   return (uint64_t)((BSP_SETTING_WAY_ENABLE + 1U) -
                     BSP_SETTING_NUM_SCRATCH_PAD_WAYS);
}

/***************************************************************************//**
 * See hw_l2_scratch.h for details of how to use this function.
 */
__attribute__((weak)) uint32_t my_num_dcache_ways(uint32_t hartid)
{
    uint32_t num_ways = 0U;
    uint32_t way_enable;
    uint32_t bit_index;

    for (uint32_t current_way = 0; current_way <= BSP_SETTING_WAY_ENABLE; current_way++) {
        /* disable evictions from all but current_way */
        switch (hartid)
        {
            case 0:
                way_enable = (uint32_t)BSP_SETTING_WAY_MASK_E51_DCACHE;
               break;
            case 1:
                way_enable = (uint32_t)BSP_SETTING_WAY_MASK_U54_1_DCACHE;
                break;
            case 2:
                way_enable = (uint32_t)BSP_SETTING_WAY_MASK_U54_2_DCACHE;
                break;
            case 3:
                way_enable = (uint32_t)BSP_SETTING_WAY_MASK_U54_3_DCACHE;
                break;
            case 4:
                way_enable = (uint32_t)BSP_SETTING_WAY_MASK_U54_4_DCACHE;
                break;
        }
    }

    bit_index = 0U;

    while(bit_index < 16U)
    {
       if( way_enable & (1U<<bit_index))
       {
           num_ways++;
       }
       bit_index++;
    }
    return (uint64_t)(num_ways);
}

/***************************************************************************//**
 * See mss_uart.h for details of how to use this function.
 */
__attribute__((weak)) void config_l2_cache(void)
{
    static_assert(BSP_SETTING_WAY_ENABLE < 16U, "Too many ways");
    /*
     * confirm the amount of l2lim used in the Linker script has been allocated
     * in the MSS Configurator
     */
    ASSERT(((const uint64_t)&__l2lim_end - (const uint64_t)&__l2lim_start)\
            <= ((15U - BSP_SETTING_WAY_ENABLE) * WAY_BYTE_LENGTH));

    /*
     * Set the number of ways that will be shared between cache and scratchpad.
     */
    __atomic_store_8 (&CACHE_CTRL->WAY_ENABLE , BSP_SETTING_WAY_ENABLE, __ATOMIC_RELAXED);

    /*
     * shutdown L2 as directed
     */
    SYSREG->L2_SHUTDOWN_CR = BSP_SETTING_L2_SHUTDOWN_CR;

    /* The scratchpad has already been set-up, first check enough space before
     * copying */
    check_config_l2_scratchpad();

    /* If you are not using scratchpad, no need to include the following code */

    static_assert(BSP_SETTING_WAY_ENABLE >=
            BSP_SETTING_NUM_SCRATCH_PAD_WAYS, "Scratchpad Missing");

    /*
     * Compute the mask (In HSS CONFIG_SERVICE_SCRUB=y) used to specify ways
     * that will be used by the scratchpad
     */

    uint32_t scratchpad_ways_mask = 0U;
#if (BSP_SETTING_NUM_SCRATCH_PAD_WAYS != 0)
    uint32_t inc;
    uint32_t seed_ways_mask = 0x1U << BSP_SETTING_WAY_ENABLE;
    for(inc = 0; inc < BSP_SETTING_NUM_SCRATCH_PAD_WAYS; ++inc)
    {
        scratchpad_ways_mask |= (seed_ways_mask >> inc) ;
    }
#else
    (void)scratchpad_ways_mask;
#endif

    /*
     * Make sure ways are masked if being used as scratchpad
     */
    ASSERT((BSP_SETTING_WAY_MASK_DMA & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_AXI4_PORT_0 & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_AXI4_PORT_1 & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_AXI4_PORT_2 & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_AXI4_PORT_3 & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_E51_DCACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_E51_ICACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_1_DCACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_2_DCACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_3_DCACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_4_DCACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_1_ICACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_2_ICACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_3_ICACHE & scratchpad_ways_mask) == 0UL);
    ASSERT((BSP_SETTING_WAY_MASK_U54_4_ICACHE & scratchpad_ways_mask) == 0UL);

    /*
     * Setup all masters, apart from one we are using to setup scratch
     */

    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_DMA , BSP_SETTING_WAY_MASK_DMA, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_AXI4_SLAVE_PORT_0 , BSP_SETTING_WAY_MASK_AXI4_PORT_0, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_AXI4_SLAVE_PORT_1 , BSP_SETTING_WAY_MASK_AXI4_PORT_1, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_AXI4_SLAVE_PORT_2 , BSP_SETTING_WAY_MASK_AXI4_PORT_2, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_AXI4_SLAVE_PORT_3 , BSP_SETTING_WAY_MASK_AXI4_PORT_3, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_E51_ICACHE , BSP_SETTING_WAY_MASK_E51_ICACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_1_DCACHE , BSP_SETTING_WAY_MASK_U54_1_DCACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_1_ICACHE , BSP_SETTING_WAY_MASK_U54_1_ICACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_2_DCACHE , BSP_SETTING_WAY_MASK_U54_2_DCACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_2_ICACHE , BSP_SETTING_WAY_MASK_U54_2_ICACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_3_DCACHE , BSP_SETTING_WAY_MASK_U54_3_DCACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_3_ICACHE , BSP_SETTING_WAY_MASK_U54_3_ICACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_4_DCACHE , BSP_SETTING_WAY_MASK_U54_4_DCACHE, __ATOMIC_RELAXED);
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_U54_4_ICACHE , BSP_SETTING_WAY_MASK_U54_4_ICACHE, __ATOMIC_RELAXED);


#if (BSP_SETTING_NUM_SCRATCH_PAD_WAYS != 0)
    /*
     * Assign ways to Zero Device
     */
    uint64_t * p_scratchpad = (uint64_t *)ZERO_DEVICE_BOTTOM;
    uint32_t ways_inc;
    uint64_t current_way = 0x1U << (((BSP_SETTING_WAY_ENABLE + 1U) - BSP_SETTING_NUM_SCRATCH_PAD_WAYS) );

    for(ways_inc = 0; ways_inc < BSP_SETTING_NUM_SCRATCH_PAD_WAYS; ++ways_inc)
    {
        /*
         * Populate the scratchpad memory one way at a time.
         */
        __atomic_store_8 (&CACHE_CTRL->WAY_MASK_E51_DCACHE, current_way, __ATOMIC_RELAXED);
        mb();
        /*
         * Write to the first 64-bit location of each cache block.
         */
        for(inc = 0; inc < (WAY_BYTE_LENGTH / CACHE_BLOCK_BYTE_LENGTH); ++inc)
        {

            *p_scratchpad = g_init_marker /* + inc */;
            p_scratchpad += CACHE_BLOCK_BYTE_LENGTH / UINT64_BYTE_LENGTH;
        }
        current_way = current_way << 1U;
        mb();
    }
#endif  /* (BSP_SETTING_NUM_SCRATCH_PAD_WAYS != 0) */
    /*
     * Prevent E51 from evicting from scratchpad ways.
     */
    __atomic_store_8 (&CACHE_CTRL->WAY_MASK_E51_DCACHE , BSP_SETTING_WAY_MASK_E51_DCACHE, __ATOMIC_RELAXED);
    mb();
}

/*==============================================================================
 * Configure the L2 scratchpad based on linker symbols:
 *  __l2_scratchpad_vma_start
 *  __l2_scratchpad_vma_end
 *
 *  These linker symbols specify the start address and length of the scratchpad.
 *  The scratchpad must be located within the Zero Device memory range.
 */
static void check_config_l2_scratchpad(void)
{
    extern char __l2_scratchpad_vma_start;
    extern char __l2_scratchpad_vma_end;

    uint8_t n_scratchpad_ways;
    const uint64_t end = (const uint64_t)&__l2_scratchpad_vma_end;
    const uint64_t start = (const uint64_t)&__l2_scratchpad_vma_start;
    uint64_t modulo;

    ASSERT(start >= (uint64_t)ZERO_DEVICE_BOTTOM);
    ASSERT(end < (uint64_t)ZERO_DEVICE_TOP);
    ASSERT(end >= start);

    /*
     * Figure out how many cache ways will be required from linker script
     * symbols.
     */
    n_scratchpad_ways = (uint8_t)((end - start) / WAY_BYTE_LENGTH);
    modulo = (end - start) % WAY_BYTE_LENGTH;
    if(modulo > 0)
    {
        ++n_scratchpad_ways;
    }

    ASSERT(BSP_SETTING_NUM_SCRATCH_PAD_WAYS >= n_scratchpad_ways);
}

/***************************************************************************//**
 * See mss_l2_scratch.h for details of how to use this function.
 */
void flush_l2_cache(uint32_t hartid)
{
    /*
     * flush L2 Cache, way-by-way
     *  see https://forums.sifive.com/t/flush-invalidate-l1-l2-on-the-u54-mc/4483/9
     *  the thing to be wary of is the policy is random replacement by way,
     *  so there must be only 1 way enabled at a time...
     *  then, still need to go through ~2MiB (2MiB/16 per way) of reads to
     *  safely ensure the L2 is cleared...
     */

    for (uint32_t current_way = 0; current_way <= BSP_SETTING_WAY_ENABLE; current_way++) {
        /* disable evictions from all but current_way */
        switch (hartid)
        {
            case 0:
               __atomic_store_8(&CACHE_CTRL->WAY_MASK_E51_DCACHE, current_way, __ATOMIC_RELAXED);
               break;
            case 1:
                __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_1_DCACHE, current_way, __ATOMIC_RELAXED);
                break;
            case 2:
                __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_2_DCACHE, current_way, __ATOMIC_RELAXED);
                break;
            case 3:
                __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_3_DCACHE, current_way, __ATOMIC_RELAXED);
                break;
            case 4:
                __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_4_DCACHE, current_way, __ATOMIC_RELAXED);
                break;
        }

        /* read 2MiB/16 from L2 zero device */
        for (uint64_t i = 0u; i < 131u*1024u; i+=8u)
        { (void)*(volatile uint64_t *)(ZERO_DEVICE_BOTTOM + i); };
    }
    /* restore WayMask values... */
    switch (hartid)
    {
        case 0:
            __atomic_store_8(&CACHE_CTRL->WAY_MASK_E51_DCACHE, BSP_SETTING_WAY_MASK_E51_DCACHE, __ATOMIC_RELAXED);
           break;
        case 1:
            __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_1_DCACHE, BSP_SETTING_WAY_MASK_U54_1_DCACHE, __ATOMIC_RELAXED);
            break;
        case 2:
            __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_2_DCACHE, BSP_SETTING_WAY_MASK_U54_2_DCACHE, __ATOMIC_RELAXED);
            break;
        case 3:
            __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_3_DCACHE, BSP_SETTING_WAY_MASK_U54_3_DCACHE, __ATOMIC_RELAXED);
            break;
        case 4:
            __atomic_store_8(&CACHE_CTRL->WAY_MASK_U54_4_DCACHE, BSP_SETTING_WAY_MASK_U54_4_DCACHE, __ATOMIC_RELAXED);
            break;
    }
}
