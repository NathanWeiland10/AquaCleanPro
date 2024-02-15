#include <stdlib.h>
#include <stdio.h>
#include "fmgr.h"

PG_MODULE_MAGIC;

// Run these commands to create C library:
// gcc -fPIC -c foo.c
// gcc -shared -o foo.so foo.o

// https://www.postgresql.org/docs/current/xfunc-c.html
int TestFunc()
{
    printf("Hello from postgres.\n");
    return 0;
}