#include "solar_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void testSolarSystemIO() {
    // Create a sample SolarSystem with planets
    //SolarSystem system = { "SolarSystemX", {1, 2, 3}, 5, NULL, 3, 300, 123 };
    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };

    PlanetNode pNode3 = { &planet3,NULL };
    PlanetNode pNode2 = { &planet2,&pNode3 };
    PlanetNode pNode1 = { &planet1,&pNode2 };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };

    // Write the system to a file
    FILE* fp = fopen("test_solarsystem.txt", "w");
    assert(fp != NULL);
    writeSolarSystemToText(fp, &system);
    fclose(fp);

    // Read the system back from the file
    SolarSystem readSystem = { 0 };
    fp = fopen("test_solarsystem.txt", "r");
    assert(fp != NULL);
    assert(readSolarSystemFromText(fp, &readSystem) == 1);
    fclose(fp);

    // Assertions to check system properties
    assert(strcmp(system.name, readSystem.name) == 0);
    assert(system.portal_location.x == readSystem.portal_location.x);
    assert(system.risk_level == readSystem.risk_level);
    assert(system.num_planets == readSystem.num_planets);
    assert(system.size == readSystem.size);
    assert(system.id == readSystem.id);

    // Assertions to check planets
    PlanetNode* orig = system.planetsHead;
    PlanetNode* read = readSystem.planetsHead;
    while (orig && read) {
        assert(strcmp(orig->planet->name, read->planet->name) == 0);
        assert(orig->planet->id == read->planet->id);
        assert(orig->planet->riskLevel == read->planet->riskLevel);
        assert(orig->planet->size == read->planet->size);
        orig = orig->next;
        read = read->next;
    }
    assert(orig == NULL && read == NULL);  // Ensure both lists end at the same time

}

void testSolarSystemBinaryIO() {
    FILE* fp = fopen("test_solarsystem.bin", "w+b");
    if (!fp) return;

    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };

    PlanetNode pNode3 = { &planet3,NULL };
    PlanetNode pNode2 = { &planet2,&pNode3 };
    PlanetNode pNode1 = { &planet1,&pNode2 };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };

    assert(writeSolarSystemToBinaryFile(&system, fp));
    rewind(fp);
    SolarSystem loadedSystem;
    assert(readSolarSystemFromBinaryFile(&loadedSystem, fp));

    // Implement assert conditions to verify the integrity of loadedSystem
    fclose(fp);
}











void debugCompareSS(const SolarSystem* pSS1, const SolarSystem* pSS2) {
    printf("Comparing Planets...\n");
    printf("Name: %s - %s\n", pSS1->name, pSS2->name);
    printf("Location X: %d - %d\n", pSS1->portal_location.x, pSS2->portal_location.x);
    printf("Location Y: %d - %d\n", pSS1->portal_location.y, pSS2->portal_location.y);
    printf("Location Z: %d - %d\n", pSS1->portal_location.z, pSS2->portal_location.z);
    printf("ID: %d - %d\n", pSS1->id, pSS2->id);
    printf("Risk Level: %d - %d\n", pSS1->risk_level, pSS2->risk_level);
    printf("Size: %d - %d\n", pSS1->size, pSS2->size);
    printf("\n\n");
    debugComparePlanets(pSS1->planetsHead, pSS2->planetsHead);
}

void testPlanetAndSolarSystemReadWrite() {
    // Create a sample planet and solar system
    Planet earth = { "Earth", {1, 2, 3}, 45, 10, 1000 };
    SolarSystem sol = { "Sol", {100, 200, 300}, 2, 9000, 1, 1 };

    PlanetNode earthNode = { &earth, NULL };
    sol.planetsHead = &earthNode;

    // Write to text file
    FILE* fp = fopen("test_solarsystem.txt", "w");
    writeSolarSystemToText(fp, &sol);
    fclose(fp);

    // Read back
    SolarSystem solRead;
    fp = fopen("test_solarsystem.txt", "r");
    readSolarSystemFromText(fp, &solRead);
    fclose(fp);

    debugCompareSS(&sol, &solRead);
    // Implement comparison functions and assert results
    //assert(comparePlanets(&earth, solRead.planetsHead->planet));
    assert(compareSolarSystems(&sol, &solRead));


    // Free dynamically allocated memory
    // Free planet nodes in solRead
}

int compareSolarSystems(const SolarSystem* pSS1, const SolarSystem* pSS2) {
    if (strcmp(pSS1->name, pSS2->name) != 0) return 0;
    if (pSS1->portal_location.x != pSS2->portal_location.x ||
        pSS1->portal_location.y != pSS2->portal_location.y ||
        pSS1->portal_location.z != pSS2->portal_location.z) return 0;
    if (pSS1->id != pSS2->id) return 0;
    if (pSS1->risk_level != pSS2->risk_level) return 0;
    if (pSS1->size != pSS2->size) return 0;
    if (!comparePlanets(pSS1->planetsHead, pSS2->planetsHead)) return 0;
    return 1;
}

