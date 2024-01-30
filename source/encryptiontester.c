#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "tinyaes/aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester.c -lstdc++ -o encryptiontester
// Run the above in the source directory

int main()
{
    struct AES_ctx ctx;
    unsigned char testData[] = "[{\"time\":\"2024-01-18T13:35:36.742489\",\"temp\":100.00,\"ph\":7.0}]";
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
    // Print status of buffer before encryption
    printf("Length of buffer: %d\n", strlen(paddedData));
    printf("Is the string divisible by 16? %d\n", strlen(paddedData) % 16 == 0);
    assert(strlen(paddedData) % 16 == 0);
    printf("\n Raw buffer\n");
    printf("%s", paddedData);
    fflush(stdout);

    // Generate a key
    unsigned char key[128];
    unsigned char iv[128];
    srand(time(NULL));
    printf("\n Key Generated: \n");
    for(int i = 0; i < sizeof(key); i++)
    {
        key[i] = rand() % 128;
        iv[i] = rand() % 128;
        printf("%c", key[i]);
    }
    printf("\n IV Generated: \n");
    for(int x = 0; x < sizeof(iv); x++)
    {
        printf("%c", iv[x]);
    }
    fflush(stdout);

    // Encrypt data (print hex)
    AES_init_ctx(&ctx, key);
    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_encrypt_buffer(&ctx, paddedData, paddedLength);
    printf("\n Encrypted buffer\n");
    for(int i = 0; i < paddedLength; i++)
    {
        printf("%c", paddedData[i]);
    }
    fflush(stdout);

    // Try decrypting
    printf("\nDecryption...\n");
    AES_init_ctx(&ctx, key);
    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_decrypt_buffer(&ctx, paddedData, paddedLength);
    for(int i = 0; i < paddedLength; i++)
    {
        printf("%c", paddedData[i]);
    }
    fflush(stdout);

    printf('\n');

    return 0;
}

