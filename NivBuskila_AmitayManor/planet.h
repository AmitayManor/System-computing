#ifndef PLANET_H
#define PLANET_H

#include "location.h"

#define MAX_PLANET_NAME 50

typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int ID;
    int riskLevel;
} Planet;

Planet* create_planet(const char* name, Location location, int ID, int riskLevel);
void free_planet(Planet* planet);

#endif // PLANET_H