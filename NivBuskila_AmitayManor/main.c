#include <stdio.h>
#include <assert.h>
#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"

   // testPlanetAndSolarSystemReadWrite();
    //testPlanetReadWrite();

void testCreateGalaxy() {
    UniversalManager manager;
    initUniversalManager(&manager);
    Galaxy* galaxy = create_galaxy(&manager);

    assert(galaxy != NULL); // Galaxy should be created successfully.
    assert(strlen(galaxy->name) > 0); // Name should not be empty.
    printf("\ngalaxy->name: %s\n", galaxy->name);
    assert(galaxy->id > 0 && galaxy->id < 10000);
    printf("\ngalaxy->id: %d\n", galaxy->id);
    assert(galaxy->size > 0); // Size should be positive.
    printf("\ngalaxy->size: %d\n", galaxy->size);
    assert(check_unique_galaxy_id(&manager, galaxy->id));
    
    int initialCount = manager.numGalaxies;
    printf("\ninitialCount:%d\n", initialCount);
    addGalaxy(&manager, galaxy);
    //addGalaxyToManager(&manager);

    assert(manager.numGalaxies == initialCount + 1); // The number of galaxies should increase by 1.
    printf("\ninitialCount:%d\n", manager.numGalaxies);
    assert(manager.galaxies[initialCount] != NULL); // The new galaxy should be added to the end of the manager's array.

    
}


void testCreateSolarSystem() {
    UniversalManager manager;
    initUniversalManager(&manager); // Assume this initializes a UniversalManager and its galaxies
    Galaxy galaxy = { "Amitay",{1,1,1}, NULL, 0,10,100,1 };
        
    SolarSystem* system = ALLOCATE(SolarSystem*, 1);
    add_solar_system(&galaxy, system);

    
    assert(system != NULL);
    assert(strlen(system->name) > 0);
    
    /*
    assert(system->id > 0 && system->id < 10000); // ID should be within valid range
    assert(system->size > 0); // Size should be positive
    assert(check_unique_solarSystem_id(&galaxy, system->id)); // ID should be unique within the galaxy
    assert(check_unique_solarSystem_location(&galaxy, system->portal_location)); // Location should be unique within the galaxy
    assert(isSolarSystemWithinGalaxy(&galaxy, system)); // SolarSystem should be within its parent Galaxy
  */
   


}














int main() {
  
    //testCreateGalaxy();
    testCreateSolarSystem();
    printf("\nDone\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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
