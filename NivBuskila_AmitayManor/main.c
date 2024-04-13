#include <stdio.h>
#include <assert.h>
#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"


int main() {
    
    /*
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

    InterstellarTravel tr1 = { "G0001S0032P0001","G0001S0032P0003", &sp1, {12,12,2024},{12,12,2024}, 5, 2, 1,1 };
    InterstellarTravel tr2 = { "G0001S0032P0001","G0001S0032P0002", &sp1, {13,12,2024},{13,12,2024}, 1, 2, 1,2 };

    InterstellarTravel** travels = ALLOCATE(InterstellarTravel**, 2);
    travels[0] = &tr1;
    travels[1] = &tr2;

    Company cm1 = {"SpaceX", 1997, 4, sCrafts, travels, 2,eGALAXY };
    Company cm2 = { "China", 2000, 4, sCrafts, travels, 2,eSOLARSYSTEM };
    Company cm3 = { "USA", 1968, 4, sCrafts, travels, 2,ePLANET };

    Company** companies = ALLOCATE(Company**, 3);

    companies[0] = &cm1;
    companies[1] = &cm2;
    companies[2] = &cm3;

    UniversalManager manager = { galaxies,1, companies,3 };
    
    */

    int choice;
    UniversalManager manager;
    initUniversalManager(&manager);
   

    do {
       
        printf("\nMain Menu:\n");
        printf("1. Add cosmic element\n");
        printf("2. Companies interface\n");
        printf("3. Display The Universe\n");
        printf("4. Display All Companies\n");
        printf("5. Rename cosmic element\n");
        printf("6. Export all data to file\n");
        printf("7. Import all data to file\n");
        printf("8. Exit\n");
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
            
            exportData(&manager);
            break;
        }
        
        case 7: {
            importData(&manager);
            break;
        }
        case 8: {
            printf("Exiting...\n");
            break;
        }

        default: {
            printf("Invalid choice. Please try again.\n");
        }
        }
    } while (choice != 8);

    freeUniversalManager(&manager);

    return 0;
    
}
