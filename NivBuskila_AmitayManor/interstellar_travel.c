#include "interstellar_travel.h"
#include "universal_manager.h"
#include <stdlib.h>
#include <string.h>


char* get_travelCode_Src(UniversalManager* mg, InterstellarTravel* tr, Permission permission) {
    if (mg && tr) {
        
        /* Step One: Display ALL Options */
        

        /* Step Two: Check permissions:
        * 
        * if 1. only travel between plantes in the SAME solar system AND Same Galaxy
        * if 2. Travel in the SAME Galaxy, freely between Solar systems and Plantes
        * if 3. Travel Freely
        * 
        */

        int per = (int)&permission;
        
        switch (per) {
        
        case 1: {
            printf("Limited Permission.\nCan travel only between Planets (in the same Solar system).\n");
            
            
            break; }  //Between Plantes in the Same Solar System in the Same Galaxy

        case 2: { 
            printf("Flex Permission.\nCan travel only between Solar systems (in the same Galaxy).\n");
            
            
            break; }  //Between Solar systems in the Same Galaxy

        case 3: { 
            printf("Deluxe Permission.\nFree to travel aound the universe.\n");
            
            
            break; }  // Freely
        
        case 0: {
            printf("No Permission is given.\n");
            break; }  // No Permissions

        default: {
            printf("Error in given Permission.\n");
        }
        
        }while (per != 0);
        

        /* Step Three: Choose based on Permission zone
        *   Validate choice
        */

        /* Step Four: Initialize Values */

    }
    else {
        printf("Error with manager and travels allocations");
    }
}

char* get_travelCode_Dst(UniversalManager* mg, InterstellarTravel* tr, Permission permission) {
    if (mg && tr) {

        /* Step One: Check permissions:
         *
         * if 1. only travel between plantes in the SAME solar system AND Same Galaxy
         * if 2. Travel in the SAME Galaxy, freely between Solar systems and Plantes
         * if 3. Travel Freely
         *
         */

         /* Step Two: Display ALL Options */

         /* Step Three: Choose based on Permission zone
         *   Validate choice
         */

         /* Step Four: Initialize Values */
    }
    else {
        printf("Error with manager and travels allocations");
    }
}

void get_departure_date(InterstellarTravel* tr){}














InterstellarTravel* create_interstellar_travel(const char* code, SpaceCraft* craft, Date departure, Date arrival, double distance, int riskLevel) {
    InterstellarTravel* travel = (InterstellarTravel*)malloc(sizeof(InterstellarTravel));
    if (travel) {
        //travel->travelCode = strdup(code); // Assuming strdup is available or implemented
        travel->spaceCraft = craft;
        travel->departureDate = departure;
        travel->arrivalDate = arrival;
        travel->distance = distance;
        travel->riskLevel = riskLevel;
        travel->isCompleted = 0; // Assuming travels start as not completed
    }
    return travel;
}

void calculate_arrival_date(InterstellarTravel* travel) {
    if (travel && travel->spaceCraft) {
        // Implement logic to calculate the arrival date based on distance and spacecraft speed
        // You may need to use the departureDate and spaceCraft->maxSpeed
        // For simplicity, let's assume a fixed speed for all spacecraft
        double travelDuration = travel->distance / 100000.0; // Assuming 100,000 units/day
        int daysToAdd = (int)travelDuration;
        travel->arrivalDate = advance_date(travel->departureDate, daysToAdd);
    }
}

Date advance_date(Date date, int daysToAdd) {
    // Implement logic to advance the date by the given number of days
    // Assume the date is valid and handle leap years, month lengths, etc.
    // Return the advanced date
    return date;
}

int calculate_risk_level(InterstellarTravel* travel) {
    if (travel) {
        // Implement logic to calculate the risk level based on travel details
        // You may need to consider the source, destination, distance, spacecraft model, etc.
        // For simplicity, let's assume a fixed risk level based on distance
        if (travel->distance < 1000000.0) {
            return 1; // Low risk
        }
        else if (travel->distance < 5000000.0) {
            return 2; // Medium risk
        }
        else {
            return 3; // High risk
        }
    }
    return 0; // Invalid travel
}

int is_travel_successful(InterstellarTravel* travel) {
    if (travel) {
        // Implement logic to determine if the travel was successful based on risk level and other factors
        // You may need to consider the risk level, spacecraft model, and any other relevant factors
        // For simplicity, let's assume a random success/failure based on risk level
        int randomValue = rand() % 100;
        switch (travel->riskLevel) {
        case 1: // Low risk
            return randomValue < 90; // 90% success rate
        case 2: // Medium risk
            return randomValue < 70; // 70% success rate
        case 3: // High risk
            return randomValue < 50; // 50% success rate
        default:
            return 0; // Failure
        }
    }
    return 0; // Invalid travel
}

void print_interstellar_travel(const InterstellarTravel* travel) {
    if (travel) {
        printf("Travel Code (Source): %s\n", travel->travelCodeSrc);
        printf("Travel Code (Destination): %s\n", travel->travelCodeDst);
        printf("Spacecraft: %s (%s)\n", travel->spaceCraft->name, travel->spaceCraft->model);
        printf("Departure Date: ");
        print_date(&travel->departureDate);
        printf("\nArrival Date: ");
        print_date(&travel->arrivalDate);
        printf("\nDistance: %.2f\n", travel->distance);
        printf("Risk Level: %d\n", travel->riskLevel);
        printf("Completed: %s\n", travel->isCompleted ? "Yes" : "No");
    }
}

char extractTrcalCode(char code[MAX_CODE_LEN])
{}

void free_interstellar_travel(InterstellarTravel* travel) {
    if (travel) {
        //free(travel->travelCode);
        // Note: Do not free spaceCraft here if it is managed elsewhere
        free(travel);
    }
}
