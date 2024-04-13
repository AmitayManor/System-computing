#ifndef PLANET_H
#define PLANET_H

#include "location.h"
#include "utility.h"

typedef struct SolarSystem SolarSystem;

#define MAX_PLANET_NAME 50

typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int id;
    int riskLevel;
    int size;
} Planet;

typedef struct PlanetNode {
    Planet* planet;
    struct PlanetNode* next;
} PlanetNode;

Planet* create_planet(SolarSystem* solarSystem);
void free_planet(Planet* planet);
void rename_planet(Planet* planet);

#endif // PLANET_H