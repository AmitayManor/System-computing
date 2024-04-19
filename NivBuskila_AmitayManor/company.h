#ifndef COMPANY_H
#define COMPANY_H

#include "macros.h"
#include "permission.h"
#include "interstellar_travel.h"
#include "spacecraft.h"
#include "utility.h"

#define MAX_AMOUNT_OF_CRAFTS 50
#define MAX_COMPANY_NAME 256


typedef struct Company {
    char* name;
    int establishedYear;
    int numSpacecrafts;
    SpaceCraft** spaceCrafts;
    InterstellarTravel** travels;
    int numTravels;
    Permission permissionsZone;
} Company;


void writeCompanyToText(FILE* fp, const Company* company);
int readCompanyFromText(FILE* fp, Company* company);
int writeCompanyToBinaryFile(const Company* company, FILE* fp);
int readCompanyFromBinaryFile(Company* company, FILE* fp);

SpaceCraft* searchSpaceCraft(Company* company);
SpaceCraft* searchSpaceCraftFromFile(Company* company, const id);

int compareCompanyByNumTravels(const void* a, const void* b);
int compareCompanyByName(const void* a, const void* b);
int compareCompanyByNumSpaceCrafts(const void* a, const void* b);

void get_company_name(char* name);
int get_establishment_year();
int get_num_of_spacecrafts();
int get_num_of_travels();
void initialize_company_spacecrafts(Company* company, int numOfSpaceCrafts);
void initialize_company_travels(UniversalManager* mg, Company* company, int numOfTravels);
Permission get_permission_zone();
int isCraftIdUnique(const Company* company, int craftId);
void free_company(Company* company);
SpaceCraft* searchSpaceCraftAcrossCompanies(const Company* company, char* searchString, const int type);
void searchTravel(Company* company);

#endif // COMPANY_H