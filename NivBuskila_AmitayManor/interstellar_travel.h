#ifndef INTERSTELLAR_TRAVEL_H
#define INTERSTELLAR_TRAVEL_H

#include "date.h"
#include "spacecraft.h"

typedef struct {
    char* travelCode;
    SpaceCraft* spaceCraft;
    Date departureDate;
    Date arrivalDate;
    double distance;
    int riskLevel;
    int isCompleted;
} InterstellarTravel;

InterstellarTravel* create_interstellar_travel(const char* code, SpaceCraft* craft, Date departure, Date arrival, double distance, int riskLevel);
void free_interstellar_travel(InterstellarTravel* travel);

#endif // INTERSTELLAR_TRAVEL_H