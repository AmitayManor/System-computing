#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#define MAX_LEN_SPACE_CRAFT 100     //Defines the max length of the name or model of a space craft
#define MAX_SPEED 300000
#define MIN_SPEED 0

typedef struct {
    char* name;
    char* model;
    double maxSpeed;
    int craftId;
} SpaceCraft;

SpaceCraft* create_spacecraft(const char* name, const char* model, double maxSpeed, int id);
void free_spacecraft(SpaceCraft* craft);

#endif // SPACECRAFT_H