#ifndef BMS_H
#define BMS_H

#include <stdint.h>
#include <stdbool.h>

/* Battery Management System ECU - monitors cell voltages, pack current, temperature and reports state-of-charge */

#define BMS_MAX_CELLS  16

typedef enum {
    BMS_OK = 0,
    BMS_FAULT_OVERVOLTAGE,
    BMS_FAULT_UNDERTEMP,
    BMS_FAULT_COMM
} BMS_StatusType;

typedef struct {
    uint16_t cellVoltage_mV[BMS_MAX_CELLS];
    int16_t cellTemp_dC[BMS_MAX_CELLS];
    uint8_t cellCount;
    int32_t packCurrent_mA;
    BMS_StatusType status;
    bool initialized;
} BMS_HandleType;

BMS_StatusType BMS_Init(BMS_HandleType *h, uint8_t cells);
BMS_StatusType BMS_UpdateMeasurements(BMS_HandleType *h);
int BMS_CalcSOC(const BMS_HandleType *h);
BMS_StatusType BMS_RunDiagnostics(BMS_HandleType *h);

#endif /* BMS_H */
