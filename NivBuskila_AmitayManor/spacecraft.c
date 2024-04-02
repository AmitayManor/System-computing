#include "spacecraft.h"
#include <stdlib.h>
#include <string.h>

SpaceCraft* create_spacecraft(const char* name, const char* model, double maxSpeed) {
    SpaceCraft* craft = (SpaceCraft*)malloc(sizeof(SpaceCraft));
    if (craft) {
        craft->name = strdup(name); // Assuming strdup is available or implemented
        craft->model = strdup(model);
        craft->maxSpeed = maxSpeed;
    }
    return craft;
}

void free_spacecraft(SpaceCraft* craft) {
    if (craft) {
        free(craft->name);
        free(craft->model);
        free(craft);
    }
}
