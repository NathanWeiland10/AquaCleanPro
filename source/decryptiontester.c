#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "aes.h"

#define AES128 1

struct AES_ctx ctx;
unsigned char* hexKey = "2279494b693e50722c705e4b57792f42";
unsigned char* hexIv = "4f4054635948416f2e5e2e3471336930";

uint8_t final[] = {123, 34, 116, 101, 109, 112, 34, 58, 32, 53, 48, 46, 48, 44, 32, 34, 112, 104, 34, 58, 32, 55, 46, 48, 125, 7, 7, 7, 7, 7, 7, 7, 32};
uint8_t encryptedVals[] = {87, 78, 140, 128, 150, 71, 84, 129, 219, 53, 243, 92, 96, 215, 33, 70, 160, 115, 222, 71, 3, 155, 19, 6, 64, 210, 55, 46, 180, 92, 190, 51};

// Run this command to compile: gcc decryptiontester.c -o decryptiontester.o --include aes.c
// Run the above in the source directory

int main()
{
    // Grab the argument
    unsigned char* buf = "574e8c8096475481db35f35c60d72146a073de47039b130640d2372eb45cbe33";
    int len = strlen(buf);

    // Set up key and iv
    unsigned char fileBuffer[257];
    unsigned char key[16];
    unsigned char iv[16];
    uint8_t buffer[len / 2];

    strcpy(fileBuffer, buf);
    printf("Hex Encrypted buffer: %s\n", fileBuffer);
    int d = 0;
    for(int i = 0; i < len; i+=2)
    {
      char hex[2];
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      buffer[d++] = (uint8_t)c;
    }
    printf("Encrypted ASCII buffer: %s\n", buffer);
    // Make sure this matches what we expect
    assert(sizeof(buffer) / sizeof(buffer[0]) == sizeof(encryptedVals) / sizeof(encryptedVals[0]));
    for(int i = 0; i < len / 2; i++)
    {
      assert(buffer[i] == encryptedVals[i]);
    }
    // Key
    strcpy(fileBuffer, hexKey);
    d = 0;
    for(int i = 0; i < strlen(hexKey); i+=2)
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
    for(int i = 0; i < strlen(hexIv); i+=2)
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
    AES_CBC_decrypt_buffer(&ctx, buffer, len / 2);
    printf("Decrypted buffer: %s\n", buffer);
    fflush(stdout);
    printf("\n");

    // Assertions to make sure we did everything right
    assert(sizeof(buffer) / sizeof(buffer[0]) == (sizeof(final) / sizeof(final[0])) - 1);
    // Create int array for buffer
    for (int i = 0; i < sizeof(buffer) / sizeof(buffer[0]); i++)
    {
      assert(buffer[i] == final[i]);
    }
}