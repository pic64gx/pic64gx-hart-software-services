/*******************************************************************************
 * Copyright 2019-2024 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

#ifndef HW_DDR_OPTIONS_H_
#define HW_DDR_OPTIONS_H_

#if !defined (BSP_SETTING_CA_BUS_RX_OFF_POST_TRAINING)
/*Tip config: Referenced receivers in the CA bus are turned on for CA training.
These burn static power.(0x01 => turn off ; 0x00 => no action ) */
#define BSP_SETTING_CA_BUS_RX_OFF_POST_TRAINING    0x00000001UL
    /* CA_BUS_RX_OFF_POST_TRAINING       [0:1]   RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_USER_INPUT_PHY_RANKS_TO_TRAIN)
/*Tip config: 1 => 1 rank, 3 => 2 ranks */
#define BSP_SETTING_USER_INPUT_PHY_RANKS_TO_TRAIN    0x00000001UL
    /* USER_INPUT_PHY_RANKS_TO_TRAIN     [0:2]   RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_TRAINING_SKIP_SETTING)
/*Tip config: Pick what trainings we want performed by the TIP, default is 0x1F
*/
#define BSP_SETTING_TRAINING_SKIP_SETTING    0x00000002UL
    /* SKIP_BCLKSCLK_TIP_TRAINING        [0:1]   RW value= 0x0 */
    /* SKIP_ADDCMD_TIP_TRAINING          [1:1]   RW value= 0x1 */
    /* SKIP_WRLVL_TIP_TRAINING           [2:1]   RW value= 0x0 */
    /* SKIP_RDGATE_TIP_TRAINING          [3:1]   RW value= 0x0 */
    /* SKIP_DQ_DQS_OPT_TIP_TRAINING      [4:1]   RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_TIP_CFG_PARAMS)
/*Tip config: default: 0x2,0x4,0x0,0x1F,0x1F */
#define BSP_SETTING_TIP_CFG_PARAMS    0x07CFE003UL
    /* ADDCMD_OFFSET                     [0:3]   RW value= 0x3 */
    /* BCKLSCLK_OFFSET                   [3:3]   RW value= 0x0 */
    /* WRCALIB_WRITE_COUNT               [6:7]   RW value= 0x0 */
    /* READ_GATE_MIN_READS               [13:9]  RW value= 0x7F */
    /* ADDRCMD_WAIT_COUNT                [22:9]  RW value= 0x1F */
