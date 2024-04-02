#ifndef GALAXY_H
#define GALAXY_H

#include "location.h"
#include "solar_system.h"
#include <stdio.h>
#define MAX_GALAXY_NAME 100

typedef struct Galaxy {
    char* name;
    Location portal_location;
    SolarSystem** star_systems;
    int num_solar_systems;
    int riskLevel;
} Galaxy;

void load_galaxy_from_binary(FILE* file, Galaxy* galaxy);
void save_galaxy_to_binary(FILE* file, Galaxy* galaxy);
void save_galaxy_to_text(FILE* file, Galaxy* galaxy);
void load_galaxy_from_text(FILE* file, Galaxy* galaxy);
void sort_solar_systems(Galaxy* galaxy, int sort_choice);
void* search_by_name(const void* key, SolarSystem** systems, size_t num_systems);
void* search_by_risk_level(const void* key, SolarSystem** systems, size_t num_systems);
void* search_by_num_planets(const void* key, SolarSystem** systems, size_t num_systems);
void display_system(Galaxy* galaxy);
void add_solar_system(Galaxy* galaxy);
void display_subcomponents(Galaxy* galaxy);
void add_planet(Galaxy* galaxy);
void display_all_planets(Galaxy* galaxy);
void free_galaxy(Galaxy* galaxy);

#endif // GALAXY_H