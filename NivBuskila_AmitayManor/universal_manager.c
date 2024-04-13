#include "universal_manager.h"
#include <stdlib.h>
#include <string.h>

static int (*compareCompanyFunctions[])(const void*, const void*) = {
    compareCompanyByNumTravels,
    compareCompanyByName,
    compareCompanyByNumSpaceCrafts
};

/* ----- Manues ----- */
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
        printf("3. Manage Specific Company\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:
            printCompanies(manager);
            break;
        case 2:
            display_all_travels(manager);
            break;
        case 3: {

            flush_stdin();
            printCompanies(manager);
            char* companyName = ALLOCATE(char*, MAX_COMPANY_NAME);
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

        case 4:
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
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
        printf("3. Display incomming Travels\n");
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

    do {
        printf("\n--- Adding cosmic element system ---\n");
        printf("1. Add Galaxy\n");
        printf("2. Add Solar System\n");
        printf("3. Add Planet\n");
        printf("4. Return to Main Menu\n");
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
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);
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
    flush_stdin();
    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    galaxy = create_galaxy(manager);
    if (galaxy) {
        addGalaxy(manager, galaxy); 
    }
    else {
        LOG_DEBUG("Failed to create a new Galaxy.\n");
    }
}

void createCompany(UniversalManager* mg) {
    
    flush_stdin();
    Company* cm = ALLOCATE(Company*, 1);
    
    if (cm) {

        char name[MAX_COMPANY_NAME];
        get_company_name(name);
        cm->name = strdup(name);

        int established = get_establishment_year();
        cm->establishedYear = established;

        int numOfSpaceCrafts = get_num_of_spacecrafts();
        cm->numSpacecrafts = numOfSpaceCrafts;

        initialize_company_spacecrafts(cm, numOfSpaceCrafts);
        
        
        Permission permission = get_permission_zone();
        cm->permissionsZone = permission;
        int numOfSpaceTravels = get_num_of_travels();
        cm->numTravels = numOfSpaceTravels;
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
            free_galaxy(manager->galaxies[i]); // Assumes a free_galaxy function exists
        }
        free(manager->galaxies);

        for (int i = 0; i < manager->numCompanies; i++) {
            // Assumes a free_company function exists
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

int check_unique_galaxy_location(UniversalManager* mg, Location galaxyLoc){
   
    if (!mg || !mg->galaxies || mg->numGalaxies <= 0)
        return 1;
    for (int i = 0; i < mg->numGalaxies; ++i) {
        if (isSameLocation(mg->galaxies[i]->portal_location, galaxyLoc))
            return 0;
    }
    return 1;
}

int check_unique_galaxy_id(UniversalManager* mg, int id) {
 
    if (!mg || !mg->galaxies || mg->numGalaxies <= 0) 
        return 1;

    for (int i = 0; i < mg->numGalaxies; ++i) {
        if (mg->galaxies[i]->id == id) 
            return 0;
    }
    return 1;
}

void displayCosmicElements(const UniversalManager* manager) {
    
    if (manager) {
        for (int i = 0; i < manager->numGalaxies; i++)
            generic_print(manager->galaxies[i], print_galaxy);
    }
}

void renameGalaxy(UniversalManager* manager) {
  
    char galaxyName[MAX_GALAXY_NAME], newName[MAX_GALAXY_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);
    
    int nameFalg = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy)
            printf("Galaxy '%s' not found.\n", galaxyName);
        else
            nameFalg = 1;
        
    } while (!nameFalg);
    rename_galaxy(galaxy);
}

void renameSolarSystem(UniversalManager* manager) {
   
    
    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME] ;
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    int nameFalg = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy)
            printf("Galaxy '%s' not found.\n", galaxyName);
        else
            nameFalg = 1;

    } while (!nameFalg);

    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    nameFalg = 0;
    SolarSystem* system = ALLOCATE(SolarSystem*, 1);
    
    do {
        system = findSolarSystem(galaxy, systemName);
        if (!system)
            printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
        else
            nameFalg = 1;
    } while (!nameFalg);
    rename_solarSystem(system);

}

void renamePlanet(UniversalManager* manager) {
    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME], planetName[MAX_PLANET_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    int nameFlag = 0;
    Galaxy* galaxy = ALLOCATE(Galaxy*, 1);
    do {
        galaxy = findGalaxy(manager, galaxyName);
        if (!galaxy)
            printf("Galaxy '%s' not found.\n", galaxyName);
        else
            nameFlag = 1;

    } while (!nameFlag);

    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    nameFlag = 0;
    SolarSystem* system = ALLOCATE(SolarSystem*, 1);

    do {
        system = findSolarSystem(galaxy, systemName);
        if (!system)
            printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
        else
            nameFlag = 1;
    } while (!nameFlag);

    nameFlag = 0;
    printf("Enter Planet Name: ");
    myGets(planetName, MAX_PLANET_NAME);

    Planet* planet = ALLOCATE(Planet*, 1);

    do {
        planet = findPlanet(system, planetName);
        if (!planet)
            printf("Planet '%s' not found in Solar System '%s'.\n", planetName, systemName);
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
//      printf("No manager initialized.\n");
        return;
    }
    printf("\n--- All Travels ---\n");
    for (int i = 0; i < manager->numCompanies; i++) {
        Company* company = manager->companies[i];
        printf("\nCompany: %s\n", company->name);
        if (company->numTravels > 0) {
            for (int j = 0; j < company->numTravels; j++) {
                InterstellarTravel* travel = company->travels[j];
                printf("Travel %d: From %s to %s\n", j + 1, travel->travelCodeSrc, travel->travelCodeDst);
                printf("  Spacecraft: %s (ID: %s, Model: %s, Max Speed: %.2f)\n", travel->spaceCraft->name, travel->spaceCraft->craftId, travel->spaceCraft->model, travel->spaceCraft->maxSpeed);

                printf("  Departure: ");
                print_date(&travel->departureDate);

                printf(", Arrival: ");
                print_date(&travel->arrivalDate);
                printf(", Distance: %.2f, Risk Level: %d, Completed: %s\n", travel->distance, travel->riskLevel, travel->isCompleted ? "Yes" : "No");
            }
        }
        printf("\thas %d Travels\n",company->numTravels);
    }
}

