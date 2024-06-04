#ifndef HSS_TRIGGER_H
#define HSS_TRIGGER_H

/*******************************************************************************
 * Copyright 2019-2022 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: MIT
 *
 * PIC64GX HSS Embedded Software
 *
 */

enum HSS_Event {
    EVENT_OPENSBI_INITIALIZED,
    EVENT_IPI_INITIALIZED,
    EVENT_DDR_TRAINED,
    EVENT_STARTUP_COMPLETE,
    EVENT_USBDMSC_REQUESTED,
    EVENT_USBDMSC_FINISHED,
    EVENT_POST_BOOT,
    EVENT_HART_STATE_CHANGED,
    EVENT_HEALTHMON,
};

void HSS_Trigger_Notify(enum HSS_Event event);
bool HSS_Trigger_IsNotified(enum HSS_Event event);
void HSS_Trigger_Clear(enum HSS_Event event);

#endif
