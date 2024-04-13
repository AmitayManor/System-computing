#ifndef UTILITY_H
#define UTILITY_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "macros.h"

void generic_print(void* entity, void (*print_func)(void*));
char* my_strdup(const char* s);
void flush_stdin();
char* myGets(char* buffer, int size);

#endif // UTILITY_H