void display_company_basic_data(Company* company){
    printf("\n\n--- Company Basic Data ---\n");
    printf("Name: %s\n", company->name);
    printf("Number of Spacecrafts: %d\n", company->numSpacecrafts);
    printf("Number of Travels: %d\n", company->numTravels);
    printf("Permissions Zone: %d\n", company->permissionsZone);
    printf("\n");
}

void display_company_spacecrafts(Company* company){
   
    printf("\n\n--- %s Fleet of Space Crafts ---\n", company->name);
    for (int i = 0; i < company->numSpacecrafts; i++) {
        printf("Spacecraft %d: Name: %s, Model: %s, Max Speed: %.2f, ID: %d\n", i + 1, company->spaceCrafts[i]->name, company->spaceCrafts[i]->model, company->spaceCrafts[i]->maxSpeed, company->spaceCrafts[i]->craftId);
    }
    printf("\n");
}

void display_company_travels(Company* company){
  
    printf("\n\n--- %s has %d Incoming Travels ---\n", company->name, company->numTravels);
    
    for (int i = 0; i < company->numTravels; i++) {
        InterstellarTravel* travel = company->travels[i];
        printf("Travel %d: Src: %s, Dst: %s, SpaceCraft: %s, Departure: ", i + 1, travel->travelCodeSrc, travel->travelCodeDst, travel->spaceCraft->name);
        print_date(&travel->departureDate);
        printf(", Arrival: ");
        print_date(&travel->arrivalDate);
        printf(", Distance: %.2f, Risk Level: %d\n", travel->distance, travel->riskLevel);
    }
    
    printf("\n");
}

void addSolarSystemToManger(UniversalManager* manager) {
    
    flush_stdin();
    char galaxyName[MAX_GALAXY_NAME];
    Galaxy* galaxy = NULL;

    displayCosmicElements(manager);

    do {

        printf("Enter galaxy's name :\n");
        
        if (!myGets(galaxyName, MAX_GALAXY_NAME)) {
            printf("Failed to read input. Please try again.\n");
            continue; 
        }

        galaxy = findGalaxy(manager, galaxyName);
        if (galaxy == NULL) {
            printf("Error! Galaxy is not found. Try again.\n");
            //flush_stdin();
        }
    } while (!galaxy);
    
    add_solar_system(galaxy);
    
}

void addPlanetToManager(UniversalManager* manager) {
    flush_stdin();
    char galaxyName[MAX_GALAXY_NAME];
    Galaxy* galaxy = NULL;

    for (int i = 0; i < manager->numGalaxies; i++)
        print_galaxy(manager->galaxies[i]);

    do {
        printf("Enter galaxy's name :\n");
        if (!myGets(galaxyName, MAX_GALAXY_NAME)) {
            LOG_DEBUG("Failed to read input. Please try again.\n");

            continue;
        }

        galaxy = findGalaxy(manager, galaxyName);
        if (galaxy == NULL) {
            printf("Error! Galaxy is not found. Try again.\n");
        }
    } while (!galaxy);

    print_galaxy(galaxy);

    char systemName[MAX_SOLAR_SYSTEM_NAME];  
    SolarSystem* system = NULL;
    do {
        printf("Enter Solar System's name :\n");
        if (!myGets(systemName, MAX_SOLAR_SYSTEM_NAME)) {
            printf("Failed to read input. Please try again.\n");
            continue;
        }

        system = findSolarSystem(galaxy, systemName);
        if (system == NULL) {
            printf("Error! Solar System is not found. Try again.\n");
        }
    } while (!system);

    Planet* planet = create_planet(system);  // Assuming create_planet does not need parameters
    if (planet) {
        addPlanet(system, planet);  // Adjusted to use the new linked list addition function
    }
    else {
        printf("Failed to create a new planet.\n");
    }
}

void searchCompany(UniversalManager* manager) {
    int attribute;

    char* searchString = ALLOCATE(char*, MAX_COMPANY_NAME);
    //char* searchString = (char*)malloc(MAX_COMPANY_NAME * sizeof(char));

    printf("Search Company by: 1. Number of Travels\n2. Name\n3. Number of SpaceCrafts\nEnter choice: ");
    scanf("%d", &attribute);
    Company searchKey;
    Company* searchKeyPtr = &searchKey;

    switch (attribute) {
    case 1:  // Number of Travels
        printf("Enter Number of Travels: ");
        scanf("%d", &searchKey.numTravels);
        qsort(manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyByNumTravels);
        break;
    case 2:  // Name
        printf("Enter Company Name: ");
        myGets(searchString, MAX_COMPANY_NAME);
        searchKey.name = searchString;
        qsort(manager->companies, manager->numCompanies, sizeof(Company*), compareCompanyByName);
        break;
    case 3:  // Number of SpaceCrafts
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
//        printf("Company not found.\n");
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
        InterstellarTravel* newTravel = ALLOCATE(InterstellarTravel*, 1);
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