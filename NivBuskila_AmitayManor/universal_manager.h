#ifndef UNIVERSAL_MANAGER_H
#define UNIVERSAL_MANAGER_H

#include "macros.h"
#include "utility.h"
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
void increaseRiskLevels(UniversalManager* manager);

Galaxy* findGalaxy(UniversalManager* manager, const char* name);
SolarSystem* findSolarSystem(Galaxy* galaxy, const char* name);
Planet* findPlanet(SolarSystem* system, const char* name);

Galaxy* findGalaxy_byID(UniversalManager* manager, const int id);
SolarSystem* findSolarSystem_byID(Galaxy* galaxy, const int id);
Planet* findPlanet_byID(SolarSystem* system, const int id);


int check_unique_galaxy_location(UniversalManager* mg, Location galaxyLoc);
int check_unique_galaxy_id(UniversalManager* mg, int id);

void displaySolarSystem(const UniversalManager* manager);
void displayCosmicElements(const UniversalManager* manager);
void renamePlanet(UniversalManager* manager);
void renameSolarSystem(UniversalManager* manager);
void renameGalaxy(UniversalManager* manager);
void renameCosmicElement(UniversalManager* manager);

void createCompany(UniversalManager* mg);
void addCompanyToManager(UniversalManager* manager);
void addGalaxyToManager(UniversalManager* manager);
void manage_company_operations(UniversalManager* manager);
void manage_specific_company(UniversalManager* manager, Company* company);

void display_all_travels(const UniversalManager* manager);
void addSolarSystemToManger(UniversalManager* manager);
void display_company_basic_data(Company* company);
void display_company_spacecrafts(Company* company);
void display_company_travels(Company* company);
void add_spacecraft_to_company(Company* company, UniversalManager* manager);
void add_travel_to_company(Company* company, UniversalManager* manager);
void edit_company_permissions(Company* company, UniversalManager* manager);
void export_company_data_to_bin(Company* company, const char* filename);
void export_company_data_to_txt(Company* company, const char* filename);
void addCosmicElement(UniversalManager* manager);
#endif // UNIVERSAL_MANAGER_H