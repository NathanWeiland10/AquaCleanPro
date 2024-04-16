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
unsigned char* hexKey = "7777343e484d6f592d360726726f0c300a7471080a0a0f432b3722794b4447486d42044f35023f346d1b461f0368463c0808533c325c67545b0d5b3d00036f33436f48776a416d4d5e33497e2c3c2c56071e4a2744593a445c3578076e3c644d3a3d4074274b36643e3c50032d2b7e3f467614087d4049526d703a1853306454";
unsigned char* hexIv = "631d463b06693f56325c24030147451b1c2d486c444827384a022d37177c7d10250b0c6404362144563a5c3653062c34463f572c0e3d77011e0d77087d6d1a0c4752744b2a656f776a0147365d370e226f4b29492035522e012014463b6e527d0832402f3735672f2c7226435e192c2558107f04386d7801337e44320f416523";

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
    unsigned char charBuffer[len / 2];
    // Buffer back to character
    strcpy(fileBuffer, buf);
    printf("Encrypted buffer: %s\n", fileBuffer);
    int d = 0;
    for(int i = 0; i < len; i+=2)
    {
        char hex[2];
        sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
        int c = strtoul(hex, NULL, 16);
        charBuffer[d++] = (unsigned char)c;
    }

    // Set up key and iv
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
    // Set up the context and decrypt
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, buf, len);
    elog(NOTICE, "Decrypted buffer: %s", buf);

    // Close server connection
    SPI_finish();
    // Return the unencrypted buffer to Postgres
    PG_RETURN_VARCHAR_P((VarChar *)buf);
}