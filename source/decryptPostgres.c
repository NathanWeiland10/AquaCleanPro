#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <postgres.h>
#include <commands/trigger.h>
#include <fmgr.h>
#include <catalog/pg_type.h>
#include <utils/builtins.h>
#include "aes.h"

#define AES128 1

struct AES_ctx ctx;
unsigned char* hexKey = "<ENTER 256 HEX KEY HERE>";
unsigned char* hexIv = "<ENTER 256 HEX IV HERE>";

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(decryptBuffer);

Datum
decryptBuffer(PG_FUNCTION_ARGS)
{
    // Get trigger context
    TriggerData *trigdata = (TriggerData *) fcinfo->context;
    HeapTuple   tuple;
    HeapTuple   rettuple;

    //Make sure that the function is called from a trigger
    if (!CALLED_AS_TRIGGER(fcinfo))
        elog(ERROR, "are you sure you are calling from trigger manager?");

    // Connect to server
    SPI_connect();

    // Set up key and iv
    unsigned char fileBuffer[256];
    unsigned char key[128];
    unsigned char iv[128];
    strcpy(fileBuffer, hexKey);
    int d = 0;
    for(int i = 0; i < 256; i+=2)
    {
       char hex[2];
       sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
       int c = strtoul(hex, NULL, 16);
       key[d++] = (unsigned char)c;
    }
    // IV
    strcpy(fileBuffer, hexIv);
    d = 0;
    for(int i = 0; i < 256; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      iv[d++] = (unsigned char)c;
    }

    char* buf;
    // Triggered by INSERT event
    if (TRIGGER_FIRED_BY_INSERT(trigdata->tg_event))
    {
        // Grab the argument
        HeapTupleHeader t = PG_GETARG_HEAPTUPLEHEADER(0);
        bool isnull;
        Datum type = GetAttributeByName(t, "type", &isnull);
        buf = VARDATA(DatumGetVarCharPP(type));
        int len = VARSIZE(DatumGetVarCharPP(type)) - VARHDRSZ;
        // Set up the context and decrypt
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CBC_decrypt_buffer(&ctx, buf, len);
    }

    // Close server connection
    SPI_finish();
    // Return the unencrypted buffer to Postgres
    PG_RETURN_VARCHAR_P((VarChar *)buf);
    // Can insert this buffer into water_data from SQL
    // If that fails we can look into bringing in a HTTP library and post it that way
}