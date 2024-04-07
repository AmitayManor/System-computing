#ifndef LOCATION_H
#define LOCATION_H

#include "macros.h"
#include "utility.h"

typedef struct Location {
    int x, y, z;
} Location;

double calculateDistance(Location loc1, Location loc2);
int isSameLocation(Location loc1, Location loc2);

#endif // LOCATION_H