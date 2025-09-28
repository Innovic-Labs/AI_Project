#include "brake.h"
#include <stdio.h>

Brake_StatusType Brake_Init(Brake_HandleType *h) {
    if (h == NULL) return BRAKE_FAULT_SENSOR;
    h->initialized = true;
    h->pressure_kPa = 0;
    h->absEngaged = false;
    return BRAKE_OK;
}

Brake_StatusType Brake_SetPressure(Brake_HandleType *h, uint16_t pressure_kPa) {
    if (h == NULL || !h->initialized) return BRAKE_FAULT_SENSOR;
    /* safety clamp */
    if (pressure_kPa > 10000) return BRAKE_FAULT_ACTUATOR;
    h->pressure_kPa = pressure_kPa;
    /* Log */
    printf("Brake: pressure set to %u kPa\n", pressure_kPa);
    return BRAKE_OK;
}

Brake_StatusType Brake_EngageABS(Brake_HandleType *h, bool engage) {
    if (h == NULL || !h->initialized) return BRAKE_FAULT_SENSOR;
    h->absEngaged = engage;
    printf("Brake: ABS %s\n", engage ? "ENGAGED" : "DISENGAGED");
    return BRAKE_OK;
}
Brake_StatusType Brake_GetStatus(Brake_HandleType *h, uint16_t *outPressure_kPa, bool *outAbsEngaged) {
    if (h == NULL || !h->initialized) return BRAKE_FAULT_SENSOR;
    if (outPressure_kPa) *outPressure_kPa = h->pressure_kPa;
    if (outAbsEngaged) *outAbsEngaged = h->absEngaged;
    return BRAKE_OK;
}

/* Simple ABS event handler - called periodically */
void Brake_PeriodicTask(Brake_HandleType *h) {
    if (h == NULL || !h->initialized) return;
    if (h->absEngaged) {
        /* modulate pressure - example stub */
        if (h->pressure_kPa > 5000) {
            /* reduce pressure to prevent lock */
            h->pressure_kPa -= 1000;
            printf("Brake: ABS modulated, pressure now %u kPa\n", h->pressure_kPa);
        }
    }
}