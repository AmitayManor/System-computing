#include "planet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_planet(void* p) {
    Planet* planet = (Planet*)p;
    printf("Planet ID: %d, Name: %s, Risk Level: %d\n", planet->id, planet->name, planet->riskLevel);
}

Planet* create_planet(SolarSystem* system) {
    Planet* newPlanet = ALLOCATE(Planet*, 1);
//    Planet* newPlanet = (Planet*)malloc(sizeof(Planet));
    if (newPlanet == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    printf("Enter the name for the Planet (up to %d characters): ", MAX_PLANET_NAME - 1);

    // Use myGets to safely read the name into the galaxy's name field
    if (!myGets(newPlanet->name, MAX_PLANET_NAME)) {
        LOG_DEBUG("Failed to read Planet name or input was empty.\n");
//        fprintf(stderr, "Failed to read Planet name or input was empty.\n");
        free(newPlanet);  // Cleanup the allocated memory if input fails
        return NULL;
    }
       
    newPlanet->riskLevel = 0;

    int idFlag = 0;
    int id;
    do {
        printf("Enter the Planet ID (1-9999): ");
        scanf("%d", &id);
        if (check_unique_planet_id(system, id) && id > 0 && id < 10000) {
            idFlag = 1;
            newPlanet->id = id;
        }
        else
            printf("\nError! ID is not valid. Try again.\n");

    } while (!idFlag);

    int locFlag = 0;
    do {
        printf("Enter the Planet location coordinates (x y z): ");
        scanf("%d %d %d", &newPlanet->portal_location.x, &newPlanet->portal_location.y, &newPlanet->portal_location.z);
        if (check_unique_planet_location(system, newPlanet->portal_location))
            locFlag = 1;
        else
            printf("\nError! Location is not valid. Try again.\n");
    } while (!locFlag);

    int radiusFalg = 0;
    do {
        printf("Enter the Galaxy radius: ");
        scanf("%d", &newPlanet->size);
        if (newPlanet->size > 0)
            radiusFalg = 1;
    } while (!radiusFalg);

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
