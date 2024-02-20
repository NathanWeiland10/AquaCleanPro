#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <postgres.h>
#include <fmgr.h>
#include <catalog/pg_type.h>
#include <utils/builtins.h>
#include "tinyaes/aes.h"

#define AES128 1

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(decryptOnInsert);

Datum
decryptOnInsert(PG_FUNCTION_ARGS)
{
    // Get trigger context
    TriggerData *trigdata = (TriggerData *) fcinfo->context;
    HeapTuple   tuple;
    HeapTuple   rettuple;
    int         attnum = 0;
    Datum       datumVal;

    //Make sure that the function is called from a trigger
    if (!CALLED_AS_TRIGGER(fcinfo))
        elog(ERROR, "are you sure you are calling from trigger manager?");

    // Connect to server
    SPI_connect();

    // Triggered by INSERT event
    if (TRIGGER_FIRED_BY_INSERT(trigdata->tg_event))
    {
        // Grab the tuple
        tuple = trigdata->tg_trigtuple;
    }

    // Close server connection
    SPI_finish();
    return PointerGetDatum(tuple);
}