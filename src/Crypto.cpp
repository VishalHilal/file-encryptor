#include "Crypto.hpp"
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <iostream>

int Crypto::encrypt_file_stream(FILE* in, FILE* out, const unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]) {
    if (!in || !out) return -1;

    // Initialize the push (encrypt) state
    crypto_secretstream_xchacha20poly1305_state st;
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];

    if (crypto_secretstream_xchacha20poly1305_init_push(&st, header, key) != 0) {
        return -2;
    }

    // Write the header to the output first
    if (fwrite(header, 1, sizeof(header), out) != sizeof(header)) return -3;

    const size_t CHUNK = 64 * 1024;
    std::vector<unsigned char> inbuf(CHUNK);
    std::vector<unsigned char> outbuf(CHUNK + crypto_secretstream_xchacha20poly1305_ABYTES);

    while (true) {
        size_t read = fread(inbuf.data(), 1, CHUNK, in);
        if (read == 0) {
            // finalize with tag FINAL
            unsigned long long outlen;
            if (crypto_secretstream_xchacha20poly1305_push(&st, outbuf.data(), &outlen,
                    nullptr, 0, nullptr, 0, crypto_secretstream_xchacha20poly1305_TAG_FINAL) != 0) {
                return -4;
            }
            if (fwrite(outbuf.data(), 1, (size_t)outlen, out) != (size_t)outlen) return -5;
            break;
        }

        unsigned long long outlen;
        if (crypto_secretstream_xchacha20poly1305_push(&st, outbuf.data(), &outlen,
                inbuf.data(), read, nullptr, 0, 0) != 0) {
            return -6;
        }
        if (fwrite(outbuf.data(), 1, (size_t)outlen, out) != (size_t)outlen) return -7;
    }

    return 0;
}

int Crypto::decrypt_file_stream(FILE* in, FILE* out, const unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]) {
    if (!in || !out) return -1;

    // Read header
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    if (fread(header, 1, sizeof(header), in) != sizeof(header)) return -2;

    crypto_secretstream_xchacha20poly1305_state st;
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, key) != 0) {
        return -3;
    }

    const size_t CHUNK = 64 * 1024;
    std::vector<unsigned char> inbuf(CHUNK + crypto_secretstream_xchacha20poly1305_ABYTES);
    std::vector<unsigned char> outbuf(CHUNK);

    while (true) {
        size_t read = fread(inbuf.data(), 1, inbuf.size(), in);
        if (read == 0) {
            // End of file: nothing left
            break;
        }

        unsigned long long outlen;
        unsigned char tag;
        if (crypto_secretstream_xchacha20poly1305_pull(&st, outbuf.data(), &outlen, &tag,
                inbuf.data(), (unsigned long long)read, nullptr, 0) != 0) {
            // Forged or corrupt
            return -4;
        }

        if (fwrite(outbuf.data(), 1, (size_t)outlen, out) != (size_t)outlen) return -5;

        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL) {
            break; // finished successfully
        }
    }

    return 0;
}

bool Crypto::derive_key_from_password(const std::string &password,
                                     const unsigned char salt[crypto_pwhash_SALTBYTES],
                                     unsigned char out_key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]) {
    // Use recommended opslimit/memlimit from libsodium docs (adjust as needed)
    const unsigned long long opslimit = crypto_pwhash_OPSLIMIT_MODERATE;
    const size_t memlimit = crypto_pwhash_MEMLIMIT_MODERATE;

    if (crypto_pwhash(out_key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES,
                      password.c_str(), password.size(),
                      salt, opslimit, memlimit, crypto_pwhash_ALG_ARGON2ID13) != 0) {
        return false; // out of memory
    }
    return true;
}
