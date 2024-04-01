#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Macros
#define MAX_GALAXY_NAME 100
#define MAX_PLANET_NAME 50
#define MAX_STAR_SYSTEMS 10


// Structures
typedef struct Date {
    int day, month, year;
} Date;

typedef struct {
    char* name;
    char* model;
    double maxSpeed; // Maximum speed of the spacecraft
    // Other relevant attributes...
} SpaceCraft;

typedef struct {
    char* travelCode;
    SpaceCraft* spaceCraft; // Pointer to associated SpaceCraft
    Date departureDate;
    Date arrivalDate;
    double distance; // In astronomical units, light years, etc.
    int riskLevel; // A metric for the risk associated with the travel
    int isCompleted; // Could be a boolean indicating if the travel has been completed
} InterstellarTravel;



typedef struct {
    char* name;
    int establishedYear;
    int numSpacecrafts;
    // If there are interstellar travels managed by the company, you might need a dynamic array for them
    InterstellarTravel** travels;
    int numTravels;
} Company;



typedef struct Location {
    int x, y, z;
} Location;

typedef struct Planet {
    char name[MAX_PLANET_NAME];
    Location portal_location;
    int ID;
} Planet;

typedef struct SolarSystem {
    char* name;
    Location portal_location;
    int risk_level;
    Planet* planets[MAX_STAR_SYSTEMS]; // Array of pointers of unknown size
    int num_planets;

} SolarSystem;

typedef struct Galaxy {
    char* name; // char* variable
    Location portal_location;
    SolarSystem** star_systems; // Array of unknown size
    int num_solar_systems;
} Galaxy;

// Function declarations
void load_system_data();
void save_system_data();
void display_system();
void display_subcomponents();
void add_component();
void sort_components();
void search_components();
void custom_action_one();
void custom_action_two();

// Main menu
char* my_strdup(const char* s) {
    size_t len = strlen(s) + 1; // Include space for the terminating null byte
    char* new_str = malloc(len);
    if (new_str) {
        memcpy(new_str, s, len);
    }
    return new_str;
}
char* safe_strdup(const char* s) {
    if (s == NULL) return NULL;
    char* new_str = malloc(strlen(s) + 1);
    if (new_str) strcpy(new_str, s);
    return new_str;
}

char* myGets(char* buffer, int size)
{
    char* ok;
    if (buffer != NULL && size > 0)
    {
        do {
            ok = fgets(buffer, size, stdin);
        } while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
        if (ok)
        {
            char* back = buffer + strlen(buffer);

            while ((buffer < back) && (isspace(*--back)));
            *(back + 1) = '\0';
            return buffer;
        }
        buffer[0] = '\0';
    }
    return NULL;
}

SpaceCraft* create_spacecraft(const char* name, const char* model, int capacity, double maxSpeed) {
    SpaceCraft* craft = (SpaceCraft*)malloc(sizeof(SpaceCraft));
    if (craft) {
        craft->name = safe_strdup(name);
        craft->model = safe_strdup(model);
        craft->maxSpeed = maxSpeed;
        // Initialize other attributes...
    }
    return craft;
}
Planet* create_planet(const char* name, Location location, int ID) {
    Planet* new_planet = (Planet*)malloc(sizeof(Planet));
    if (new_planet) {
        size_t name_length = strlen(name);
        if (name_length >= MAX_PLANET_NAME) {
            fprintf(stderr, "Planet name too long (maximum %d characters).\n", MAX_PLANET_NAME - 1);
            free(new_planet);
            return NULL;
        }
        strncpy(new_planet->name, name, MAX_PLANET_NAME - 1);
        new_planet->name[MAX_PLANET_NAME - 1] = '\0'; // Ensure null-termination
        new_planet->portal_location = location;
        new_planet->ID = ID;
    }
    else {
        fprintf(stderr, "Failed to allocate memory for new Planet.\n");
    }
    return new_planet;
}


void free_spacecraft(SpaceCraft* craft) {
    if (craft) {
        free(craft->name);
        free(craft->model);
        // Free other dynamically allocated attributes...
        free(craft);
    }
}
void free_planet(Planet* planet) {
    if (planet) {
        // Free any dynamically allocated attributes if necessary
        // For this struct, we don't have dynamic attributes other than the struct itself
        free(planet);
    }
}

