#include "interstellar_travel.h"
#include "universal_manager.h"

#include <stdlib.h>
#include <string.h>


char* get_travelCode_Src(UniversalManager* mg, InterstellarTravel* tr) {
    if (mg && tr) {

        displayCosmicElements(mg);

        int galaxyID, systemID, planetID;
        int idFlag = 0;

        Galaxy* galaxy = NULL;
        SolarSystem* system = NULL;
        Planet* planet = NULL;

        // Find Galaxy by ID
        do {
            printf("Enter Galaxy ID: ");
            scanf("%d", &galaxyID);
            galaxy = findGalaxy_byID(mg, galaxyID);
            if (galaxy)
                idFlag = 1;
            else
                printf("\nError! Galaxy's ID is not valid. Try again.\n");
        } while (!idFlag);
        
        // Find Solar System by ID and reinitialize ifFlag
        idFlag = 0;
        do {
            printf("Enter Solar System ID: ");
            scanf("%d", &systemID);
            system = findSolarSystem_byID(galaxy, systemID);
            if (system)
                idFlag = 1;
            else
                printf("\nError! Solar System's ID is not valid. Try again.\n");
        } while (!idFlag);

        // Find Planet by ID and reinitialize ifFlag
        idFlag = 0;
        do {
            printf("Enter Planet ID: ");
            scanf("%d", &planetID);
            planet = findPlanet_byID(system, planetID);
            if (planet)
                idFlag = 1;
            else
                printf("\nError! Solar System's ID is not valid. Try again.\n");
        } while (!idFlag);
        

        snprintf(tr->travelCodeSrc, MAX_CODE_LEN, "G%04dS%04dP%04d", galaxyID, systemID, planetID);
        tr->travelCodeSrc[MAX_CODE_LEN] = '\0';
    }
    else {
        printf("Error with manager and travels allocations");
    }
}

char* get_travelCode_Dst(UniversalManager* mg, InterstellarTravel* tr, Permission permission) {
    if (!mg || !tr) {
        printf("Error with manager and travels allocations\n");
        return;
    }

    int srcGalaxyID, srcSystemID, srcPlanetID;
    sscanf(tr->travelCodeSrc, "G%04dS%04dP%04d", &srcGalaxyID, &srcSystemID, &srcPlanetID);

    int dstGalaxyID, dstSystemID, dstPlanetID;
    Galaxy* galaxy = NULL;
    SolarSystem* system = NULL;
    Planet* planet = NULL;
    int idFlag = 0; 

    
    switch (permission) {
    case ePLANET:

        /*Print all Planets in srcGalaxyID and srcSystemID*/

        printf("\nYour Permission:\t***Cross Planets***\n");
        // Limited to planets within the same solar system
        galaxy = findGalaxy_byID(mg, srcGalaxyID);
        system = findSolarSystem_byID(galaxy, srcSystemID);

        do {
            printf("Enter destination Planet ID within Galaxy %04d and Solar System %04d : \n", srcGalaxyID, srcSystemID);
            scanf("%d", &dstPlanetID);
            planet = findPlanet_byID(system, dstPlanetID);

            if (planet) idFlag = 1;
            else printf("\nError! Planet's ID is not valid. Try again.\n");

        } while (!idFlag);
        snprintf(tr->travelCodeDst, MAX_CODE_LEN, "G%04dS%04dP%04d", srcGalaxyID, srcSystemID, dstPlanetID);
        tr->travelCodeDst[MAX_CODE_LEN - 1] = '\0';
        break;
    
    case eSOLARSYSTEM:
        printf("\nYour Permission:\t***Cross Solar Systems***\n");
        
        /*Print all Solar Systems in srcGalaxyID*/
        
        galaxy = findGalaxy_byID(mg, srcGalaxyID);

        do {
            printf("Enter destination Solar System ID within Galaxy %04d: ", srcGalaxyID);
            scanf("%d", &dstSystemID);
            system = findSolarSystem_byID(galaxy, dstSystemID);

            if (system) idFlag = 1;
            else printf("\nError! Solar System's ID is not valid. Try again.\n");

        } while (!idFlag);
        
        idFlag = 0;
        do {
            printf("Enter destination Planet ID within Galaxy %04d and Solar System %04d : \n", srcGalaxyID, dstSystemID);
            scanf("%d", &dstPlanetID);
            planet = findPlanet_byID(system, dstPlanetID);

            if (planet) idFlag = 1;
            else printf("\nError! Planet's ID is not valid. Try again.\n");

        } while (!idFlag);
        snprintf(tr->travelCodeDst, MAX_CODE_LEN, "G%04dS%04dP%04d", srcGalaxyID, dstSystemID, dstPlanetID);
        tr->travelCodeDst[MAX_CODE_LEN-1] = '\0';
        break;
    
    case eGALAXY:
        
        /*Print all the unverse*/
        
        printf("\nYour Permission:\t***Cross Galaxies***\n");
        do {
            printf("Enter destination Galaxy ID: ");
            scanf("%d", &dstGalaxyID);
            galaxy = findGalaxy_byID(mg, dstGalaxyID);

            if (galaxy) idFlag = 1;
            else printf("\nError! Galaxy's ID is not valid. Try again.\n");

        } while (!idFlag);
       

        idFlag = 0;
        do {
            printf("Enter destination Solar System ID within Galaxy %04d: ", dstGalaxyID);
            scanf("%d", &dstSystemID);
            system = findSolarSystem_byID(galaxy, dstSystemID);

            if (system) idFlag = 1;
            else printf("\nError! Solar System's ID is not valid. Try again.\n");

        } while (!idFlag);

        idFlag = 0;
        do {
            printf("Enter destination Planet ID within Galaxy %04d and Solar System %04d : \n", dstGalaxyID, dstSystemID);
            scanf("%d", &dstPlanetID);
            planet = findPlanet_byID(system, dstPlanetID);

            if (planet) idFlag = 1;
            else printf("\nError! Planet's ID is not valid. Try again.\n");

        } while (!idFlag);
        snprintf(tr->travelCodeDst, MAX_CODE_LEN, "G%04dS%04dP%04d", dstGalaxyID, dstSystemID, dstPlanetID);
        tr->travelCodeDst[MAX_CODE_LEN-1] = '\0';
        break;

    case eNOPERMISSION:
        printf("No permission to travel.\n");
        
        strcpy(tr->travelCodeDst, "G0000S0000P0000");
        tr->travelCodeDst[MAX_CODE_LEN-1] = '\0';
        break;

    default:
        printf("Error in given Permission.\n");
        strcpy(tr->travelCodeDst, "ERROR");
        break;
    }
}

