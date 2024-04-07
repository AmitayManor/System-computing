#include "universal_manager.h"
#include <stdlib.h>
#include <string.h>

static int (*compareCompanyFunctions[])(const void*, const void*) = {
    compareCompanyByNumTravels,
    compareCompanyByName,
    compareCompanyByNumSpaceCrafts
};


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
//        printf("Failed to create a new Galaxy.\n");
    }
}

void createCompany(UniversalManager* mg) {
    
    Company* cm = ALLOCATE(Company*, 1);
//    Company* cm = (Company*)malloc(sizeof(Company));
    
    if (cm) {

        char name[MAX_COMPANY_NAME];
        get_company_name(name);
        int established = get_establishment_year();
        int numOfSpaceCrafts = get_num_of_spacecrafts();
        initialize_company_spacecrafts(cm, numOfSpaceCrafts);
        Permission permission = get_permission_zone();
        int numOfSpaceTravels = get_num_of_travels();
        initialize_company_travels(mg, cm, numOfSpaceTravels);

        cm->name = strdup(name);
        cm->establishedYear = established;
        cm->numSpacecrafts = numOfSpaceCrafts;
        //cm->travels = NULL;  initialized via initialize_company_travels func //
        cm->numTravels = 0;  numOfSpaceTravels;
        cm->permissionsZone = permission;
    }
    Company** new_companies_array = realloc(mg->companies, (mg->numCompanies + 1) * sizeof(Company*));
    if (new_companies_array) {
        mg->companies = new_companies_array;
        mg->companies[mg->numCompanies] = cm;
        mg->numCompanies++;
    }

    else {
        LOG_DEBUG("Failed to allocate memory for new Company.\n");
        //printf("Failed to allocate memory for new Company.\n");
    }
}

void addCompanyToManager(UniversalManager* manager) {
    
    if (manager) {
        createCompany(manager);
    }
}

