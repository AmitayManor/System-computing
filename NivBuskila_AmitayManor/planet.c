#include "planet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Planet* create_planet(SolarSystem* solarSystem) {
    if (solarSystem == NULL) {
        printf("Error: No solar system provided.\n");
        return NULL;
    }
    Planet* newPlanet = (Planet*)malloc(sizeof(Planet));
    if (newPlanet == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

  
    // Prompt the user for the planet's name
    printf("Enter the name of the planet: ");
    myGets(newPlanet->name, MAX_PLANET_NAME);

    int id;
    do {
        printf("Enter Planet ID (1-9999): ");
        scanf("%d", &id);
        while (getchar() != '\n');  // Clear the input buffer
        if (!isPlanetIDUnique(solarSystem, id)) {
            printf("This ID is already in use within this solar system. Please enter a unique ID.\n");
        }
        else {
            newPlanet->id = id;
            break;  // Exit loop if ID is unique
        }
    } while (1);

    printf("Enter the size of the planet: ");
    scanf("%d", &newPlanet->size);
    while (getchar() != '\n');  // Clear the input buffer
    // input the user for the planet's location
    Location loc;
    printf("Enter location coordinates (x y z): ");
    scanf("%d %d %d", &loc.x, &loc.y, &loc.z);
    while (getchar() != '\n');  // Clear the input buffer

    if (!isPlanetLocationUnique(solarSystem, loc) || !isPlanetWithinSolarSystem(solarSystem, loc)) {
        printf("This location is either occupied or out of the reach of the solar system. Please enter a different location.\n");
        free(newPlanet);
        return;
    }

    newPlanet->portal_location = loc;

    int riskLevel;
    do {
        printf("Enter the risk level (1-5): ");
        scanf("%d", &riskLevel);
        while (getchar() != '\n');  // Clear the input buffer
        if (riskLevel < 1 || riskLevel > 5) {
            printf("Invalid risk level. Please enter a value between 1 and 5.\n");
        }
        else {
            newPlanet->riskLevel = riskLevel;
            break;  // Exit loop if risk level is valid
        }
    } while (1);


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