InterstellarTravel* create_interstellar_travel(const char* code, SpaceCraft* craft, Date departure, Date arrival, double distance, int riskLevel) {
    InterstellarTravel* travel = (InterstellarTravel*)malloc(sizeof(InterstellarTravel));
    if (travel) {
        travel->travelCode = safe_strdup(code);
        travel->spaceCraft = craft; // Assuming the SpaceCraft is already created and passed as a pointer
        travel->departureDate = departure;
        travel->arrivalDate = arrival;
        travel->distance = distance;
        travel->riskLevel = riskLevel;
        travel->isCompleted = 0; // Assuming the travel has not yet completed
        // Initialize other attributes...
    }
    return travel;
}

void free_interstellar_travel(InterstellarTravel* travel) {
    if (travel) {
        free(travel->travelCode);
        // Do not free the spacecraft here if it's managed elsewhere
        // free_spacecraft(travel->spaceCraft);
        free(travel);
    }
}

void load_galaxy_from_binary(FILE* file, Galaxy* galaxy) {
    int name_length;
    fread(&name_length, sizeof(int), 1, file);
    galaxy->name = malloc(name_length);
    fread(galaxy->name, sizeof(char), name_length, file);
    fread(&galaxy->num_solar_systems, sizeof(int), 1, file);
    galaxy->star_systems = malloc(galaxy->num_solar_systems * sizeof(SolarSystem*));
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        galaxy->star_systems[i] = malloc(sizeof(SolarSystem));
        // Deserialize each SolarSystem...
    }
    // Deserialize other data as needed
}

void save_galaxy_to_binary(FILE* file, Galaxy* galaxy) {
    int name_length = strlen(galaxy->name) + 1;
    fwrite(&name_length, sizeof(int), 1, file);
    fwrite(galaxy->name, sizeof(char), name_length, file);
    fwrite(&galaxy->num_solar_systems, sizeof(int), 1, file);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        SolarSystem* system = galaxy->star_systems[i];
        // Serialize each SolarSystem...
    }
    // Serialize other data as needed
}

void free_solar_system(SolarSystem* system) {
    if (!system) return;
    free(system->name);
    for (int i = 0; i < system->num_planets; i++) {
        free(system->planets[i]); // Assuming planets were dynamically allocated
    }
    free(system);
}

// Function implementations will follow here
// Helper function prototypes (to be implemented)
void save_galaxy_to_text(FILE* file, Galaxy* galaxy);
void load_galaxy_from_text(FILE* file, Galaxy* galaxy);

// Load system data from file
void load_system_data(Galaxy* galaxy) {
    printf("Load from (1) Text file, (2) Binary file: ");
    int choice;
    scanf("%d", &choice);
    char filename[256];

    printf("Enter filename: ");
    scanf("%255s", filename);

    FILE* file = NULL;
    switch (choice) {
    case 1:
        file = fopen(filename, "r");
        if (file) {
            load_galaxy_from_text(file, galaxy);
            fclose(file);
        }
        else {
            printf("Failed to open the file.\n");
        }
        break;
    case 2:
        file = fopen(filename, "rb");
        if (file) {
            load_galaxy_from_binary(file, galaxy);
            fclose(file);
        }
        else {
            printf("Failed to open the file.\n");
        }
        break;
    default:
        printf("Invalid choice.\n");
    }
}

// Save system data to file
void save_system_data(Galaxy* galaxy) {
    printf("Save as (1) Text file, (2) Binary file: ");
    int choice;
    scanf("%d", &choice);
    char filename[256];

    printf("Enter filename: ");
    scanf("%255s", filename);

    FILE* file = NULL;
    switch (choice) {
    case 1:
        file = fopen(filename, "w");
        if (file) {
            save_galaxy_to_text(file, galaxy);
            fclose(file);
        }
        else {
            printf("Failed to open the file for writing.\n");
        }
        break;
    case 2:
        file = fopen(filename, "wb");
        if (file) {
            save_galaxy_to_binary(file, galaxy);
            fclose(file);
        }
        else {
            printf("Failed to open the file for writing.\n");
        }
        break;
    default:
        printf("Invalid choice.\n");
    }
}

// Implement the helper functions for saving and loading from text and binary formats here...
// Helper function to serialize Galaxy structure to text
void save_galaxy_to_text(FILE* file, Galaxy* galaxy) {
    fprintf(file, "Galaxy Name: %s\n", galaxy->name);
    fprintf(file, "Number of Solar Systems: %d\n", galaxy->num_solar_systems);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        SolarSystem* system = galaxy->star_systems[i];
        fprintf(file, "Solar System %d Name: %s\n", i + 1, system->name);
        fprintf(file, "Solar System %d Risk Level: %d\n", i + 1, system->risk_level);
        // Add more details as needed
    }
    // More data can be added here in a similar fashion
}

