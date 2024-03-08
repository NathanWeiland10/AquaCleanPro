# Using TinyAES
## Keys and IVs
An AES key has two parts: the main **key** and the Initialization Vector **iv**. The key is used to encrypt/decrypt your data while the iv is used to encrypt the first 'block' of data and set other behind-the-scenes processes.

In order for AES encryption to work, your string must have a length that is divisible by 16, this can be done by adding additional characters to the end of your string as such:
`padded buffer size = length of string + 16 - (length of string mod 16)`

## Using Tinyaes
Once you have your key and iv set up. Add the tinyaes header file to your script:

- `#include "aes.hpp"` (for C++)
- `#include "aes.h"` (for C)

Also define the size of your key and iv in your script:

`#define AES128 1` (for 128 character keys)

Next is to create the encryption context. Create an aes_context object, and call `AES_init_ctx_iv` to set the context with your key and iv.
```
struct AES_ctx ctx;
unsigned char key[128];
unsigned char iv[128];

AES_init_ctx_iv(&ctx, key, iv);
```
You can now call `AES_CBC_decrypt_buffer()` and `AES_CBC_encrypt_buffer()` with your data buffer and the aes context to encrypt/decrypt your data buffer.