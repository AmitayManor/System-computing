#ifndef UNIVERSAL_MANAGER_H
#define UNIVERSAL_MANAGER_H

#include "macros.h"
#include "utility.h"
#include "galaxy.h"
#include "company.h"

#define MAX_RISK_LVL 10
#define MIN_RISK_LVL 0

typedef struct UniversalManager {
    Galaxy** galaxies;
    int numGalaxies;
    Company** companies;
    int numCompanies;
} UniversalManager;

void writeUniversalManagerToText(FILE* fp, const UniversalManager* manager);
int readUniversalManagerFromText(FILE* fp, UniversalManager* manager);
int writeUniversalManagerToBinaryFile(const UniversalManager* manager, FILE* fp);
int readUniversalManagerFromBinaryFile(UniversalManager* manager, FILE* fp);


void initUniversalManager(UniversalManager* manager);
void addGalaxy(UniversalManager* manager, Galaxy* galaxy);

void printCompanies(const UniversalManager* manager);
void freeUniversalManager(UniversalManager* manager);

Galaxy* findGalaxy(UniversalManager* manager, const char name[MAX_GALAXY_NAME]);
SolarSystem* findSolarSystem(Galaxy* galaxy, const char name[MAX_SOLAR_SYSTEM_NAME]);
Planet* findPlanet(SolarSystem* system, const name[MAX_PLANET_NAME]);

Galaxy* findGalaxy_byID(UniversalManager* manager, const int id);
SolarSystem* findSolarSystem_byID(Galaxy* galaxy, const int id);
Planet* findPlanet_byID(SolarSystem* system, const int id);
void searchCompany(UniversalManager* manager);

int check_unique_galaxy_location(UniversalManager* mg, Location galaxyLoc);
int check_unique_galaxy_id(UniversalManager* mg, int id);

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
void addPlanetToManager(UniversalManager* manager);
void addSolarSystemToManger(UniversalManager* manager);
void display_company_basic_data(Company* company);
void display_company_spacecrafts(Company* company);
void display_company_travels(Company* company);
void add_spacecraft_to_company(Company* company, UniversalManager* manager);
void add_travel_to_company(Company* company, UniversalManager* manager);
void addCosmicElement(UniversalManager* manager);

int isGalaxyIDUnique(const UniversalManager* manager, const int id);
int isGalaxyLocationUnique(const UniversalManager* manager, const Location loc);

#endif // UNIVERSAL_MANAGER_H