#include "location.h"

double calculateDistance(const Location loc1, const Location loc2) {
    return sqrt(pow(loc2.x - loc1.x, 2) + pow(loc2.y - loc1.y, 2) + pow(loc2.z - loc1.z, 2));
}

int isSameLocation(const Location loc1, const Location loc2) {
    if (loc1.x == loc2.x && loc1.y == loc2.y && loc1.z == loc2.z) 
        return 1;  
    else 
        return 0;
}