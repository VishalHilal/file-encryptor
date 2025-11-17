#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>
#include <vector>
#include <sodium.h>

class Crypto {
public:
    static bool derive_key_from_password(const std::string &password,
                                         const unsigned char salt[crypto_pwhash_SALTBYTES],
                                         unsigned char out_key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]);

    static int encrypt_file_stream(FILE* in, FILE* out, const unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]);

    static int decrypt_file_stream(FILE* in, FILE* out, const unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]);
};

#endif