int writeSolarSystemToBinaryFile(const SolarSystem* system, FILE* fp) {
    // Write SolarSystem attributes
    fwrite(system->name, sizeof(char), MAX_SOLAR_SYSTEM_NAME, fp);
    fwrite(&system->portal_location, sizeof(Location), 1, fp);
    fwrite(&system->risk_level, sizeof(int), 1, fp);
    fwrite(&system->num_planets, sizeof(int), 1, fp);
    fwrite(&system->size, sizeof(int), 1, fp);
    fwrite(&system->id, sizeof(int), 1, fp);

    // Write each planet in the linked list
    PlanetNode* current = system->planetsHead;
    while (current != NULL) {
        savePlanetToBinaryFileCompressed(current->planet, fp);
        current = current->next;
    }

    return 1;
}
int readSolarSystemFromBinaryFile(SolarSystem* system, FILE* fp) {
    // Read SolarSystem attributes
    fread(system->name, sizeof(char), MAX_SOLAR_SYSTEM_NAME, fp);
    fread(&system->portal_location, sizeof(Location), 1, fp);
    fread(&system->risk_level, sizeof(int), 1, fp);
    fread(&system->num_planets, sizeof(int), 1, fp);
    fread(&system->size, sizeof(int), 1, fp);
    fread(&system->id, sizeof(int), 1, fp);

    // Initialize the linked list head to NULL
    system->planetsHead = NULL;
    PlanetNode* lastNode = NULL;

    // Read each planet and reconstruct the linked list
    for (int i = 0; i < system->num_planets; i++) {
        PlanetNode* newNode = malloc(sizeof(PlanetNode));
        if (newNode == NULL) return 0;
        newNode->planet = malloc(sizeof(Planet));
        if (newNode->planet == NULL) {
            free(newNode);
            return 0;
        }
        if (!readPlanetFromBinaryFileCompressed(newNode->planet, fp)) {
            free(newNode->planet);
            free(newNode);
            return 0;
        }
        newNode->next = NULL;
        if (lastNode == NULL) {
            system->planetsHead = newNode;
        }
        else {
            lastNode->next = newNode;
        }
        lastNode = newNode;
    }

    return 1;
}


int readSolarSystemFromText(FILE* fp, SolarSystem* system) {
    char buffer[MAX_SOLAR_SYSTEM_NAME + 1];
    if (fscanf(fp, "SolarSystem Name: %[^\n]\n", buffer) != 1) return 0;
    strncpy(system->name, buffer, MAX_SOLAR_SYSTEM_NAME);

    if (fscanf(fp, "Portal Location: %d %d %d\n", &system->portal_location.x,
        &system->portal_location.y, &system->portal_location.z) != 3) return 0;

    if (fscanf(fp, "Risk Level: %d\n", &system->risk_level) != 1) return 0;
    if (fscanf(fp, "Number of Planets: %d\n", &system->num_planets) != 1) return 0;
    if (fscanf(fp, "System Size: %d\n", &system->size) != 1) return 0;
    if (fscanf(fp, "System ID: %d\n", &system->id) != 1) return 0;

    system->planetsHead = NULL;
    PlanetNode* lastNode = NULL;
    for (int i = 0; i < system->num_planets; i++) {
        PlanetNode* newNode = ALLOCATE(PlanetNode*,1);
        if (!newNode) return 0; 

        newNode->planet = ALLOCATE(Planet*,1);
        if (!newNode->planet) {
            free(newNode);
            return 0; 
        }
        if (!readPlanetFromText(fp, newNode->planet)) {
            free(newNode->planet);
            free(newNode);
            return 0; 
        }

        newNode->next = NULL;
        if (lastNode == NULL) {
            system->planetsHead = newNode;
        }
        else {
            lastNode->next = newNode;
        }
        lastNode = newNode;
    }

    return 1;
}

void writeSolarSystemToText(FILE* fp, const SolarSystem* system) {
    fprintf(fp, "SolarSystem Name: %s\n", system->name);
    fprintf(fp, "Portal Location: %d %d %d\n", system->portal_location.x, system->portal_location.y, system->portal_location.z);
    fprintf(fp, "Risk Level: %d\n", system->risk_level);
    fprintf(fp, "Number of Planets: %d\n", system->num_planets);
    fprintf(fp, "System Size: %d\n", system->size);
    fprintf(fp, "System ID: %d\n", system->id);

    PlanetNode* current = system->planetsHead;
    while (current != NULL) {
        writePlanetToText(fp, current->planet);
        current = current->next;
    }
}




