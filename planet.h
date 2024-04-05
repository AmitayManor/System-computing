#ifndef PLANET_H
#define PLANET_H

#include "location.h"
#include "utility.h"
#define MAX_PLANET_NAME 50

typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int ID;
    int riskLevel;
} Planet;

Planet* create_planet();
void free_planet(Planet* planet);
void rename_planet(Planet* planet);

#endif // PLANET_H