void printGalaxies(const UniversalManager* manager) {
    
    if (manager && manager->galaxies) {
        printf("List of Galaxies:\n");
        for (int i = 0; i < manager->numGalaxies; i++) {
           if (manager->galaxies[i]) {
                printf("Galaxy %d: %s\n", i + 1, manager->galaxies[i]->name);
               // add_solar_system(manager->galaxies[i]);
               // display_solar_systems(manager->galaxies[i]);
            }
        }
    }
    else {
        LOG_DEBUG("No galaxies are currently managed.\n");
//        printf("No galaxies are currently managed.\n");
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
        //printf("No companies are currently managed.\n");
    }
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

void increaseRiskLevels(UniversalManager* manager) {
    if (manager && manager->galaxies) {
        for (int i = 0; i < manager->numGalaxies; i++) {
            if (manager->galaxies[i]) {
                manager->galaxies[i]->riskLevel++; // Increase the risk level of each galaxy
                printf("Increased risk level of Galaxy %s to %d\n", manager->galaxies[i]->name, manager->galaxies[i]->riskLevel);
            }
        }
    }
    else {
        LOG_DEBUG("No galaxies to update.\n");
        //printf("No galaxies to update.\n");
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


Galaxy* findGalaxy(UniversalManager* manager, const char* name) {
  
    for (int i = 0; i < manager->numGalaxies; i++) {

        if(STR_EQUAL(manager->galaxies[i]->name, name))
            return manager->galaxies[i];
    }
    return NULL;
}

SolarSystem* findSolarSystem(Galaxy* galaxy, const char* name) {
 
    for (int i = 0; i < galaxy->num_solar_systems; i++) {

        if(STR_EQUAL(galaxy->star_systems[i]->name, name))
            return galaxy->star_systems[i];
    }
    return NULL; 
}

Planet* findPlanet(SolarSystem* system, const char* name) {
    
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

    /*
    printf("\n--- Displaying Cosmic Elements ---\n");
    for (int i = 0; i < manager->numGalaxies; ++i) {
        Galaxy* galaxy = manager->galaxies[i];
        printf("Galaxy %d: %s | ID: %d\n", i + 1, galaxy->name, galaxy->id);

        for (int j = 0; j < galaxy->num_solar_systems; ++j) {
            SolarSystem* solarSystem = galaxy->star_systems[j];
            printf("\tSolar System %d: %s| ID: %d\n", j + 1, solarSystem->name, solarSystem->id);

            for (int k = 0; k < solarSystem->num_planets; ++k) {
                Planet* planet = solarSystem->planets[k];
                printf("\t\tPlanet %d: %s| ID: %d\n", k + 1, planet->name, planet->id);
            }
        }
    }
    */
}

/*Add do-while loop*/
void renameGalaxy(UniversalManager* manager) {
  
    char galaxyName[MAX_GALAXY_NAME], newName[MAX_GALAXY_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);
    

    Galaxy* galaxy = findGalaxy(manager, galaxyName);
    if (!galaxy) {
        printf("Galaxy '%s' not found.\n", galaxyName);
        return;
    }
    rename_galaxy(galaxy);
}
/*Add do-while loop*/
void renameSolarSystem(UniversalManager* manager) {
   
    
    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME] ;
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    Galaxy* galaxy = findGalaxy(manager, galaxyName);
    if (!galaxy) {
        printf("Galaxy '%s' not found.\n", galaxyName);
        return;
    }

    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    SolarSystem* system = findSolarSystem(galaxy, systemName);
    if (!system) {
        printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
        return;
    }
    rename_solarSystem(system);

}
/*Add do-while loop*/
void renamePlanet(UniversalManager* manager) {
    char galaxyName[MAX_GALAXY_NAME], systemName[MAX_SOLAR_SYSTEM_NAME], planetName[MAX_PLANET_NAME];
    printf("Enter Galaxy Name: ");
    myGets(galaxyName, MAX_GALAXY_NAME);

    Galaxy* galaxy = findGalaxy(manager, galaxyName);
    if (!galaxy) {
        printf("Galaxy '%s' not found.\n", galaxyName);
        return;
    }

    printf("Enter Solar System Name: ");
    myGets(systemName, MAX_SOLAR_SYSTEM_NAME);

    SolarSystem* system = findSolarSystem(galaxy, systemName);
    if (!system) {
        printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
        return;
    }

    printf("Enter Planet Name: ");
    myGets(planetName, MAX_PLANET_NAME);

    Planet* planet = findPlanet(system, planetName);
    if (!planet) {
        printf("Planet '%s' not found in Solar System '%s'.\n", planetName, systemName);
        return;
    }

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
        for (int j = 0; j < company->numTravels; j++) {
            InterstellarTravel* travel = company->travels[j];
            printf("Travel %d: From %s to %s\n", j + 1, travel->travelCodeSrc, travel->travelCodeDst);
            printf("  Spacecraft: %s (ID: %s, Model: %s, Max Speed: %.2f)\n",travel->spaceCraft->name, travel->spaceCraft->craftId ,travel->spaceCraft->model, travel->spaceCraft->maxSpeed);
            
            printf("  Departure: ");
            print_date(&travel->departureDate);
            
            printf(", Arrival: ");
            print_date(&travel->arrivalDate);
            printf(", Distance: %.2f, Risk Level: %d, Completed: %s\n", travel->distance, travel->riskLevel, travel->isCompleted ? "Yes" : "No");
        }
    }
}

void display_company_basic_data(Company* company){
    printf("\n--- Company Basic Data ---\n");
    printf("Name: %s\n", company->name);
    printf("Number of Spacecrafts: %d\n", company->numSpacecrafts);
    printf("Number of Travels: %d\n", company->numTravels);
    printf("Permissions Zone: %d\n", company->permissionsZone);
}

void display_company_spacecrafts(Company* company){
   
    printf("\n--- Company's Spacecrafts Fleet ---\n");
    for (int i = 0; i < company->numSpacecrafts; i++) {
        printf("Spacecraft %d: Name: %s, Model: %s, Max Speed: %.2f, ID: %d\n", i + 1, company->spaceCrafts[i]->name, company->spaceCrafts[i]->model, company->spaceCrafts[i]->maxSpeed, company->spaceCrafts[i]->craftId);
    }
}

void display_company_travels(Company* company){
  
    printf("\n--- Company's Incoming Travels ---\n");
    for (int i = 0; i < company->numTravels; i++) {
        InterstellarTravel* travel = company->travels[i];
        printf("Travel %d: Src: %s, Dst: %s, SpaceCraft: %s, Departure: ", i + 1, travel->travelCodeSrc, travel->travelCodeDst, travel->spaceCraft->name);
        print_date(&travel->departureDate);
        printf(", Arrival: ");
        print_date(&travel->arrivalDate);
        printf(", Distance: %.2f, Risk Level: %d\n", travel->distance, travel->riskLevel);
    }
}

/* To check if neccesery*/
void add_spacecraft_to_company(Company* company, UniversalManager* manager){
    
    if (company->numSpacecrafts >= MAX_AMOUNT_OF_CRAFTS) {
        
        LOG_DEBUG("Maximum number of spacecrafts reached.\n");
        //printf("Maximum number of spacecrafts reached.\n");
        return;
    }

    char* name = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);
    char* model = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);

    //char* name = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));     // MAX = 100
    //char* model = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));    // MAX = 100
    double maxSpeed;
    int craftId = company->numSpacecrafts + 1;  // Example ID generation logic
     
    printf("Enter spacecraft name: ");                  // Name checker
    scanf("%99s", name);
    printf("Enter spacecraft model: ");                 // Model checker
    scanf("%99s", model);
    printf("Enter max speed Max speed is: 300,000: ");  // Speed checker
    scanf("%lf", &maxSpeed);

    // Ensure the company's spaceCrafts array is large enough to hold another spacecraft
    company->spaceCrafts = realloc(company->spaceCrafts, (company->numSpacecrafts + 1) * sizeof(SpaceCraft));

    // Allocate a new spacecraft in the array
    SpaceCraft* newCraft = &company->spaceCrafts[company->numSpacecrafts];
    newCraft->name = name;  // name is already dynamically allocated
    newCraft->model = model;  // model is already dynamically allocated
    newCraft->maxSpeed = maxSpeed;
    newCraft->craftId = craftId;

    company->numSpacecrafts++;

    printf("Spacecraft '%s' added to company '%s'.\n", newCraft->name, company->name);

    free(name);
    free(model);

}

