#ifndef PLANET_H
#define PLANET_H

#include "macros.h"
#include "location.h"
#include "utility.h"
#define MAX_PLANET_NAME 50


typedef struct SolarSystem SolarSystem;


typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int id;
    int riskLevel;
    int size;
} Planet;

void print_planet(void* p);
Planet* create_planet(SolarSystem* system);
void free_planet(Planet* planet);
void rename_planet(Planet* planet);

#endif // PLANET_H