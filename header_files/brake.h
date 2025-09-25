#ifndef BRAKE_H
#define BRAKE_H

#include <stdint.h>
#include <stdbool.h>

/* Brake ECU - ABS + braking command management (simplified) */

typedef enum {
    BRAKE_OK = 0,
    BRAKE_FAULT_SENSOR,
    BRAKE_FAULT_ACTUATOR
} Brake_StatusType;

typedef struct {
    bool initialized;
    uint16_t pressure_kPa; /* current hydraulic pressure */
    bool absEngaged;
} Brake_HandleType;

Brake_StatusType Brake_Init(Brake_HandleType *h);
Brake_StatusType Brake_SetPressure(Brake_HandleType *h, uint16_t pressure_kPa);
Brake_StatusType Brake_ApplyABS(Brake_HandleType *h, bool enable);

#endif /* BRAKE_H */