#endif
#if !defined (BSP_SETTING_TIP_CONFIG_PARAMS_BCLK_VCOPHS_OFFSET)
/*in simulation we need to set this to 2, for hardware it will be dependent on
the trace lengths */
#define BSP_SETTING_TIP_CONFIG_PARAMS_BCLK_VCOPHS_OFFSET    0x00000002UL
    /* TIP_CONFIG_PARAMS_BCLK_VCOPHS     [0:32]  RW value= 0x02 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1333_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR3_1333_NUM_OFFSETS    0x00000003UL
    /* REFCLK_DDR3_1333_NUM_OFFSETS      [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1333_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR3L_1333_NUM_OFFSETS    0x00000003UL
    /* REFCLK_DDR3L_1333_NUM_OFFSETS     [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1600_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR4_1600_NUM_OFFSETS    0x00000004UL
    /* REFCLK_DDR4_1600_NUM_OFFSETS      [0:32]  RW value= 4 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1600_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_LPDDR3_1600_NUM_OFFSETS    0x00000003UL
    /* REFCLK_LPDDR3_1600_NUM_OFFSETS    [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1600_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_LPDDR4_1600_NUM_OFFSETS    0x00000001UL
    /* REFCLK_LPDDR4_1600_NUM_OFFSETS    [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1067_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR3_1067_NUM_OFFSETS    0x00000001UL
    /* REFCLK_DDR3_1067_NUM_OFFSETS      [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1067_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR3L_1067_NUM_OFFSETS    0x00000001UL
    /* REFCLK_DDR3L_1067_NUM_OFFSETS     [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1333_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_DDR4_1333_NUM_OFFSETS    0x00000004UL
    /* REFCLK_DDR4_1333_NUM_OFFSETS      [0:32]  RW value= 4 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1333_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_LPDDR3_1333_NUM_OFFSETS    0x00000002UL
    /* REFCLK_LPDDR3_1333_NUM_OFFSETS    [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1333_NUM_OFFSETS)
/*Number of offsets used when training */
#define BSP_SETTING_REFCLK_LPDDR4_1333_NUM_OFFSETS    0x00000003UL
    /* REFCLK_LPDDR4_1333_NUM_OFFSETS    [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1333_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR3_1333_OFFSET_0    0x00000000UL
    /* REFCLK_DDR3_1333_OFFSET_0         [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1333_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR3_1333_OFFSET_1    0x00000001UL
    /* REFCLK_DDR3_1333_OFFSET_1         [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1333_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR3_1333_OFFSET_2    0x00000007UL
    /* REFCLK_DDR3_1333_OFFSET_2         [0:32]  RW value= 7 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1333_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR3_1333_OFFSET_3    0x00000000UL
    /* REFCLK_DDR3_1333_OFFSET_3         [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_0    0x00000000UL
    /* REFCLK_DDR3L_1333_OFFSET_0        [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_1    0x00000001UL
    /* REFCLK_DDR3L_1333_OFFSET_1        [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_2    0x00000000UL
    /* REFCLK_DDR3L_1333_OFFSET_2        [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR3L_1333_OFFSET_3    0x00000000UL
    /* REFCLK_DDR3L_1333_OFFSET_3        [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1600_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR4_1600_OFFSET_0    0x00000007UL
    /* REFCLK_DDR4_1600_OFFSET_0         [0:32]  RW value= 7 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1600_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR4_1600_OFFSET_1    0x00000006UL
    /* REFCLK_DDR4_1600_OFFSET_1         [0:32]  RW value= 6 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1600_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR4_1600_OFFSET_2    0x00000005UL
    /* REFCLK_DDR4_1600_OFFSET_2         [0:32]  RW value= 5 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1600_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR4_1600_OFFSET_3    0x00000000UL
    /* REFCLK_DDR4_1600_OFFSET_3         [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_0    0x00000007UL
    /* REFCLK_LPDDR3_1600_OFFSET_0       [0:32]  RW value= 7 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_1    0x00000000UL
    /* REFCLK_LPDDR3_1600_OFFSET_1       [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_2    0x00000001UL
    /* REFCLK_LPDDR3_1600_OFFSET_2       [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_LPDDR3_1600_OFFSET_3    0x00000002UL
    /* REFCLK_LPDDR3_1600_OFFSET_3       [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_0    0x00000003UL
    /* REFCLK_LPDDR4_1600_OFFSET_0       [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_1    0x00000004UL
    /* REFCLK_LPDDR4_1600_OFFSET_1       [0:32]  RW value= 4 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_2    0x00000002UL
    /* REFCLK_LPDDR4_1600_OFFSET_2       [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_LPDDR4_1600_OFFSET_3    0x00000005UL
    /* REFCLK_LPDDR4_1600_OFFSET_3       [0:32]  RW value= 5 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1067_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR3_1067_OFFSET_0    0x00000001UL
    /* REFCLK_DDR3_1067_OFFSET_0         [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1067_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR3_1067_OFFSET_1    0x00000002UL
    /* REFCLK_DDR3_1067_OFFSET_1         [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1067_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR3_1067_OFFSET_2    0x00000003UL
    /* REFCLK_DDR3_1067_OFFSET_2         [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3_1067_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR3_1067_OFFSET_3    0x00000002UL
    /* REFCLK_DDR3_1067_OFFSET_3         [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_0    0x00000001UL
    /* REFCLK_DDR3L_1067_OFFSET_0        [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_1    0x00000002UL
    /* REFCLK_DDR3L_1067_OFFSET_1        [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_2    0x00000003UL
    /* REFCLK_DDR3L_1067_OFFSET_2        [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR3L_1067_OFFSET_3    0x00000002UL
    /* REFCLK_DDR3L_1067_OFFSET_3        [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1333_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_DDR4_1333_OFFSET_0    0x00000000UL
    /* REFCLK_DDR4_1333_OFFSET_0         [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1333_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_DDR4_1333_OFFSET_1    0x00000001UL
    /* REFCLK_DDR4_1333_OFFSET_1         [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1333_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_DDR4_1333_OFFSET_2    0x00000006UL
    /* REFCLK_DDR4_1333_OFFSET_2         [0:32]  RW value= 6 */
