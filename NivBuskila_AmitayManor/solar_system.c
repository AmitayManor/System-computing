#include "solar_system.h"
#include <stdlib.h>
#include <stdio.h>

void display_solar_system(const SolarSystem* system) {
    if (system) {
        printf("Solar System Name: %s\n", system->name);
        printf("Number of Planets: %d\n", system->num_planets);
        // Additional details can be displayed here
    }
}

void free_solar_system(SolarSystem* system) {
    if (system) {
        free(system->name);
        for (int i = 0; i < system->num_planets; i++) {
            free_planet(system->planets[i]); // Assumes a free_planet function exists
        }
        free(system);
    }
}
