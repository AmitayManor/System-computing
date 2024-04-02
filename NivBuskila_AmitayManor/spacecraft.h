#ifndef SPACECRAFT_H
#define SPACECRAFT_H

typedef struct {
    char* name;
    char* model;
    double maxSpeed;
} SpaceCraft;

SpaceCraft* create_spacecraft(const char* name, const char* model, int capacity, double maxSpeed);
void free_spacecraft(SpaceCraft* craft);

#endif // SPACECRAFT_H