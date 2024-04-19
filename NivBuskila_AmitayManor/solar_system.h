#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "macros.h"
#include "utility.h"
#include "planet.h"


typedef struct Galaxy Galaxy;


#define MAX_STAR_SYSTEMS 10
#define MAX_SOLAR_SYSTEM_NAME 50
#define MAX_RISK_LVL 10
#define MIN_RISK_LVL 0



typedef struct SolarSystem {
    char name[MAX_SOLAR_SYSTEM_NAME];
    Location portal_location;
    int risk_level;
    PlanetNode* planetsHead;
    int num_planets;
    int size;
    int id;
} SolarSystem;


void updateSolarSystemRiskLevel(SolarSystem* system);
void add_planet_to_solar_system(SolarSystem* system);

int readSolarSystemFromText(FILE* fp, SolarSystem* system);
void writeSolarSystemToText(FILE* fp, const SolarSystem* system);

int writeSolarSystemToBinaryFile(const SolarSystem* system, FILE* fp);
int readSolarSystemFromBinaryFile(SolarSystem* system, FILE* fp);


void freePlanetList(SolarSystem* system);
void print_solar_system(void* ss);
void display_solar_system(const SolarSystem* system);
void free_solar_system(SolarSystem* system);
SolarSystem* create_solar_system(Galaxy* galaxy);
void rename_solarSystem(SolarSystem* system);
int isPlanetWithinSolarSystem(SolarSystem* system, const Location newPlanetLoc);
int check_unique_planet_id(SolarSystem* sSystem, const int id);
int check_unique_planet_location(SolarSystem* sSystem, const Location planetLoc);

void get_solar_name(SolarSystem* system);
void get_solar_id(Galaxy* galaxy, SolarSystem* system);
void get_solar_location(Galaxy* galaxy, SolarSystem* system);
void get_solar_radius(SolarSystem* system);
#endif // SOLAR_SYSTEM_H