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
void addCompany(UniversalManager* manager, Company* company, Permission permission);
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
Company* createCompany();
void addCompanyToManager(UniversalManager* manager);
Galaxy* createGalaxy();
void addGalaxyToManager(UniversalManager* manager);

#endif // UNIVERSAL_MANAGER_H