#include "universal_manager.h"
#include <stdlib.h>
#include <string.h>

static int (*compareCompanyFunctions[])(const void*, const void*) = {
    compareCompanyByNumTravels,
    compareCompanyByName,
    compareCompanyByNumSpaceCrafts
};
/* ----- Manus ----- */
void manage_company_operations(UniversalManager* manager) {

    if (!manager) {
        printf("Universal Manager is not initialized.\n");
        return;
    }

    int choice;
    do {
        printf("\n\n ---------- Company Management Menu: ----------\n");
        printf("1. Show all Companies\n");
        printf("2. Show all Travels\n");
        printf("3. Show all Space Crafts\n");
        printf("4. Add a new Company\n");
        printf("5. Manage Specific Company\n");
        printf("6. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:{
            printCompanies(manager);
            break;
        }
        case 2: {
            display_all_travels(manager);
            break;
        }
        case 3: {
            display_all_spaceCrafts(manager);
            break;
        }

        case 4: {
            addCompanyToManager(manager);
            break;
        }

        case 5: {
            flush_stdin();
            printCompanies(manager);

            if (manager->numCompanies == 0)
                break;

            char* companyName = ALLOCATE(char, MAX_COMPANY_NAME);
            printf("Enter Company Name: ");
            myGets(companyName, MAX_COMPANY_NAME);

            Company* selectedCompany = NULL;
            for (int i = 0; i < manager->numCompanies; i++) {
                if (STR_EQUAL(manager->companies[i]->name, companyName)) {
                    selectedCompany = manager->companies[i];
                    break;
                }
            }
            if (selectedCompany) manage_specific_company(manager, selectedCompany);
            else printf("Company with name '%s' not found.\n", companyName);

            break;
        }
        case 6: {
            printf("Returning to Main Menu...\n");
            break;
        }





        default: {
            printf("Invalid choice. Please try again.\n");
        }
        }
    } while (choice != 6);
}

