#include "my_assert.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void my_assert(const char * str, const char * file, int line, const char * warning, ...)
{
    va_list args;
    va_start(args, warning);
    
    fprintf(stderr, "Assertion failed: %s   ", str);
    fprintf(stderr, "file %s, line %d\n", file, line);
    vfprintf(stderr, warning, args);

    va_end(args);
    abort();
}
