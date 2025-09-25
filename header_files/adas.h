#ifndef ADAS_H
#define ADAS_H

#include <stdint.h>
#include <stdbool.h>

/* ADAS ECU (advanced driver assistance) - simple lane keep + distance assist stub */

typedef enum {
    ADAS_OK = 0,
    ADAS_FAULT_SENSOR,
    ADAS_FAULT_ALGO
} ADAS_StatusType;

typedef struct {
    bool initialized;
    bool lane_keep_enabled;
    bool adaptive_cruise_enabled;
    uint16_t desired_distance_cm;
} ADAS_HandleType;

ADAS_StatusType ADAS_Init(ADAS_HandleType *h);
ADAS_StatusType ADAS_EnableLaneKeep(ADAS_HandleType *h, bool enable);
ADAS_StatusType ADAS_SetDistance(ADAS_HandleType *h, uint16_t cm);

#endif /* ADAS_H */