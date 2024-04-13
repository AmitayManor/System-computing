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

void writeCompanyToText(FILE* fp, const Company* company) {
    fprintf(fp, "Company Name: %s\n", company->name);
    fprintf(fp, "Established Year: %d\n", company->establishedYear);
    fprintf(fp, "Number of SpaceCrafts: %d\n", company->numSpacecrafts);
    for (int i = 0; i < company->numSpacecrafts; i++) {
        fprintf(fp, "SpaceCraft %d:\n", i + 1);
        writeSpaceCraftToText(fp, company->spaceCrafts[i]);
    }
    fprintf(fp, "Number of Travels: %d\n", company->numTravels);
    for (int j = 0; j < company->numTravels; j++) {
        fprintf(fp, "Travel %d:\n", j + 1);
        writeInterstellarTravelToText(fp, company->travels[j]);
    }
    fprintf(fp, "Permissions Zone: %d\n", company->permissionsZone);
}

int readCompanyFromText(FILE* fp, Company* company) {
    char buffer[MAX_COMPANY_NAME];
    if (fscanf(fp, "Company Name: %[^\n]\n", buffer) != 1) return 0;
    company->name = strdup(buffer);

    if (fscanf(fp, "Established Year: %d\n", &company->establishedYear) != 1) return 0;

    int numSpacecrafts;
    fscanf(fp, "Number of SpaceCrafts: %d\n", &numSpacecrafts);
    company->spaceCrafts = ALLOCATE(SpaceCraft**, numSpacecrafts);
    for (int i = 0; i < numSpacecrafts; i++) {
        company->spaceCrafts[i] = ALLOCATE(SpaceCraft*,1);
        if (!readSpaceCraftFromText(fp, company->spaceCrafts[i])) return 0;
    }
    company->numSpacecrafts = numSpacecrafts;

    int numTravels;
    fscanf(fp, "Number of Travels: %d\n", &numTravels);
    company->travels = ALLOCATE(InterstellarTravel**, numTravels);
    for (int j = 0; j < numTravels; j++) {
        company->travels[j] = ALLOCATE(InterstellarTravel*,1);
        if (!readInterstellarTravelFromText(fp, company->travels[j], company)) return 0;
    }
    company->numTravels = numTravels;

    fscanf(fp, "Permissions Zone: %d\n", &company->permissionsZone);

    return 1;
}

int writeCompanyToBinaryFile(const Company* company, FILE* fp) {
    int nameLen = strlen(company->name) + 1;  // Include null terminator
    fwrite(&nameLen, sizeof(int), 1, fp);
    fwrite(company->name, sizeof(char), nameLen, fp);
    fwrite(&company->establishedYear, sizeof(int), 1, fp);
    fwrite(&company->numSpacecrafts, sizeof(int), 1, fp);
    for (int i = 0; i < company->numSpacecrafts; i++) {
        writeSpaceCraftToBinaryFile(company->spaceCrafts[i], fp);
    }
    fwrite(&company->numTravels, sizeof(int), 1, fp);
    for (int j = 0; j < company->numTravels; j++) {
        writeInterstellarTravelToBinaryFile(company->travels[j], fp);
    }
    fwrite(&company->permissionsZone, sizeof(int), 1, fp);

    return 1;
}

int readCompanyFromBinaryFile(Company* company, FILE* fp) {
    int nameLen;
    fread(&nameLen, sizeof(int), 1, fp);
    company->name = ALLOCATE(char*,nameLen);
    fread(company->name, sizeof(char), nameLen, fp);
    fread(&company->establishedYear, sizeof(int), 1, fp);
    int numSpacecrafts;
    fread(&numSpacecrafts, sizeof(int), 1, fp);
    company->spaceCrafts = ALLOCATE(SpaceCraft**,numSpacecrafts);
    for (int i = 0; i < numSpacecrafts; i++) {
        company->spaceCrafts[i] = ALLOCATE(SpaceCraft*,1);
        readSpaceCraftFromBinaryFile(company->spaceCrafts[i], fp);
    }
    int numTravels;
    fread(&numTravels, sizeof(int), 1, fp);
    company->travels = ALLOCATE(InterstellarTravel**, numTravels);
    for (int j = 0; j < numTravels; j++) {
        company->travels[j] = ALLOCATE(InterstellarTravel*,1);
        readInterstellarTravelFromBinaryFile(company->travels[j], fp, company);
    }
    fread(&company->permissionsZone, sizeof(int), 1, fp);

    return 1;
}



void get_company_name(char* name) {
    printf("Enter Company Name: ");
    
    if (!myGets(name, MAX_COMPANY_NAME)) {
        LOG_DEBUG("Error reading company name.\n");
        
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
        return 1;  // Considered unique since there's nothing to compare against
    }

    for (int i = 0; i < company->numSpacecrafts; ++i) {
        if (company->spaceCrafts[i] && company->spaceCrafts[i]->craftId == craftId) {
            return 0;  // Found a duplicate
        }
    }
    return 1;
}

