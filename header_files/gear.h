#ifndef GEAR_H
#define GEAR_H

#include <stdint.h>
#include <stdbool.h>

/* Gear ECU - manages gear selection and state machine for an automotive transmission controller */

typedef enum {
    GEAR_PARK = 0,
    GEAR_REVERSE,
    GEAR_NEUTRAL,
    GEAR_DRIVE,
    GEAR_FIRST,
    GEAR_SECOND,
    GEAR_THIRD,
    GEAR_UNKNOWN
} Gear_PositionType;

typedef enum {
    GEAR_OK = 0,
    GEAR_ERR = 1,
    GEAR_TIMEOUT = 2
} Gear_ReturnType;

typedef struct {
    Gear_PositionType current;
    Gear_PositionType requested;
    bool initialized;
} Gear_HandleType;

Gear_ReturnType Gear_Init(Gear_HandleType *h);
Gear_ReturnType Gear_SetPosition(Gear_HandleType *h, Gear_PositionType pos);
Gear_PositionType Gear_GetPosition(Gear_HandleType *h);
Gear_ReturnType Gear_UpdateState(Gear_HandleType *h, uint32_t dt_ms);

#endif /* GEAR_H */
