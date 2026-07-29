#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int main() {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);

    // Generate 2048-bit RSA key pair
    RSA_generate_key_ex(rsa, 2048, e, nullptr);

    std::string message = "Hello RSA";

    unsigned char encrypted[256];
    int encryptedLen = RSA_public_encrypt(
        message.length(),
        (unsigned char*)message.c_str(),
        encrypted,
        rsa,
        RSA_PKCS1_OAEP_PADDING
    );

    if (encryptedLen == -1) {
        std::cout << "Encryption failed\n";
        return 1;
    }

    unsigned char decrypted[256];
    int decryptedLen = RSA_private_decrypt(
        encryptedLen,
        encrypted,
        decrypted,
        rsa,
        RSA_PKCS1_OAEP_PADDING
    );

    if (decryptedLen == -1) {
        std::cout << "Decryption failed\n";
        return 1;
    }

    decrypted[decryptedLen] = '\0';

    std::cout << "Original : " << message << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    RSA_free(rsa);
    BN_free(e);

    return 0;
}
