#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "aes.h"

#define AES128 1

// Run this command to compile: gcc tinyaes/aes.c encryptiontester2.c -lstdc++ -o encryptiontester
// Run the above in the source directory

/*
* Runs the encryption part of the process, similar to how that case would run on the ardunio hardware
*/

int main()
{
    struct AES_ctx ctx;
    // Read from key.txt and iv.txt
    // Hex arrays
    unsigned char fileBuffer[256];
    // Processed arrays (char)
    // TODO, dynamic buffer size
    unsigned char buffer[128];
    unsigned char key[128];
    unsigned char iv[128];

    // Get the buffer
    FILE* fptr = fopen("buffer.txt", "r");
    fgets(fileBuffer, 129, fptr);
    fclose(fptr);
    int d = 0;
    // The last two characters of the buffer should be the number of padded characters
    // Convert from hex back to char
    for(int i = 0; i < 128; i+=2)
    {
       char hex[2];
       sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
       int c = strtoul(hex, NULL, 16);
       buffer[d++] = (unsigned char)c;
    }
    // Key
    fptr = fopen("key.txt", "r");
    fgets(fileBuffer, 256, fptr);
    fclose(fptr);
    d = 0;
    for(int i = 0; i < 256; i+=2)
    {
       char hex[2];
       sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
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
      sprintf(&hex, "%c%c", fileBuffer[i], fileBuffer[i+1]);
      int c = strtoul(hex, NULL, 16);
      iv[d++] = (unsigned char)c;
      printf("%0.2x", iv[d-1]);
    }
 
    printf("\nEncrypted buffer:\n");
    for(int i = 0; i < sizeof(buffer); i++)
    {
      printf("%c", buffer[i]);
    }
    fflush(stdout);
    // Form the context
    AES_init_ctx(&ctx, key);
    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_decrypt_buffer(&ctx, buffer, sizeof(buffer));
    printf("\nDecrypted buffer:\n");
    for(int i = 0; i < sizeof(buffer); i++)
    {
      printf("%c", buffer[i]);
    }
    fflush(stdout);
    return 0;
}