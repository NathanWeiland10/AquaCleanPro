#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <postgres.h>
#include <catalog/pg_type_d.h>

#include "aes.h"

#define AES128 1

struct AES_ctx ctx;
unsigned char* hexKey = "<128 bit key>";
unsigned char* hexIv = "<128 bit IV>";

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(decryptBuffer);

Datum
decryptBuffer(PG_FUNCTION_ARGS)
{
    // Grab the argument
    unsigned char* buf = VARDATA(PG_GETARG_VARCHAR_P(0));
    int len = strlen(buf);

    uint8_t* buffer = malloc((len / 2) * sizeof(uint8_t));
    unsigned char key[17];
    unsigned char iv[17];
    
    elog(NOTICE, "Encrypted buffer: %s", buf);
    elog(NOTICE, "Buffer size: %d", len);
    // Buffer back to char
    int d = 0;
    for(int i = 0; i < len; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", buf[i], buf[i+1]);
      int c = strtoul(hex, NULL, 16);
      buffer[d++] = (uint8_t)c;
    }

    // Set up key and iv
    d = 0;
    for(int i = 0; i < 32; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", hexKey[i], hexKey[i+1]);
      int c = strtoul(hex, NULL, 16);
      key[d++] = (unsigned char)c;
    }
    key[16] = '\0';

    // IV
    d = 0;
    for(int i = 0; i < 32; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", hexIv[i], hexIv[i+1]);
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
    // Free malloc'd memory
    free(buffer);
}