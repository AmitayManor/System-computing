#ifndef COMPANY_H
#define COMPANY_H

#define MAX_AMOUNT_OF_CRAFTS 50
#define MAX_COMPANY_NAME 256
#include "permission.h"
#include "interstellar_travel.h"
#include "spacecraft.h"
#include "utility.h"


typedef struct {
    char* name;
    int establishedYear;
    int numSpacecrafts;
    SpaceCraft** spaceCrafts;
    InterstellarTravel** travels;
    int numTravels;
    Permission permissionsZone;
} Company;


Company* createCompany();
void upgrade_permission(Company* company);
void add_spacecraft(Company* company, SpaceCraft** spacecraft);
void add_interstellar_travel(Company* company, InterstellarTravel* travel);
void downgrade_permission(Company* company);
void free_company(Company* company);



#endif // COMPANY_H