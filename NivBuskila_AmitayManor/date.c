#include "date.h"
#include <stdio.h>

// Function to compare two dates
int compare_dates(const Date* date1, const Date* date2) {
    if (!date1 || !date2) return 0; // Error or equal, depending on how you want to handle it

    // Compare year, then month, then day
    if (date1->year != date2->year)
        return date1->year - date2->year;
    if (date1->month != date2->month)
        return date1->month - date2->month;
    return date1->day - date2->day;
}

// Function to print a date in a standard format
void print_date(const Date* date) {
    if (!date) return;

    printf("%02d/%02d/%04d", date->day, date->month, date->year);
}

// Function to check if a given date is valid
int is_valid_date(const Date* date) {
    if (!date) return 0;

    // Check year range, if needed
    if (date->year < 1) return 0;

    // Check month
    if (date->month < 1 || date->month > 12) return 0;

    // Check days
    switch (date->month) {
    case 2: // February
        // Check for leap year
        if ((date->year % 4 == 0 && date->year % 100 != 0) || (date->year % 400 == 0)) {
            if (date->day < 1 || date->day > 29) return 0;
        }
        else {
            if (date->day < 1 || date->day > 28) return 0;
        }
        break;
    case 4: case 6: case 9: case 11: // April, June, September, November
        if (date->day < 1 || date->day > 30) return 0;
        break;
    default: // All other months
        if (date->day < 1 || date->day > 31) return 0;
    }

    return 1; // Date is valid
}
