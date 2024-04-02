#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <postgres.h>
#include <fmgr.h>
#include <catalog/pg_type.h>
#include <utils/builtins.h>
#include <utils/geo_decls.h>
#include <varatt.h>

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
    // Grab the argument
    char* buf = VARDATA(PG_GETARG_VARCHAR_P(0));
    int len = strlen(buf);
    elog(NOTICE, "Encrypted buffer: %s", buf);

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
    elog(NOTICE, "Key and IV set up");

    // Set up the context and decrypt
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, buf, len);
    elog(NOTICE, "Decrypted buffer: %s", buf);

    // Close server connection
    SPI_finish();
    // Return the unencrypted buffer to Postgres
    PG_RETURN_VARCHAR_P((VarChar *)buf);
}