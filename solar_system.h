#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H
#include "utility.h"
#include "planet.h"

#define MAX_STAR_SYSTEMS 10
#define MAX_SOLAR_SYSTEM_NAME 50
typedef struct SolarSystem {
    char name[MAX_SOLAR_SYSTEM_NAME];
    Location portal_location;
    int risk_level;
    Planet* planets[MAX_STAR_SYSTEMS];
    int num_planets;
} SolarSystem;

void display_solar_system(const SolarSystem* system);
void free_solar_system(SolarSystem* system);
SolarSystem* create_solar_system();
void add_planet_to_solar_system(SolarSystem* system, Planet* planet);



#endif // SOLAR_SYSTEM_H