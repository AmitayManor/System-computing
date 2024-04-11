#include "planet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

void debugSinglePlanet(const Planet* planet) {
    printf( "Planet Name: %s\n", planet->name);
    printf( "Location: %d %d %d\n", planet->portal_location.x, &planet->portal_location.y, &planet->portal_location.z);
    printf( "Planet ID: %d\n", planet->id);
    printf( "Risk Level: %d\n", planet->riskLevel);
    printf("Size: %d\n", planet->size);


}

void writePlanetToText(FILE* fp, const Planet* planet) {
    fprintf(fp, "Planet Name: %s\n", planet->name);
    fprintf(fp, "Portal Location: %d %d %d\n", planet->portal_location.x, planet->portal_location.y, planet->portal_location.z);
    fprintf(fp, "Planet ID: %d\n", planet->id);
    fprintf(fp, "Risk Level: %d\n", planet->riskLevel);
    fprintf(fp, "Size: %d\n", planet->size);
    fprintf(fp, "---\n");
}

void readPlanetFromText(FILE* fp, Planet* planet) {
    char buffer[256]; // Temporary buffer for reading lines
    fgets(buffer, sizeof(buffer), fp); // Read the planet name line
    sscanf(buffer, "Planet Name: %[^\n]", planet->name);

    fgets(buffer, sizeof(buffer), fp); // Read the portal location line
    sscanf(buffer, "Portal Location: %d %d %d", &planet->portal_location.x, &planet->portal_location.y, &planet->portal_location.z);

    fgets(buffer, sizeof(buffer), fp); // Read the planet ID line
    sscanf(buffer, "Planet ID: %d", &planet->id);

    fgets(buffer, sizeof(buffer), fp); // Read the risk level line
    sscanf(buffer, "Risk Level: %d", &planet->riskLevel);

    fgets(buffer, sizeof(buffer), fp); // Read the size line
    sscanf(buffer, "Size: %d", &planet->size);

    fgets(buffer, sizeof(buffer), fp); // Skip the delimiter line
}

void debugComparePlanets(const Planet* pPl1, const Planet* pPl2) {
    printf("Comparing Planets...\n");
    printf("Name: %s - %s\n", pPl1->name, pPl2->name);
    printf("Location X: %d - %d\n", pPl1->portal_location.x, pPl2->portal_location.x);
    printf("Location Y: %d - %d\n", pPl1->portal_location.y, pPl2->portal_location.y);
    printf("Location Z: %d - %d\n", pPl1->portal_location.z, pPl2->portal_location.z);
    printf("ID: %d - %d\n", pPl1->id, pPl2->id);
    printf("Risk Level: %d - %d\n", pPl1->riskLevel, pPl2->riskLevel);
    printf("Size: %d - %d\n", pPl1->size, pPl2->size);
}

void testPlanetReadWrite() {
    Planet originalPlanet;
    Planet readPlanet;
    FILE* fp;

    // Create and set up a sample planet
    createSamplePlanet(&originalPlanet);

    // Save the planet to a binary file
    fp = fopen("test_planet.bin", "wb");
    assert(fp != NULL);
    int saveSuccess = savePlanetToBinaryFileCompressed(&originalPlanet, fp);
    fclose(fp);
    assert(saveSuccess == 1);  // Ensure the planet was saved successfully

    // Read the planet back from the binary file
    fp = fopen("test_planet.bin", "rb");
    assert(fp != NULL);
    int readSuccess = readPlanetFromBinaryFileCompressed(&readPlanet, fp);
    fclose(fp);
    assert(readSuccess == 1);  // Ensure the planet was read successfully

    //debugComparePlanets(&originalPlanet, &readPlanet);

    // Compare the original and read-back planets
    assert(comparePlanets(&originalPlanet, &readPlanet) == 1);

    printf("Test Passed: The written and read planets match.\n");
}

int comparePlanets(const Planet* pPl1, const Planet* pPl2) {
    if (strcmp(pPl1->name, pPl2->name) != 0) return 0;
    if (pPl1->portal_location.x != pPl2->portal_location.x ||
        pPl1->portal_location.y != pPl2->portal_location.y ||
        pPl1->portal_location.z != pPl2->portal_location.z) return 0;
    if (pPl1->id != pPl2->id) return 0;
    if (pPl1->riskLevel != pPl2->riskLevel) return 0;
    if (pPl1->size != pPl2->size) return 0;
    return 1;
}

void createSamplePlanet(Planet* pPl) {
    strncpy(pPl->name, "Earth", MAX_PLANET_NAME - 1);
    pPl->name[MAX_PLANET_NAME - 1] = '\0';
    pPl->portal_location.x = 100; // Sample coordinates
    pPl->portal_location.y = 200;
    pPl->portal_location.z = 300;
    pPl->id = 42;                 // Sample ID
    pPl->riskLevel = 5;           // Sample risk level
    pPl->size = 10000;            // Sample size
}

