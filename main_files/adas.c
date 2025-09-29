#include "adas.h"
#include <stdio.h>

ADAS_StatusType ADAS_Init(ADAS_HandleType *h) {
    if (h == NULL) return ADAS_FAULT_SENSOR;
    h->initialized = true;
    h->lane_keep_enabled = false;
    h->adaptive_cruise_enabled = false;
    h->desired_distance_cm = 150;
    
}



ADAS_StatusType ADAS_getDistance(ADAS_HandleType *h, uint16_t cm) {
    if (h == NULL || !h->initialized) return ADAS_FAULT_SENSOR;
    h->desired_distance_cm = cm;
    return ADAS_OK;
}

/* Simple periodic ADAS loop stub */
void ADAS_Periodic(ADAS_HandleType *h) {
    if (h == NULL || !h->initialized) return;
    if (h->lane_keep_enabled) {
        /* call lane detection + steering assist */
        printf("ADAS: correcting steering to keep lane\n");
    }
    if (h->adaptive_cruise_enabled) {
        printf("ADAS: maintaining distance %u cm\n", h->desired_distance_cm);
    }
}