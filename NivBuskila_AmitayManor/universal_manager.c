#include "universal_manager.h"
#include <stdlib.h>
#include <string.h>

void initUniversalManager(UniversalManager* manager) {
    if (manager) {
        manager->galaxies = NULL;
        manager->numGalaxies = 0;
        manager->companies = NULL;
        manager->numCompanies = 0;
    }
}
Galaxy* createGalaxy() {
    char name[256];
    printf("Enter Galaxy Name: ");
    scanf("%255s", name); // Get the galaxy name from the user

    Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy)); // Allocate memory for the new Galaxy
    if (galaxy) {
        galaxy->name = strdup(name); // Duplicate the name and assign it to the Galaxy
        // Initialize other Galaxy attributes as needed...
    }
    return galaxy; // Return the pointer to the new Galaxy
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
    Galaxy* galaxy = createGalaxy(); // Create a new Galaxy
    if (galaxy) {
        addGalaxy(manager, galaxy); // Add the new Galaxy to the UniversalManager
    }
    else {
        printf("Failed to create a new Galaxy.\n");
    }
}
Company* createCompany() {
    char name[256];
    printf("Enter Company Name: ");
    scanf("%255s", name); // Get the company name from the user

    Company* company = (Company*)malloc(sizeof(Company)); // Allocate memory for the new Company
    if (company) {
        company->name = strdup(name); // Duplicate the name and assign it to the Company
        // Initialize other Company attributes as needed...
        company->permissionsZone = eNOPERMISSION; // Set default permissions
    }
    return company; // Return the pointer to the new Company
}

void addCompany(UniversalManager* manager, Company* company, Permission permission) {
    if (manager && company) {
        company->permissionsZone = permission;
        Company** new_companies_array = realloc(manager->companies, (manager->numCompanies + 1) * sizeof(Company*));
        if (new_companies_array) {
            manager->companies = new_companies_array;
            manager->companies[manager->numCompanies] = company;
            manager->numCompanies++;
        }
    }
}
void addCompanyToManager(UniversalManager* manager) {
    Company* company = createCompany(); // Create a new Company
    if (company) {
        addCompany(manager, company, company->permissionsZone); // Add the new Company to the UniversalManager
    }
    else {
        printf("Failed to create a new Company.\n");
    }
}

void printGalaxies(const UniversalManager* manager) {
    if (manager && manager->galaxies) {
        printf("List of Galaxies:\n");
        for (int i = 0; i < manager->numGalaxies; i++) {
            if (manager->galaxies[i]) {
                printf("Galaxy %d: %s\n", i + 1, manager->galaxies[i]->name);
            }
        }
    }
    else {
        printf("No galaxies are currently managed.\n");
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
        printf("No companies are currently managed.\n");
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

void loadSystemData(UniversalManager* manager, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Assuming each line contains either "Galaxy" or "Company" followed by respective names and attributes
        char type[10], name[50];
        if (sscanf(line, "%s %s", type, name) == 2) {
            if (strcmp(type, "Galaxy") == 0) {
                Galaxy* galaxy = (Galaxy*)malloc(sizeof(Galaxy));
                galaxy->name = strdup(name); // Assuming Galaxy struct has a name field
                // Initialize other galaxy fields as needed...
                addGalaxy(manager, galaxy);
            }
            else if (strcmp(type, "Company") == 0) {
                Company* company = (Company*)malloc(sizeof(Company));
                company->name = strdup(name); // Assuming Company struct has a name field
                // Initialize other company fields and set permissions as needed...
                addCompany(manager, company, eNOPERMISSION); // Example permission
            }
        }
    }

    fclose(file);
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
        printf("No galaxies to update.\n");
    }
}

Galaxy* findGalaxy(UniversalManager* manager, const char* name) {
    for (int i = 0; i < manager->numGalaxies; i++) {
        if (strcmp(manager->galaxies[i]->name, name) == 0) {
            return manager->galaxies[i];
        }
    }
    return NULL; // Not found
}

SolarSystem* findSolarSystem(Galaxy* galaxy, const char* name) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        if (strcmp(galaxy->star_systems[i]->name, name) == 0) {
            return galaxy->star_systems[i];
        }
    }
    return NULL; // Not found
}

Planet* findPlanet(SolarSystem* system, const char* name) {
    for (int i = 0; i < system->num_planets; i++) {
        if (strcmp(system->planets[i]->name, name) == 0) {
            return system->planets[i];
        }
    }
    return NULL; // Not found
}

void displayAllPlanets(const UniversalManager* manager) {
    // Assuming the UniversalManager has a method to iterate through all galaxies and their solar systems
    printf("Displaying all planets in the Universal Manager:\n");
    // This is a simplified placeholder. Actual iteration and display logic goes here...
    printf("Planet display functionality is not implemented yet.\n");
}

void renamePlanet(UniversalManager* manager) {
    char galaxyName[256], systemName[256], planetName[256], newName[256];
    printf("Enter Galaxy Name: ");
    scanf("%255s", galaxyName);
    printf("Enter Solar System Name: ");
    scanf("%255s", systemName);
    printf("Enter Planet Name: ");
    scanf("%255s", planetName);
    printf("Enter New Planet Name: ");
    scanf("%255s", newName);

    Galaxy* galaxy = findGalaxy(manager, galaxyName);
    if (!galaxy) {
        printf("Galaxy '%s' not found.\n", galaxyName);
        return;
    }

    SolarSystem* system = findSolarSystem(galaxy, systemName);
    if (!system) {
        printf("Solar System '%s' not found in Galaxy '%s'.\n", systemName, galaxyName);
        return;
    }

    Planet* planet = findPlanet(system, planetName);
    if (!planet) {
        printf("Planet '%s' not found in Solar System '%s'.\n", planetName, systemName);
        return;
    }

    // Rename the planet
    strncpy(planet->name, newName, sizeof(planet->name) - 1);
    planet->name[sizeof(planet->name) - 1] = '\0'; // Ensure null termination
    printf("Planet '%s' in Solar System '%s' of Galaxy '%s' renamed to '%s'.\n", planetName, systemName, galaxyName, newName);
}
