#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "universal_manager.h"
#include "galaxy.h"
#include "company.h"


int main() {  

    int choice;
    
    UniversalManager manager;
    initUniversalManager(&manager);

    printf("\n----- Welcome -----\n");
    
    importData(&manager);

    do {
       
        printf("\nMain Menu:\n");
        printf("1.  Display The System\n");
        printf("2.  Cosmic interface\n");
        printf("3.  Companies interface\n");
        printf("4.  Export all data to file\n");
        printf("5.  Sort Company's Elements\n");
        printf("6.  Search Company's Elements\n");
        printf("7.  Special 1 - Longest Travel in Space\n");
        printf("8.  Special 2 - Most dangerous cosmic element in Space\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        
        case 1: {
            displayCosmicElements(&manager);
            printCompanies(&manager);
            break;
        }
        case 2: {
            
            addCosmicElement(&manager);
            break;
        }
        case 3: {
            manage_company_operations(&manager);
            break;
        }
        
        case 4: {
            
            exportData(&manager);
            break;
        }
        
        case 5: {
            sortElements(&manager);
            break;
        }
        case 6: {
            searchElements(&manager);
            break;
        }
        
        case 7:{
            special_longestTravel(&manager);
            break;
        }

        case 8: {
            special_dangerousCosmicElement(&manager);
            break;
        }
        case 9: {
            printf("Exiting...\n");
            break;
        }
        default: {
            printf("Invalid choice. Please try again.\n");
        }
        }
    } while (choice != 9);
    


    freeUniversalManager(&manager);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
    
}
