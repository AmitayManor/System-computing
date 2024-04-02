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

void display_system(Galaxy* galaxy) {
    // Displaying galaxy and its solar systems
}

void add_solar_system(Galaxy* galaxy) {
    // Adding a new solar system to the galaxy
}

void display_subcomponents(Galaxy* galaxy) {
    // Displaying planets in each solar system of the galaxy
}

void add_planet(Galaxy* galaxy) {
    // Adding a new planet to a solar system in the galaxy
}

void display_all_planets(Galaxy* galaxy) {
    // Displaying all planets in the galaxy
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
