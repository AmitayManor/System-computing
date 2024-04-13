#include "galaxy.h"
#include <stdlib.h>
#include <stdio.h>

void load_galaxy_from_binary(FILE* file, Galaxy* galaxy) {
    // Binary file reading logic
}

void save_galaxy_to_binary(FILE* file, Galaxy* galaxy) {
    // Binary file writing logic
}

void save_galaxy_to_text(FILE* file, Galaxy* galaxy) {
    // Text file writing logic
}

void load_galaxy_from_text(FILE* file, Galaxy* galaxy) {
    // Text file reading logic
}

void sort_solar_systems(Galaxy* galaxy, int sort_choice) {
    // Sorting logic based on sort_choice
}


void display_solar_systems(Galaxy* galaxy) {
    printf("Galaxy Name: %s\n", galaxy->name);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        printf("%d. ", i + 1);
        display_solar_system(galaxy->star_systems[i]);
    }
}


void add_solar_system(Galaxy* galaxy) {
    if (!galaxy) {
        printf("Error: No galaxy provided.\n");
        return;
    }

    SolarSystem* newSystem = create_solar_system(galaxy);
    if (newSystem) {
        
        SolarSystem** temp = realloc(galaxy->star_systems, (galaxy->num_solar_systems + 1) * sizeof(SolarSystem*));
        if (temp == NULL) {
            printf("Failed to allocate memory for new solar system.\n");
            free_solar_system(newSystem);  
            return;
        }

        galaxy->star_systems = temp;
        galaxy->star_systems[galaxy->num_solar_systems] = newSystem;  
        galaxy->num_solar_systems++; 
        printf("Solar System '%s' added successfully to Galaxy '%s'.\n", newSystem->name, galaxy->name);

    }
    else {
        printf("Failed to create a new Solar System.\n");
    }
}



void free_galaxy(Galaxy* galaxy) {
    if (galaxy) {
        free(galaxy->name);
        for (int i = 0; i < galaxy->num_solar_systems; i++) {
            free_solar_system(galaxy->star_systems[i]);
        }
        free(galaxy->star_systems);
        free(galaxy);
    }
}

Galaxy* create_galaxy(UniversalManager* manager) {
    Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));
    if (!galaxy) {
        fprintf(stderr, "Failed to allocate memory for Galaxy.\n");
        return NULL;
    }
    galaxy->num_solar_systems = 0;
    galaxy->riskLevel = 0;
    galaxy->star_systems = NULL;

    printf("Enter the name for the galaxy (up to %d characters): ", MAX_GALAXY_NAME - 1);
    if (!myGets(galaxy->name, MAX_GALAXY_NAME)) {
        fprintf(stderr, "Failed to read Galaxy name.\n");
        free(galaxy);
        return NULL;
    }
    int id;
    do {
        printf("Enter Galaxy ID (1-9999): ");
        scanf("%d", &id);
        flush_stdin();
        if (!isGalaxyIDUnique(manager, id)) {
            printf("This ID is already in use. Please enter a unique ID.\n");
        }
        else {
            galaxy->id = id;
            break;
        }
    } while (1);
    Location loc;
    printf("Enter location coordinates (x y z): ");
    scanf("%d %d %d", &loc.x, &loc.y, &loc.z);
    while (getchar() != '\n'); 

    if (!isGalaxyLocationUnique(manager, loc)) {
        printf("This location is already occupied. Please enter a unique location.\n");
        free(galaxy);
        return;
    }

    galaxy->portal_location = loc;
    printf("Enter the Galaxy radius: ");
    scanf("%d", &galaxy->radius);
    flush_stdin();

    printf("Galaxy '%s' has been created.\n", galaxy->name);

    return galaxy;
}

void rename_galaxy(Galaxy* galaxy)
{
    if (!galaxy) {
        printf("Invalid input.\n");
        return;
    }

    char newName[MAX_GALAXY_NAME];
    printf("Enter new name for the Galaxy: ");
    if (myGets(newName, MAX_GALAXY_NAME)) {
        strncpy(galaxy->name, newName, MAX_GALAXY_NAME - 1);
        galaxy->name[MAX_GALAXY_NAME - 1] = '\0';
        printf("Galaxy successfully renamed to %s.\n", galaxy->name);
    }
    else {
        printf("Failed to read new name.\n");
    }
}


int isSolarSystemIDUnique(const Galaxy* galaxy, int id) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (galaxy->star_systems[i]->id == id) {
            return 0;  // ID is not unique
        }
    }
    return 1;  // ID is unique
}
int isSolarSystemLocationUnique(const Galaxy* galaxy, Location loc) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (isSameLocation(galaxy->star_systems[i]->portal_location, loc)) {
            return 0;  // Location is not unique
        }
    }
    return 1;  // Location is unique
}
int isSolarSystemWithinGalaxy(Galaxy* galaxy, Location newSystemLoc) {
    double distance = calculateDistance(galaxy->portal_location, newSystemLoc);
    if (distance <= galaxy->radius) {
        return 1;  // Solar System is within the galaxy's reach
    }
    return 0;  // Solar System is not within the galaxy's reach
}
void updateGalaxyRiskLevel(Galaxy* galaxy) {
    if (galaxy == NULL || galaxy->num_solar_systems == 0) {
        printf("Error: No galaxy provided or no solar systems exist within the galaxy.\n");
        galaxy->riskLevel = 0;  // Default to 0 if no solar systems exist
        return;
    }

    int totalRisk = 0;
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        totalRisk += galaxy->star_systems[i]->risk_level;
    }

    galaxy->riskLevel = totalRisk / galaxy->num_solar_systems;  // Calculate average risk level
    printf("Updated Galaxy '%s' risk level to %d based on its solar systems.\n", galaxy->name, galaxy->riskLevel);
}