void manage_company_operations(UniversalManager* manager) {
    
    if (!manager) {
        printf("Universal Manager is not initialized.\n");
        return;
    }

    int choice;
    do {
        printf("\nCompany Management Menu:\n");
        printf("1. Show all Companies\n");
        printf("2. Show all Travels\n");
        printf("3. Manage Specific Company\n");
        printf("4. Export all Data\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printCompanies(manager);
            break;
        case 2:
            display_all_travels(manager);
            break;
        case 3: {

            char* companyName = ALLOCATE(char*, MAX_COMPANY_NAME);
//            char companyName[MAX_COMPANY_NAME];     // Max is 256 chars
            printf("Enter Company Name: ");
            myGets(companyName, MAX_COMPANY_NAME);  // Read the company name

            Company* selectedCompany = NULL;
            for (int i = 0; i < manager->numCompanies; i++) {
                if(STR_EQUAL(manager->companies[i]->name, companyName)) {
                    selectedCompany = manager->companies[i];
                    break;  
                }
            }

            if (selectedCompany) {
                manage_specific_company(manager, selectedCompany);
            }
            else {
                printf("Company with name '%s' not found.\n", companyName);
            }
            break;
        }

        case 4:
            
            /*
            Export all the companies data:
                1. Export to Bin file
                2. Export to txt file
            */

            break;
        case 5:
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

/*Check if neccesery*/
void addSolarSystemToManger(UniversalManager* manager) {
    
    char galaxyName[MAX_GALAXY_NAME];
    Galaxy* galaxy = NULL;
    printGalaxies(manager);
    
    //flush_stdin();
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

    char* galaxyName = ALLOCATE(char*, MAX_GALAXY_NAME);
//    char galaxyName[MAX_GALAXY_NAME];
    Galaxy* galaxy = NULL;

    printGalaxies(manager);
    do {
        printf("Enter galaxy's name :\n");
        if (!myGets(galaxyName, MAX_GALAXY_NAME)) {
            LOG_DEBUG("Failed to read input. Please try again.\n");
//            printf("Failed to read input. Please try again.\n");
            continue;
        }

        galaxy = findGalaxy(manager, galaxyName);
        if (galaxy == NULL) {
            printf("Error! Galaxy is not found. Try again.\n");
        }
    } while (!galaxy);

    display_solar_systems(galaxy);
    char systemName[MAX_SOLAR_SYSTEM_NAME];  // Assuming there's a constant for solar system names
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


/*
void addPlanetToManager(UniversalManager* manager) {
   
    char galaxyName[MAX_GALAXY_NAME];
    Galaxy* galaxy = NULL;

    printGalaxies(manager);
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
    //flush_stdin();

    display_solar_systems(galaxy);
    char systemName[MAX_PLANET_NAME];
    SolarSystem* system = NULL;
    do {

        printf("Enter Solar System's name :\n");

        if (!myGets(systemName, MAX_PLANET_NAME)) {
            printf("Failed to read input. Please try again.\n");
            continue;
        }

        system = findSolarSystem(galaxy, systemName);
        if (system == NULL) {
            printf("Error! Solar System is not found. Try again.\n");
            //flush_stdin();
        }
    } while (!system);
    
    //flush_stdin();

    Planet* planet = create_planet(system);
    add_planet_to_solar_system(system, planet);
    
}
*/

void addCosmicElement(UniversalManager* manager) {
    int choice;

    do {
        printf("\n--- Adding cosmic element system ---\n");
        printf("1. Add Galaxy\n");
        printf("2. Add Solar System\n");
        printf("3. Add Planet\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        //flush_stdin();
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
            printf("Exiting adding cosmic element system.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 4);
}

void manage_specific_company(UniversalManager* manager, Company* company) {
    
    if (!company) {
        printf("Company not found.\n");
        return;
    }

    int choice;
    do {
        printf("\nManaging Company: %s\n", company->name);
        printf("1. Display Basic Data\n");
        printf("2. Display company's space crafts fleet\n");
        printf("3. Display incomming Travels\n");
        printf("4. Add Space craft\n");
        printf("5. Add Travel\n");
        printf("6. Edit Permissions\n");
        printf("7. Return to Company Management Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // Display Basic Data (Company's name, ID, number of travels, number of space crafts, Flight Permissions)
            display_company_basic_data(company);
            break;
        case 2:
            // Display company's space crafts fleet (display for each space craft: name, model, maxSpeed, craftID)
            display_company_spacecrafts(company);
            break;
        case 3:
            // Display incomming Travels (display for each travel: travelCodeSrc,travelCodeDst, spaceCraft, departureDate, arrivalDate, distance, riskLevel)
            display_company_travels(company);
            break;
        case 4:
            // Add Space craft (add a new space craft from universalManager or create a new one and update also in universalManager)
            add_spacecraft_to_company(company, manager);
            break;
        case 5:
            // Add Travel (create a new travel based on the company' limitation: Permission zone and space crafts) 
            add_travel_to_company(company, manager);
            break;
        case 6:
            // Edit Permissions (downgrade or update permissions, needs to send a request to universalManager - and get an approval response from universalManager)
            edit_company_permissions(company, manager);
            break;
        case 7:
            printf("Returning to Company Management Menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

void displaySolarSystem(const UniversalManager* manager) {

    int numberOfGalaxy;
    printGalaxies(manager);
    printf("Enter galaxy number :\n");

    scanf("%d", &numberOfGalaxy); // need to enter do while
    display_solar_systems(manager->galaxies[numberOfGalaxy - 1]);
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


void add_travel_to_company(Company* company, UniversalManager* manager) {}
void edit_company_permissions(Company* company, UniversalManager* manager) {}
void export_company_data_to_bin(Company* company, const char* filename) {}
void export_company_data_to_txt(Company* company, const char* filename) {}

