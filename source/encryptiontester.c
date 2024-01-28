#include <stdlib.h>
#include <stdio.h>
#include "tinyaes/aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester.c -lstdc++ -lssl -o encryptiontester

int main()
{
    struct AES_ctx ctx;
    // uint8_t testString[] = "[{\"time\":\"2024-01-18T13:35:36.742489\",\"temp\":100.00,\"ph\":7.0}]";
    unsigned char str[] = "This a sample text, Length eq 32";
    // TODO: Add padding to support strings where str.length() % 16 != 0 (padding)
    unsigned char key[128];
    uint8_t iv[] = "bbbbbbbbbbbbbbbb";

    printf("\n Raw buffer\n");
    printf("%s", str);
    fflush(stdout);

    // Generate a key
    srand(time(NULL));
    for(int i = 0; i < sizeof(key); i++)
    {
        key[i] = rand() % 128;
    }
    printf("\n Key Generated:\n");
    printf("%s", key);

    AES_init_ctx(&ctx, key);
    AES_CBC_encrypt_buffer(&ctx, str, 32);

    printf("\n Encrypted buffer\n");
    for(int i = 0; i < 32; i++)
    {
        printf("%.2x", str[i]);
    }
}

