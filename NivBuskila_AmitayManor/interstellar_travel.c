#include "interstellar_travel.h"
#include <stdlib.h>
#include <string.h>

InterstellarTravel* create_interstellar_travel(const char* code, SpaceCraft* craft, Date departure, Date arrival, double distance, int riskLevel) {
    InterstellarTravel* travel = (InterstellarTravel*)malloc(sizeof(InterstellarTravel));
    if (travel) {
        travel->travelCode = strdup(code); // Assuming strdup is available or implemented
        travel->spaceCraft = craft;
        travel->departureDate = departure;
        travel->arrivalDate = arrival;
        travel->distance = distance;
        travel->riskLevel = riskLevel;
        travel->isCompleted = 0; // Assuming travels start as not completed
    }
    return travel;
}

void free_interstellar_travel(InterstellarTravel* travel) {
    if (travel) {
        free(travel->travelCode);
        // Note: Do not free spaceCraft here if it is managed elsewhere
        free(travel);
    }
}
