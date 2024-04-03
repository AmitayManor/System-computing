#include "company.h"
#include <stdlib.h>
#include <stdio.h>

// Assuming the existence of create_interstellar_travel and free_interstellar_travel functions

/*
Company* createCompany() {

    Company* company = (Company*)malloc(sizeof(Company));

    char name[MAX_COMPANY_NAME];
    int established, numOfSpaceCrafts, numOfTravels;
    Permission permission;

    printf("Enter Company Name: ");
    scanf("%255s", name); // Get the company name from the user

    do {
        printf("Enter Company's year of establishment: ");
        scanf("%d", &established);
    } while (established <= 0);


    do {
        printf("Enter Company's amount of Space Crafts: ");
        scanf("%d", &numOfSpaceCrafts);
    } while (numOfSpaceCrafts < 0);

    SpaceCraft* spaceCrafts = NULL;
    if (numOfSpaceCrafts > 0) {
        spaceCrafts = malloc(numOfSpaceCrafts * sizeof(SpaceCraft));
        for (int i = 0; i < numOfSpaceCrafts; i++) {
            char craftName[MAX_LEN_SPACE_CRAFT], craftModel[MAX_LEN_SPACE_CRAFT];
            double craftMaxSpeed = -1;
            int id = i + 1;

            printf("Enter name for spacecraft %d: ", id);
            scanf("%99s", craftName);

            printf("Enter model for spacecraft %d: ", id);
            scanf("%99s", craftModel);

            do {
                printf("Enter max speed (in km/s) for spacecraft %d (0 - 300000): ", i + 1);
                scanf("%lf", &craftMaxSpeed);
                if (craftMaxSpeed < MIN_SPEED || craftMaxSpeed > MAX_SPEED) {
                    printf("Invalid speed. Please enter a value between 0 and 300000.\n");
                }
            } while (craftMaxSpeed < MIN_SPEED || craftMaxSpeed > MAX_SPEED);

            char* dynamicCraftName = strdup(craftName);
            char* dynamicCraftModel = strdup(craftModel);

            SpaceCraft* newCraft = create_spacecraft(dynamicCraftName, dynamicCraftModel, craftMaxSpeed, id);

            if (!newCraft) {
                printf("Failed to create spacecraft %d.\n", i + 1);
                free(dynamicCraftName);
                free(dynamicCraftModel);
                break;
            }
            company->spaceCrafts[i] = newCraft;
        }
    }

    do {
        printf("Enter permission zone (0: No Permission, 1: Planet, 2: SolarSystem, 3: Galaxy): ");
        scanf("%d", (int*)&permission);
    } while (permission < eNOPERMISSION || permission >= eNUMOFPERMISSION);


    // Allocate memory for the new Company
    if (company) {
        company->name = strdup(name);
        company->establishedYear = established;
        company->numSpacecrafts = numOfSpaceCrafts;
        company->travels = NULL;        // implement
        company->numTravels = 0;        // implement
        company->permissionsZone = permission;

    }
    return company; // Return the pointer to the new Company
}
*/

/*
void get_company_name(char* name) {
    printf("Enter Company Name: ");
    scanf("%255s", name);  // Read the company name
}
*/

void get_company_name(char* name) {
    printf("Enter Company Name: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (!myGets(name, MAX_COMPANY_NAME)) {
        fprintf(stderr, "Error reading company name.\n");
        strncpy(name, "DefaultCompany", MAX_COMPANY_NAME - 1);
        name[MAX_COMPANY_NAME - 1] = '\0';
    }
}

int get_establishment_year() {
    int established;
    do {
        printf("Enter Company's year of establishment: ");
        scanf("%d", &established);
    } while (established <= 0);
    return established;
}

int get_num_of_spacecrafts() {
    int numOfSpaceCrafts;
    do {
        printf("Enter Company's amount of Space Crafts: ");
        scanf("%d", &numOfSpaceCrafts);
    } while (numOfSpaceCrafts < 0);
    return numOfSpaceCrafts;
}

