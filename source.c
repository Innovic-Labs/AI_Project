#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
// ---------------------- Instrument Cluster Simulation ----------------------
//workflow


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
//function
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
// Simulate driving for duration second
    }
}
