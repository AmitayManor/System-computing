#include "planet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void writePlanetToText(FILE* fp, const Planet* planet) {
    fprintf(fp, "Planet Name: %s\n", planet->name);
    fprintf(fp, "Portal Location: %d %d %d\n", planet->portal_location.x, planet->portal_location.y, planet->portal_location.z);
    fprintf(fp, "Planet ID: %d\n", planet->id);
    fprintf(fp, "Risk Level: %d\n", planet->riskLevel);
    fprintf(fp, "Size: %d\n", planet->size);
}

int readPlanetFromText(FILE* fp, Planet* planet) {
    char buffer[MAX_PLANET_NAME + 1] = {0};
    if (fscanf(fp, "Planet Name: %[^\n]\n", buffer) != 1) return 0;
    strncpy(planet->name, buffer, MAX_PLANET_NAME);

    if (fscanf(fp, "Portal Location: %d %d %d\n", &planet->portal_location.x,
        &planet->portal_location.y, &planet->portal_location.z) != 3) return 0;

    if (fscanf(fp, "Planet ID: %d\n", &planet->id) != 1) return 0;
    if (fscanf(fp, "Risk Level: %d\n", &planet->riskLevel) != 1) return 0;
    if (fscanf(fp, "Size: %d\n", &planet->size) != 1) return 0;

    return 1;
}

int readPlanetFromBinaryFileCompressed(Planet* pPl, FILE* fp) {
    
    fread(pPl->name, sizeof(char), MAX_PLANET_NAME, fp);
    pPl->name[MAX_PLANET_NAME-1] = '\0';
    fread(&pPl->portal_location.x, sizeof(int), 1, fp);
    fread(&pPl->portal_location.y, sizeof(int), 1, fp);
    fread(&pPl->portal_location.z, sizeof(int), 1, fp);

   
    unsigned char buffer[3] = { 0 };
    fread(buffer, sizeof(unsigned char), 3, fp);
   
    pPl->id = (buffer[0] << 6) | (buffer[1] >> 2); 
    pPl->riskLevel = ((buffer[1] & 0x03) << 2) | (buffer[2] >> 6); 
    fread(&pPl->size, sizeof(int), 1, fp);

    return 1; 
}

int savePlanetToBinaryFileCompressed(const Planet* pPl, FILE* fp) {
    
    fwrite(pPl->name, sizeof(char), 50, fp); 
    fwrite(&pPl->portal_location.x, sizeof(int), 1, fp);
    fwrite(&pPl->portal_location.y, sizeof(int), 1, fp);
    fwrite(&pPl->portal_location.z, sizeof(int), 1, fp);

    
    unsigned char buffer[3] = { 0 }; 
    int id = pPl->id & 0x3FFF; 
    int riskLevel = pPl->riskLevel & 0x0F; 
    buffer[0] = id >> 6; 
    buffer[1] = (id & 0x3F) << 2 | (riskLevel >> 2); 
    buffer[2] = (riskLevel & 0x03) << 6; 
    fwrite(buffer, sizeof(unsigned char), 3, fp);

    
    fwrite(&pPl->size, sizeof(int), 1, fp);

    return 1; 
}

void print_planet(void* p) {
    Planet* planet = (Planet*)p;
    printf("\n\t\tPlanet: %s\n", planet->name);
    printf("\t\tID: %d\n", planet->id);
    printf("\t\tLocation: (%d,%d,%d)\n", planet->portal_location.x, planet->portal_location.y, planet->portal_location.z);
    printf("\t\tSize: %d\n", planet->size);
    printf("\t\tRisk Level: %d\n", planet->riskLevel);
}


void get_planet_name(Planet* planet) {
    if (!planet) {
        LOG_DEBUG("Error! Planet not initiated")
            return NULL;
    }
    else {
        printf("Enter the name for the Planet (up to %d characters): ", MAX_PLANET_NAME - 1);

        if (!myGets(planet->name, MAX_PLANET_NAME)) {
            LOG_DEBUG("Failed to read Planet name or input was empty.\n");

            free(planet);
            return NULL;
        }
    }
}

void get_planet_id(SolarSystem* system, Planet* planet){

    int idFlag = 0;
    int id;
    do {
        printf("Enter the Planet ID (1-9999): ");
        scanf("%d", &id);
        if (check_unique_planet_id(system, id) && id > 0 && id < 10000) {
            idFlag = 1;
            planet->id = id;
        }
        else
            printf("\nError! ID is not valid. Try again.\n");

    } while (!idFlag);
}

void get_planet_location(SolarSystem* system, Planet* planet){

    int locFlag = 0;
    Location loc;
    do {
        printf("Enter the Planet location coordinates (x y z): ");
        scanf("%d %d %d", &loc.x, &loc.y, &loc.z);
        if (check_unique_planet_location(system, loc) && isPlanetWithinSolarSystem(system, loc)) {
            locFlag = 1;
            planet->portal_location = loc;
        }
        else
            printf("\nError! Location is not valid. Try again.\n");
    } while (!locFlag);
}

void get_planet_radius(Planet* planet){
    int radiusFlag = 0;
    int size;
    do {
        printf("Enter the Planet radius: ");
        scanf("%d", &size);
        if (size > 0) {
            radiusFlag = 1;
            planet->size = size;
        }
    } while (!radiusFlag);
}

void get_planet_risk(Planet* planet){
    int risk;
    int riskFlag = 0;
    do {
        printf("Enter the risk level of this planet:(0-10)\n\t%d - Most Dangerous.\n\t%d - Most Safe ", MAX_RISK_LVL, MIN_RISK_LVL);
        scanf("%d", &risk);

        if (risk >= MIN_RISK_LVL && risk <= MAX_RISK_LVL) {
            planet->riskLevel = risk;
            riskFlag = 1;
        }
        else
            printf("\nError! Not a valid input. Try again\n");


    } while (!riskFlag);
}

Planet* create_planet(SolarSystem* system) {

    flush_stdin();
    if (!system) {
        LOG_DEBUG("Error: No solar system provided.\n");
        return NULL;
    }

    Planet* newPlanet = ALLOCATE(Planet, 1);
    if (newPlanet == NULL) {
        LOG_DEBUG("Memory allocation failed\n");
        return NULL;
    }

    get_planet_name(newPlanet);
    get_planet_id(system, newPlanet);
    get_planet_location(system, newPlanet);
    get_planet_radius(newPlanet);
    get_planet_risk(newPlanet);

    flush_stdin();
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
    if(planet) free(planet);
}

void freePlanetNode(PlanetNode* node) {
    if (node != NULL) {
        free_planet(node->planet);
        free(node); 
    }
}