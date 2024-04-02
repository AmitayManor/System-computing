#ifndef COMPANY_H
#define COMPANY_H

#include "permission.h"
#include "interstellar_travel.h"

typedef struct {
    char* name;
    int establishedYear;
    int numSpacecrafts;
    InterstellarTravel** travels;
    int numTravels;
    Permission permissionsZone;
} Company;

#endif // COMPANY_H