SolarSystem* create_solar_system(Galaxy* galaxy) {

    if (!galaxy) {
        LOG_DEBUG("Error: No galaxy provided.\n");
        return NULL;
    }

    SolarSystem* system = ALLOCATE(SolarSystem*, 1);
    if (system) {

        printf("Enter Solar System Name: ");
        if (!myGets(system->name, MAX_SOLAR_SYSTEM_NAME)) {
            LOG_DEBUG("Failed to read Solar System name.\n");
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
            if (isSolarSystemIDUnique(galaxy, id) && id > 0 && id < 10000) {
                idFlag = 1;
                system->id = id;
            }
            else
                printf("\nError! ID is not valid. Try again.\n");

        } while (!idFlag);

        Location loc;
        int locFlag = 0;
        do {
            printf("Enter the Solar System location coordinates (x y z): ");
            scanf("%d %d %d", &loc.x, &loc.y, &loc.z);

            if (!isSolarSystemLocationUnique(galaxy, loc) || !isSolarSystemWithinGalaxy(galaxy, loc))
                printf("This location is either occupied or out of the reach of the galaxy. Please enter a different location.\n");
               
            else{
                locFlag = 1;
                system->portal_location = loc;
            }
                
        } while (!locFlag);

        int radiusFalg = 0;
        int size;
        do {
            printf("Enter the Solar System radius: ");
            scanf("%d", &size);
            if (size > 0) {
                radiusFalg = 1;
                system->size = size;
            }
            else
                printf("\nError! Radius is not valid. Try again.\n");
        } while (!radiusFalg);

    }
    else {
        LOG_DEBUG("Memory allocation failed for SolarSystem.\n");
        return NULL;
    }
    return system;
}

void add_planet_to_solar_system(SolarSystem* system) {
    if (!system) {
        printf("Error: No solar system provided.\n");
        return;
    }

    Planet* newPlanet = create_planet(system);
    
    if (newPlanet) {

        PlanetNode* newNode = ALLOCATE(PlanetNode*,1);
        if (newNode == NULL) {
            printf("Failed to allocate memory for new planet node.\n");
            free_planet(newPlanet);  
            return;
        }

        newNode->planet = newPlanet;  
        newNode->next = NULL;  

        if (system->planetsHead == NULL) {
            system->planetsHead = newNode;
        }
        else {
           
            PlanetNode* current = system->planetsHead;
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
    system->planetsHead = NULL;  
    system->num_planets = 0;
}

void print_solar_system(void* ss) {
    SolarSystem* system = (SolarSystem*)ss;
    printf("\n\tSolar System: %s\n", system->name);
    printf("\tID: %d\n", system->id);
    printf("\tLocation: (%d,%d,%d)\n", system->portal_location.x, system->portal_location.y, system->portal_location.z);
    printf("\tSize (Radius): %d\n", system->size);
    printf("\tRisk Level: %d\n", system->risk_level);

    if (system->num_planets == 0)
        printf("    - No planets in this solar system.\n");
    else {
        PlanetNode* current = system->planetsHead;
        while (current != NULL) {

            generic_print(current->planet, print_planet);
            current = current->next;
        }
    }
}

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

int check_unique_planet_id(SolarSystem* sSystem,const int id) {
    if (!sSystem || !sSystem->planetsHead || sSystem->num_planets <= 0)
        return 1;

    PlanetNode* current = sSystem->planetsHead;
    while (current ) {
        if (current->planet->id == id) {
            return 0;  
        }
        current = current->next; 
    }
    return 1;
}

int check_unique_planet_location(SolarSystem* sSystem, const Location planetLoc) {
    if (!sSystem || !sSystem->planetsHead || sSystem->num_planets <= 0)
        return 1;

    PlanetNode* current = sSystem->planetsHead;
    while (current) {
        if (isSameLocation(current->planet->portal_location, planetLoc)) {
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

void updateSolarSystemRiskLevel(SolarSystem* system) {
    if (system == NULL || system->planetsHead == NULL) {
        printf("Error: No solar system provided or no planets exist within the system.\n");
        return;
    }

    int totalRisk = 0;
    int count = 0;
    PlanetNode* current = system->planetsHead;
    
    while (current != NULL) {
        totalRisk += current->planet->riskLevel;
        count++;
        current = current->next;
    }

    if (count > 0) 
        system->risk_level = totalRisk / count;
    else 
        system->risk_level = 0;  

    printf("Updated Solar System '%s' risk level to %d.\n", system->name, system->risk_level);
}

int isPlanetWithinSolarSystem(SolarSystem* system, const Location newPlanetLoc) {
    double distance = calculateDistance(system->portal_location, newPlanetLoc);
    if (distance <= system->size) {
        return 1;  
    }
    return 0;  
}