void initialize_company_spacecrafts(Company* company, int numOfSpaceCrafts) {
    
    if (numOfSpaceCrafts > 0) {
        company->spaceCrafts = ALLOCATE(SpaceCraft**, numOfSpaceCrafts);
        if (company->spaceCrafts == NULL) {
            LOG_DEBUG("Error: Failed to allocate memory for spacecrafts.\n");
            return;
        }

        for (int i = 0; i < numOfSpaceCrafts; i++) {
            company->spaceCrafts[i] = ALLOCATE(SpaceCraft*, 1);
            if (company->spaceCrafts[i] == NULL) {
                LOG_DEBUG("Allocation failed for SpaceCraft index %d\n", i);
            }
            else {   
                company->spaceCrafts[i]->craftId = -1;  
            }
        }

        for (int i = 0; i < numOfSpaceCrafts; i++) {
            SpaceCraft* newCraft = ALLOCATE(SpaceCraft*, 1);
            if (newCraft == NULL) {
                LOG_DEBUG("Error: Failed to create spacecraft %d.\n", i + 1);
                
                for (int j = 0; j < i; j++) {
                    free_spacecraft(company->spaceCrafts[j]);
                }
                free(company->spaceCrafts);
                company->spaceCrafts = NULL;
                company->numSpacecrafts = 0;
                return;
            }

            newCraft->craftId = -1; 

            int idFlag = 0;
            do {
                get_SpaceCraft_id(newCraft);
                if (isCraftIdUnique(company, newCraft->craftId)) {
                    idFlag = 1;
                }
                else {
                    printf("\n\nGenerated ID is not Unique. Try Again.\n\n");
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
        if (company->travels == NULL) {
            LOG_DEBUG("Error: Failed to allocate memory for travels.\n");
            return;
        }

        for (int i = 0; i < numOfTravels; i++) {
            company->travels[i] = ALLOCATE(SpaceCraft*, 1);
            if (company->travels[i] == NULL) {
                LOG_DEBUG("Allocation failed for SpaceCraft index %d\n", i);
            }
            else {
                company->travels[i]->travelID = -1;
            }
        }

        for (int i = 0; i < numOfTravels; i++) {
            InterstellarTravel* newTravel = ALLOCATE(InterstellarTravel*, 1);

            if (newTravel == NULL) {
                LOG_DEBUG("Error: Failed to create travel %d.\n", i + 1);

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

                if (check_unique_travel_id(company, trId)){
                    newTravel->travelID = trId;
                    idFlag = 1;
                }
                else
                    printf("\nError! This ID is not valid. Try again.\n");

            } while (!idFlag);

            get_travelCode_Src(mg, newTravel);
            get_travelCode_Dst(mg, newTravel, company->permissionsZone);
            get_spaceCraft(company, newTravel);
            get_departureDate(newTravel);
            get_arrival_date(mg, newTravel);

            company->travels[i] = newTravel;
        }
    }
    else {
        company->spaceCrafts = NULL;
    }
}

void get_departureDate(InterstellarTravel* tr) {
    
    printf("\n-------- Create the Departure date for Travel ID: %d --------\n", tr->travelID);
    Date* date = createDate();
    if (!date) {
        LOG_DEBUG("\nError! Memmory allocation failed.\n");
        return;
    }
    tr->departureDate = *date;


}

void get_spaceCraft(Company* company, InterstellarTravel* tr) {

    if (company && tr) {
        SpaceCraft* craft = ALLOCATE(SpaceCraft*, 1);
        if (!craft) {
            LOG_DEBUG("\nError! Space Craft not valid.\n");
            free_spacecraft(craft);
            return;
        }

        printf("\n-------- %d available Space Crfats in: %s --------\n", company->numSpacecrafts, company->name);
        for (int i = 0; i < company->numSpacecrafts; i++)
            print_spacecraft(company->spaceCrafts[i]);
        printf("\n---------------------------------------------------\n");

        craft = searchSpaceCraft(company);

        printf("\nchecking init craft\n");
        print_spacecraft(craft);
        printf("\n");
        
        tr->spaceCraft = craft;


    }
    else
        LOG_DEBUG("\nError! one of the fields are not initialized.\n");

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

SpaceCraft* searchSpaceCraftFromFile(Company* company, const id) {

    SpaceCraft searchKey;
    SpaceCraft* searchKeyPtr = &searchKey;
    searchKey.craftId = id;
    qsort(company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByID);
    SpaceCraft** found = (SpaceCraft**)bsearch(&searchKeyPtr, company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftFunctions[0]);

    if (found) {
        SpaceCraft* foundSpaceCraft = *found;
        return foundSpaceCraft;
    }
}

SpaceCraft* searchSpaceCraft(Company* company) {
    int attribute, searchID;
    char* searchString = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);

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

    free(searchString);

    SpaceCraft** found = (SpaceCraft**)bsearch(&searchKeyPtr, company->spaceCrafts, company->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftFunctions[attribute - 1]);
    if (found) {
        SpaceCraft* foundSpaceCraft = *found;
        return foundSpaceCraft;
    }
    else {
        printf("SpaceCraft not found.\n");
        return NULL;
    }
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



