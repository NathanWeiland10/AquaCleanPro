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

// Contains no key/IV generation

int main()
{
    unsigned char fileBuffer[257];
    unsigned char key[128];
    unsigned char iv[128];

    unsigned char testData[] = "{\"temp\": 50.0, \"ph\": 7.0}";
    // Create padded string divisible by 16
    size_t paddedLength = strlen(testData) + 16 - (strlen(testData) % 16);
    unsigned char paddedData[paddedLength];
    // Copy data to paddedData, but add padding at the end
    for(int i = 0; i < paddedLength; i++)
    {
        if (i < strlen(testData))
        {
            paddedData[i] = testData[i];
        }
        else
        {
            paddedData[i] = 16 - (strlen(testData) % 16);
        }
    }
    // Get Key and IV
    // Key
    strcpy(fileBuffer, hexKey);
    int d = 0;
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

    // Encrypt
    srand(time(NULL));
    AES_init_ctx(&ctx, key);
    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_encrypt_buffer(&ctx, paddedData, paddedLength);

    printf("Encrypted buffer: ");
    for (int i = 0; i < paddedLength; i++)
    {
        printf("%c", paddedData[i]);
    }
    printf("\n");

    // Decrypt
    printf("Decrypted buffer: ");
    AES_init_ctx(&ctx, key);
    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_decrypt_buffer(&ctx, paddedData, paddedLength);
    for(int i = 0; i < paddedLength; i++)
    {
        printf("%c", paddedData[i]);
    }
    printf("\n");
}