void initialize_company_spacecrafts(Company* company, int numOfSpaceCrafts) {
    if (numOfSpaceCrafts > 0) {
        company->spaceCrafts = malloc(numOfSpaceCrafts * sizeof(SpaceCraft*));
        if (company->spaceCrafts == NULL) {
            
            fprintf(stderr, "Error: Failed to allocate memory for spacecrafts.\n");
            return;
        }

        for (int i = 0; i < numOfSpaceCrafts; i++) {
            //SpaceCraft* newCraft = create_individual_spacecraft(i + 1);
            
            SpaceCraft* newCraft = (SpaceCraft*)malloc(sizeof(SpaceCraft));

            if (newCraft == NULL) {
                
                fprintf(stderr, "Error: Failed to create spacecraft %d.\n", i + 1);
                
                for (int j = 0; j < i; j++) {
                    free_spacecraft(company->spaceCrafts[j]); 
                }
                free(company->spaceCrafts);  
                company->spaceCrafts = NULL; 
                company->numSpacecrafts = 0; 
                return;
            }

            newCraft->craftId = i + 1;
            get_SpaceCraft_name(newCraft);
            get_SpaceCraft_model(newCraft);
            get_SpaceCraft_speed(newCraft);

            company->spaceCrafts[i] = newCraft;  
        }
    }
    else {
        company->spaceCrafts = NULL;
    }
}

Permission get_permission_zone() {
    Permission permission;
    do {
        printf("Enter permission zone (0: No Permission, 1: Planet, 2: SolarSystem, 3: Galaxy): ");
        scanf("%d", (int*)&permission);
    } while (permission < eNOPERMISSION || permission >= eNUMOFPERMISSION);
    return permission;
}

void test_createCompany(Company* cm) {

}

Company* createCompany() {
    
    Company* company = (Company*)malloc(sizeof(Company));
    char name[MAX_COMPANY_NAME];

    get_company_name(name);
    int established = get_establishment_year();
    int numOfSpaceCrafts = get_num_of_spacecrafts();

    initialize_company_spacecrafts(company, numOfSpaceCrafts);

    Permission permission = get_permission_zone();

    if (company) {
        company->name = strdup(name);
        company->establishedYear = established;
        company->numSpacecrafts = numOfSpaceCrafts;
        company->travels = NULL;  // To be implemented
        company->numTravels = 0;  // To be implemented
        company->permissionsZone = permission;
    }
    return company;
}



void print_company(const Company* company) {
    if (company) {
        printf("Company Name: %s\n", company->name);
        printf("Established Year: %d\n", company->establishedYear);
        printf("Number of Spacecrafts: %d\n", company->numSpacecrafts);
        printf("Number of Interstellar Travels: %d\n", company->numTravels);
        printf("Permission Zone: %d\n", company->permissionsZone);
    }
}
                                                    
void upgrade_permission(Company* company) {
    if (company && company->permissionsZone < eNUMOFPERMISSION - 1) {
        company->permissionsZone++;
    }
}

void add_spacecraft(Company* company, SpaceCraft** spacecraft) {
    if (company && spacecraft) {
        company->numSpacecrafts++;
        company->spaceCrafts = realloc(company->spaceCrafts, company->numSpacecrafts * sizeof(SpaceCraft*));
        company->spaceCrafts[company->numSpacecrafts - 1] = *spacecraft;
    }
}

void add_interstellar_travel(Company* company, InterstellarTravel* travel) {
    if (company && travel) {
        company->numTravels++;
        company->travels = realloc(company->travels, company->numTravels * sizeof(InterstellarTravel*));
        company->travels[company->numTravels - 1] = travel;
    }
}

void downgrade_permission(Company* company) {
    if (company && company->permissionsZone > eNOPERMISSION) {
        company->permissionsZone--;
    }
}

void free_company(Company* company) {
    if (company) {
        free(company->name);
        for (int i = 0; i < company->numSpacecrafts; i++) {
            free_spacecraft(company->spaceCrafts+i); // Assumes a free_spacecraft function exists
        }
        free(company->spaceCrafts);

        for (int i = 0; i < company->numTravels; i++) {
            free_interstellar_travel(company->travels[i]); // Assumes a free_interstellar_travel function exists
        }
        free(company->travels);
        free(company);
    }
}
