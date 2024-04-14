#ifndef DATE_H
#define DATE_H

#include "macros.h"

typedef struct Date {
    int day, month, year;
} Date;

int compare_dates(const Date* date1, const Date* date2);
void print_date(const Date* date);
int is_valid_date(const Date* date);
Date* createDate();

#endif // DATE_H
