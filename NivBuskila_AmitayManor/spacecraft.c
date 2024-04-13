#include "spacecraft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


void testSpaceCraftIO() {
    SpaceCraft craft = { "Enterprise", "NX-01", 250000, 1701 };
    FILE* fp = fopen("test_spacecraft.txt", "w+");
    assert(fp != NULL);
    writeSpaceCraftToText(fp, &craft);
    rewind(fp);
    SpaceCraft loadedCraft;
    assert(readSpaceCraftFromText(fp, &loadedCraft));
    fclose(fp);

    fp = fopen("test_spacecraft.bin", "w+b");
    assert(fp != NULL);
    writeSpaceCraftToBinaryFile(&craft, fp);
    rewind(fp);
    assert(readSpaceCraftFromBinaryFile(&loadedCraft, fp));
    fclose(fp);

    // Assertions to verify all properties
    assert(strcmp(craft.name, loadedCraft.name) == 0);
    assert(strcmp(craft.model, loadedCraft.model) == 0);
    assert(craft.maxSpeed == loadedCraft.maxSpeed);
    assert(craft.craftId == loadedCraft.craftId);

    free(loadedCraft.name);
    free(loadedCraft.model);
}


void writeSpaceCraftToText(FILE* fp, const SpaceCraft* craft) {
    if (craft && fp) {
        fprintf(fp, "Name: %s\n", craft->name);
        fprintf(fp, "Model: %s\n", craft->model);
        fprintf(fp, "Max Speed: %.2f\n", craft->maxSpeed);
        fprintf(fp, "Craft ID: %d\n", craft->craftId);
    }
}

int readSpaceCraftFromText(FILE* fp, SpaceCraft* craft) {
    if (!craft || !fp) return 0;

    char bufferName[MAX_LEN_SPACE_CRAFT];
    char bufferModel[MAX_LEN_SPACE_CRAFT];

    if (fscanf(fp, "Name: %[^\n]\n", bufferName) != 1) return 0;
    if (fscanf(fp, "Model: %[^\n]\n", bufferModel) != 1) return 0;
    if (fscanf(fp, "Max Speed: %lf\n", &craft->maxSpeed) != 1) return 0;
    if (fscanf(fp, "Craft ID: %d\n", &craft->craftId) != 1) return 0;

    craft->name = strdup(bufferName);
    craft->model = strdup(bufferModel);

    return 1;
}

int writeSpaceCraftToBinaryFile(const SpaceCraft* craft, FILE* fp) {
    if (!craft || !fp) return 0;

    int nameLen = strlen(craft->name) + 1; // Include null terminator
    int modelLen = strlen(craft->model) + 1; // Include null terminator

    fwrite(&nameLen, sizeof(int), 1, fp);
    fwrite(craft->name, sizeof(char), nameLen, fp);

    fwrite(&modelLen, sizeof(int), 1, fp);
    fwrite(craft->model, sizeof(char), modelLen, fp);

    fwrite(&craft->maxSpeed, sizeof(double), 1, fp);
    fwrite(&craft->craftId, sizeof(int), 1, fp);

    return 1;
}

int readSpaceCraftFromBinaryFile(SpaceCraft* craft, FILE* fp) {
    if (!craft || !fp) return 0;

    int nameLen, modelLen;

    fread(&nameLen, sizeof(int), 1, fp);
    craft->name = ALLOCATE(char*,nameLen);
    fread(craft->name, sizeof(char), nameLen, fp);

    fread(&modelLen, sizeof(int), 1, fp);
    craft->model = ALLOCATE(char*, modelLen);
    fread(craft->model, sizeof(char), modelLen, fp);

    fread(&craft->maxSpeed, sizeof(double), 1, fp);
    fread(&craft->craftId, sizeof(int), 1, fp);

    return 1;
}


SpaceCraft* create_spacecraft(const char* name, const char* model, double maxSpeed, int id) {
    SpaceCraft* craft = ALLOCATE(SpaceCraft*, 1);
//    SpaceCraft* craft = (SpaceCraft*)malloc(sizeof(SpaceCraft));
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
        char* name = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);
        //char* name = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));
        printf("Enter name for spacecraft %d: ", sp->craftId);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (!myGets(name, MAX_LEN_SPACE_CRAFT)) {
            LOG_DEBUG("Error reading company name.\n");
//            fprintf(stderr, "Error reading company name.\n");
            strncpy(name, "DefaultCompany", MAX_LEN_SPACE_CRAFT - 1);
            name[MAX_LEN_SPACE_CRAFT - 1] = '\0';
        }
        sp->name = strdup(name);
        free(name);
    }
}

void get_SpaceCraft_model(SpaceCraft* sp) {

    if (sp) {
        char* model = ALLOCATE(char*, MAX_LEN_SPACE_CRAFT);
        //char* model = (char*)malloc(MAX_LEN_SPACE_CRAFT * sizeof(char));
        printf("Enter model for spacecraft %d: ", sp->craftId);
        int c;
        //while ((c = getchar()) != '\n' && c != EOF);
        if (!myGets(model, MAX_LEN_SPACE_CRAFT)) {
            LOG_DEBUG("Error reading company name.\n");
//            fprintf(stderr, "Error reading company name.\n");
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

    return STR_EQUAL(scA->name, scB->name);
    //return strcmp(scA->name, scB->name);
}

int compareSpaceCraftByModel(const void* a, const void* b) {
    const SpaceCraft* scA = *(const SpaceCraft**)a;
    const SpaceCraft* scB = *(const SpaceCraft**)b;
    return STR_EQUAL(scA->model, scB->model);
    //return strcmp(scA->model, scB->model);
}

void free_spacecraft(SpaceCraft* craft) {
    if (craft) {
        free(craft->name);
        free(craft->model);
        free(craft);
    }
}

