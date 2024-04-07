#include "spacecraft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


SpaceCraft* create_spacecraft(const char* name, const char* model, double maxSpeed, int id) {
    SpaceCraft* craft = (SpaceCraft*)malloc(sizeof(SpaceCraft));
    if (craft) {
        craft->name = strdup(name); // Assuming strdup is available or implemented
        craft->model = strdup(model);
        craft->maxSpeed = maxSpeed;
        craft->craftId = id;
    }
    return craft;
}

SpaceCraft* create_individual_spacecraft(int id) {
    char craftName[MAX_LEN_SPACE_CRAFT], craftModel[MAX_LEN_SPACE_CRAFT];
    double craftMaxSpeed = -1;

    printf("Enter name for spacecraft %d: ", id);
    scanf("%99s", craftName);

    printf("Enter model for spacecraft %d: ", id);
    scanf("%99s", craftModel);

    do {
        printf("Enter max speed (in km/s) for spacecraft %d (0 - 300000): ", id);
        scanf("%lf", &craftMaxSpeed);
        if (craftMaxSpeed < MIN_SPEED || craftMaxSpeed > MAX_SPEED) {
            printf("Invalid speed. Please enter a value between 0 and 300000.\n");
        }
    } while (craftMaxSpeed < MIN_SPEED || craftMaxSpeed > MAX_SPEED);

    return create_spacecraft(craftName, craftModel, craftMaxSpeed, id);
}

void print_spacecraft(void* sc) {
    SpaceCraft* spacecraft = (SpaceCraft*)sc;
    printf("SpaceCraft ID: %d, Model: %s, Max Speed: %.2f\n", spacecraft->craftId, spacecraft->model, spacecraft->maxSpeed);
}

/*
void print_spacecraft(SpaceCraft* craft) {
    if (craft) {
        printf("Space Craft Name: %s\n", craft->name);
        printf("Space Craft ID: %d\n", craft->craftId);
        printf("Model: %s\n", craft->model);
        printf("Space Craft ID: %d\n", craft->craftId);
        printf("Max Speed: %.2f\n", craft->maxSpeed);
    }
}
*/
void get_SpaceCraft_id(SpaceCraft* sp) {
    if (sp) {
        int id;
        do {
            printf("Enter wanted id (1-9999): ");
            scanf("%d", &id);
            if (id < MIN_ID || id > MAX_ID) {
                printf("Invalid id. Please enter a value between 1 and 9999.\n");
            }
        } while (id < MIN_ID || id > MAX_ID);
        sp->craftId = id;
    }
    else {
        printf("Error! Space Craft's ID not initialized");
    }
}

void get_SpaceCraft_name(SpaceCraft* sp) {

    if (sp) {
        char* name = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));
        printf("Enter name for spacecraft %d: ", sp->craftId);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (!myGets(name, MAX_LEN_SPACE_CRAFT)) {
            fprintf(stderr, "Error reading company name.\n");
            strncpy(name, "DefaultCompany", MAX_LEN_SPACE_CRAFT - 1);
            name[MAX_LEN_SPACE_CRAFT - 1] = '\0';
        }
        sp->name = strdup(name);
        free(name);
    }
}

void get_SpaceCraft_model(SpaceCraft* sp) {

    if (sp) {
        char* model = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));
        printf("Enter model for spacecraft %d: ", sp->craftId);
        int c;
        //while ((c = getchar()) != '\n' && c != EOF);
        if (!myGets(model, MAX_LEN_SPACE_CRAFT)) {
            fprintf(stderr, "Error reading company name.\n");
            strncpy(model, "DefaultCompany", MAX_LEN_SPACE_CRAFT - 1);
            model[MAX_LEN_SPACE_CRAFT - 1] = '\0';
        }

        sp->model = strdup(model);
        free(model);
    }
    else {
        printf("Error! Space Craft not initialized");
    }

}

void get_SpaceCraft_speed(SpaceCraft* sp) {

    if (sp) {
        double speed;
        do {
            printf("Enter max speed (in km/s) for spacecraft %d (0 - 300000): ", sp->craftId);
            scanf("%lf", &speed);
            if (speed < MIN_SPEED || speed > MAX_SPEED) {
                printf("Invalid speed. Please enter a value between 0 and 300000.\n");
            }
        } while (speed < MIN_SPEED || speed > MAX_SPEED);
        sp->maxSpeed = speed;
    }
    else {
        printf("Error! Space Craft not initialized");
    }
}

int compareSpaceCraftByID(const void* a, const void* b) {
    const SpaceCraft* scA = *(const SpaceCraft**)a;
    const SpaceCraft* scB = *(const SpaceCraft**)b;
    return (scA->craftId - scB->craftId);
}

int compareSpaceCraftByName(const void* a, const void* b) {
    const SpaceCraft* scA = *(const SpaceCraft**)a;
    const SpaceCraft* scB = *(const SpaceCraft**)b;
    return strcmp(scA->name, scB->name);
}

int compareSpaceCraftByModel(const void* a, const void* b) {
    const SpaceCraft* scA = *(const SpaceCraft**)a;
    const SpaceCraft* scB = *(const SpaceCraft**)b;
    return strcmp(scA->model, scB->model);
}



void free_spacecraft(SpaceCraft* craft) {
    if (craft) {
        free(craft->name);
        free(craft->model);
        free(craft);
    }
}

