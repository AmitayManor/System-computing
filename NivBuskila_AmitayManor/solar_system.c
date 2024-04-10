#include "solar_system.h"
#include <stdlib.h>
#include <stdio.h>

void addPlanet(SolarSystem* system, Planet* planet) {
    PlanetNode* newNode = ALLOCATE(PlanetNode*, 1);
//    PlanetNode* newNode = (PlanetNode*)malloc(sizeof(PlanetNode));
    if (newNode == NULL) {
        printf("Failed to allocate memory for the new planet node.\n");
        return;
    }

    // Assign the planet to the node and insert it at the head of the list
    newNode->planet = planet;
    newNode->next = system->planetsHead;
    system->planetsHead = newNode;
}

void removePlanet(SolarSystem* system, int planetID) {
   
    PlanetNode* current = system->planetsHead;
    PlanetNode* prev = NULL;

    while (current != NULL) {
        Planet* p = (Planet*)current->planet;
        if (p->id == planetID) {
            if (prev == NULL) {
                system->planetsHead = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            system->num_planets--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void freePlanetList(SolarSystem* system) {
    
    PlanetNode* current = system->planetsHead;
    while (current != NULL) {
        PlanetNode* temp = current;
        current = current->next;
        free(temp);
    }
    system->planetsHead = NULL;  // Ensure the head is NULL after freeing
    system->num_planets = 0;
}



void print_solar_system(void* ss) {
    SolarSystem* system = (SolarSystem*)ss;
    printf("Solar System ID: %d, Name: %s, Number of Planets: %d\n", system->id, system->name, system->num_planets);
    
    PlanetNode* current = system->planetsHead; // Start with the head of the linked list
    while (current != NULL) {

        generic_print(current->planet, print_planet); 
        current = current->next; 
    }
}

SolarSystem* create_solar_system(Galaxy* galaxy) {
    SolarSystem* system = ALLOCATE(SolarSystem*, 1);
//    SolarSystem* system = malloc(sizeof(SolarSystem));
    if (system) {
       
        printf("Enter Solar System Name: ");
        if (!myGets(system->name, MAX_SOLAR_SYSTEM_NAME)) {
            LOG_DEBUG("Failed to read Solar System name.\n");
//            fprintf(stderr, "Failed to read Solar System name.\n");
            free(system);
            return NULL;
        }
        system->risk_level = 0;
        system->num_planets = 0;
        system->planetsHead = NULL; 
        system->num_planets = 0;

        int idFlag = 0;
        int id;
        do {
            printf("Enter the Solar System ID (1-9999): ");
            scanf("%d", &id);
            if (check_unique_solarSystem_id(galaxy, id) && id > 0 && id < 10000) {
                idFlag = 1;
                system->id = id;
            }
            else
                printf("\nError! ID is not valid. Try again.\n");

        } while (!idFlag);

        int locFlag = 0;
        do {
            printf("Enter the Solar System location coordinates (x y z): ");
            scanf("%d %d %d", &system->portal_location.x, &system->portal_location.y, &system->portal_location.z);

            if (check_unique_solarSystem_location(galaxy, system->portal_location))
                locFlag = 1;
            else
                printf("\nError! Location is not valid. Try again.\n");

        } while (!locFlag);

        int radiusFalg = 0;
        do {
            printf("Enter the Solar System radius: ");
            scanf("%d", &system->size);
            if (system->size > 0 && isSolarSystemWithinGalaxy(galaxy, system))
                radiusFalg = 1;
            else
                printf("\nError! Radius is not valid. Try again.\n");
        } while (!radiusFalg);

    }
    else {
        LOG_DEBUG("Memory allocation failed for SolarSystem.\n");
//        fprintf(stderr, "Memory allocation failed for SolarSystem.\n");
    }
    return system;
}

int isPlanetWithinSolarSystem(SolarSystem* solarSystem , Planet* planet) {

    double distance = calculateDistance(planet->portal_location, solarSystem->portal_location);

    if (distance <= solarSystem->size) return 1;  
   
    else return 0;  
    
}

/*  Needs do-while loop 
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
}*/

void display_solar_system(const SolarSystem* system) {
    if (system) {
        printf("Solar System Name: %s\n", system->name);
        printf("Solar System ID: %d\n", system->id);
        printf("Number of Planets: %d\n", system->num_planets);
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

int check_unique_planet_id(SolarSystem* sSystem, int id) {
    if (!sSystem || !sSystem->planetsHead || sSystem->num_planets <= 0)
        return 1;

    PlanetNode* current = sSystem->planetsHead;
    while (current != NULL) {
        Planet* planet = (Planet*)current->planet;
        if (planet->id == id) {
            return 0;  
        }
        current = current->next; 
    }
    return 1;
}

int check_unique_planet_location(SolarSystem* sSystem, Location planetLoc) {
    if (!sSystem || !sSystem->planetsHead || sSystem->num_planets <= 0)
        return 1;

    PlanetNode* current = sSystem->planetsHead;
    while (current != NULL) {
        Planet* planet = (Planet*)current->planet;
        if (isSameLocation(planet->portal_location, planetLoc)) {
            return 0;  
        }
        current = current->next;  
    }
    return 1;
}

void free_solar_system(SolarSystem* system) {
    if (system) {
       
        freePlanetList(system);
        free(system);
    }
}
