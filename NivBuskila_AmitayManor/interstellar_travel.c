#include "interstellar_travel.h"
#include "universal_manager.h"

#include <stdlib.h>
#include <string.h>


int writeInterstellarTravelToText(FILE* fp, const InterstellarTravel* travel) {
    if (fp && travel) {
        fprintf(fp, "Travel Code Src: %s\n", travel->travelCodeSrc);
        fprintf(fp, "Travel Code Dst: %s\n", travel->travelCodeDst);
        fprintf(fp, "SpaceCraft ID: %d\n", travel->spaceCraft ? travel->spaceCraft->craftId : -1);
        fprintf(fp, "Departure Date: %d-%d-%d\n", travel->departureDate.day, travel->departureDate.month, travel->departureDate.year);
        fprintf(fp, "Arrival Date: %d-%d-%d\n", travel->arrivalDate.day, travel->arrivalDate.month, travel->arrivalDate.year);
        fprintf(fp, "Distance: %lf\n", travel->distance);
        fprintf(fp, "Risk Level: %d\n", travel->riskLevel);
        fprintf(fp, "Is Completed: %d\n", travel->isCompleted);
        fprintf(fp, "Travel ID: %d\n", travel->travelID);
        return 1;
    }
    else
        return 0;
}

int readInterstellarTravelFromText(FILE* fp, InterstellarTravel* travel, Company* company) {
    if (!fp || !travel) return 0;

    int craftId;
    char bufferSrc[MAX_CODE_LEN];
    char bufferDst[MAX_CODE_LEN];

    if (fscanf(fp, "Travel Code Src: %s\n", bufferSrc) != 1) return 0;
    if (fscanf(fp, "Travel Code Dst: %s\n", bufferDst) != 1) return 0;
    if (fscanf(fp, "SpaceCraft ID: %d\n", &craftId) != 1) return 0;
    if (fscanf(fp, "Departure Date: %d-%d-%d\n", &travel->departureDate.day, &travel->departureDate.month, &travel->departureDate.year) != 3) return 0;
    if (fscanf(fp, "Arrival Date: %d-%d-%d\n", &travel->arrivalDate.day, &travel->arrivalDate.month, &travel->arrivalDate.year) != 3) return 0;
    if (fscanf(fp, "Distance: %lf\n", &travel->distance) != 1) return 0;
    if (fscanf(fp, "Risk Level: %d\n", &travel->riskLevel) != 1) return 0;
    if (fscanf(fp, "Is Completed: %d\n", &travel->isCompleted) != 1) return 0;
    if (fscanf(fp, "Travel ID: %d\n", &travel->travelID) != 1) return 0;

    travel->spaceCraft = searchSpaceCraftFromFile(company, craftId);
    strcpy(travel->travelCodeSrc, bufferSrc);
    strcpy(travel->travelCodeDst, bufferDst);
    return 1;
}

int writeInterstellarTravelToBinaryFile(const InterstellarTravel* travel, FILE* fp) {
    if (!travel || !fp) return 0;

    fwrite(travel->travelCodeSrc, sizeof(char), MAX_CODE_LEN, fp);
    fwrite(travel->travelCodeDst, sizeof(char), MAX_CODE_LEN, fp);
    int craftId = travel->spaceCraft ? travel->spaceCraft->craftId : -1;
    fwrite(&craftId, sizeof(int), 1, fp);
    fwrite(&travel->departureDate, sizeof(Date), 1, fp);
    fwrite(&travel->arrivalDate, sizeof(Date), 1, fp);
    fwrite(&travel->distance, sizeof(double), 1, fp);
    fwrite(&travel->riskLevel, sizeof(int), 1, fp);
    fwrite(&travel->isCompleted, sizeof(int), 1, fp);
    fwrite(&travel->travelID, sizeof(int), 1, fp);

    return 1;
}

int readInterstellarTravelFromBinaryFile(InterstellarTravel* travel, FILE* fp, Company* company) {
    if (!travel || !fp) return 0;

    int craftId;
    fread(travel->travelCodeSrc, sizeof(char), MAX_CODE_LEN, fp);
    fread(travel->travelCodeDst, sizeof(char), MAX_CODE_LEN, fp);
    fread(&craftId, sizeof(int), 1, fp);
    fread(&travel->departureDate, sizeof(Date), 1, fp);
    fread(&travel->arrivalDate, sizeof(Date), 1, fp);
    fread(&travel->distance, sizeof(double), 1, fp);
    fread(&travel->riskLevel, sizeof(int), 1, fp);
    fread(&travel->isCompleted, sizeof(int), 1, fp);
    fread(&travel->travelID, sizeof(int), 1, fp);

    travel->spaceCraft = searchSpaceCraftFromFile(company, craftId);

    return 1;
}