// Helper function to deserialize Galaxy structure from text
void load_galaxy_from_text(FILE* file, Galaxy* galaxy) {
    char buffer[MAX_GALAXY_NAME + 1];
    if (fscanf(file, "Galaxy Name: %100s\n", buffer) == 1) {
        free(galaxy->name); // Free existing name
        galaxy->name = safe_strdup(buffer);
    }
    fscanf(file, "Number of Solar Systems: %d\n", &galaxy->num_solar_systems);
    galaxy->star_systems = malloc(galaxy->num_solar_systems * sizeof(SolarSystem*));
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        galaxy->star_systems[i] = malloc(sizeof(SolarSystem));
        fscanf(file, "Solar System %*d Name: %s\n", buffer);
        char* new_name = strdup(buffer);
        if (new_name) {
            free(galaxy->star_systems[i]->name); // Free the existing name
            galaxy->star_systems[i]->name = new_name;
        }
        else {
            fprintf(stderr, "Memory allocation failed for SolarSystem name.\n");
            // Handle the allocation failure appropriately
        }
        fscanf(file, "Solar System %*d Risk Level: %d\n", &galaxy->star_systems[i]->risk_level);
        // Load more details as needed
    }
    // More data can be loaded here in a similar fashion
}

// Helper function to deserialize Galaxy structure from binary




// Comparison functions for qsort
int compare_by_name(const void* a, const void* b) {
    SolarSystem* system_a = (SolarSystem*)a;
    SolarSystem* system_b = (SolarSystem*)b;
    return strcmp(system_a->name, system_b->name);
}

int compare_by_risk_level(const void* a, const void* b) {
    SolarSystem* system_a = (SolarSystem*)a;
    SolarSystem* system_b = (SolarSystem*)b;
    return (system_a->risk_level - system_b->risk_level);
}

int compare_by_num_planets(const void* a, const void* b) {
    SolarSystem* system_a = (SolarSystem*)a;
    SolarSystem* system_b = (SolarSystem*)b;
    return (system_a->num_planets - system_b->num_planets);
}

void sort_solar_systems(Galaxy* galaxy, int sort_choice) {
    switch (sort_choice) {
    case 1:
        qsort(galaxy->star_systems, galaxy->num_solar_systems, sizeof(SolarSystem*), compare_by_name);
        break;
    case 2:
        qsort(galaxy->star_systems, galaxy->num_solar_systems, sizeof(SolarSystem*), compare_by_risk_level);
        break;
    case 3:
        qsort(galaxy->star_systems, galaxy->num_solar_systems, sizeof(SolarSystem*), compare_by_num_planets);
        break;
    default:
        printf("Invalid sort choice.\n");
    }
}
// Search functions for bsearch
void* search_by_name(const void* key, SolarSystem** systems, size_t num_systems) {
    return bsearch(key, systems, num_systems, sizeof(SolarSystem*), compare_by_name);
}

void* search_by_risk_level(const void* key, SolarSystem** systems, size_t num_systems) {
    return bsearch(key, systems, num_systems, sizeof(SolarSystem*), compare_by_risk_level);
}

void* search_by_num_planets(const void* key, SolarSystem** systems, size_t num_systems) {
    return bsearch(key, systems, num_systems, sizeof(SolarSystem*), compare_by_num_planets);
}
void process_void_array(void** array, size_t num_elements, void (process)(void)) {
    for (size_t i = 0; i < num_elements; i++) {
        process(array[i]);
    }
}

// Example process function
void print_solar_system(void* data) {
    SolarSystem* system = (SolarSystem*)data;
    printf("Solar System: %s, Risk Level: %d, Number of Planets: %d\n",
        system->name, system->risk_level, system->num_planets);
}

// Example usage:
// process_void_array((void**)galaxy->star_systems, galaxy->num_solar_systems, print_solar_system);
// Function to display a single SolarSystem
void display_solar_system(const SolarSystem* system) {
    printf("Solar System Name: %s\n", system->name);
    printf("Risk Level: %d\n", system->risk_level);
    printf("Number of Planets: %d\n", system->num_planets);
    // Display more details as needed
}

// Function to display all SolarSystems in a Galaxy
void display_system(Galaxy* galaxy) {
    printf("Galaxy Name: %s\n", galaxy->name);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        display_solar_system(galaxy->star_systems[i]);
    }
}

