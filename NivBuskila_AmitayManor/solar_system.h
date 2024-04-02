#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "planet.h"

#define MAX_STAR_SYSTEMS 10

typedef struct SolarSystem {
    char* name;
    Location portal_location;
    int risk_level;
    Planet* planets[MAX_STAR_SYSTEMS];
    int num_planets;
} SolarSystem;

void display_solar_system(const SolarSystem* system);
void free_solar_system(SolarSystem* system);

#endif // SOLAR_SYSTEM_H