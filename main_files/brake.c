#include "brake.h"
#include <stdio.h>



Brake_StatusType Brake_SetPressure(Brake_HandleType *h, uint16_t pressure_kPa) {
    if (h == NULL || !h->initialized) return BRAKE_FAULT_SENSOR;
    /* safety clamp */
    if (pressure_kPa > 10000) return BRAKE_FAULT_ACTUATOR;
    h->pressure_kPa = pressure_kPa;
    /* Log */
    printf("Brake: pressure set to %u kPa\n", pressure_kPa);
    return BRAKE_OK;
}

Brake_StatusType Brake_ApplyABS(Brake_HandleType *h, bool enable) {
    if (h == NULL || !h->initialized) return BRAKE_FAULT_SENSOR;
    h->absEngaged = enable;
    printf("Brake: ABS %s\n", enable ? "ENABLED" : "DISABLED");
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