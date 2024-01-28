#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "tinyaes/aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester.c -lstdc++ -lssl -o encryptiontester

int main()
{
    struct AES_ctx ctx;
    unsigned char testData[] = "[{\"time\":\"2024-01-18T13:35:36.742489\",\"temp\":100.00,\"ph\":7.0}]";
    // Create padded string divisible by 16
    size_t paddedLength = strlen(testData) + 16 - (strlen(testData) % 16);
    unsigned char paddedData[paddedLength];
    // Copy current data over to padded buffer
    printf("Length of buffer pre-padding: %d\n", strlen(paddedData));
    // Copy data to paddedData, but add padding at the end
    for(int i = 0; i < paddedLength; i++)
    {
        if (i < strlen(testData))
        {
            paddedData[i] = testData[i];
        }
        else
        {
            paddedData[i] = (strlen(testData) % 16);
        }
    }
    printf("Is the string divisible by 16? %d\n", strlen(paddedData) % 16 == 0);
    assert(strlen(paddedData) % 16 == 0);

    printf("\n Raw buffer\n");
    printf("%s", paddedData);
    fflush(stdout);

    // Generate a key
    unsigned char key[128];
    srand(time(NULL));
    for(int i = 0; i < sizeof(key); i++)
    {
        key[i] = rand() % 128;
    }
    printf("\n Key Generated:\n");
    printf("%s", key);

    AES_init_ctx(&ctx, key);
    AES_CBC_encrypt_buffer(&ctx, testData, 32);

    printf("\n Encrypted buffer\n");
    for(int i = 0; i < 32; i++)
    {
        printf("%.2x", testData[i]);
    }
}