void get_travelCode_Src(UniversalManager* mg, InterstellarTravel* tr) {
    if (mg && tr) {

        displayCosmicElements(mg);

        int galaxyID, systemID, planetID;
        int idFlag = 0;

        Galaxy* galaxy = NULL;
        SolarSystem* system = NULL;
        Planet* planet = NULL;

        do {
            printf("\nEnter Galaxy ID: ");
            scanf("%d", &galaxyID);
            galaxy = findGalaxy_byID(mg, galaxyID);
            if (galaxy)
                idFlag = 1;
            else
                printf("\nError! Galaxy's ID is not valid. Try again.\n");
        } while (!idFlag);
        
        idFlag = 0;
        do {
            printf("\nEnter Solar System ID: ");
            scanf("%d", &systemID);
            system = findSolarSystem_byID(galaxy, systemID);
            if (system)
                idFlag = 1;
            else
                printf("\nError! Solar System's ID is not valid. Try again.\n");
        } while (!idFlag);

        idFlag = 0;
        do {
            printf("\nEnter Planet ID: ");
            scanf("%d", &planetID);
            planet = findPlanet_byID(system, planetID);
            if (planet)
                idFlag = 1;
            else
                printf("\nError! Solar System's ID is not valid. Try again.\n");
        } while (!idFlag);
        

        snprintf(tr->travelCodeSrc, MAX_CODE_LEN, "G%04dS%04dP%04d", galaxyID, systemID, planetID);
        
    }
    else {
        printf("Error with manager and travels allocations");
    }
}

void get_travelCode_Dst(UniversalManager* mg, InterstellarTravel* tr, Permission permission) {
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

        displayCosmicElements(mg);

        printf("\nYour Permission:\t***Cross Planets***\n");
        galaxy = findGalaxy_byID(mg, srcGalaxyID);
        system = findSolarSystem_byID(galaxy, srcSystemID);

        do {
            printf("\nEnter destination Planet ID within Galaxy %04d and Solar System %04d : \n", srcGalaxyID, srcSystemID);
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
        
        displayCosmicElements(mg);
        galaxy = findGalaxy_byID(mg, srcGalaxyID);

        do {
            printf("\nEnter destination Solar System ID within Galaxy %04d: ", srcGalaxyID);
            scanf("%d", &dstSystemID);
            system = findSolarSystem_byID(galaxy, dstSystemID);

            if (system) idFlag = 1;
            else printf("\nError! Solar System's ID is not valid. Try again.\n");

        } while (!idFlag);
        
        idFlag = 0;
        do {
            printf("\nEnter destination Planet ID within Galaxy %04d and Solar System %04d : \n", srcGalaxyID, dstSystemID);
            scanf("%d", &dstPlanetID);
            planet = findPlanet_byID(system, dstPlanetID);

            if (planet) idFlag = 1;
            else printf("\nError! Planet's ID is not valid. Try again.\n");

        } while (!idFlag);
        snprintf(tr->travelCodeDst, MAX_CODE_LEN, "G%04dS%04dP%04d", srcGalaxyID, dstSystemID, dstPlanetID);
        tr->travelCodeDst[MAX_CODE_LEN-1] = '\0';
        break;
    
    case eGALAXY:
        
        displayCosmicElements(mg);
        printf("\nYour Permission:\t***Cross Galaxies***\n");
        do {
            printf("\nEnter destination Galaxy ID: ");
            scanf("%d", &dstGalaxyID);
            galaxy = findGalaxy_byID(mg, dstGalaxyID);

            if (galaxy) idFlag = 1;
            else printf("\nError! Galaxy's ID is not valid. Try again.\n");

        } while (!idFlag);
       

        idFlag = 0;
        do {
            printf("\nEnter destination Solar System ID within Galaxy %04d: ", dstGalaxyID);
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
        Planet* pD = findPlanet_byID(sD, dstPlanetID);
        
        tr->distance = calculateDistance(pS->portal_location, pD->portal_location);

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

void get_travelID(Company* company, InterstellarTravel* tr) {
    
    if (company && tr) {

        int idFlag = 0;
        int trId;
        do {
            printf("\nEnter an ID for this Travel (1-9999):");
            scanf("%d", &trId);

            if (check_unique_travel_id(company, trId)) {
                tr->travelID = trId;
                idFlag = 1;
            }
            else
                printf("\nError! This ID is not valid. Try again.\n");

        } while (!idFlag);
    }
    else {
        LOG_DEBUG("\nError! Memmory allocation failed.\n");
        return;
    }
}

void free_interstellar_travel(InterstellarTravel* travel) {
    if (travel) {
        free(travel);
    }
}

int calculate_risk_level(InterstellarTravel* travel) {
    if (travel) {
        
        if (travel->distance < 1000000.0) {
            return 1; 
        }
        else if (travel->distance < 5000000.0) {
            return 2; 
        }
        else {
            return 3; 
        }
    }
    return 0;
}

int is_travel_successful(InterstellarTravel* travel) {
    if (travel) {
        
        int randomValue = rand() % 100;
        switch (travel->riskLevel) {
        case 1: 
            return randomValue < 90;
        case 2: 
            return randomValue < 70; 
        case 3: 
            return randomValue < 50; 
        default:
            return 0; 
        }
    }
    return 0; 
}


