#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "macros.h"
#include "utility.h"
#include "planet.h"


typedef struct Galaxy Galaxy;


#define MAX_STAR_SYSTEMS 10
#define MAX_SOLAR_SYSTEM_NAME 50

typedef struct PlanetNode {
    void* planet;  // Pointer to a Planet structure
    struct PlanetNode* next;  // Pointer to the next node in the list
} PlanetNode;

typedef struct SolarSystem {
    char name[MAX_SOLAR_SYSTEM_NAME];
    Location portal_location;
    int risk_level;
    //Planet* planets[MAX_STAR_SYSTEMS];
    PlanetNode* planetsHead;
    int num_planets;
    int size;
    int id;
} SolarSystem;

int compareSolarSystems(const SolarSystem* pSS1, const SolarSystem* pSS2);
void debugCompareSS(const SolarSystem* pSS1, const SolarSystem* pSS2);
void testPlanetAndSolarSystemReadWrite();
void readSolarSystemFromText(FILE* fp, SolarSystem* system);
void writeSolarSystemToText(FILE* fp, const SolarSystem* system);

void addPlanet(SolarSystem* system, Planet* planet);

void removePlanet(SolarSystem* system, int planetID);

void freePlanetList(SolarSystem* system);


void print_solar_system(void* ss);
void display_solar_system(const SolarSystem* system);
void free_solar_system(SolarSystem* system);
SolarSystem* create_solar_system(Galaxy* galaxy);
// void add_planet_to_solar_system(SolarSystem* system, Planet* planet);
void rename_solarSystem(SolarSystem* system);
int isPlanetWithinSolarSystem(SolarSystem* solarSystem, Planet* planet);

int check_unique_planet_id(SolarSystem* sSystem, int id);
int check_unique_planet_location(SolarSystem* sSystem, Location planetLoc);

#endif // SOLAR_SYSTEM_H