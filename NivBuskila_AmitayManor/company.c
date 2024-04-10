#include "company.h"
#include <stdlib.h>
#include <stdio.h>

static int (*compareSpaceCraftFunctions[])(const void*, const void*) = {
    compareSpaceCraftByID,
    compareSpaceCraftByName,
    compareSpaceCraftByModel
};

static int (*compareTravelFunctions[])(const void*, const void*) = {
    compareTravelByID,
    compareTravelByDepartureDate,
    compareTravelByDistance
};

/*----Finished----*/

void get_company_name(char* name) {
    printf("Enter Company Name: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if (!myGets(name, MAX_COMPANY_NAME)) {
        LOG_DEBUG("Error reading company name.\n");
        //fprintf(stderr, "Error reading company name.\n");
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

int get_num_of_travels() {
    int numOfSpaceTravels;
    do {
        printf("Enter Company's amount of Intersteller Travels: ");
        scanf("%d", &numOfSpaceTravels);
    } while (numOfSpaceTravels < 0);
    return numOfSpaceTravels;
}

int isCraftIdUnique(const Company* company, int craftId) {
    if (!company || !company->spaceCrafts || company->numSpacecrafts <= 0) {
        return 1;
    }

    for (int i = 0; i < company->numSpacecrafts; ++i) {
        if (company->spaceCrafts[i]->craftId == craftId) {

            return 0;
        }
    }

    return 1;
}

void initialize_company_spacecrafts(Company* company, int numOfSpaceCrafts) {
    if (numOfSpaceCrafts > 0) {
        company->spaceCrafts = ALLOCATE(SpaceCraft**, numOfSpaceCrafts);
//        company->spaceCrafts = malloc(numOfSpaceCrafts * sizeof(SpaceCraft*));
        if (company->spaceCrafts == NULL) {
            LOG_DEBUG("Error: Failed to allocate memory for spacecrafts.\n");
            //fprintf(stderr, "Error: Failed to allocate memory for spacecrafts.\n");
            return;
        }

        for (int i = 0; i < numOfSpaceCrafts; i++) {
            //SpaceCraft* newCraft = create_individual_spacecraft(i + 1);
            SpaceCraft* newCraft = ALLOCATE(SpaceCraft*, 1);
            //SpaceCraft* newCraft = (SpaceCraft*)malloc(sizeof(SpaceCraft));

            if (newCraft == NULL) {
                LOG_DEBUG("Error: Failed to create spacecraft %d.\n", i + 1);
                //fprintf(stderr, "Error: Failed to create spacecraft %d.\n", i + 1);

                for (int j = 0; j < i; j++) {
                    free_spacecraft(company->spaceCrafts[j]);
                }
                free(company->spaceCrafts);
                company->spaceCrafts = NULL;
                company->numSpacecrafts = 0;
                return;
            }

            int idFlag = 0;
            do {
                get_SpaceCraft_id(newCraft->craftId);
                if (isCraftIdUnique(company, newCraft->craftId)) {
                    idFlag = 1;
                }
                else {
                    printf("\n\n Generated ID is not Unique. Try Again/\n\n");
                }
            } while (!idFlag);

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

void initialize_company_travels(UniversalManager* mg, Company* company, int numOfTravels) {

    if (numOfTravels > 0) {
        company->travels = ALLOCATE(InterstellarTravel**, numOfTravels);
//        company->travels = malloc(numOfTravels * sizeof(InterstellarTravel*));
        if (company->travels == NULL) {
            LOG_DEBUG("Error: Failed to allocate memory for travels.\n");
//            fprintf(stderr, "Error: Failed to allocate memory for travels.\n");
            return;
        }

        for (int i = 0; i < numOfTravels; i++) {
            InterstellarTravel* newTravel = ALLOCATE(InterstellarTravel*, 1);
            //InterstellarTravel* newTravel = (InterstellarTravel*)malloc(sizeof(InterstellarTravel));

            if (newTravel == NULL) {
                LOG_DEBUG("Error: Failed to create travel %d.\n", i + 1);
                //fprintf(stderr, "Error: Failed to create travel %d.\n", i + 1);

                for (int j = 0; j < i; j++) {
                    free_interstellar_travel(company->travels[j]);
                }
                free(company->travels);
                company->travels = NULL;
                company->numTravels = 0;
                return;
            }

            int idFlag = 0;
            int trId;
            do {
                printf("\nEnter an ID for this Travel (1-9999):\n");
                scanf("%d", &trId);

                if (check_unique_travel_id(company, trId))
                    newTravel->travelID = trId;
                else
                    printf("\nError! This ID is not valid. Try again.\n");

            } while (!idFlag);

            get_travelCode_Src(mg, newTravel);
            get_travelCode_Dst(mg, newTravel, company->permissionsZone);
            get_arrival_date(mg, newTravel);

            company->travels[i] = newTravel;
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

void print_company(void* cmp) {
    Company* company = (Company*)cmp;
    printf("Company Name: %s, Number of SpaceCrafts: %d, Number of Travels: %d\n", company->name, company->numSpacecrafts, company->numTravels);

    for (int i = 0; i < company->numSpacecrafts; i++) {
        generic_print(company->spaceCrafts[i], print_spacecraft);  // Use generic_print for each SpaceCraft
    }

    for (int i = 0; i < company->numTravels; i++) {
        generic_print(company->travels[i], print_travel);  // Use generic_print for each Travel
    }
}

void free_company(Company* company) {
    if (company) {
        free(company->name);
        for (int i = 0; i < company->numSpacecrafts; i++) {
            free_spacecraft(company->spaceCrafts + i); // Assumes a free_spacecraft function exists
        }
        free(company->spaceCrafts);

        for (int i = 0; i < company->numTravels; i++) {
            free_interstellar_travel(company->travels[i]); // Assumes a free_interstellar_travel function exists
        }
        free(company->travels);
        free(company);
    }
}

int compareCompanyByNumTravels(const void* a, const void* b) {
    const Company* cA = *(const Company**)a;
    const Company* cB = *(const Company**)b;
    return (cA->numTravels - cB->numTravels);
}

int compareCompanyByName(const void* a, const void* b) {
    const Company* cA = *(const Company**)a;
    const Company* cB = *(const Company**)b;
    return STR_EQUAL(cA->name, cB->name);
    //    return strcmp(cA->name, cB->name);
}

int compareCompanyByNumSpaceCrafts(const void* a, const void* b) {
    const Company* cA = *(const Company**)a;
    const Company* cB = *(const Company**)b;
    return (cA->numSpacecrafts - cB->numSpacecrafts);
}

void searchSpaceCraft(Company* company) {
    int attribute, searchID;
    char* searchString = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);
//    char* searchString = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));

    printf("Search SpaceCraft by: 1. ID\n2. Name\n3. Model\nEnter choice: ");
    scanf("%d", &attribute);
    SpaceCraft searchKey;
    SpaceCraft* searchKeyPtr = &searchKey;

    switch (attribute) {
    case 1:  // ID
        printf("Enter SpaceCraft ID: ");
        scanf("%d", &searchID);
        searchKey.craftId = searchID;
        qsort(company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByID);
        break;
    case 2:  // Name
        printf("Enter SpaceCraft Name: ");
        myGets(searchString, MAX_LEN_SPACE_CRAFT);  
        searchKey.name = searchString;
        qsort(company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByName);
        break;
    case 3:  // Model
        printf("Enter SpaceCraft Model: ");
        myGets(searchString, MAX_LEN_SPACE_CRAFT);  
        searchKey.model = searchString;
        qsort(company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByModel);
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    SpaceCraft** found = (SpaceCraft**)bsearch(&searchKeyPtr, company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftFunctions[attribute - 1]);
    if (found) {
        SpaceCraft* foundSpaceCraft = *found;
    }
    else {
        printf("SpaceCraft not found.\n");
    }
    free(searchString);
}

void searchTravel(Company* company) {
    int attribute;
    printf("Search Travel by: 1. ID\n2. Departure Date\n3. Distance\nEnter choice: ");
    scanf("%d", &attribute);
    InterstellarTravel searchKey;
    InterstellarTravel* searchKeyPtr = &searchKey;
    Date searchDate;

    switch (attribute) {
    case 1:  // ID
        printf("Enter Travel ID: ");
        scanf("%d", &searchKey.travelID);
        qsort(company->travels, company->numTravels, sizeof(InterstellarTravel*), compareTravelByID);
        break;
    case 2:  // Departure Date
        printf("Enter Departure Date (YYYY MM DD): ");
        scanf("%d %d %d", &searchDate.year, &searchDate.month, &searchDate.day);
        searchKey.departureDate = searchDate;
        qsort(company->travels, company->numTravels, sizeof(InterstellarTravel*), compareTravelByDepartureDate);
        break;
    case 3:  // Distance
        printf("Enter Travel Distance: ");
        scanf("%lf", &searchKey.distance);  
        qsort(company->travels, company->numTravels, sizeof(InterstellarTravel*), compareTravelByDistance);
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    InterstellarTravel** found = (InterstellarTravel**)bsearch(&searchKeyPtr, company->travels, company->numTravels, sizeof(InterstellarTravel*), compareTravelFunctions[attribute - 1]);
    if (found) {
        InterstellarTravel* foundTravel = *found;
        
    }
    else {
        printf("Travel not found.\n");
    }
}

/*----Needs to be finished----*/
void upgrade_permission(Company* company) {
    if (company && company->permissionsZone < eNUMOFPERMISSION - 1) {
        company->permissionsZone++;
    }
}

void downgrade_permission(Company* company) {
    if (company && company->permissionsZone > eNOPERMISSION) {
        company->permissionsZone--;
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



