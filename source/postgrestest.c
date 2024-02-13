#include <stdlib.h>
#include <stdio.h>

// gcc -shared -o postgrestest.so -fPIC .\source\postgrestest.c
int TestFunc()
{
    printf("Hello from postgres.\n");
    return 0;
}