int readPlanetFromBinaryFileCompressed(Planet* pPl, FILE* fp) {
    // Read the name directly
    fread(pPl->name, sizeof(char), 50, fp);
    pPl->name[49] = '\0'; // Ensure null-termination

    // Read portal_location as 32-bit ints directly
    fread(&pPl->portal_location.x, sizeof(int), 1, fp);
    fread(&pPl->portal_location.y, sizeof(int), 1, fp);
    fread(&pPl->portal_location.z, sizeof(int), 1, fp);

    // Read the buffer for ID and riskLevel
    unsigned char buffer[3] = { 0 };
    fread(buffer, sizeof(unsigned char), 3, fp);
    // Decode ID and risk level from buffer
    pPl->id = (buffer[0] << 6) | (buffer[1] >> 2); // 14-bit ID
    pPl->riskLevel = ((buffer[1] & 0x03) << 2) | (buffer[2] >> 6); // 4-bit risk level

    // Read size as 32-bit int directly
    fread(&pPl->size, sizeof(int), 1, fp);

    return 1; //
    
    /*
    BYTE data[8]; // Adjust size as needed based on actual bit allocations
    if (fread(&data, sizeof(BYTE), 8, fp) != 8)
        return 0;

    int len = (data[0] >> 3) & 0x1F; // 5 bits for name length
    if (len >= MAX_PLANET_NAME) {
        len = MAX_PLANET_NAME - 1;
    }
    pPl->portal_location.x = ((data[0] & 0x7) << 7) | ((data[1] >> 1) & 0x7F); // 10 bits for x
    pPl->portal_location.y = ((data[1] & 0x1) << 9) | (data[2] & 0xFF); // 10 bits for y
    pPl->portal_location.z = ((data[3] & 0x3) << 8) | (data[4] & 0xFF); // 10 bits for z
    pPl->id = ((data[3] & 0xFC) << 2) | ((data[4] >> 6) & 0x3); // 12 bits for id
    pPl->riskLevel = (data[5] >> 1) & 0x7F; // 7 bits for riskLevel
    pPl->size = ((data[5] & 0x1) << 6) | ((data[6] >> 2) & 0x3F); // 7 bits for size

    if (fread(pPl->name, sizeof(char), len, fp) != len) {  // Read the name into the struct's name array
        return 0;  // Return 0 on failure to read the full name
    }
    pPl->name[len] = '\0';

    return 1;
    */
}

int savePlanetToBinaryFileCompressed(const Planet* pPl, FILE* fp) {
    // Write the name directly, no compression needed
    fwrite(pPl->name, sizeof(char), 50, fp); // Fixed-size 50 chars, directly written

    // Write portal_location as 32-bit ints directly
    fwrite(&pPl->portal_location.x, sizeof(int), 1, fp);
    fwrite(&pPl->portal_location.y, sizeof(int), 1, fp);
    fwrite(&pPl->portal_location.z, sizeof(int), 1, fp);

    // Prepare a buffer for ID and riskLevel
    unsigned char buffer[3] = { 0 }; // 3 bytes = 24 bits, enough for 14-bit ID and 4-bit risk level
    // Encode ID (14 bits) and risk level (4 bits) into buffer
    int id = pPl->id & 0x3FFF; // Ensure ID is within 14 bits
    int riskLevel = pPl->riskLevel & 0x0F; // Ensure risk level is within 4 bits
    buffer[0] = id >> 6; // First 8 bits of ID
    buffer[1] = (id & 0x3F) << 2 | (riskLevel >> 2); // Last 6 bits of ID, first 2 bits of risk level
    buffer[2] = (riskLevel & 0x03) << 6; // Last 2 bits of risk level, 6 bits padding
    fwrite(buffer, sizeof(unsigned char), 3, fp);

    // Write size as 32-bit int directly
    fwrite(&pPl->size, sizeof(int), 1, fp);

    return 1; // Success
    /*
    BYTE data[8] = { 0 }; // Adjust size as needed based on actual bit allocations

    int len = (int)strlen(pPl->name);
    data[0] = len << 3 | (pPl->portal_location.x >> 7) & 0x7; // 5 bits for name length, 3 bits for x
    data[1] = ((pPl->portal_location.x & 0x7F) << 1) | ((pPl->portal_location.y >> 9) & 0x1); // 7 bits for x, 1 bit for y
    data[2] = pPl->portal_location.y & 0xFF; // 8 bits for y
    data[3] = (pPl->portal_location.z >> 8) & 0x3 | (pPl->id >> 4) & 0xFC; // 2 bits for z, 4 bits for id
    data[4] = ((pPl->portal_location.z & 0xFF) << 6) | ((pPl->id & 0xF) << 2) | ((pPl->riskLevel >> 5) & 0x3); // 6 bits for z, 4 bits for id, 2 bits for riskLevel
    data[5] = (pPl->riskLevel & 0x1F) << 1 | ((pPl->size >> 6) & 0x1); // 5 bits for riskLevel, 1 bit for size
    data[6] = ((pPl->size & 0x3F) << 2); // 6 bits for size

    if (fwrite(&data, sizeof(BYTE), 8, fp) != 8)
        return 0;

    if (fwrite(pPl->name, sizeof(char), len, fp) != len)
        return 0;

    return 1;
    */
}

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
