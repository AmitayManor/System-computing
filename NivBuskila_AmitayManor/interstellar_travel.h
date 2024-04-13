#ifndef INTERSTELLAR_TRAVEL_H
#define INTERSTELLAR_TRAVEL_H

#include "macros.h"
#include "date.h"
#include "spacecraft.h"
#include "permission.h"
//#include "company.h"

#define MAX_CODE_LEN 16     // Travel code format: G####S####P####

typedef struct UniversalManager UniversalManager;
typedef struct  Company Company;

typedef struct {
    char travelCodeSrc[MAX_CODE_LEN];
    char travelCodeDst[MAX_CODE_LEN];
    SpaceCraft* spaceCraft;
    Date departureDate;
    Date arrivalDate;
    double distance;
    int riskLevel;
    int isCompleted;
    int travelID;
} InterstellarTravel;


int compareTravelByID(const void* a, const void* b);

int compareTravelByDepartureDate(const void* a, const void* b);

int compareTravelByDistance(const void* a, const void* b);

void initialize_interstellar_travel(InterstellarTravel* travel, UniversalManager* manager, Company* company);
void get_travelID(Company* company, InterstellarTravel* tr);
void get_departureDate(InterstellarTravel* tr);
void get_spaceCraft(Company* company,InterstellarTravel* tr);
void get_travelCode_Src(UniversalManager* mg, InterstellarTravel* tr);
void get_travelCode_Dst(UniversalManager* mg, InterstellarTravel* tr, Permission permission);
void get_arrival_date(UniversalManager* mg, InterstellarTravel* tr);

int check_unique_travel_id(Company* cm, const int id);

Date advance_date(Date date, int daysToAdd);
int calculate_risk_level(InterstellarTravel* travel);
int is_travel_successful(InterstellarTravel* travel);

void print_travel(void* tr);
void free_interstellar_travel(InterstellarTravel* travel);

#endif // INTERSTELLAR_TRAVEL_H