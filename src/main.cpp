#include <iostream>
#include <sodium.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include "Crypto.hpp"

static const char MAGIC[] = "FENC01"; // magic header to identify file format

void print_usage(const char* prog) {
    std::cout << "Usage:\n"
              << prog << " encrypt <infile> <outfile>\n"
              << prog << " decrypt <infile> <outfile>\n";
}

int main(int argc, char** argv) {
    if (sodium_init() < 0) {
        std::cerr << "libsodium init failed\n";
        return 1;
    }

    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    std::string mode = argv[1];
    std::string infile = argv[2];
    std::string outfile = argv[3];

    if (mode == "encrypt") {
        std::string password;
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        // generate salt
        unsigned char salt[crypto_pwhash_SALTBYTES];
        randombytes_buf(salt, sizeof salt);

        unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];
        if (!Crypto::derive_key_from_password(password, salt, key)) {
            std::cerr << "Failed to derive key\n";
            return 1;
        }

        FILE* in = fopen(infile.c_str(), "rb");
        if (!in) { perror("fopen input"); return 1; }
        FILE* out = fopen(outfile.c_str(), "wb");
        if (!out) { perror("fopen output"); fclose(in); return 1; }

        // write header: magic + salt
        if (fwrite(MAGIC, 1, strlen(MAGIC), out) != strlen(MAGIC)) { perror("write"); fclose(in); fclose(out); return 1; }
        if (fwrite(salt, 1, sizeof salt, out) != sizeof salt) { perror("write salt"); fclose(in); fclose(out); return 1; }

        int res = Crypto::encrypt_file_stream(in, out, key);
        fclose(in);
        fclose(out);

        if (res != 0) {
            std::cerr << "Encryption failed: " << res << "\n";
            return 1;
        }

        // wipe key from memory
        sodium_memzero(key, sizeof key);
        std::cout << "Encrypted -> " << outfile << "\n";
    } else if (mode == "decrypt") {
        std::string password;
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        FILE* in = fopen(infile.c_str(), "rb");
        if (!in) { perror("fopen input"); return 1; }

        // read magic + salt
        char magicbuf[sizeof(MAGIC)];
        if (fread(magicbuf, 1, strlen(MAGIC), in) != strlen(MAGIC)) { std::cerr << "Invalid input or short file\n"; fclose(in); return 1; }
        if (strncmp(magicbuf, MAGIC, strlen(MAGIC)) != 0) { std::cerr << "Wrong file format\n"; fclose(in); return 1; }

        unsigned char salt[crypto_pwhash_SALTBYTES];
        if (fread(salt, 1, sizeof salt, in) != sizeof salt) { std::cerr << "Failed to read salt\n"; fclose(in); return 1; }

        unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];
        if (!Crypto::derive_key_from_password(password, salt, key)) {
            std::cerr << "Failed to derive key\n";
            fclose(in);
            return 1;
        }

        FILE* out = fopen(outfile.c_str(), "wb");
        if (!out) { perror("fopen output"); fclose(in); return 1; }

        int res = Crypto::decrypt_file_stream(in, out, key);
        fclose(in);
        fclose(out);

        sodium_memzero(key, sizeof key);

        if (res != 0) {
            std::cerr << "Decryption failed: possible wrong password or corrupted file (err=" << res << ")\n";
            return 1;
        }
        std::cout << "Decrypted -> " << outfile << "\n";
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}

