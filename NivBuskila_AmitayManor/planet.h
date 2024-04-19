#ifndef PLANET_H
#define PLANET_H

#include "macros.h"
#include "location.h"
#include "utility.h"

#define MAX_PLANET_NAME 50
#define MAX_RISK_LVL 10
#define MIN_RISK_LVL 0

typedef struct SolarSystem SolarSystem;

typedef unsigned char BYTE;

typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int id;
    int riskLevel;
    int size;
} Planet;

typedef struct PlanetNode {
    Planet* planet;
    struct PlanetNode* next;
} PlanetNode;


int readPlanetFromText(FILE* fp, Planet* planet);
void writePlanetToText(FILE* fp, const Planet* planet);

int readPlanetFromBinaryFileCompressed(Planet* pPl, FILE* fp);
int savePlanetToBinaryFileCompressed(const Planet* pPl, FILE* fp);

void print_planet(void* p);
Planet* create_planet(SolarSystem* system);
void free_planet(Planet* planet);
void rename_planet(Planet* planet);
void freePlanetNode(PlanetNode* node);
void get_planet_name(Planet* planet);
void get_planet_id(SolarSystem* system, Planet* planet);
void get_planet_location(SolarSystem* system, Planet* planet);
void get_planet_radius(Planet* planet);
void get_planet_risk(Planet* planet);

#endif // PLANET_H