// Function to add a new SolarSystem to a Galaxy
void add_solar_system(Galaxy* galaxy) {
    // Allocate memory for the new Solar System
    SolarSystem* new_system = (SolarSystem*)malloc(sizeof(SolarSystem));
    if (!new_system) {
        fprintf(stderr, "Memory allocation failed for the new Solar System.\n");
        return;
    }

    // Initialize the new Solar System fields
    new_system->name = NULL;
    new_system->portal_location = (Location){ 0, 0, 0 }; // Assuming default values for location
    new_system->risk_level = 0;
    new_system->num_planets = 0;

    // Initialize all planet pointers in the planets array to NULL
    for (int i = 0; i < MAX_STAR_SYSTEMS; i++) {
        new_system->planets[i] = NULL;
    }

    // Temporary buffer for Solar System name input
    char temp[MAX_GALAXY_NAME];
    printf("Enter Solar System Name: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0; // Remove trailing newline

    // Allocate memory and assign the name to the new Solar System
    new_system->name = strdup(temp);
    if (!new_system->name) {
        fprintf(stderr, "Failed to allocate memory for Solar System name.\n");
        free(new_system);
        return;
    }

    // Prompt for Risk Level
    printf("Enter Risk Level: ");
    scanf("%d", &new_system->risk_level);
    while (getchar() != '\n');  // Clear input buffer

    // Reallocate the galaxy's star_systems array to accommodate the new Solar System
    SolarSystem** new_array = (SolarSystem*)realloc(galaxy->star_systems, (galaxy->num_solar_systems + 1) * sizeof(SolarSystem));
    if (new_array) {
        galaxy->star_systems = new_array;
        galaxy->star_systems[galaxy->num_solar_systems] = new_system;
        galaxy->num_solar_systems++;
        printf("New Solar System '%s' added successfully.\n", new_system->name);
    }
    else {
        fprintf(stderr, "Failed to reallocate memory for new solar systems.\n");
        free(new_system->name);
        free(new_system);
    }
}



// Function to display sub-components of a SolarSystem
void display_subcomponents(Galaxy* galaxy) {
    // For example, list all planets in each SolarSystem
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        SolarSystem* system = galaxy->star_systems[i];
        printf("Solar System: %s\n", system->name);
        for (int j = 0; j < system->num_planets; j++) {
            printf("Planet %d: %s\n", j + 1, system->planets[j]->name);
        }
    }
}

// Creative actions: Let's assume we want to increase risk levels and rename a planet
void increase_risk_levels(Galaxy* galaxy) {
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        galaxy->star_systems[i]->risk_level++;
    }
    printf("Increased risk levels for all Solar Systems.\n");
}

void rename_planet(Galaxy* galaxy) {
    // Assuming we have the planet's ID and the new name
    int planet_id;
    char new_name[MAX_PLANET_NAME];
    printf("Enter Planet ID to rename: ");
    scanf("%d", &planet_id);
    printf("Enter new name for the Planet: ");
    scanf("%49s", new_name); // Assuming the name won't exceed the MAX_PLANET_NAME

    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        for (int j = 0; j < galaxy->star_systems[i]->num_planets; j++) {
            if (galaxy->star_systems[i]->planets[j]->ID == planet_id) {
                strncpy(galaxy->star_systems[i]->planets[j]->name, new_name, MAX_PLANET_NAME);
                printf("Planet ID %d renamed to %s.\n", planet_id, new_name);
                return;
            }
        }
    }
    printf("Planet ID %d not found.\n", planet_id);
}
// Function to add a planet to a solar system
void add_planet(Galaxy* galaxy) {
    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    // Prompt for which solar system to add the planet to
    int system_index;
    printf("Enter the index of the Solar System to add a planet to (0 to %d): ", galaxy->num_solar_systems - 1);
    char input[MAX_PLANET_NAME];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return;
    }

    // Validate and parse the system index
    if (sscanf(input, "%d", &system_index) != 1) {
        printf("Invalid input for Solar System index.\n");
        return;
    }

    if (system_index < 0 || system_index >= galaxy->num_solar_systems || galaxy->star_systems == NULL) {
        printf("Invalid Solar System index or no Solar Systems available.\n");
        return;
    }


    SolarSystem* solar_system = galaxy->star_systems[system_index];

    if (solar_system->num_planets >= MAX_STAR_SYSTEMS) {
        printf("This Solar System already has the maximum number of planets (%d).\n", MAX_STAR_SYSTEMS);
        return; // Exit the function to prevent adding more planets
    }
    // Gather details about the new planet
    char planet_name[MAX_PLANET_NAME];
    printf("Enter the name of the new Planet: ");
    if (fgets(planet_name, sizeof(planet_name), stdin) == NULL) {
        printf("Error reading planet name.\n");
        return;
    }
    planet_name[strcspn(planet_name, "\n")] = '\0'; // Remove the newline character

    // Assume we have functions to get location and other details for Planet
    Location location = { 0 }; // Replace with actual user input or function to get location

    char input_id[256];
    int planet_id;
    printf("Enter the ID for the new Planet: ");
    if (fgets(input_id, sizeof(input_id), stdin) == NULL || input_id[strcspn(input_id, "\n")] != '\n') {
        printf("Error reading planet ID or input too long.\n");
        return;
    }
    input_id[strcspn(input_id, "\n")] = '\0';

    // Validate and parse the planet ID
    if (sscanf(input_id, "%d", &planet_id) != 1) {
        printf("Invalid input for Planet ID.\n");
        return;
    }

    // Check for duplicate planet ID
    for (int i = 0; i < solar_system->num_planets; i++) {
        if (solar_system->planets[i] != NULL && solar_system->planets[i]->ID == planet_id) {
            printf("Planet with ID %d already exists in this Solar System.\n", planet_id);
            return;
        }
    }
    if (planet_id <= 0) {
        printf("Invalid Planet ID. The ID must be a positive integer.\n");
        return;
    }

    // Create and add the planet to the chosen solar system
    if (solar_system->num_planets >= MAX_STAR_SYSTEMS) {
        printf("This Solar System already has the maximum number of planets.\n");
    }
    else {
        Planet* new_planet = create_planet(planet_name, location, planet_id);
        solar_system->planets[solar_system->num_planets] = new_planet;
        solar_system->num_planets++;
        printf("Planet %s added to Solar System %s.\n", planet_name, solar_system->name);
    }
}

