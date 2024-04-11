#include "galaxy.h"

#include <stdlib.h>
#include <stdio.h>

void print_galaxy(void* g) {
    Galaxy* galaxy = (Galaxy*)g;
    printf("Galaxy ID: %d, Name: %s, Number of Solar Systems: %d\n", galaxy->id, galaxy->name, galaxy->num_solar_systems);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        generic_print(galaxy->star_systems[i], print_solar_system);  // Use generic_print for each solar system
    }
}

int check_unique_solarSystem_id(Galaxy* galaxy, int id) {
    if (!galaxy || !galaxy->star_systems || galaxy->num_solar_systems <= 0)
        return 1;

    for (int i = 0; i < galaxy->num_solar_systems; ++i) {
        if (galaxy->star_systems[i]->id == id)
            return 0;
    }
    return 1;
}

int check_unique_solarSystem_location(Galaxy* galaxy, Location sSytemLoc) {
    if (!galaxy || !galaxy->star_systems || galaxy->num_solar_systems <= 0)
        return 1;
    for (int i = 0; i < galaxy->num_solar_systems; ++i) {
        if (isSameLocation(galaxy->star_systems[i]->portal_location, sSytemLoc))
            return 0;
    }
    return 1;
}

void display_solar_systems(Galaxy* galaxy) {
    printf("Galaxy Name: \n", galaxy->name);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        printf("%d. ", i + 1);
        display_solar_system(galaxy->star_systems[i]);
    }
}

void add_solar_system(Galaxy* galaxy) {
    if (!galaxy) {
        LOG_DEBUG("Galaxy pointer is NULL.\n");
        //fprintf(stderr, "Galaxy pointer is NULL.\n");
        return;
    }
    
  
    else
    {   
        SolarSystem* system = create_solar_system(galaxy);

        SolarSystem** new_array = realloc(galaxy->star_systems, (galaxy->num_solar_systems + 1) * sizeof(SolarSystem*));
               
        if (!new_array) {
            LOG_DEBUG("Failed to reallocate memory for new solar systems.\n");
//            fprintf(stderr, "Failed to reallocate memory for new solar systems.\n");
            free(system);
            return;
        }

        galaxy->star_systems = new_array;
        galaxy->star_systems[galaxy->num_solar_systems] = system;
        galaxy->num_solar_systems++;
        printf("New Solar System '%s' added successfully to %s galaxy.\n", system->name, galaxy->name);
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

Galaxy* create_galaxy(UniversalManager* mg) {

    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    //Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));
    if (!galaxy) {
        LOG_DEBUG("Failed to allocate memory for Galaxy.\n");
        //fprintf(stderr, "Failed to allocate memory for Galaxy.\n");
        return NULL;
    }

    printf("Enter the name for the galaxy (up to %d characters): ", MAX_GALAXY_NAME - 1);
    
    if (!myGets(galaxy->name, MAX_GALAXY_NAME)) {
        LOG_DEBUG("Failed to read Galaxy name or input was empty.\n");
        //fprintf(stderr, "Failed to read Galaxy name or input was empty.\n");
        free(galaxy);  
        return NULL;
    }
    galaxy->num_solar_systems = 0;
    galaxy->star_systems = NULL;
    
    int idFlag = 0;
    int id;
    do {
        printf("Enter the Galaxy ID (1-9999): ");
        scanf("%d", &id);
        if (check_unique_galaxy_id(mg, id) && id > 0 && id < 10000) {
            idFlag = 1;
            galaxy->id = id;
        }
        else
            printf("\nError! ID is not valid. Try again.\n");
      
    } while (!idFlag);


    int locFlag = 0;
    do {
        printf("Enter the Galaxy location coordinates (x y z): ");
        scanf("%d %d %d", &galaxy->portal_location.x, &galaxy->portal_location.y, &galaxy->portal_location.z);
        if (check_unique_galaxy_location(mg, galaxy->portal_location))
            locFlag = 1;
        else
            printf("\nError! Location is not valid. Try again.\n");
    } while (!locFlag);

    int radiusFalg = 0;
    do {
        printf("Enter the Galaxy radius: ");
        scanf("%d", &galaxy->size);
        if (galaxy->size > 0)
            radiusFalg = 1;
    } while (!radiusFalg);
    
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

int isSolarSystemWithinGalaxy(Galaxy* galaxy, SolarSystem* system)
{
    double distance = calculateDistance(system->portal_location, galaxy->portal_location);
    
    double gRadius = (double)galaxy->size;

    if (system->size >= fabs(gRadius - distance)) return 1;
    else return 0;

}


/*------Needs to be finished------*/

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