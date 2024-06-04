/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

/*!
 * \file DDR Retraining Driver State Machine
 * \brief DDR Retraining
 */

#include "config.h"
#include "hss_types.h"
#include "hss_state_machine.h"
#include "hss_debug.h"
#include "ssmb_ipi.h"

#include "hss_trigger.h"
#include "hss_init.h"
#include "ddr_service.h"

#include <assert.h>

/* Timeouts */
#define DDR_IDLE_PERIODIC_TIMEOUT (ONE_SEC * 60llu * 60llu * 10llu)

/* Module Prototypes (states) */
static void ddr_init_handler(struct StateMachine * const pMyMachine);
static void ddr_train_handler(struct StateMachine * const pMyMachine);
static void ddr_idle_handler(struct StateMachine * const pMyMachine);
static void ddr_retrain_handler(struct StateMachine * const pMyMachine);

/*!
 * \brief DDR Driver States
 */
enum DDRStatesEnum {
    DDR_INITIALIZATION,
    DDR_TRAIN,
    DDR_IDLE,
    DDR_RETRAIN,
    DDR_NUM_STATES = DDR_IDLE+1
};

/*!
 * \brief DDR Driver State Descriptors
 */
static const struct StateDesc ddr_state_descs[] = {
    { (const stateType_t)DDR_INITIALIZATION, (const char *)"Init",    NULL, NULL, &ddr_init_handler },
    { (const stateType_t)DDR_TRAIN,          (const char *)"Train",   NULL, NULL, &ddr_train_handler },
    { (const stateType_t)DDR_IDLE,           (const char *)"Idle",    NULL, NULL, &ddr_idle_handler },
    { (const stateType_t)DDR_RETRAIN,        (const char *)"Retrain", NULL, NULL, &ddr_retrain_handler }
};

/*!
 * \brief DDR Driver State Machine
 */
struct StateMachine ddr_service = {
    .state             = (stateType_t)DDR_INITIALIZATION,
    .prevState         = (stateType_t)SM_INVALID_STATE,
    .numStates         = (const uint32_t)DDR_NUM_STATES,
    .pMachineName      = (const char *)"ddr_service",
    .startTime         = 0u,
    .lastExecutionTime = 0u,
    .executionCount    = 0u,
    .pStateDescs       = ddr_state_descs,
    .debugFlag         = false,
    .priority          = 0u,
    .pInstanceData     = NULL
};

// --------------------------------------------------------------------------------------------------
// Handlers for each state in the state machine
//
static void ddr_init_handler(struct StateMachine * const pMyMachine)
{
    (void) pMyMachine;

    if (HSS_Trigger_IsNotified(EVENT_IPI_INITIALIZED)) {
        HSS_DDR_Train();
        pMyMachine->state = DDR_TRAIN;
    }
}

/////////////////

static void ddr_train_handler(struct StateMachine * const pMyMachine)
{
    (void) pMyMachine;

    if (HSS_Trigger_IsNotified(EVENT_DDR_TRAINED)) {
        pMyMachine->state = DDR_IDLE;
    }
}

/////////////////

static void ddr_idle_handler(struct StateMachine * const pMyMachine)
{
    (void) pMyMachine;

    if (HSS_Timer_IsElapsed(pMyMachine->startTime, (HSSTicks_t)DDR_IDLE_PERIODIC_TIMEOUT)) {
        pMyMachine->state = DDR_RETRAIN;
    }
}

/////////////////

static void ddr_retrain_handler(struct StateMachine * const pMyMachine)
{
    (void) pMyMachine;

    //HSS_DDRInit();
    pMyMachine->state = DDR_IDLE;
}

