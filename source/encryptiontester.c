#include <openssl/rand.h>
#include "tinyaes/aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester.c -lstdc++ -o encryptiontester

int main()
{
    struct AES_ctx ctx;
    // uint8_t testString[] = "[{\"time\":\"2024-01-18T13:35:36.742489\",\"temp\":100.00,\"ph\":7.0}]";
    uint8_t str[] = "This a sample text, Length eq 32";
    uint8_t key[] = "aaaaaaaaaaaaaaaa";
    uint8_t iv[] = "bbbbbbbbbbbbbbbb";

    printf("\n Raw buffer\n");
    for(int i = 0; i < 32; i++)
    {
        printf("%.2x", str[i]);
    }

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, str, 32);

    printf("\n Encrypted buffer\n");
    for(int i = 0; i < 32; i++)
    {
        printf("%.2x", str[i]);
    }
}