#include "planet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Planet* create_planet() {
    Planet* newPlanet = (Planet*)malloc(sizeof(Planet));
    if (newPlanet == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    // Initialize ID and riskLevel to 0
    newPlanet->ID = 0;
    newPlanet->riskLevel = 0;

    // Prompt the user for the planet's name
    printf("Enter the name of the planet: ");
    myGets(newPlanet->name, MAX_PLANET_NAME);

    // Prompt the user for the planet's location
    printf("Enter the planet's location coordinates (x y z): ");
    scanf("%d %d %d", &newPlanet->portal_location.x, &newPlanet->portal_location.y, &newPlanet->portal_location.z);

    // Flush stdin to clear any leftover input
    flush_stdin();

    return newPlanet;
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
    
    free(planet);
}
