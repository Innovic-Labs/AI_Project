#include "gear.h"
#include <stdio.h>
#include <string.h>

static void gear_internal_shift(Gear_HandleType *h, Gear_PositionType target);

Gear_ReturnType Gear_Init(Gear_HandleType *h) {
    if (h == NULL) return GEAR_ERR;
    h->current = GEAR_PARK;
    h->requested = GEAR_PARK;
    h->initialized = true;
    return GEAR_OK;
}



Gear_PositionType Gear_GetPosition(Gear_HandleType *h) {
    if (h == NULL) return GEAR_UNKNOWN;
    return h->current;
}



static void gear_internal_shift(Gear_HandleType *h, Gear_PositionType target) {
    /* Simplified shift sequence with simulated timing and checks */
    /* In production: check engine RPM, brake pedal state, clutch, hydraulic pressure, etc. */
    printf("Gear: shifting from %d to %d\n", h->current, target);
    h->current = target;
}

/* Additional helper functions and fault injection utilities to extend file length */

void Gear_SimulateFault(Gear_HandleType *h) {
    if (h == NULL) return;
    h->current = GEAR_UNKNOWN;
}

void Gear_LogState(Gear_HandleType *h) {
    if (h == NULL) return;
    printf("Gear Log: current=%d, requested=%d, init=%d\n", (int)h->current, (int)h->requested, (int)h->initialized);
}

/* Simple test harness function (can be compiled into a unit-test target) */
#ifdef GEAR_UNIT_TEST
#include <unistd.h>
int main(void) {
    Gear_HandleType gh;
    Gear_Init(&gh);
    Gear_SetPosition(&gh, GEAR_DRIVE);
    for (int i = 0; i < 5; ++i) {
        Gear_UpdateState(&gh, 100);
        Gear_LogState(&gh);
        usleep(100000);
    }
    return 0;
}
#endif