#ifndef __MACROS__
#define __MACROS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define LOG_DEBUG(msg) printf("[DEBUG] %s:%d: %s\n", __FILE__, __LINE__, msg)
#else
#define LOG_DEBUG(msg)
#endif

#define ALLOCATE(type, count) (type*)malloc((count) * sizeof(type))

#define STR_EQUAL(str1, str2) (strcmp((str1), (str2)) == 0)


#endif // !__MACROS__

