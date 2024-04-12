#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "macros.h"

#define MAX_LEN_SPACE_CRAFT 100     //Defines the max length of the name or model of a space craft
#define MAX_SPEED 300000
#define MIN_SPEED 0
#define MIN_ID 0
#define MAX_ID 10000

typedef struct {
    char* name;
    char* model;
    double maxSpeed;
    int craftId;
} SpaceCraft;


int compareSpaceCraftByID(const void* a, const void* b);

int compareSpaceCraftByName(const void* a, const void* b);

int compareSpaceCraftByModel(const void* a, const void* b);

SpaceCraft* create_spacecraft(const char* name, const char* model, double maxSpeed, int id);

void print_spacecraft(void* sc);

//void print_spacecraft(SpaceCraft* craft);
void get_SpaceCraft_id(SpaceCraft* sp);
void get_SpaceCraft_name(SpaceCraft* sp);
void get_SpaceCraft_model(SpaceCraft* sp);
void get_SpaceCraft_speed(SpaceCraft* sp);
void free_spacecraft(SpaceCraft* craft);

#endif // SPACECRAFT_H