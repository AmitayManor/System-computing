#include "planet.h"
#include <stdlib.h>
#include <string.h>

Planet* create_planet(const char* name, Location location, int ID, int riskLevel) {
    Planet* new_planet = (Planet*)malloc(sizeof(Planet));
    if (new_planet) {
        strncpy(new_planet->name, name, MAX_PLANET_NAME - 1);
        new_planet->name[MAX_PLANET_NAME - 1] = '\0'; // Ensure null termination
        new_planet->portal_location = location;
        new_planet->ID = ID;
        new_planet->riskLevel = riskLevel;
    }
    return new_planet;
}
void rename_planet(Planet* planet) {
    if (!planet) {
        printf("Invalid input.\n");
        return;
    }

    char newName[MAX_PLANET_NAME];
    printf("Enter new name for the planet: ");
    if (myGets(newName, MAX_PLANET_NAME)) {
        strncpy(planet->name, newName, MAX_PLANET_NAME - 1);
        planet->name[MAX_PLANET_NAME - 1] = '\0';
        printf("Planet successfully renamed to %s.\n", planet->name);
    }
    else {
        printf("Failed to read new name.\n");
    }
}
void free_planet(Planet* planet) {
    // No dynamic memory inside Planet, just free the planet itself
    free(planet);
}
