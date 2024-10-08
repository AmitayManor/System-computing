#include "galaxy.h"
#include <stdlib.h>
#include <stdio.h>


int readGalaxyFromBinaryFile(Galaxy* galaxy, FILE* fp) {
    
    fread(galaxy->name, sizeof(char), MAX_GALAXY_NAME, fp);
    fread(&galaxy->portal_location, sizeof(Location), 1, fp);
    fread(&galaxy->riskLevel, sizeof(int), 1, fp);
    fread(&galaxy->size, sizeof(int), 1, fp);
    fread(&galaxy->id, sizeof(int), 1, fp);
    fread(&galaxy->num_solar_systems, sizeof(int), 1, fp);

    galaxy->star_systems = ALLOCATE(SolarSystem*, galaxy->num_solar_systems);
    if (!galaxy->star_systems) {
        return 0;  
    }

    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        galaxy->star_systems[i] = ALLOCATE(SolarSystem,1);
        if (!galaxy->star_systems[i]) {
            return 0;
        }
        if (!readSolarSystemFromBinaryFile(galaxy->star_systems[i], fp)) {
            return 0;
        }
    }

    return 1;
}

int writeGalaxyToBinaryFile(const Galaxy* galaxy, FILE* fp) {
   
    fwrite(galaxy->name, sizeof(char), MAX_GALAXY_NAME, fp);
    fwrite(&galaxy->portal_location, sizeof(Location), 1, fp);
    fwrite(&galaxy->riskLevel, sizeof(int), 1, fp);
    fwrite(&galaxy->size, sizeof(int), 1, fp);
    fwrite(&galaxy->id, sizeof(int), 1, fp);
    fwrite(&galaxy->num_solar_systems, sizeof(int), 1, fp);


    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (!writeSolarSystemToBinaryFile(galaxy->star_systems[i], fp)) {
            return 0;  
        }
    }

    return 1;
}

void writeGalaxyToText(FILE* fp, const Galaxy* galaxy) {
    fprintf(fp, "Galaxy Name: %s\n", galaxy->name);
    fprintf(fp, "Portal Location: %d %d %d\n", galaxy->portal_location.x, galaxy->portal_location.y, galaxy->portal_location.z);
    fprintf(fp, "Risk Level: %d\n", galaxy->riskLevel);
    fprintf(fp, "Galaxy Size: %d\n", galaxy->size);
    fprintf(fp, "Galaxy ID: %d\n", galaxy->id);
    fprintf(fp, "Number of Solar Systems: %d\n", galaxy->num_solar_systems);

    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        writeSolarSystemToText(fp, galaxy->star_systems[i]);
    }
}

int readGalaxyFromText(FILE* fp, Galaxy* galaxy) {
    char buffer[MAX_GALAXY_NAME + 1];
    if (fscanf(fp, "Galaxy Name: %[^\n]\n", buffer) != 1) return 0;
    strncpy(galaxy->name, buffer, MAX_GALAXY_NAME);
    

    if (fscanf(fp, "Portal Location: %d %d %d\n", &galaxy->portal_location.x,
        &galaxy->portal_location.y, &galaxy->portal_location.z) != 3) return 0;

    if (fscanf(fp, "Risk Level: %d\n", &galaxy->riskLevel) != 1) return 0;
    if (fscanf(fp, "Galaxy Size: %d\n", &galaxy->size) != 1) return 0;
    if (fscanf(fp, "Galaxy ID: %d\n", &galaxy->id) != 1) return 0;

    int numSystems;
    if (fscanf(fp, "Number of Solar Systems: %d\n", &numSystems) != 1) return 0;
    galaxy->star_systems = ALLOCATE(SolarSystem*,numSystems);
    if (!galaxy->star_systems) return 0;
    galaxy->num_solar_systems = numSystems;

    for (int i = 0; i < numSystems; i++) {
        galaxy->star_systems[i] = ALLOCATE(SolarSystem,1);
        if (!galaxy->star_systems[i]) return 0;
        if (!readSolarSystemFromText(fp, galaxy->star_systems[i])) return 0; 
    }

    return 1;
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
        updateGalaxyRiskLevel(galaxy);
        printf("Solar System '%s' added successfully to Galaxy '%s'.\n", newSystem->name, galaxy->name);

    }
    else {
        printf("Failed to create a new Solar System.\n");
    }
}

