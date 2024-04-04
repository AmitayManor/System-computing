#ifndef INTERSTELLAR_TRAVEL_H
#define INTERSTELLAR_TRAVEL_H

#include "date.h"
#include "spacecraft.h"
#include "permission.h"

#define MAX_CODE_LEN 16     // Travel code format: G####S####P####

typedef struct UniversalManager UniversalManager;


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

char* get_travelCode_Src(UniversalManager* mg, InterstellarTravel* tr, Permission permission);

char* get_travelCode_Dst(UniversalManager* mg, InterstellarTravel* tr, Permission permission);

void get_departure_date(InterstellarTravel* tr);


InterstellarTravel* create_interstellar_travel(const char* code, SpaceCraft* craft, Date departure, Date arrival, double distance, int riskLevel);
void calculate_arrival_date(InterstellarTravel* travel);
Date advance_date(Date date, int daysToAdd);
int calculate_risk_level(InterstellarTravel* travel);
int is_travel_successful(InterstellarTravel* travel);
void print_interstellar_travel(const InterstellarTravel* travel);
char extractTrcalCode(char code[MAX_CODE_LEN]);                     
void free_interstellar_travel(InterstellarTravel* travel);

#endif // INTERSTELLAR_TRAVEL_H