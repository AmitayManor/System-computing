#include "solar_system.h"
#include <stdlib.h>
#include <stdio.h>

SolarSystem* create_solar_system() {
    SolarSystem* system = malloc(sizeof(SolarSystem));
    if (system) {
        printf("Enter Solar System Name: ");
        if (!myGets(system->name, MAX_SOLAR_SYSTEM_NAME)) {
            fprintf(stderr, "Failed to read Solar System name.\n");
            free(system);
            return NULL;
        }
        system->portal_location = (Location){ 0, 0, 0 };
        system->risk_level = 0;
        system->num_planets = 0;
        for (int i = 0; i < MAX_STAR_SYSTEMS; i++) {
            system->planets[i] = NULL;
        }
    }
    else {
        fprintf(stderr, "Memory allocation failed for SolarSystem.\n");
    }
    return system;
}

void add_planet_to_solar_system(SolarSystem* system, Planet* planet) {
    if (system->num_planets < MAX_STAR_SYSTEMS) {
        system->planets[system->num_planets++] = planet;
    }
    else {
        fprintf(stderr, "SolarSystem has reached its maximum capacity of planets.\n");
    }
}

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
