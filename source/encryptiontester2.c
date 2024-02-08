#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "tinyaes/aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester2.c -lstdc++ -o encryptiontester
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
    printf("\n Raw buffer\n");
    printf("%s\n", paddedData);
    fflush(stdout);

    // Read from key.txt and iv.txt
    // Hex arrays
    unsigned char preKey[256];
    unsigned char preIv[256];
    // Processed arrays (char)
    unsigned char key[128];
    unsigned char iv[128];

    FILE* fptr = fopen("key.txt", "r");
    fgets(preKey, 128, fptr);
    fclose(fptr);
    int c = 0;
    for(int i = 1; i < sizeof(preKey); i+=2)
    {
        key[c] = (char)(preKey[i] + preKey[i-1]);
        c++;
    }
    fptr = fopen("iv.txt", "r");
    fgets(preIv, 128, fptr);
    fclose(fptr);
    c = 0;
    for(int i = 1; i < sizeof(preIv); i+=2)
    {
        iv[c] = (char)(preIv[i] + preIv[i-1]);
        c++;
    }
}