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
        system->risk_level = 0;
        system->num_planets = 0;
        for (int i = 0; i < MAX_STAR_SYSTEMS; i++) {
            system->planets[i] = NULL;
        }
        printf("Enter the solar system location coordinates (x y z): ");
        scanf("%d %d %d", &system->portal_location.x, &system->portal_location.y, &system->portal_location.z);
        printf("Enter the solar system radius: ");
        scanf("%d", &system->radius);
        // Flush stdin to clear any leftover input
        flush_stdin();

    }
    else {
        fprintf(stderr, "Memory allocation failed for SolarSystem.\n");
    }
    return system;
}
int isPlanetWithinSolarSystem(SolarSystem* solarSystem , Planet* planet) {
    // Calculate the distance between the planet and the solar system's portal location
    double distance = calculateDistance(planet->portal_location, solarSystem->portal_location);

    // Check if the distance is within the solar system's radius
    if (distance <= solarSystem->radius) {
        return 1;  // The planet is within the solar system
    }
    else {
        return 0;  // The planet is outside the solar system
    }
}
void add_planet_to_solar_system(SolarSystem* system, Planet* planet) {
    if (!isPlanetWithinSolarSystem(system, planet))
    {
        printf("The planet is outside the solar system radius.\n");
    }
    else
    {

         if (system->num_planets < MAX_STAR_SYSTEMS) {
        system->planets[system->num_planets++] = planet;
        printf("New planet '%s' added successfully to %s solar system.\n", planet->name, system->name);
            }
            else {
                fprintf(stderr, "SolarSystem has reached its maximum capacity of planets.\n");
            }
    
         }
}

void display_solar_system(const SolarSystem* system) {
    if (system) {
        printf("Solar System Name: %s\n", system->name);
        printf("Number of Planets: %d\n", system->num_planets);
        // Additional details can be displayed here
    }
}


void rename_solarSystem(SolarSystem* system) {
    if (!system) {
        printf("Invalid input.\n");
        return;
    }

    char newName[MAX_SOLAR_SYSTEM_NAME];
    printf("Enter new name for the Solar System: ");
    if (myGets(newName, MAX_SOLAR_SYSTEM_NAME)) {
        strncpy(system->name, newName, MAX_SOLAR_SYSTEM_NAME - 1);
        system->name[MAX_SOLAR_SYSTEM_NAME - 1] = '\0';
        printf("Solar System successfully renamed to %s.\n", system->name);
    }
    else {
        printf("Failed to read new name.\n");
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
