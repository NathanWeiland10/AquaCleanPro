#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tinyaes/aes.hpp"

#define AES128 1

struct AES_ctx ctx;
unsigned char key[128];
unsigned char iv[128];

void setup() 
{
    char fileBuffer[256];
    // Grab the key and IV info
    FILE* fptr = fopen("key.txt", "r");
    fgets(fileBuffer, 256, fptr);
    fclose(fptr);
    int d = 0;
    for(int i = 0; i < 256; i+=2)
    {
       char hex[2];
       sprintf(hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
       int c = strtoul(hex, NULL, 16);
       key[d++] = (unsigned char)c;
    }
    // IV
    fptr = fopen("iv.txt", "r");
    fgets(fileBuffer, 256, fptr);
    fclose(fptr);
    d = 0;
    for(int i = 0; i < 256; i+=2)
    {
      char hex[2];
      sprintf(hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      iv[d++] = (unsigned char)c;
      printf("%0.2x", iv[d-1]);
    }
    // Set up the context
    AES_init_ctx_iv(&ctx, key, iv);
    delete[] fileBuffer;
}

void loop() 
{

}
