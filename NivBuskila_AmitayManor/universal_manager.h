#ifndef UNIVERSAL_MANAGER_H
#define UNIVERSAL_MANAGER_H

#include "galaxy.h"
#include "company.h"

typedef struct UniversalManager {
    Galaxy** galaxies;
    int numGalaxies;
    Company** companies;
    int numCompanies;
} UniversalManager;

void initUniversalManager(UniversalManager* manager);
void addGalaxy(UniversalManager* manager, Galaxy* galaxy);
//void addCompany(UniversalManager* manager, Company* company, Permission permission);
void printGalaxies(const UniversalManager* manager);
void printCompanies(const UniversalManager* manager);
void freeUniversalManager(UniversalManager* manager);
void loadSystemData(UniversalManager* manager, const char* filename);
void increaseRiskLevels(UniversalManager* manager);

Galaxy* findGalaxy(UniversalManager* manager, const char* name);
SolarSystem* findSolarSystem(Galaxy* galaxy, const char* name);
Planet* findPlanet(SolarSystem* system, const char* name);
void displayAllPlanets(const UniversalManager* manager);
void renamePlanet(UniversalManager* manager);
void createCompany(UniversalManager* mg);
void addCompanyToManager(UniversalManager* manager);
Galaxy* createGalaxy();
void addGalaxyToManager(UniversalManager* manager);
void manage_company_operations(UniversalManager* manager);
void manage_specific_company(UniversalManager* manager, Company* company);
void display_all_travels(const UniversalManager* manager);

void display_company_basic_data(Company* company);
void display_company_spacecrafts(Company* company);
void display_company_travels(Company* company);
void add_spacecraft_to_company(Company* company, UniversalManager* manager);
void add_travel_to_company(Company* company, UniversalManager* manager);
void edit_company_permissions(Company* company, UniversalManager* manager);
void export_company_data_to_bin(Company* company, const char* filename);
void export_company_data_to_txt(Company* company, const char* filename);

#endif // UNIVERSAL_MANAGER_H