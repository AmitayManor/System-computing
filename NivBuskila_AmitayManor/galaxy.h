#ifndef GALAXY_H
#define GALAXY_H

#include "macros.h"
#include "utility.h"
#include "location.h"
#include "solar_system.h"
#include <stdio.h>

#define MAX_GALAXY_NAME 50
#define MAX_RISK_LVL 10
#define MIN_RISK_LVL 0

typedef struct UniversalManager UniversalManager;

typedef struct Galaxy {
    char name[MAX_GALAXY_NAME];
    Location portal_location;
    SolarSystem** star_systems;
    int num_solar_systems;
    int riskLevel;
    int size;
    int id;
} Galaxy;

void testGalaxyIO();

void testGalaxyBinaryIO();


void print_galaxy(void* g);

void updateGalaxyRiskLevel(Galaxy* galaxy);
int isSolarSystemIDUnique(const Galaxy* galaxy, const int id);
int isSolarSystemLocationUnique(const Galaxy* galaxy, const Location loc);
int isSolarSystemWithinGalaxy(const Galaxy* galaxy, const Location newSystemLoc);

int readGalaxyFromBinaryFile(Galaxy* galaxy, FILE* fp);
int writeGalaxyToBinaryFile(const Galaxy* galaxy, FILE* fp);
void writeGalaxyToText(FILE* fp, const Galaxy* galaxy);
int readGalaxyFromText(FILE* fp, Galaxy* galaxy);
void sort_solar_systems(Galaxy* galaxy, int sort_choice);

void display_solar_systems(Galaxy* galaxy);
void add_solar_system(Galaxy* galaxy);

void free_galaxy(Galaxy* galaxy);
Galaxy* create_galaxy(UniversalManager* mg);
void rename_galaxy(Galaxy* galaxy);

#endif // GALAXY_H