#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#define MOE_VARARG_MSG(prefix) \
    va_list args; \
    fprintf(stderr, "\n" prefix ": "); \
    va_start( args, fmt ); \
    vfprintf(stderr, fmt, args); \
    va_end( args ); \
    fprintf(stderr, "\n");

void moe_error(const char *fmt, ...)
{
    MOE_VARARG_MSG("ERROR");
    exit(1);
}

void moe_warning(const char *fmt, ...)
{
    MOE_VARARG_MSG("WARNING");
}