// Function to display all planets in the galaxy
void display_all_planets(Galaxy* galaxy) {
    printf("Displaying all planets in the Galaxy:\n");
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        SolarSystem* solar_system = galaxy->star_systems[i];
        for (int j = 0; j < solar_system->num_planets; j++) {
            Planet* planet = solar_system->planets[j];
            printf("Planet Name: %s, ID: %d, Location: (%d, %d, %d)\n",
                planet->name, planet->ID,
                planet->portal_location.x,
                planet->portal_location.y,
                planet->portal_location.z);
        }
    }
}


// Assuming a Galaxy structure is declared and initialized elsewhere in the program:
// Galaxy galaxy = / ... initialization ... */;

// Main menu function (simplified for brevity)
void main_menu(Galaxy* galaxy) {
    int choice;
    do {
        printf("\nMain Menu:\n");
        printf("1. Upload system data\n");
        printf("2. Display system\n");
        printf("3. Display sub-components\n");
        printf("4. Add a new solar system\n");
        printf("5. Add a new planet\n"); // New menu item for adding planets
        printf("6. Increase risk levels (Creative Action 1)\n");
        printf("7. Rename a planet (Creative Action 2)\n");
        printf("8. Display all planets\n"); // New menu item for displaying planets
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            load_system_data(galaxy);
            break;
        case 2:
            display_system(galaxy);
            break;
        case 3:
            display_subcomponents(galaxy);
            break;
        case 4:
            add_solar_system(galaxy);
            break;
        case 5:
            add_planet(galaxy); // Function to add a new planet
            break;
        case 6:
            increase_risk_levels(galaxy);
            break;
        case 7:
            rename_planet(galaxy);
            break;
        case 8:
            display_all_planets(galaxy); // Function to display all planets
            break;
        case 9:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}
// Free memory for the Galaxy structure
void free_galaxy(Galaxy* galaxy) {
    if (!galaxy) return;
    free(galaxy->name);
    for (int i = 0; i < galaxy->num_solar_systems; i++) {
        free_solar_system(galaxy->star_systems[i]);
    }
    free(galaxy->star_systems);
}



// Example of checking dynamic memory allocation
SolarSystem* create_solar_system() {
    SolarSystem* system = malloc(sizeof(SolarSystem));
    if (!system) {
        fprintf(stderr, "Memory allocation failed for SolarSystem.\n");
        return NULL; // Handle the error appropriately
    }
    // ... Initialize the SolarSystem
    return system;
}
// Example of testing the return value from a function
void load_galaxy_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file %s for reading.\n", filename);
        return; // Handle the error appropriately
    }
    // ... Read data from file
    fclose(file); // Always close your files
}
int main() {
    // Create a new Galaxy object
    Galaxy* gal = (Galaxy*)malloc(sizeof(Galaxy));
    if (!gal) {
        fprintf(stderr, "Failed to allocate memory for Galaxy.\n");
        return EXIT_FAILURE;
    }
    gal->name = NULL;
    gal->star_systems = NULL; // Ensure this is NULL initially
    gal->num_solar_systems = 0;


    main_menu(gal); // Start the main menu

    free_galaxy(gal); // Free the memory for the galaxy
    return 0;
}