#endif
#if !defined (BSP_SETTING_REFCLK_DDR4_1333_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_DDR4_1333_OFFSET_3    0x00000007UL
    /* REFCLK_DDR4_1333_OFFSET_3         [0:32]  RW value= 7 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_0    0x00000000UL
    /* REFCLK_LPDDR3_1333_OFFSET_0       [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_1    0x00000001UL
    /* REFCLK_LPDDR3_1333_OFFSET_1       [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_2    0x00000006UL
    /* REFCLK_LPDDR3_1333_OFFSET_2       [0:32]  RW value= 6 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_LPDDR3_1333_OFFSET_3    0x00000000UL
    /* REFCLK_LPDDR3_1333_OFFSET_3       [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_0)
/*offset for iteration 0 */
#define BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_0    0x00000002UL
    /* REFCLK_LPDDR4_1333_OFFSET_0       [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_1)
/*offset for iteration 1 */
#define BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_1    0x00000001UL
    /* REFCLK_LPDDR4_1333_OFFSET_1       [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_2)
/*offset for iteration 2 */
#define BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_2    0x00000003UL
    /* REFCLK_LPDDR4_1333_OFFSET_2       [0:32]  RW value= 3 */
#endif
#if !defined (BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_3)
/*offset for iteration 3 */
#define BSP_SETTING_REFCLK_LPDDR4_1333_OFFSET_3    0x00000000UL
    /* REFCLK_LPDDR4_1333_OFFSET_3       [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR3)
/*Zero degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR3    0x00000000UL
    /* ZERO_DEGRESS_ORDER                [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR3L)
/*Zero degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR3L    0x00000000UL
    /* ZERO_DEGRESS_ORDER                [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR4)
/*Zero degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_DDR4    0x00000000UL
    /* ZERO_DEGRESS_ORDER                [0:32]  RW value= 0x0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_LPDDR3)
/*Zero degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_LPDDR3    0x00000000UL
    /* ZERO_DEGRESS_ORDER                [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_LPDDR4)
/*Zero degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_0_DEG_LPDDR4    0x00000000UL
    /* ZERO_DEGRESS_ORDER                [0:32]  RW value= 0 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR3)
/*Forty five degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR3    0x00000001UL
    /* FORTY_FIVE_DEGRESS_ORDER          [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR3L)
/*Forty five degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR3L    0x00000001UL
    /* FORTY_FIVE_DEGRESS_ORDER          [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR4)
/*Forty five degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_DDR4    0x00000001UL
    /* FORTY_FIVE_DEGRESS_ORDER          [0:32]  RW value= 0x1 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_LPDDR3)
/*Forty five degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_LPDDR3    0x00000001UL
    /* FORTY_FIVE_DEGRESS_ORDER          [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_LPDDR4)
/*Forty five degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_45_DEG_LPDDR4    0x00000001UL
    /* FORTY_FIVE_DEGRESS_ORDER          [0:32]  RW value= 1 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR3)
/*Ninty degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR3    0x00000002UL
    /* NINTY_DEGRESS_ORDER               [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR3L)
/*Ninty degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR3L    0x00000002UL
    /* NINTY_DEGRESS_ORDER               [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR4)
/*Ninty degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_DDR4    0x00000002UL
    /* NINTY_DEGRESS_ORDER               [0:32]  RW value= 0x2 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_LPDDR3)
/*Ninty degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_LPDDR3    0x00000002UL
    /* NINTY_DEGRESS_ORDER               [0:32]  RW value= 2 */
#endif
#if !defined (BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_LPDDR4)
/*Ninty degres clock move order */
#define BSP_SETTING_ADD_CMD_CLK_MOVE_ORDER_90_DEG_LPDDR4    0x00000002UL
    /* NINTY_DEGRESS_ORDER               [0:32]  RW value= 2 */
#endif

#endif /* #ifdef HW_DDR_OPTIONS_H_ */