void manage_specific_company(UniversalManager* manager, Company* company) {

    if (!company) {
        printf("Company not found.\n");
        return;
    }

    int choice;
    do {
        printf("\n ---------- Managing Company: %s ----------\n", company->name);
        printf("1. Display Basic Data\n");
        printf("2. Display company's space crafts fleet\n");
        printf("3. Display incoming Travels\n");
        printf("4. Add Space craft\n");
        printf("5. Add Travel\n");
        printf("6. Return to Company Management Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:
            display_company_basic_data(company);
            break;
        case 2:
            display_company_spacecrafts(company);
            break;
        case 3:
            display_company_travels(company);
            break;
        case 4:
            add_spacecraft_to_company(company, manager);
            break;
        case 5:
            add_travel_to_company(company, manager);
            break;
        case 6:
            printf("Returning to Company Management Menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void addCosmicElement(UniversalManager* manager) {
    int choice;
    flush_stdin();
    do {
        printf("\n ---------- Cosmic Management Menu: ----------\n");
        printf("1. Add Galaxy\n");
        printf("2. Add Solar System\n");
        printf("3. Add Planet\n");
        printf("4. Rename cosmic element\n");
        printf("5. Return to Main Menu\n");
        printf("Select an option: ");

        scanf("%d", &choice);


        switch (choice) {
        case 1:
            addGalaxyToManager(manager);
            break;
        case 2:
            addSolarSystemToManger(manager);
            break;
        case 3:
            addPlanetToManager(manager);
            break;

        case 4: 
            renameCosmicElement(manager);
            break;
        
        case 5:
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 5);
}

/* ----- Files -----*/
void importData(UniversalManager* manager) {
   
    int success = 0;
    FILE* fp;
    int choice;
    printf("\n--- Importing Data ---\n");
    if (!manager) {
        LOG_DEBUG("Error! no information.");
        return;
    }


    printf("Choose how to import the data:\n1. from .txt\n2. from .bin\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1: 
        fp = fopen("universal_manager.txt", "r");
        if (fp == NULL) {
            printf("Failed to open file for reading.\n");
            return;
        }
        success = readUniversalManagerFromText(fp, manager);
        if (success) {
            printf("Data imported successfully from universal_manager.txt\n");
        }
        else {
            printf("Failed to read data from text file.\n");
        }
        fclose(fp);
        break;
    case 2: 
        fp = fopen("universal_manager.bin", "rb");
        if (fp == NULL) {
            printf("Failed to open file for reading.\n");
            return;
        }
        success = readUniversalManagerFromBinaryFile(manager, fp);
        if (success) {
            printf("Data imported successfully from universal_manager.bin\n");
        }
        else {
            printf("Failed to read data from binary file.\n");
        }
        fclose(fp);
        break;
    default:
        printf("Invalid import type selected.\n");
        break;
    }
}

void exportData(const UniversalManager* manager) {

    FILE* fp;
    int choice;
    printf("\n--- Exporting the Data ---\n");
    if (!manager) {
        LOG_DEBUG("Error! no information.");
        return;
    }

    
        printf("Choose how to export the data:\n1. to .txt\n2. to .bin\n");
        scanf("%d", &choice);


        switch (choice) {
        case 1:  
            fp = fopen("universal_manager.txt", "w");
            if (fp == NULL) {
                printf("Failed to open file for writing.\n");
                return;
            }
            writeUniversalManagerToText(fp, manager);
            printf("Data exported successfully to universal_manager.txt\n");
            fclose(fp);
            break;
        case 2:  
            fp = fopen("universal_manager.bin", "wb");
            if (fp == NULL) {
                printf("Failed to open file for writing.\n");
                return;
            }
            if (writeUniversalManagerToBinaryFile(manager, fp)) {
                printf("Data exported successfully to universal_manager.bin\n");
            }
            else {
                printf("Failed to write data to binary file.\n");
            }
            fclose(fp);
            break;


        default:
            printf("Invalid export type selected.\n");
            break;
        }
    
}

void writeUniversalManagerToText(FILE* fp, const UniversalManager* manager) {
    fprintf(fp, "Number of Galaxies: %d\n", manager->numGalaxies);
    for (int i = 0; i < manager->numGalaxies; i++) {
        
        writeGalaxyToText(fp, manager->galaxies[i]);
    }

    fprintf(fp, "Number of Companies: %d\n", manager->numCompanies);
    for (int j = 0; j < manager->numCompanies; j++) {
        
        writeCompanyToText(fp, manager->companies[j]);
    }
}

int readUniversalManagerFromText(FILE* fp, UniversalManager* manager) {
    int numGalaxies, numCompanies;

    fscanf(fp, "Number of Galaxies: %d\n", &numGalaxies);
    manager->galaxies = ALLOCATE(Galaxy*,numGalaxies);
    for (int i = 0; i < numGalaxies; i++) {
        manager->galaxies[i] = ALLOCATE(Galaxy,1);
        if (!readGalaxyFromText(fp, manager->galaxies[i])) return 0;
    }
    manager->numGalaxies = numGalaxies;

    fscanf(fp, "Number of Companies: %d\n", &numCompanies);
    manager->companies = ALLOCATE(Company*,numCompanies);
    for (int j = 0; j < numCompanies; j++) {
        manager->companies[j] = ALLOCATE(Company,1);
        if (!readCompanyFromText(fp, manager->companies[j])) return 0;
    }
    manager->numCompanies = numCompanies;

    return 1;
}

int writeUniversalManagerToBinaryFile(const UniversalManager* manager, FILE* fp) {
    fwrite(&manager->numGalaxies, sizeof(int), 1, fp);
    for (int i = 0; i < manager->numGalaxies; i++) {
        writeGalaxyToBinaryFile(manager->galaxies[i], fp);
    }

    fwrite(&manager->numCompanies, sizeof(int), 1, fp);
    for (int j = 0; j < manager->numCompanies; j++) {
        writeCompanyToBinaryFile(manager->companies[j], fp);
    }

    return 1;
}

int readUniversalManagerFromBinaryFile(UniversalManager* manager, FILE* fp) {
    int numGalaxies, numCompanies;

    fread(&numGalaxies, sizeof(int), 1, fp);
    manager->galaxies = ALLOCATE(Galaxy*,numGalaxies);
    for (int i = 0; i < numGalaxies; i++) {
        manager->galaxies[i] = ALLOCATE(Galaxy,1);
        readGalaxyFromBinaryFile(manager->galaxies[i], fp);
    }
    manager->numGalaxies = numGalaxies;

    fread(&numCompanies, sizeof(int), 1, fp);
    manager->companies = ALLOCATE(Company*,numCompanies);
    for (int j = 0; j < numCompanies; j++) {
        manager->companies[j] = ALLOCATE(Company,1);
        readCompanyFromBinaryFile(manager->companies[j], fp);
    }
    manager->numCompanies = numCompanies;

    return 1;
}

/* ----- Functions ----- */
void initUniversalManager(UniversalManager* manager) {
    if (manager) {
        manager->galaxies = NULL;
        manager->numGalaxies = 0;
        manager->companies = NULL;
        manager->numCompanies = 0;
    }
}

void addGalaxy(UniversalManager* manager, Galaxy* galaxy) {
    if (manager && galaxy) {
        Galaxy** new_galaxies_array = realloc(manager->galaxies, (manager->numGalaxies + 1) * sizeof(Galaxy*));
        if (new_galaxies_array) {
            manager->galaxies = new_galaxies_array;
            manager->galaxies[manager->numGalaxies] = galaxy;
            manager->numGalaxies++;
        }
    }
}

void addGalaxyToManager(UniversalManager* manager) {
     
    Galaxy* galaxy = create_galaxy(manager);
    if (galaxy) {
        addGalaxy(manager, galaxy); 
    }
    else {
        LOG_DEBUG("Failed to create a new Galaxy.\n");
    }
}

void createCompany(UniversalManager* mg) {
    printf("\n--- Create Companies ---\n");
    flush_stdin();
    Company* cm = ALLOCATE(Company, 1);
    
    if (cm) {

        char name[MAX_COMPANY_NAME];
        get_company_name(name);
        cm->name = strdup(name);

        int established = get_establishment_year();
        cm->establishedYear = established;

        int numOfSpaceCrafts = get_num_of_spacecrafts();
        cm->numSpacecrafts = numOfSpaceCrafts;
        printf("\n");
        initialize_company_spacecrafts(cm, numOfSpaceCrafts);
        
        
        Permission permission = get_permission_zone();
        cm->permissionsZone = permission;
        int numOfSpaceTravels = get_num_of_travels();
        cm->numTravels = numOfSpaceTravels;
        printf("\n");
        initialize_company_travels(mg, cm, numOfSpaceTravels);

    }
    Company** new_companies_array = realloc(mg->companies, (mg->numCompanies + 1) * sizeof(Company*));
    if (new_companies_array) {
        mg->companies = new_companies_array;
        mg->companies[mg->numCompanies] = cm;
        mg->numCompanies++;
    }

    else {
        LOG_DEBUG("Failed to allocate memory for new Company.\n");
    }


}

void addCompanyToManager(UniversalManager* manager) {
    
    if (manager) {
        createCompany(manager);
    }
}

void printCompanies(const UniversalManager* manager) {
    if (manager && manager->companies) {
        printf("List of Companies:\n");
        for (int i = 0; i < manager->numCompanies; i++) {
            if (manager->companies[i]) {
                printf("Company %d: %s, Permission Zone: %d\n", i + 1, manager->companies[i]->name, manager->companies[i]->permissionsZone);
            }
        }
    }

    else {
        LOG_DEBUG("No companies are currently managed.\n");
    }
    if (manager->companies == 0)
        printf("\nThere are 0 Companies.\n");
}

void freeUniversalManager(UniversalManager* manager) {
    if (manager) {
        
        for (int i = 0; i < manager->numGalaxies; i++) {
            free_galaxy(manager->galaxies[i]); 
        }
        free(manager->galaxies);
        

        for (int i = 0; i < manager->numCompanies; i++) {
            free_company(manager->companies[i]);
        }
        free(manager->companies);
    }
}

Galaxy* findGalaxy_byID(UniversalManager* manager, const int id){
 
    for (int i = 0; i < manager->numGalaxies; i++) {
        if (manager->galaxies[i]->id==id) {
            return manager->galaxies[i];
        }
    }
    return NULL;
}

SolarSystem* findSolarSystem_byID(Galaxy* galaxy, const int id){
  
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (galaxy->star_systems[i]->id == id) {
            return galaxy->star_systems[i];
        }
    }
    return NULL;
}

Planet* findPlanet_byID(SolarSystem* system, const int id) {
   
    PlanetNode* current = system->planetsHead;
    while (current != NULL) {
        Planet* planet = (Planet*)current->planet;
        if (planet->id == id) {
            return planet;
        }
        current = current->next;
    }
        
    return NULL; 

}

Galaxy* findGalaxy(UniversalManager* manager, const char name[MAX_GALAXY_NAME]) {
  
    for (int i = 0; i < manager->numGalaxies; i++) {

        if(STR_EQUAL(manager->galaxies[i]->name, name))
            return manager->galaxies[i];
    }
    return NULL;
}

SolarSystem* findSolarSystem(Galaxy* galaxy, const char name[MAX_SOLAR_SYSTEM_NAME]) {
 
    for (int i = 0; i < galaxy->num_solar_systems; i++) {

        if(STR_EQUAL(galaxy->star_systems[i]->name, name))
            return galaxy->star_systems[i];
    }
    return NULL; 
}

Planet* findPlanet(SolarSystem* system, const name[MAX_PLANET_NAME]) {
    
    if (!system || !system->planetsHead || !name) {
        return NULL; 
    }

    PlanetNode* current = system->planetsHead;
    while (current != NULL) {
        Planet* planet = (Planet*)current->planet;
        if (planet && STR_EQUAL(planet->name, name)) {
            return planet; 
        }
        current = current->next; 
    }
    return NULL;
}

void displayCosmicElements(const UniversalManager* manager) {
    
    if (manager ) {
        for (int i = 0; i < manager->numGalaxies; i++)
            generic_print(manager->galaxies[i], print_galaxy);
    }
    else{
        LOG_DEBUG("No Galaxies are currently managed.\n");
    }
    if (manager->galaxies == 0)
        printf("\nThere are 0 Cosmic elements.\n");
}

void renameGalaxy(UniversalManager* manager) {
    
    flush_stdin();
    printf("\n--- All Galaxies ---\n");
    
    for (int i = 0; i < manager->numGalaxies;i++)
        printf("%d) %s\n", i+1, manager->galaxies[i]->name);

    char galaxyName[MAX_GALAXY_NAME], newName[MAX_GALAXY_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);
    
    int nameFalg = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy) {
            printf("Galaxy '%s' not found.\n", galaxyName);
            flush_stdin();
            myGets(galaxyName, MAX_GALAXY_NAME);
        }
        else
            nameFalg = 1;
        
    } while (!nameFalg);
    rename_galaxy(galaxy);
}

void renameSolarSystem(UniversalManager* manager) {
   
    flush_stdin();
    printf("\n--- All Galaxies ---\n");

    for (int i = 0; i < manager->numGalaxies;i++)
        printf("%d) %s\n", i + 1, manager->galaxies[i]->name);

    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME] ;
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    int nameFlag = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy) {
            printf("Galaxy '%s' not found.\n", galaxyName);
            flush_stdin();
            myGets(galaxyName, MAX_GALAXY_NAME);
        }
        else
            nameFlag = 1;

    } while (!nameFlag);

    printf("\n--- All Solar Systems ---\n");

    for (int i = 0; i < galaxy->num_solar_systems;i++)
        printf("%d) %s\n", i + 1, galaxy->star_systems[i]->name);

    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    nameFlag = 0;
    SolarSystem* system = ALLOCATE(SolarSystem, 1);
    
    do {
        system = findSolarSystem(galaxy, systemName);
        if (!system) {
            printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
            myGets(systemName, MAX_SOLAR_SYSTEM_NAME);
        }
        else
            nameFlag = 1;
    } while (!nameFlag);
    rename_solarSystem(system);

}