void get_arrival_date(UniversalManager* mg, InterstellarTravel* tr) {

    if (mg && tr && tr->spaceCraft) {

        int srcGalaxyID, srcSystemID, srcPlanetID;
        sscanf(tr->travelCodeSrc, "G%04dS%04dP%04d", &srcGalaxyID, &srcSystemID, &srcPlanetID);

        int dstGalaxyID, dstSystemID, dstPlanetID;
        sscanf(tr->travelCodeDst, "G%04dS%04dP%04d", &dstGalaxyID, &dstSystemID, &dstPlanetID);

        Galaxy* gS = findGalaxy_byID(mg, srcGalaxyID);
        Galaxy* gD = findGalaxy_byID(mg, dstGalaxyID);

        SolarSystem* sS = findSolarSystem_byID(gS, srcSystemID);
        SolarSystem* sD = findSolarSystem_byID(gD, dstSystemID);

        Planet* pS = findPlanet_byID(sS, srcPlanetID);
        Planet* pD = findPlanet_byID(sD, dstSystemID);
        
        double distance = calculateDistance(pS->portal_location, pD->portal_location);

        double travelDuration = (tr->distance) / (tr->spaceCraft->maxSpeed);
        int daysToAdd = (int)travelDuration;
        tr->arrivalDate = advance_date(tr->departureDate, daysToAdd);
    }

}

int check_unique_travel_id(Company* cm, const int id) {
    if (!cm || !cm->travels || cm->numTravels <= 0)
        return 1;

    for (int i = 0; i < cm->numTravels; ++i) {
        if (cm->travels[i]->travelID == id)
            return 0;
    }
    return 1;
}

Date advance_date(Date date, int daysToAdd) {

    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    date.day += daysToAdd; 
    while (1) {
        int daysThisMonth = daysInMonth[date.month - 1];

        // Check for leap year if it's February
        if (date.month == 2 && ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0))) {
            daysThisMonth++;
        }

        if (date.day <= daysThisMonth) {
            break; 
        }

        date.day -= daysThisMonth; 
        date.month++; 

        
        if (date.month > 12) {
            date.month = 1;
            date.year++;
        }
    }

    return date;
}

int compareTravelByID(const void* a, const void* b) {
    const InterstellarTravel* tA = *(const InterstellarTravel**)a;
    const InterstellarTravel* tB = *(const InterstellarTravel**)b;
    return (tA->travelID - tB->travelID);
}

int compareTravelByDepartureDate(const void* a, const void* b) {
    const InterstellarTravel* tA = *(const InterstellarTravel**)a;
    const InterstellarTravel* tB = *(const InterstellarTravel**)b;

    if (tA->departureDate.year != tB->departureDate.year) {
        return tA->departureDate.year - tB->departureDate.year;
    }

    if (tA->departureDate.month != tB->departureDate.month) {
        return tA->departureDate.month - tB->departureDate.month;
    }

    return tA->departureDate.day - tB->departureDate.day;
}

int compareTravelByDistance(const void* a, const void* b) {
    const InterstellarTravel* tA = *(const InterstellarTravel**)a;
    const InterstellarTravel* tB = *(const InterstellarTravel**)b;
   
    if (tA->distance < tB->distance) return -1;
    if (tA->distance > tB->distance) return 1;
    return 0;
}


void print_travel(void* tr) {
    InterstellarTravel* travel = (InterstellarTravel*)tr;
    printf("Travel ID: %d, SRC: %s, DST: %s, Departure Date: %d/%d/%d\n",travel->travelID ,travel->travelCodeSrc, travel->travelCodeDst, travel->departureDate.day, travel->departureDate.month, travel->departureDate.year);
}

/*
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

*/

void free_interstellar_travel(InterstellarTravel* travel) {
    if (travel) {
        //free(travel->travelCode);
        // Note: Do not free spaceCraft here if it is managed elsewhere
        free(travel);
    }
}


/*------Needs to be finished------*/
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


