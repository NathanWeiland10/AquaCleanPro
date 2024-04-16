#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "aes.h"

#define AES128 1

struct AES_ctx ctx;
unsigned char* hexKey = "3f535e475b6e3762596e355f226d704e636837652333273c722143494a5f2e3e66274148607127635842755b423825727657267574683b3667305e5a5c2862254a3875513c2c2d653671224c745b266d563b537247615b78733d736f6e66617679403f5d516a426b304d493344632a73332d66685f382f6f6373366556796050";
unsigned char* hexIv = "2e28736b51253267623b76263825564b3e5d357259393160302d765a5256492d2c3a6b435a67337979216a5b56655528783d25656c21517358626a3d2e61365e5b4f336f3f5658737530675e6a7275502b676b6e2469622d2c75256d66315953375238225a492552443f5853352b5f3f396769536e3e2a3e5832425964757272";

// Run this command to compile: gcc decryptiontester.c -o decryptiontester.o --include aes.c
// Run the above in the source directory

int main()
{
    // Grab the argument
    unsigned char* buf = "4cf9f92e1482b41199d484b7cc892896ec1c56337382f455275e6a2b2e11601c";
    int len = strlen(buf);

    // Set up key and iv
    unsigned char fileBuffer[257];
    unsigned char key[128];
    unsigned char iv[128];
    unsigned char buffer[len / 2];
    // Buffer back to character
    strcpy(fileBuffer, buf);
    printf("Encrypted buffer: %s\n", fileBuffer);
    int d = 0;
    for(int i = 0; i < len; i+=2)
    {
        char hex[2];
        sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
        int c = strtoul(hex, NULL, 16);
        buffer[d++] = (unsigned char)c;
    }
    // Key
    strcpy(fileBuffer, hexKey);
    d = 0;
    for(int i = 0; i < 257; i+=2)
    {
       char hex[2];
       sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
       int c = strtoul(hex, NULL, 16);
       key[d++] = (unsigned char)c;
    }
    printf("Key: %s\n", key);
    fflush(stdout);
    // IV
    strcpy(fileBuffer, hexIv);
    d = 0;
    for(int i = 0; i < 257; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      iv[d++] = (unsigned char)c;
    }
    printf("IV: %s\n", iv);
    fflush(stdout);
    // Set up the context and decrypt
    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer, len);
    printf("Decrypted buffer: %s", buffer);
    fflush(stdout);
}