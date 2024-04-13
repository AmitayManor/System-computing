#include <stdio.h>
#include <assert.h>
#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"

void test_planet_io() {
    Planet writePlanet = { "Earth", {0, 100, 200}, 1, 5, 1000 };
    FILE* fp = fopen("test_planet.txt", "w+");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    writePlanetToText(fp, &writePlanet);
    rewind(fp);  // Reset file pointer for reading

    Planet readPlanet;
    if (readPlanetFromText(fp, &readPlanet)) {
        printf("Planet read successfully:\n");
        printf("Name: %s\n", readPlanet.name);
        printf("Location: %d %d %d\n", readPlanet.portal_location.x, readPlanet.portal_location.y, readPlanet.portal_location.z);
        printf("ID: %d\n", readPlanet.id);
        printf("Risk Level: %d\n", readPlanet.riskLevel);
        printf("Size: %d\n", readPlanet.size);
    }
    else {
        printf("Failed to read planet from file.\n");
    }

    fclose(fp);
}






int main() {

    testInterstellarTravelIO();
    testSpaceCraftIO();
//    testGalaxyBinaryIO();


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

    SolarSystem** star_system = ALLOCATE(SolarSystem**,2);
    star_system[0] = &system;
    star_system[1] = &system2;

    Galaxy galaxy = { "Amitay",{1,1,1}, star_system, 2,10,100,1 };

    Galaxy** galaxies = ALLOCATE(Galaxy**, 1);
    galaxies[0] = &galaxy;


    SpaceCraft sp1 = {"f1","t",1500,1};
    SpaceCraft sp2 = { "f2","q",1500,2 };
    SpaceCraft sp3 = { "f3","a",1500,3 };
    SpaceCraft sp4 = { "f4","z",1500,4 };

    SpaceCraft** sCrafts = ALLOCATE(SpaceCraft**, 4);
    sCrafts[0] = &sp1;
    sCrafts[1] = &sp2;
    sCrafts[2] = &sp3;
    sCrafts[3] = &sp4;


    Company cm1 = {"SpaceX", 1997, 4, sCrafts, NULL, 0,eGALAXY };
    Company cm2 = { "China", 2000, 4, sCrafts, NULL, 0,eSOLARSYSTEM };
    Company cm3 = { "USA", 1968, 4, sCrafts, NULL, 0,ePLANET };

    Company** companies = ALLOCATE(Company**, 3);

    companies[0] = &cm1;
    companies[1] = &cm2;
    companies[2] = &cm3;

    UniversalManager manager = { galaxies,1, companies,3 };
    
    int choice;

    do {
       
        printf("\nMain Menu:\n");
        printf("1. Add cosmic element\n");
        printf("2. Companies interface\n");
        printf("3. Display The Universe\n");
        printf("4. Display All Companies\n");
        printf("5. Rename cosmic element\n");
        printf("6. Export all data to file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            addCosmicElement(&manager);
            break;
        }
        case 2: {
            manage_company_operations(&manager);
            break;
        }
        case 3: {
            displayCosmicElements(&manager);
            break;
        }
        case 4: {
            printCompanies(&manager);
            break;
        }
        
        case 5: {
            renameCosmicElement(&manager);
            break;
        }
        case 6: {
            //Export all data
            break;
        }
        
        case 7: {
            printf("Exiting...\n");
            break;
        }

        default: {
            printf("Invalid choice. Please try again.\n");
        }
        }
    } while (choice != 7);

    freeUniversalManager(&manager);

    return 0;
    
}