void free_galaxy(Galaxy* galaxy) {
    if (galaxy) {
        
        for (int i = 0; i < galaxy->num_solar_systems; i++) {
            free_solar_system(galaxy->star_systems[i]);
        }
        free(galaxy->star_systems);
        free(galaxy);
    }
}


void get_galaxy_name(Galaxy* galaxy){
    printf("Enter the name for the galaxy (up to %d characters): ", MAX_GALAXY_NAME - 1);

    if (!myGets(galaxy->name, MAX_GALAXY_NAME)) {
        LOG_DEBUG("Failed to read Galaxy name.\n");
        free(galaxy);
        return NULL;
    }
}
void get_galaxy_id(UniversalManager* manager, Galaxy* galaxy){
    int id;

    do {
        printf("Enter Galaxy ID (1-9999): ");
        scanf("%d", &id);
        if (!isGalaxyIDUnique(manager, id)) {
            printf("This ID is already in use. Please enter a unique ID.\n");
        }
        else {
            galaxy->id = id;
            break;
        }
    } while (1);
}
void get_galaxy_location(UniversalManager* manager, Galaxy* galaxy){
    Location loc;
    do {
        printf("Enter location coordinates (x y z): ");
        scanf("%d %d %d", &loc.x, &loc.y, &loc.z);

        if (isGalaxyLocationUnique(manager, loc)) {
            galaxy->portal_location = loc;
            break;
        }
        else printf("This location is already occupied. Please enter a unique location.\n");

    } while (1);
}
void get_galaxy_radius(Galaxy* galaxy){
    printf("Enter the Galaxy radius: ");
    scanf("%d", &galaxy->size);
}


Galaxy* create_galaxy(UniversalManager* manager) {
    flush_stdin();
    Galaxy* galaxy = ALLOCATE(Galaxy, 1);
    if (!galaxy) {
        LOG_DEBUG ("Failed to allocate memory for Galaxy.\n");
        return NULL;
    }
    galaxy->num_solar_systems = 0;
    galaxy->riskLevel = 0;
    galaxy->star_systems = NULL;

    get_galaxy_name(galaxy);
    
    get_galaxy_id(manager, galaxy);
    
    get_galaxy_location(manager, galaxy);
   
    get_galaxy_radius(galaxy);

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

int isSolarSystemIDUnique(const Galaxy* galaxy, const int id) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (galaxy->star_systems[i]->id == id) {
            return 0; 
        }
    }
    return 1;
}

int isSolarSystemLocationUnique(const Galaxy* galaxy,const Location loc) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (isSameLocation(galaxy->star_systems[i]->portal_location, loc)) {
            return 0;  
        }
    }
    return 1;  
}

int isSolarSystemWithinGalaxy(const Galaxy* galaxy,const Location newSystemLoc) {
    double distance = calculateDistance(galaxy->portal_location, newSystemLoc);
    if (distance <= galaxy->size) {
        return 1;  
    }
    return 0;  
}

void updateGalaxyRiskLevel(Galaxy* galaxy) {
    if (galaxy == NULL || galaxy->num_solar_systems == 0) {
        printf("Error: No galaxy provided or no solar systems exist within the galaxy.\n");
        galaxy->riskLevel = 0;  
        return;
    }

    int totalRisk = 0;
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        totalRisk += galaxy->star_systems[i]->risk_level;
    }

    galaxy->riskLevel = totalRisk / galaxy->num_solar_systems;  
    printf("Updated Galaxy '%s' risk level to %d based on its solar systems.\n", galaxy->name, galaxy->riskLevel);
}

void print_galaxy(void* g) {
    Galaxy* galaxy = (Galaxy*)g;
    printf("\nGalaxy: %s\n", galaxy->name);
    printf("ID: %d\n", galaxy->id);
    printf("Location: (%d,%d,%d)\n", galaxy->portal_location.x, galaxy->portal_location.y, galaxy->portal_location.z);
    printf("Size (Radius): %d\n", galaxy->size);
    printf("Risk Level: %d\n", galaxy->riskLevel);

    if (galaxy->num_solar_systems == 0) {
        printf("  - No solar systems in this galaxy.\n");
    }
    else {
        for (int i = 0; i < galaxy->num_solar_systems;i++)
            generic_print(galaxy->star_systems[i], print_solar_system);
    }
}