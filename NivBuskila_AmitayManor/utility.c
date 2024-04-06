#include "utility.h"


char* my_strdup(const char* s) {
    if (!s) return NULL;
    char* new_str = (char*)malloc(strlen(s) + 1);
    if (new_str) strcpy(new_str, s);
    return new_str;
}

char* safe_strdup(const char* s) {
    return s ? my_strdup(s) : NULL;
}

char* myGets(char* buffer, int size) {
    flush_stdin();
    if (!buffer || size <= 0) return NULL;
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        return buffer;
    }
    return NULL;
}
void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}  // Read and discard characters until newline or EOF
}

