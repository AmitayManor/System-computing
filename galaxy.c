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
        display_solar_system(galaxy->star_systems[i]);
    }
}


void add_solar_system(Galaxy* galaxy) {
    if (!galaxy) {
        fprintf(stderr, "Galaxy pointer is NULL.\n");
        return;
    }

    // Allocate memory for the new Solar System
    SolarSystem* system = create_solar_system();
  

    // Reallocate the galaxy's star_systems array to accommodate the new Solar System
    SolarSystem** new_array = realloc(galaxy->star_systems, (galaxy->num_solar_systems + 1) * sizeof(SolarSystem*));
    if (!new_array) {
        fprintf(stderr, "Failed to reallocate memory for new solar systems.\n");
        free(system);
        return;
    }

    // Update galaxy's star_systems with the new array and increment the count
    galaxy->star_systems = new_array;
    galaxy->star_systems[galaxy->num_solar_systems] = system;
    galaxy->num_solar_systems++;
    printf("New Solar System '%s' added successfully to %s galaxy.\n", system->name, galaxy->name);
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

Galaxy* create_galaxy() {
    // Allocate memory for the new Galaxy object
    Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));
    if (!galaxy) {
        fprintf(stderr, "Failed to allocate memory for Galaxy.\n");
        return NULL;
    }

    // Prompt the user for the Galaxy name
    printf("Enter the name for the galaxy (up to %d characters): ", MAX_GALAXY_NAME - 1);

    // Use myGets to safely read the name into the galaxy's name field
    if (!myGets(galaxy->name, MAX_GALAXY_NAME)) {
        fprintf(stderr, "Failed to read Galaxy name or input was empty.\n");
        free(galaxy);  // Cleanup the allocated memory if input fails
        return NULL;
    }
    galaxy->num_solar_systems = 0;
    galaxy->star_systems = NULL;

    printf("Galaxy '%s' has been created.\n", galaxy->name);

    // Return the pointer to the newly created and initialized Galaxy object
    return galaxy;
}
