#include <stdio.h>
#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"

int main() {
    UniversalManager manager;
    initUniversalManager(&manager);

    int choice;

    do {
        printf("\nMain Menu:\n");
        printf("1. Load System Data\n");
        printf("2. Display Systems\n");
        printf("3. Display Subcomponents\n");
        printf("4. Add Galaxy\n");
        printf("5. Add Company\n");
        printf("6. display Solar System\n");
        printf("7. Rename Planet\n");
        printf("8. Display All Planets\n");
        printf("9. Exit\n");
        printf("10. Test - Companies interface\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            
            addSolarSystemToManger(&manager);
            
            break;
        }
        case 2: {
            // Display Systems managed by UniversalManager
            printGalaxies(&manager);
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
            renamePlanet(&manager);
            break;
        }
        case 8: {
            // Display All Planets within Systems managed by UniversalManager
            displayAllPlanets(&manager);
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
}