void renamePlanet(UniversalManager* manager) {
    flush_stdin();
    printf("\n--- All Galaxies ---\n");

    for (int i = 0; i < manager->numGalaxies;i++)
        printf("%d) %s\n", i + 1, manager->galaxies[i]->name);

    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME], planetName[MAX_PLANET_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    int nameFlag = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy) {
            printf("Galaxy '%s' not found.\n", galaxyName);
            flush_stdin();
            myGets(galaxyName, MAX_GALAXY_NAME);
        }
        else
            nameFlag = 1;

    } while (!nameFlag);

    printf("\n--- All Solar Systems ---\n");

    for (int i = 0; i < galaxy->num_solar_systems;i++)
        printf("%d) %s\n", i + 1, galaxy->star_systems[i]->name);
    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    nameFlag = 0;
    SolarSystem* system = ALLOCATE(SolarSystem, 1);

    do {
        system = findSolarSystem(galaxy, systemName);
        if (!system) {
            printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
            flush_stdin();
            myGets(systemName, MAX_SOLAR_SYSTEM_NAME);
        }
        else
            nameFlag = 1;
    } while (!nameFlag);

    nameFlag = 0;
    printf("\n--- All Planets ---\n");

    PlanetNode* current = system->planetsHead;
    while (current != NULL) {

        generic_print(current->planet, print_planet);
        current = current->next;
    }
    printf("Enter Planet Name: ");
    myGets(planetName, MAX_PLANET_NAME);

    Planet* planet = ALLOCATE(Planet, 1);

    do {
        planet = findPlanet(system, planetName);
        if (!planet) {
            printf("Planet '%s' not found in Solar System '%s'.\n", planetName, systemName);
            flush_stdin();
            myGets(planetName, MAX_PLANET_NAME);
        }
        else
            nameFlag = 1;
    } while (!nameFlag);

    rename_planet(planet);
}

