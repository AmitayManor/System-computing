#include <stdio.h>

#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"


int main() {  

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
