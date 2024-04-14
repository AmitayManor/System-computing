#include "date.h"
#include <stdio.h>


int compare_dates(const Date* date1, const Date* date2) {
    if (!date1 || !date2) return 0; 

    if (date1->year != date2->year)
        return date1->year - date2->year;
    if (date1->month != date2->month)
        return date1->month - date2->month;
    return date1->day - date2->day;
}

void print_date(const Date* date) {
    if (!date) return;

    printf("%02d/%02d/%04d", date->day, date->month, date->year);
}

int is_valid_date(const Date* date) {
    if (!date) return 0;

    if (date->year < 1) return 0;

    if (date->month < 1 || date->month > 12) return 0;

    switch (date->month) {
    case 2: 
        // Check for leap year
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0)) {
            if (date->day < 1 || date->day > 29) return 0;
        }
        else {
            if (date->day < 1 || date->day > 28) return 0;
        }
        break;
    case 4: case 6: case 9: case 11: 
        if (date->day < 1 || date->day > 30) return 0;
        break;
    default: 
        if (date->day < 1 || date->day > 31) return 0;
    }

    return 1; 
}

Date* createDate() {
    Date* date = ALLOCATE(Date*, 1);
    if (!date) {
        free(date);
        LOG_DEBUG("\nError! Memory allocation failed.\n");
        return NULL;
    }
    do {
        printf("Enter day, month, and year (DD MM YYYY): ");
        scanf("%d %d %d", &date->day, &date->month, &date->year);

        if (!is_valid_date(date)) {
            printf("Invalid date. Please try again.\n");
        }
    } while (!is_valid_date(date));

    return date;
}
