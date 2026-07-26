#include <iostream>
#include <iomanip>
#include <cstring>
#include <openssl/des.h>
#include <openssl/rand.h>

int main() {
    // 24-byte (192-bit) 3DES key
    DES_cblock key1, key2, key3;
    memcpy(key1, "12345678", 8);
    memcpy(key2, "abcdefgh", 8);
    memcpy(key3, "ABCDEFGH", 8);

    DES_key_schedule ks1, ks2, ks3;
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // 8-byte IV
    DES_cblock iv;
    RAND_bytes(iv, sizeof(iv));

    // Plaintext (must be multiple of 8 bytes)
    unsigned char plaintext[16] = "Hello1234567890";
    unsigned char ciphertext[16];
    unsigned char decrypted[16];

    // Copy IV because OpenSSL modifies it
    DES_cblock iv_enc, iv_dec;
    memcpy(iv_enc, iv, sizeof(iv));
    memcpy(iv_dec, iv, sizeof(iv));

    // Encrypt
    DES_ede3_cbc_encrypt(
        plaintext,
        ciphertext,
        sizeof(plaintext),
        &ks1,
        &ks2,
        &ks3,
        &iv_enc,
        DES_ENCRYPT
    );

    // Decrypt
    DES_ede3_cbc_encrypt(
        ciphertext,
        decrypted,
        sizeof(ciphertext),
        &ks1,
        &ks2,
        &ks3,
        &iv_dec,
        DES_DECRYPT
    );

    std::cout << "Ciphertext: ";
    for (unsigned char c : ciphertext)
        std::cout << std::hex << std::setw(2)
                  << std::setfill('0') << (int)c;

    std::cout << "\nDecrypted: "
              << std::string(reinterpret_cast<char*>(decrypted), sizeof(decrypted))
              << std::endl;

    return 0;
}
