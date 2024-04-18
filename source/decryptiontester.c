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

// Run this command to compile: gcc decryptiontester.c -o decryptiontester.o --include aes.c
// Run the above in the source directory

int main()
{
    // Grab the argument
    unsigned char* buf = "91925206466c0fe405db1e8d907b879abd4022f24c74731145c48982ab03f88d";
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
    printf("ASCII Encrypted buffer: %s\n", buffer);
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
    AES_CBC_decrypt_buffer(&ctx, buffer, sizeof(buffer));
    printf("Decrypted buffer: %s", buffer);
    fflush(stdout);
    printf("\n");
}