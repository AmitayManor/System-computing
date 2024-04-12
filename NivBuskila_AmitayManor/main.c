#include <stdio.h>
#include <assert.h>
#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"

int main() {
  
    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };
    PlanetNode pNode3 = { (void*)&planet3,NULL };
    PlanetNode pNode2 = { (void*)&planet2,&pNode3 };
    PlanetNode pNode1 = { (void*)&planet1,&pNode2 };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };
    SolarSystem** star_system = ALLOCATE(SolarSystem**,1);
    star_system[0] = &system;
    Galaxy galaxy = { "Amitay",{1,1,1}, star_system, 1,10,100,1 };

    Galaxy** galaxies = ALLOCATE(Galaxy**, 1);
    galaxies[0] = &galaxy;


    SpaceCraft sp1 = {"f1","t",1500,1};
    SpaceCraft sp2 = { "f2","q",1500,2 };
    SpaceCraft sp3 = { "f3","a",1500,3 };
    SpaceCraft sp4 = { "f4","z",1500,4 };

    SpaceCraft** sCrafts = ALLOCATE(SpaceCraft**, 1);
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
    
    printCompanies(&manager);
    
    addCompanyToManager(&manager);
    
    manage_company_operations(&manager);
    
    
    /*
    int choice;

    do {
       
        printf("\nMain Menu:\n");
        printf("1. Add cosmic element\n");
        printf("2. Display The Universe\n");
        printf("3. Display All Companies\n");
        printf("4. Add Galaxy\n");
        printf("5. Add Company\n");
        printf("6. display Solar System\n");
        printf("7. Rename Planet\n");
        printf("8. Display All Cosmic Elements\n");
        printf("9. Exit\n");
        printf("10. Test - Companies interface\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            
            addCosmicElement(&manager);
            
            break;
        }
        case 2: {
            // Display Systems managed by UniversalManager
            displayCosmicElements(&manager);

            // Note: Considare removing "printGalaxies(&manager);"

            break;
        }
        case 3: {
            // Display Subcomponents within the Systems managed by UniversalManager
            printCompanies(&manager);
            break;
        }
        case 4: {
            // Add Galaxy to UniversalManager
            addGalaxyToManager(&manager);
            break;
        }
        case 5: {
            // Add Company to UniversalManager
            addCompanyToManager(&manager);
            break;
        }
        case 6: {
            // Increase Risk Levels across Systems managed by UniversalManager
            displaySolarSystem(&manager);
            break;
        }
        case 7: {
            // Rename a Planet within a System managed by UniversalManager
            renameCosmicElement(&manager);
            break;
        }
        case 8: {
            // Display All Cosmic elements managed by UniversalManager
            displayCosmicElements(&manager);
            break;
        }

        case 9: {
            printf("Exiting...\n");
            break;
        }

        case 10: {
            manage_company_operations(&manager);

            break;
        }
        default: {
            printf("Invalid choice. Please try again.\n");
        }
        }
    } while (choice != 9);

    // Free resources
    freeUniversalManager(&manager);

    return 0;
    */
}
