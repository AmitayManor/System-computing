#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H
#include "utility.h"
#include "planet.h"

#define MAX_STAR_SYSTEMS 10
#define MAX_SOLAR_SYSTEM_NAME 50

typedef struct Galaxy Galaxy;

typedef struct SolarSystem {
    char name[MAX_SOLAR_SYSTEM_NAME];
    Location portal_location;
    int risk_level;
    PlanetNode* planet_head;  // head of the linked list of planets
    int num_planets;
    int radius;
    int id;
} SolarSystem;

void display_solar_system(const SolarSystem* system);
void free_solar_system(SolarSystem* system);
SolarSystem* create_solar_system(Galaxy* galaxy);
void add_planet_to_solar_system(SolarSystem* system);
void rename_solarSystem(SolarSystem* system);



int isPlanetIDUnique(const SolarSystem* system, int id);
int isPlanetLocationUnique(const SolarSystem* system, Location loc);
int isPlanetWithinSolarSystem(SolarSystem* system, Location newPlanetLoc);
void updateSolarSystemRiskLevel(SolarSystem* system);
#endif // SOLAR_SYSTEM_H