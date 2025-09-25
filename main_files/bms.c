#include "bms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BMS_StatusType BMS_Init(BMS_HandleType *h, uint8_t cells) {
    if (h == NULL) return BMS_FAULT_COMM;
    if (cells == 0 || cells > BMS_MAX_CELLS) return BMS_FAULT_COMM;
    h->cellCount = cells;
    memset(h->cellVoltage_mV, 0, sizeof(uint16_t)*BMS_MAX_CELLS);
    memset(h->cellTemp_dC, 0, sizeof(int16_t)*BMS_MAX_CELLS);
    h->packCurrent_mA = 0;
    h->status = BMS_OK;
    h->initialized = true;
    return BMS_OK;
}

/* Simulated measurement update - replace with ADC/CAN reads in real system */
BMS_StatusType BMS_UpdateMeasurements(BMS_HandleType *h) {
    if (h == NULL || !h->initialized) return BMS_FAULT_COMM;
    for (uint8_t i = 0; i < h->cellCount; ++i) {
        /* produce synthetic voltages 3600mV..4200mV */
        h->cellVoltage_mV[i] = 3600 + (rand() % 601);
        h->cellTemp_dC[i] = 200 + (rand() % 151) - 50; /* -0.5 to +1.0 C approx scaled representation */
    }
    /* simulate pack current */
    h->packCurrent_mA = (rand() % 50000) - 25000; /* -25A .. +25A */
    return BMS_RunDiagnostics(h);
}

int BMS_CalcSOC(const BMS_HandleType *h) {
    if (h == NULL || !h->initialized) return -1;
    /* Very crude SOC estimate: map average cell voltage between 3.2V and 4.2V */
    uint32_t vsum = 0;
    for (uint8_t i = 0; i < h->cellCount; ++i) vsum += h->cellVoltage_mV[i];
    uint32_t avg = vsum / h->cellCount;
    if (avg <= 3200) return 0;
    if (avg >= 4200) return 100;
    int soc = (int)(((avg - 3200) * 100) / 1000);
    return soc;
}

BMS_StatusType BMS_RunDiagnostics(BMS_HandleType *h) {
    if (h == NULL || !h->initialized) return BMS_FAULT_COMM;
    h->status = BMS_OK;
    for (uint8_t i = 0; i < h->cellCount; ++i) {
        if (h->cellVoltage_mV[i] > 4200) { h->status = BMS_FAULT_OVERVOLTAGE; break; }
        if (h->cellVoltage_mV[i] < 3000) { h->status = BMS_FAULT_UNDERVOLTAGE; break; }
        if (h->cellTemp_dC[i] > 600) { h->status = BMS_FAULT_OVERTEMP; break; }
        if (h->cellTemp_dC[i] < -400) { h->status = BMS_FAULT_UNDERTEMP; break; }
    }
    return h->status;
}

/* Additional BMS helper APIs */

/* Calculate min/max cell voltages */
void BMS_GetCellMinMax(const BMS_HandleType *h, uint16_t *min_mV, uint16_t *max_mV) {
    if (h == NULL || !h->initialized) { *min_mV = 0; *max_mV = 0; return; }
    uint16_t minv = 0xFFFFu, maxv = 0;
    for (uint8_t i = 0; i < h->cellCount; ++i) {
        if (h->cellVoltage_mV[i] < minv) minv = h->cellVoltage_mV[i];
        if (h->cellVoltage_mV[i] > maxv) maxv = h->cellVoltage_mV[i];
    }
    *min_mV = minv; *max_mV = maxv;
}

/* Pack balancing control (stub) */
void BMS_ControlBalancing(BMS_HandleType *h) {
    if (h == NULL || !h->initialized) return;
    /* Example: if cell voltage > 4150mV, request balancing on that cell */
    for (uint8_t i = 0; i < h->cellCount; ++i) {
        if (h->cellVoltage_mV[i] > 4150) {
            /* request bleed resistor on cell i */
            printf("BMS: request balance on cell %d\n", i);
        }
    }
}

/* unit test harness for BMS */
#ifdef BMS_UNIT_TEST
#include <unistd.h>
int main(void) {
    BMS_HandleType bh;
    BMS_Init(&bh, 8);
    for (int k=0;k<10;++k) {
        BMS_UpdateMeasurements(&bh);
        int soc = BMS_CalcSOC(&bh);
        printf("SOC=%d status=%d current=%d mA\n", soc, bh.status, bh.packCurrent_mA);
        sleep(1);
    }
    return 0;
}
#endif