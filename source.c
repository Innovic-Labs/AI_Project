#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// headerfiles
// ---------------------- Instrument Cluster Simulation ----------------------
//workflow
// Global vehicle state
typedef struct {
    int speed;        // km/h
    int rpm;          // revolutions per minute
    int fuelLevel;    // percentage (0-100)
    int odometer;     // total distance in km
    bool engineOn;    // engine status
    bool lowFuel;     // warning light
    bool seatBelt;    // warning light
} VehicleState;

// Function prototypes
void initVehicle(VehicleState *v);
void updateVehicle(VehicleState *v);
void displayCluster(const VehicleState *v);
void checkWarnings(VehicleState *v);
void simulateDrive(VehicleState *v, int duration);

// ---------------------- Main ----------------------
int main() {
    VehicleState car;
    initVehicle(&car);

    printf("=== Automotive Instrument Cluster Simulation ===\n\n");
    simulateDrive(&car, 15); // simulate 15 seconds of driving
    printf("\n=== Drive Ended ===\n");
    return 0;
}

// ---------------------- Function Definitions ----------------------

// Initialize default vehicle state
void initVehicle(VehicleState *v) {
    v->speed = 0;
    v->rpm = 0;
    v->fuelLevel = 100;
    v->odometer = 0;
    v->engineOn = true;
    v->lowFuel = false;
    v->seatBelt = true; // assume driver wears seatbelt
}

// Random changes to simulate driving
void updateVehicle(VehicleState *v) {
    if (!v->engineOn) {
        v->speed = 0;
        v->rpm = 0;
        return;
    }

    // Simulate acceleration & braking
    int change = (rand() % 21) - 10; // -10 to +10 km/h
    v->speed += change;
    if (v->speed < 0) v->speed = 0;
    if (v->speed > 180) v->speed = 180;

    // Approximate RPM as proportional to speed
    v->rpm = v->speed * 50;
    if (v->rpm > 7000) v->rpm = 7000;

    // Fuel consumption
    v->fuelLevel -= (rand() % 3); // 0-2% per tick
    if (v->fuelLevel < 0) v->fuelLevel = 0;

    // Odometer update
    v->odometer += v->speed / 10; // approx km per tick

    // Check warnings
    checkWarnings(v);
}

// Show cluster values on console
void displayCluster(const VehicleState *v) {
    printf("Speed: %3d km/h | RPM: %4d | Fuel: %3d%% | Odo: %5d km ",
           v->speed, v->rpm, v->fuelLevel, v->odometer);

    // Warning indicators
    if (v->lowFuel)  printf("| [LOW FUEL] ");
    if (!v->seatBelt) printf("| [SEATBELT WARNING] ");
    printf("\n");
}

// Check for warning lights
void checkWarnings(VehicleState *v) {
    v->lowFuel = (v->fuelLevel <= 15);
    // Random seatbelt unbuckling for demo
    v->seatBelt = (rand() % 20 != 0); // 1/20 chance unbuckled
}

// Simulate driving for duration seconds
void simulateDrive(VehicleState *v, int duration) {
    srand(time(NULL));
    for (int i = 0; i < duration; i++) {
        updateVehicle(v);
        displayCluster(v);
        sleep(1); // delay to simulate time passing
    }
}
