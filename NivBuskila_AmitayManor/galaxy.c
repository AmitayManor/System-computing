#include "galaxy.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void testGalaxyIO() {
    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };
    Planet planet11 = { "avi", {43,1,77},1,2,10 };

    PlanetNode pNode3 = { &planet3,NULL };
    PlanetNode pNode2 = { &planet2,&pNode3 };
    PlanetNode pNode1 = { &planet1,&pNode2 };
    PlanetNode pNode11 = { &planet11,NULL };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };
    SolarSystem system2 = { "Milky",{1, 2, 43},6, &pNode11,1, 1000, 32 };

    SolarSystem** star_system = ALLOCATE(SolarSystem**, 2);
    star_system[0] = &system;
    star_system[1] = &system2;

    Galaxy galaxy = { "Amitay",{1,1,1}, star_system, 2,10,100,1 };

    FILE* fp = fopen("test_galaxy.txt", "w+");
    assert(fp != NULL);
    writeGalaxyToText(fp, &galaxy);
    rewind(fp);

    Galaxy loadedGalaxy;
    assert(readGalaxyFromText(fp, &loadedGalaxy));
    fclose(fp);
}

void testGalaxyBinaryIO() {
    FILE* fp = fopen("test_galaxy.bin", "w+b");
    if (!fp) return;

    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };
    Planet planet11 = { "avi", {43,1,77},1,2,10 };

    PlanetNode pNode3 = { &planet3,NULL };
    PlanetNode pNode2 = { &planet2,&pNode3 };
    PlanetNode pNode1 = { &planet1,&pNode2 };
    PlanetNode pNode11 = { &planet11,NULL };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };
    SolarSystem system2 = { "Milky",{1, 2, 43},6, &pNode11,1, 1000, 32 };

    SolarSystem** star_system = ALLOCATE(SolarSystem**, 2);
    star_system[0] = &system;
    star_system[1] = &system2;

    Galaxy galaxy = { "Amitay",{1,1,1}, star_system, 2,10,100,1 };

    assert(writeGalaxyToBinaryFile(&galaxy, fp));
    rewind(fp);

    Galaxy loadedGalaxy;
    assert(readGalaxyFromBinaryFile(&loadedGalaxy, fp));

    // Add assertions to check all properties of loadedGalaxy
    fclose(fp);

}


int readGalaxyFromBinaryFile(Galaxy* galaxy, FILE* fp) {
    
    fread(galaxy->name, sizeof(char), MAX_GALAXY_NAME, fp);
    fread(&galaxy->portal_location, sizeof(Location), 1, fp);
    fread(&galaxy->riskLevel, sizeof(int), 1, fp);
    fread(&galaxy->size, sizeof(int), 1, fp);
    fread(&galaxy->id, sizeof(int), 1, fp);
    fread(&galaxy->num_solar_systems, sizeof(int), 1, fp);

    galaxy->star_systems = ALLOCATE(SolarSystem**, galaxy->num_solar_systems);
    if (!galaxy->star_systems) {
        return 0;  
    }

    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        galaxy->star_systems[i] = ALLOCATE(SolarSystem*,1);
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
        galaxy->star_systems[i] = ALLOCATE(SolarSystem*,1);
        if (!galaxy->star_systems[i]) return 0;
        if (!readSolarSystemFromText(fp, galaxy->star_systems[i])) return 0; 
    }

    return 1;
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
        updateGalaxyRiskLevel(galaxy);
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

    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    if (!galaxy) {
        LOG_DEBUG ("Failed to allocate memory for Galaxy.\n");
        return NULL;
    }
    galaxy->num_solar_systems = 0;
    galaxy->riskLevel = 0;
    galaxy->star_systems = NULL;

    printf("Enter the name for the galaxy (up to %d characters): ", MAX_GALAXY_NAME - 1);
    if (!myGets(galaxy->name, MAX_GALAXY_NAME)) {
        LOG_DEBUG("Failed to read Galaxy name.\n");
        free(galaxy);
        return NULL;
    }
    int id;
    flush_stdin();
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

    
    printf("Enter the Galaxy radius: ");
    scanf("%d", &galaxy->size);
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
        galaxy->riskLevel = 0;  // Default to 0 if no solar systems exist
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
