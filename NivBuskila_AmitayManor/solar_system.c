#include "solar_system.h"
#include <stdlib.h>
#include <stdio.h>

SolarSystem* create_solar_system(Galaxy* galaxy) {
    if (galaxy == NULL) {
        printf("Error: No galaxy provided.\n");
        return NULL;
    }
    SolarSystem* system = malloc(sizeof(SolarSystem));
    if (system == NULL) {
        fprintf(stderr, "Memory allocation failed for SolarSystem.\n");
        return NULL;
    }

    // Initialize linked list head to NULL
    system->planet_head = NULL;
    system->num_planets = 0;
    system->risk_level = 0;
    // Initialize other properties
    printf("Enter Solar System Name: ");
    if (!myGets(system->name, MAX_SOLAR_SYSTEM_NAME)) {
        fprintf(stderr, "Failed to read Solar System name.\n");
        free(system);
        return NULL;
    }
     int id;
    do {
        printf("Enter Solar System ID (1-9999): ");
        scanf("%d", &id);
        while(getchar() != '\n');  // Clear the input buffer
        if (!isSolarSystemIDUnique(galaxy, id)) {
            printf("This ID is already in use within this galaxy. Please enter a unique ID.\n");
        } else {
            system->id = id;
            break;  // Exit loop if ID is unique
        }
    } while (1);


    Location loc;
    printf("Enter location coordinates (x y z): ");
    scanf("%d %d %d", &loc.x, &loc.y, &loc.z);
    while (getchar() != '\n');  // Clear the input buffer

    if (!isSolarSystemLocationUnique(galaxy, loc) || !isSolarSystemWithinGalaxy(galaxy, loc)) {
        printf("This location is either occupied or out of the reach of the galaxy. Please enter a different location.\n");
        free(system);
        return;
    }

    system->portal_location = loc;
    printf("Enter the solar system radius: ");
    scanf("%d", &system->radius);
    
    // Flush stdin to clear any leftover input
    flush_stdin();

    return system;
}


void add_planet_to_solar_system(SolarSystem* system) {
    if (!system) {
        printf("Error: No solar system provided.\n");
        return;
    }

    Planet* newPlanet = create_planet(system);
    if (newPlanet) {
        // Create a new node for the linked list of planets
        PlanetNode* newNode = malloc(sizeof(PlanetNode));
        if (newNode == NULL) {
            printf("Failed to allocate memory for new planet node.\n");
            free_planet(newPlanet);  // Free newly created planet if node allocation fails
            return;
        }

        newNode->planet = newPlanet;  // Set the planet pointer
        newNode->next = NULL;  // New node will be the last node, so next is NULL

        // Find the last node in the list
        if (system->planet_head == NULL) {
            // If the list is empty, new node is the head
            system->planet_head = newNode;
        }
        else {
            // Traverse to the end of the list and add the new node
            PlanetNode* current = system->planet_head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        system->num_planets++;

        printf("Planet '%s' added successfully to Solar System '%s'.\n", newPlanet->name, system->name);

        updateSolarSystemRiskLevel(system);

    }
    else {
        printf("Failed to create a new Planet.\n");
    }
}

void display_solar_system(const SolarSystem* system) {
    if (system) {
        printf("Solar System Name: %s\n", system->name);
        printf("Number of Planets: %d\n", system->num_planets);

        PlanetNode* current = system->planet_head;
        int planetIndex = 1;
        while (current != NULL) {
            printf("Planet %d: %s\n", planetIndex, current->planet->name);
            current = current->next;
            planetIndex++;
        }
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
        PlanetNode* current = system->planet_head;
        PlanetNode* temp;
        while (current != NULL) {
            temp = current;
            current = current->next;
            free_planet(temp->planet);
            free(temp);
        }
        free(system);
    }
}


int isPlanetIDUnique(const SolarSystem* system, int id) {
    PlanetNode* current = system->planet_head;
    while (current) {
        if (current->planet->id == id) {
            return 0;  // ID is not unique
        }
        current = current->next;
    }
    return 1;  // ID is unique
}

int isPlanetLocationUnique(const SolarSystem* system, Location loc) {
    PlanetNode* current = system->planet_head;
    while (current) {
        if (isSameLocation(current->planet->portal_location, loc)) {
            return 0;  // Location is not unique
        }
        current = current->next;
    }
    return 1;  // Location is unique
}
int isPlanetWithinSolarSystem(SolarSystem* system, Location newPlanetLoc) {
    double distance = calculateDistance(system->portal_location, newPlanetLoc);
    if (distance <= system->radius) {
        return 1;  // Planet is within the solar system's reach
    }
    return 0;  // Planet is not within the solar system's reach
}
void updateSolarSystemRiskLevel(SolarSystem* system) {
    if (system == NULL || system->planet_head == NULL) {
        printf("Error: No solar system provided or no planets exist within the system.\n");
        return;
    }

    int totalRisk = 0;
    int count = 0;
    PlanetNode* current = system->planet_head;

    // Sum all the risk levels of the planets
    while (current != NULL) {
        totalRisk += current->planet->riskLevel;
        count++;
        current = current->next;
    }

    if (count > 0) {
        system->risk_level = totalRisk / count;  // Calculate average risk level
    }
    else {
        system->risk_level = 0;  // Default to 0 if no planets exist
    }

    printf("Updated Solar System '%s' risk level to %d.\n", system->name, system->risk_level);
}
