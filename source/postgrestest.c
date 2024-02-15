#include <stdlib.h>
#include <stdio.h>
#include <postgres.h>
#include <fmgr.h>
#include <catalog/pg_type.h>
#include <utils/builtins.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(TestFunc);

// Run these commands to create C library:
// gcc -fPIC -c foo.c
// gcc -shared -o foo.so foo.o

// https://www.postgresql.org/docs/current/xfunc-c.html
Datum
TestFunc(PG_FUNCTION_ARGS)
{
    PG_RETURN_INT32(0);
}