#include "interstellar_travel.h"
#include "universal_manager.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void testInterstellarTravelIO() {
    // Setup
    Planet planet1 = { "Bijo", {4,1,2},1,2,15 };
    Planet planet2 = { "Eden", {5,1,2},2,2,15 };
    Planet planet3 = { "Omri", {4,1,7},3,2,15 };
    Planet planet11 = { "avi", {43,1,77},1,2,10 };

    PlanetNode pNode3 = { &planet3,NULL };
    PlanetNode pNode2 = { &planet2,&pNode3 };
    PlanetNode pNode1 = { &planet1,&pNode2 };
    PlanetNode pNode11 = { &planet11,NULL };

    SolarSystem system = { "Niv",{2, 2, 2},5, &pNode1,3, 1000, 32 };
    SolarSystem system2 = { "Milky",{1, 2, 43},6, &pNode11,1, 1000, 32 };

    SolarSystem** star_system = ALLOCATE(SolarSystem**, 2);
    star_system[0] = &system;
    star_system[1] = &system2;

    Galaxy galaxy = { "Amitay",{1,1,1}, star_system, 2,10,100,1 };

    Galaxy** galaxies = ALLOCATE(Galaxy**, 1);
    galaxies[0] = &galaxy;


    SpaceCraft sp1 = { "f1","t",1500,1 };
    SpaceCraft sp2 = { "f2","q",1500,2 };
    SpaceCraft sp3 = { "f3","a",1500,3 };
    SpaceCraft sp4 = { "f4","z",1500,4 };

    SpaceCraft** sCrafts = ALLOCATE(SpaceCraft**, 4);
    sCrafts[0] = &sp1;
    sCrafts[1] = &sp2;
    sCrafts[2] = &sp3;
    sCrafts[3] = &sp4;


    Company cm1 = { "SpaceX", 1997, 4, sCrafts, NULL, 0,eGALAXY };
    Company cm2 = { "China", 2000, 4, sCrafts, NULL, 0,eSOLARSYSTEM };
    Company cm3 = { "USA", 1968, 4, sCrafts, NULL, 0,ePLANET };

    Company** companies = ALLOCATE(Company**, 3);

    companies[0] = &cm1;
    companies[1] = &cm2;
    companies[2] = &cm3;

    UniversalManager manager = { galaxies,1, companies,3 };


    Company company = { "SpaceX", 1997, 4, sCrafts, NULL, 0,eGALAXY };
    InterstellarTravel travel = {
        "CodeSRC123", "CodeDST456",
        searchSpaceCraftFromFile(&company, 1),  // Assuming a SpaceCraft with ID 101 exists
        {1, 12, 2022}, {5, 1, 2023},  // Departure and arrival dates
        1000000.0, 5, 1, 999  // Distance, risk level, completion status, travel ID
    };

    // Write to text file
    FILE* fp = fopen("test_travel.txt", "w+");
    assert(fp != NULL);
    assert(writeInterstellarTravelToText(&travel, fp));
    rewind(fp);

    // Read from text file
    InterstellarTravel loadedTravel;
    assert(readInterstellarTravelFromText(fp, &loadedTravel, &company));
    fclose(fp);

    // Verify text file IO
    assert(strcmp(travel.travelCodeSrc, loadedTravel.travelCodeSrc) == 0);
    assert(strcmp(travel.travelCodeDst, loadedTravel.travelCodeDst) == 0);
    assert(travel.spaceCraft->craftId == loadedTravel.spaceCraft->craftId);
    assert(travel.departureDate.day == loadedTravel.departureDate.day);
    assert(travel.arrivalDate.day == loadedTravel.arrivalDate.day);
    assert(travel.distance == loadedTravel.distance);
    assert(travel.riskLevel == loadedTravel.riskLevel);
    assert(travel.isCompleted == loadedTravel.isCompleted);
    assert(travel.travelID == loadedTravel.travelID);

    // Write to binary file
    fp = fopen("test_travel.bin", "wb+");
    assert(fp != NULL);
    assert(writeInterstellarTravelToBinaryFile(&travel, fp));
    rewind(fp);

    // Read from binary file
    assert(readInterstellarTravelFromBinaryFile(&loadedTravel, fp, &company));
    fclose(fp);

    // Verify binary file IO
    assert(strcmp(travel.travelCodeSrc, loadedTravel.travelCodeSrc) == 0);
    assert(strcmp(travel.travelCodeDst, loadedTravel.travelCodeDst) == 0);
    assert(travel.spaceCraft->craftId == loadedTravel.spaceCraft->craftId);
    assert(travel.departureDate.day == loadedTravel.departureDate.day);
    assert(travel.arrivalDate.day == loadedTravel.arrivalDate.day);
    assert(travel.distance == loadedTravel.distance);
    assert(travel.riskLevel == loadedTravel.riskLevel);
    assert(travel.isCompleted == loadedTravel.isCompleted);
    assert(travel.travelID == loadedTravel.travelID);

    }

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

    travel->spaceCraft = searchSpaceCraftFromFile(company, craftId); // Implement this function to find SpaceCraft by ID
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
        tr->travelCodeSrc[MAX_CODE_LEN] = '\0';
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
        // Limited to planets within the same solar system
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


