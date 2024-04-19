#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "aes.h"

#define AES128 1

int main()
{
    // Generate a key
    unsigned char key[16];
    unsigned char iv[16];
    srand(time(NULL));
    printf("Key Generated: ");
    for(int i = 0; i < 16; i++)
    {
        key[i] = (rand()%(122-33))+33; // From ! to z
        iv[i] = (rand()%(122-33))+33;
        printf("%c", key[i]);

    }
    printf("\n");
    printf("IV Generated: ");
        for(int x = 0; x < sizeof(iv); x++)
    {
        printf("%c", iv[x]);
    }
    printf("\n");
    // Print stuff out (hex)
    // Key
    FILE* fptr = fopen("key.txt", "w");
    for(int i = 0; i < sizeof(key); i++)
    {
        fprintf(fptr, "%.2x", key[i]);
    }
    fclose(fptr);
    // IV
    fptr = fopen("iv.txt", "w");
    for(int i = 0; i < sizeof(iv); i++)
    {
        fprintf(fptr, "%.2x", iv[i]);
    }
    fclose(fptr);
}