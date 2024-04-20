#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <postgres.h>
#include <catalog/pg_type_d.h>

#include "aes.h"

#define AES128 1

struct AES_ctx ctx;
unsigned char* hexKey = "57214e236240224275354c325d6d5965";
unsigned char* hexIv = "6a3039335752755f3c793b22434e6e4c";

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(decryptBuffer);

Datum
decryptBuffer(PG_FUNCTION_ARGS)
{
    // Grab the argument
    unsigned char* buf = VARDATA(PG_GETARG_VARCHAR_P(0));
    int len = strlen(buf);
    elog(NOTICE, "Encrypted buffer: %s", buf);
    elog(NOTICE, "Buffer size: %d", len);

    // Buffer back to char
    unsigned char fileBuffer[257];
    uint8_t buffer[len / 2];
    strcpy(fileBuffer, buf);
    printf("Encrypted buffer: %s\n", fileBuffer);
    int d = 0;
    for(int i = 0; i < len; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      buffer[d++] = (uint8_t)c;
    }

    // Set up key and iv
    unsigned char key[17];
    unsigned char iv[17];
    strcpy(fileBuffer, hexKey);
    d = 0;
    for(int i = 0; i < 32; i+=2)
    {
       char hex[2];
       sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
       int c = strtoul(hex, NULL, 16);
       key[d++] = (unsigned char)c;
    }
    key[16] = '\0';

    // IV
    strcpy(fileBuffer, hexIv);
    d = 0;
    for(int i = 0; i < 32; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      iv[d++] = (unsigned char)c;
    }
    iv[16] = '\0';

    // Set up the context and decrypt
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer, len / 2);
    elog(NOTICE, "Decrypted buffer: %s", buffer);

    // Close server connection
    SPI_finish();
    // Return the unencrypted buffer to Postgres
    PG_RETURN_VARCHAR_P((VarChar *)buffer);
}