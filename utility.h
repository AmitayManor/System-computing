#ifndef UTILITY_H
#define UTILITY_H

char* my_strdup(const char* s);
char* safe_strdup(const char* s);
void flush_stdin();
char* myGets(char* buffer, int size);

#endif // UTILITY_H