void renameCosmicElement(UniversalManager* manager) {
    int choice;
    
    do {
        printf("\n--- Rename Cosmic Elements ---\n");
        printf("1. Rename Galaxy\n");
        printf("2. Rename Solar System\n");
        printf("3. Rename Planet\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        
        scanf("%d", &choice);

        switch (choice) {
            
        case 1:
            renameGalaxy(manager);

            break;
        case 2:
            renameSolarSystem(manager);
            break;
        case 3:
            renamePlanet(manager);
            break;
        case 4:
            printf("Returning to main menu.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);
}

void display_all_travels(const UniversalManager* manager) {
    if (!manager) {
        LOG_DEBUG("No manager initialized.\n");
        return;
    }
    printf("\n--- All Travels ---\n");
    for (int i = 0; i < manager->numCompanies; i++) {
        Company* company = manager->companies[i];
        printf("\nCompany: %s has %d incoming travels\n", company->name, company->numTravels);
        if (company->numTravels > 0) {
            for (int j = 0; j < company->numTravels; j++) {
                InterstellarTravel* travel = company->travels[j];
                printf("Travel %d: From %s to %s\n", j + 1, travel->travelCodeSrc, travel->travelCodeDst);
                printf("  Spacecraft: %s (ID: %d, Model: %s, Max Speed: %.2f)\n", travel->spaceCraft->name, travel->spaceCraft->craftId, travel->spaceCraft->model, travel->spaceCraft->maxSpeed);

                printf("  Departure: ");
                print_date(&travel->departureDate);

                printf(", Arrival: ");
                print_date(&travel->arrivalDate);
                printf(", Distance: %.2f, Risk Level: %d, Completed: %s\n", travel->distance, travel->riskLevel, travel->isCompleted ? "Yes" : "No");
            }
        }
    }
}

void display_all_spaceCrafts(const UniversalManager* manager) {
    if(!manager){
        LOG_DEBUG("No manager initialized.\n");
        return;
    }
    printf("\n--- All Space Crafts ---\n");
    for (int i = 0; i < manager->numCompanies; i++) {
        Company* company = manager->companies[i];
        printf("\nCompany: %s has %d Space Crafts\n", company->name, company->numSpacecrafts);
        if (company->numSpacecrafts > 0) {
            for (int j = 0; j < company->numSpacecrafts; j++) {
                SpaceCraft* craft = company->spaceCrafts[j];
                print_spacecraft(craft);
            }
        }
    }
}

void display_company_basic_data(Company* company){
    printf("\n\n--- Company Basic Data ---\n");
    printf("\tName: %s\n", company->name);
    printf("\tNumber of Spacecrafts: %d\n", company->numSpacecrafts);
    printf("\tNumber of Travels: %d\n", company->numTravels);
    printf("\tPermissions Zone: %d\n", company->permissionsZone);
    printf("\n");
}

void display_company_spacecrafts(Company* company){
   
    printf("\n\n--- %s Fleet of Space Crafts ---\n", company->name);
    for (int i = 0; i < company->numSpacecrafts; i++) {
        printf("\tSpacecraft %d: Name: %s, Model: %s, Max Speed: %.2f, ID: %d\n", i + 1, company->spaceCrafts[i]->name, company->spaceCrafts[i]->model, company->spaceCrafts[i]->maxSpeed, company->spaceCrafts[i]->craftId);
    }
    printf("\n");
}

void display_company_travels(Company* company){
  
    printf("\n\n--- %s has %d Incoming Travels ---\n", company->name, company->numTravels);
    
    for (int i = 0; i < company->numTravels; i++) {
        InterstellarTravel* travel = company->travels[i];
        printf("\tTravel %d: Src: %s, Dst: %s, SpaceCraft: %s, Departure: ", i + 1, travel->travelCodeSrc, travel->travelCodeDst, travel->spaceCraft->name);
        print_date(&travel->departureDate);
        printf(", Arrival: ");
        print_date(&travel->arrivalDate);
        printf(", Distance: %.2f, Risk Level: %d\n", travel->distance, travel->riskLevel);
    }
    
    printf("\n");
}

void addSolarSystemToManger(UniversalManager* manager) {
    
    printf("\n --- Adding a new Solar System ---\n");
    
    int numberOfGalaxy;

    displayCosmicElements(manager);

    do {

        printf("Choose wanted Galaxy by its number: ");
        scanf("%d", &numberOfGalaxy);


    } while (numberOfGalaxy <=0 || numberOfGalaxy > manager->numGalaxies);

    add_solar_system(manager->galaxies[numberOfGalaxy - 1]);
    
}

void addPlanetToManager(UniversalManager* manager) {

    printf("\n --- Adding a new Planet ---\n");

    int numberOfGalaxy;
    int numberOfSolarSystems;
    displayCosmicElements(manager);

    do {
        printf("Choose wanted Galaxy by its number: ");
        scanf("%d", &numberOfGalaxy);

    } while (numberOfGalaxy <= 0 || numberOfGalaxy > manager->numGalaxies);

    printf("\n");
    display_solar_systems(manager->galaxies[numberOfGalaxy - 1]);
    printf("\n");

    do {
        printf("Choose wanted Solar System by its number: ");
        scanf("%d", &numberOfSolarSystems);

        if (numberOfSolarSystems <= 0 || numberOfSolarSystems > manager->galaxies[numberOfGalaxy - 1]->num_solar_systems)
            printf("\n\tError! wrong Index. Try again.\n");

    } while (numberOfSolarSystems <= 0 || numberOfSolarSystems > manager->galaxies[numberOfGalaxy - 1]->num_solar_systems);

    add_planet_to_solar_system(manager->galaxies[numberOfGalaxy - 1]->star_systems[numberOfSolarSystems - 1]);
    updateGalaxyRiskLevel(manager->galaxies[numberOfGalaxy - 1]);
}

void searchCompany(UniversalManager* manager) {
    
    printf("\n --- Search and Find Companies by attributes ---\n");
    
    int attribute;

    char* searchString = ALLOCATE(char, MAX_COMPANY_NAME);
    printf("Search Company by:\n\t1. Number of Travels\n\t2. Name\n\t3. Number of SpaceCrafts\n\tEnter choice: ");
    scanf("%d", &attribute);
    Company searchKey;
    Company* searchKeyPtr = &searchKey;

    switch (attribute) {
    case 1:  
        printf("Enter Number of Travels: ");
        scanf("%d", &searchKey.numTravels);
        qsort(manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyByNumTravels);
        break;
    case 2:  
        printf("Enter Company Name: ");
        myGets(searchString, MAX_COMPANY_NAME);
        searchKey.name = searchString;
        qsort(manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyByName);
        break;
    case 3:  
        printf("Enter Number of SpaceCrafts: ");
        scanf("%d", &searchKey.numSpacecrafts);
        qsort(manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyByNumSpaceCrafts);
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    Company** found = (Company**)bsearch(&searchKeyPtr, manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyFunctions[attribute - 1]);
    if (found) {
        Company* foundCompany = *found;
    }
    else {
        LOG_DEBUG("Company not found.\n");
    }

    free(searchString);
}

void add_spacecraft_to_company(Company* company, UniversalManager* manager) {

    printf("\n--- %s Fleet of Space Crafts ---\n", company->name);

    for (int i = 0;i < company->numSpacecrafts;i++)
        print_spacecraft(company->spaceCrafts[i]);

    printf("\n");

    int numOfSpaceCrafts = 0;
    printf("\n ---------- Adding Space Crafts to %s ----------", company->name);
    printf("\nEnter the amount of space crafts you want to add: ");
    scanf("%d", &numOfSpaceCrafts);
    printf("\n");
    if (numOfSpaceCrafts > 0) {
        
        SpaceCraft** newSpaceCraftsArray = realloc(company->spaceCrafts,
            (company->numSpacecrafts + numOfSpaceCrafts) * sizeof(SpaceCraft*));
        if (!newSpaceCraftsArray) {
            LOG_DEBUG("Error: Failed to allocate memory to expand spacecraft array.\n");
            return;
        }
        company->spaceCrafts = newSpaceCraftsArray;

        for (int i = 0; i < numOfSpaceCrafts; i++) {
            SpaceCraft* newCraft = ALLOCATE(SpaceCraft, 1);
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
            printf("\n --- Adding %d / %d Space Crafts ---\n", i+1, numOfSpaceCrafts);
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

            company->spaceCrafts[i+ company->numSpacecrafts] = newCraft;
        }
        company->numSpacecrafts += numOfSpaceCrafts;
    }
    else {
        company->spaceCrafts = NULL;
    }

    printf("\n After adding space crafts\n");
    for (int i = 0;i < company->numSpacecrafts;i++)
        print_spacecraft(company->spaceCrafts[i]);

}

void add_travel_to_company(Company* company, UniversalManager* manager) {
    
    printf("\n--- %s's Intersteller Travels ---\n", company->name);
    if (company->numTravels > 0){
        for(int i=0; i< company->numTravels; i++)
            print_travel(company->travels[i]);
    }
    else printf("%s Has %d Travels", company->name, company->numTravels);
    printf("\n------- Adding Intersteller Travels to Company: %s -------\n", company->name);
    
    int numTravelsToAdd = 0;
    printf("\nEnter the number of travels to add: ");
    scanf("%d", &numTravelsToAdd);

    if (numTravelsToAdd < 1) {
        LOG_DEBUG("Invalid number of travels to add.\n");
        return;
    }
    InterstellarTravel** newTravels = realloc(company->travels, (company->numTravels + numTravelsToAdd) * sizeof(InterstellarTravel*));
    if (!newTravels) {
        LOG_DEBUG("Failed to allocate memory to expand travels array.\n");
    }

    for (int i = 0; i < numTravelsToAdd; i++) {
        InterstellarTravel* newTravel = ALLOCATE(InterstellarTravel, 1);
        if (!newTravel) {
            LOG_DEBUG("Failed to allocate memory for new travel.\n");
            return;  
        }
        
        printf("--- Adding %d / %d Intersteller Travels ---", i + 1, numTravelsToAdd);
        get_travelID(company, newTravel);
        get_travelCode_Src(manager, newTravel);
        get_travelCode_Dst(manager, newTravel, company->permissionsZone);
        get_departureDate(newTravel);
        get_spaceCraft(company, newTravel);
        get_arrival_date(manager, newTravel);

        company->travels = newTravels;
        company->travels[company->numTravels] = newTravel;
        company->numTravels++;

        printf("Travel number: %d added successfully.\n", i + 1);
    }

    for (int i = 0; i < company->numTravels; i++)
        print_travel(company->travels[i]);

}

int isGalaxyIDUnique(const UniversalManager* manager, const int id) {
    for (int i = 0; i < manager->numGalaxies; i++) {
        if (manager->galaxies[i]->id == id) {
            return 0;  
        }
    }
    return 1;
}

int isGalaxyLocationUnique(const UniversalManager* manager,const Location loc) {
    for (int i = 0; i < manager->numGalaxies; i++) {
        if (isSameLocation(manager->galaxies[i]->portal_location, loc)) {
            return 0;  
        }
    }
    return 1;  
}

void sortElements(const UniversalManager* manager) {
    
    int choice;

    do {
        
        printf("\n--- Sorting Company's Elements---\n");

        printf("1. Sort Intersteller Travel Elements \n");
        printf("2. Sort Space Crafts Elements\n");
        printf("3. Return to main menu...\n");

        scanf("%d", &choice);

    switch (choice) {   
    case 1: {

        /*Choose Company*/
        printf("\n--- Choose a Company ---\n");
        flush_stdin();
        printCompanies(manager);

        if (manager->numCompanies == 0)
            break;

        char* companyName = ALLOCATE(char, MAX_COMPANY_NAME);
        printf("Enter Company Name: ");
        myGets(companyName, MAX_COMPANY_NAME);

        Company* selectedCompany = NULL;
        for (int i = 0; i < manager->numCompanies; i++) {
            if (STR_EQUAL(manager->companies[i]->name, companyName)) {
                selectedCompany = manager->companies[i];
                break;
            }
        }
        if (!selectedCompany) {
            printf("Company with the name '%s' not found.\n", companyName);
            break;
        }
        else {
            printf("\n--- Before Sorting ---\n");
            
            for (int i = 0; i < selectedCompany->numTravels;i++)
                print_travel(selectedCompany->travels[i]);

            int sortType;
            do {
                printf("\n--- Sort by ---\n");
                printf("1. ID\n2. Departure Date\n3. Distance\n");

                scanf("%d", &sortType);

                switch (sortType) {
                case 1: {
                    qsort(selectedCompany->travels, selectedCompany->numTravels, sizeof(InterstellarTravel*), compareTravelByID);
                    break;
                }
                case 2: {
                    qsort(selectedCompany->travels, selectedCompany->numTravels, sizeof(InterstellarTravel*), compareTravelByDepartureDate);
                    break;
                }
                case 3: {
                    qsort(selectedCompany->travels, selectedCompany->numTravels, sizeof(InterstellarTravel*), compareTravelByDistance);
                    break;
                }
                default: {

                    printf("\nWrong input.\n");
                    break;
                }
                }
            } while (sortType <1 || sortType >= 4);


            printf("\n--- After Sorting ---\n");
            for (int i = 0; i < selectedCompany->numTravels;i++)
                print_travel(selectedCompany->travels[i]);
        }

        
        break;
    }
    case 2: {
        /* Choose Company */
        printf("\n--- Choose a Company ---\n");
        flush_stdin();
        printCompanies(manager);

        if (manager->numCompanies == 0)
            break;

        char* companyName = ALLOCATE(char, MAX_COMPANY_NAME);
        printf("Enter Company Name: ");
        myGets(companyName, MAX_COMPANY_NAME);

        Company* selectedCompany = NULL;
        for (int i = 0; i < manager->numCompanies; i++) {
            if (STR_EQUAL(manager->companies[i]->name, companyName)) {
                selectedCompany = manager->companies[i];
                break;
            }
        }
        if (!selectedCompany) {
            printf("Company with the name '%s' not found.\n", companyName);
            break;
        }
        else {
            printf("\n--- Before Sorting SpaceCrafts ---\n");
            for (int i = 0; i < selectedCompany->numSpacecrafts; i++)
                print_spacecraft(selectedCompany->spaceCrafts[i]);

            int sortType;
            do {
                printf("\n--- Sort SpaceCrafts by ---\n");
                printf("1. ID\n2. Name\n3. Model\n");

                scanf("%d", &sortType);

                switch (sortType) {
                case 1:
                    qsort(selectedCompany->spaceCrafts, selectedCompany->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByID);
                    break;
                case 2:
                    qsort(selectedCompany->spaceCrafts, selectedCompany->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByName);
                    break;
                case 3:
                    qsort(selectedCompany->spaceCrafts, selectedCompany->numSpacecrafts, sizeof(SpaceCraft*), compareSpaceCraftByModel );
                    break;
                default:
                    printf("\nWrong input.\n");
                    break;
                }
            } while (sortType < 1 || sortType > 3);

            printf("\n--- After Sorting SpaceCrafts ---\n");
            for (int i = 0; i < selectedCompany->numSpacecrafts; i++)
                print_spacecraft(selectedCompany->spaceCrafts[i]);
        }

        break;
        break;
    }
    case 3: {
        printf("\nBye bye...\n");
        break;
    }

    default: {
        printf("\nWrong input! Try again.\n");
        break;
    }

    }

    } while (choice != 3);
}

void searchElements(const UniversalManager* manager){
    int choice;

    do {
        printf("\n--- Searching Company's Elements---\n");

        printf("1. Search Space Crafts \n");
        printf("2. Return to main menu... \n");
        

        scanf("%d", &choice);
    
        switch (choice) {
        
        case 1: {
            int type;
            char* searchString = ALLOCATE(char, MAX_LEN_SPACE_CRAFT);
            printf("1. Search By Name \n");
            printf("2. Search By Model \n");
            printf("3. Return to main menu...\n");

            scanf("%d", &type);

            if (type == 3) {
                printf("\nBye bye...\n");
                break;
            }
            flush_stdin();
            printf("\nEnter the Name/Model:\n");
            myGets(searchString, MAX_LEN_SPACE_CRAFT);
            searchString[strcspn(searchString, "\n")] = 0;
            int flag = 0;
            for (int i = 0; i < manager->numCompanies;i++) {
                SpaceCraft* foundSpaceCraft = ALLOCATE(SpaceCraft, 1);
                foundSpaceCraft = searchSpaceCraftAcrossCompanies(manager->companies[i], searchString, type);
                if (foundSpaceCraft) {
                    printf("SpaceCraft Found:\n");
                    printf("ID: %d\n", foundSpaceCraft->craftId);
                    printf("Name: %s\n", foundSpaceCraft->name);
                    printf("Model: %s\n", foundSpaceCraft->model);
                    printf("Max Speed: %.2f\n", foundSpaceCraft->maxSpeed);
                    flag = 1;
                    break;
                }

            }
            if (flag) {
                free(searchString);
                break;
            }

            printf("No SpaceCraft found with the given criteria.\n");
            free(searchString);
            break;
        }
        case 2: {
            printf("\nBye bye...\n");
            break;
        }
        default: {
            printf("\nWrong input! Try again.\n");
            break;
        }
        }
    } while (choice!=2);
}

void special_longestTravel(const UniversalManager* mg) {
    if (!mg) {
        printf("Error: Universal Manager is NULL.\n");
        return NULL;
    }
    printf("\n--- Finding the longest Travel in Space ---\n");
    InterstellarTravel* longestTravel = NULL;
    Company* targetCompany = NULL;
    double maxDistance = -1.0; 
    for (int i = 0; i < mg->numCompanies; i++) {
        Company* company = mg->companies[i];
        for (int j = 0; j < company->numTravels; j++) {
            InterstellarTravel* currentTravel = company->travels[j];
            if (currentTravel && currentTravel->distance > maxDistance) {
                maxDistance = currentTravel->distance;
                longestTravel = currentTravel;
                targetCompany = company;
            }
        }
    }
    print_travel(longestTravel);
    printf("Managed By: %s\n", targetCompany->name);
}

void special_dangerousCosmicElement(const UniversalManager* mg){
    if (!mg) {
        printf("Error: Universal Manager is NULL.\n");
        return NULL;
    }
    printf("\n--- Finding the most dangerous cosmic element in Space ---\n");
    char mostDangerousName[256] = { 0 };
    int highestRiskLevel = 0;

    for (int g = 0; g < mg->numGalaxies; g++) {
        Galaxy* galaxy = mg->galaxies[g];
        if (galaxy->riskLevel > highestRiskLevel) {
            strncpy(mostDangerousName, galaxy->name, sizeof(mostDangerousName) - 1);
            highestRiskLevel = galaxy->riskLevel;
        }

        for (int s = 0; s < galaxy->num_solar_systems; s++) {
            SolarSystem* system = galaxy->star_systems[s];
            if (system->risk_level > highestRiskLevel) {
                snprintf(mostDangerousName, sizeof(mostDangerousName), "Solar System: %s", system->name);
                highestRiskLevel = system->risk_level;
            }

            for (PlanetNode* pNode = system->planetsHead; pNode != NULL; pNode = pNode->next) {
                Planet* planet = pNode->planet;
                if (planet->riskLevel > highestRiskLevel) {
                    snprintf(mostDangerousName, sizeof(mostDangerousName), "Planet: %s", planet->name);
                    highestRiskLevel = planet->riskLevel;
                }
            }
        }
    }
    if (highestRiskLevel > 0) {
        printf("The most dangerous cosmic element is %s with a risk level of %d.\n", mostDangerousName, highestRiskLevel);
    }
    else {
        printf("No dangerous elements were found.\n");
    }


}
