#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>

#include <openssl/evp.h>
#include <openssl/err.h>

using namespace std;

vector<unsigned char> hexToBytes(const string &hex)
{
    vector<unsigned char> bytes;

    for (size_t i = 0; i < hex.length(); i += 2)
    {
        string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

string bytesToHex(const unsigned char *data, int len)
{
    stringstream ss;

    for (int i = 0; i < len; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)data[i];
    }

    return ss.str();
}

const EVP_CIPHER *getCipher(const string &mode, int keyLength)
{
    if (mode == "CBC")
    {
        if (keyLength == 16) return EVP_aes_128_cbc();
        if (keyLength == 24) return EVP_aes_192_cbc();
        if (keyLength == 32) return EVP_aes_256_cbc();
    }

    if (mode == "ECB")
    {
        if (keyLength == 16) return EVP_aes_128_ecb();
        if (keyLength == 24) return EVP_aes_192_ecb();
        if (keyLength == 32) return EVP_aes_256_ecb();
    }

    if (mode == "CTR")
    {
        if (keyLength == 16) return EVP_aes_128_ctr();
        if (keyLength == 24) return EVP_aes_192_ctr();
        if (keyLength == 32) return EVP_aes_256_ctr();
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        cout << "Usage:\n";
        cout << "aes_tool <encrypt|decrypt> <CBC|ECB|CTR> <KeyHex> <IVHex> <Input>\n";
        return 1;
    }

    string operation = argv[1];
    string mode = argv[2];
    string keyHex = argv[3];
    string ivHex = argv[4];
    string input = argv[5];

    vector<unsigned char> key = hexToBytes(keyHex);
    vector<unsigned char> iv = hexToBytes(ivHex);

    const EVP_CIPHER *cipher = getCipher(mode, key.size());

    if (!cipher)
    {
        cout << "Unsupported cipher." << endl;
        return 1;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    vector<unsigned char> output(4096);

    int outlen1 = 0;
    int outlen2 = 0;

    if (operation == "encrypt")
    {
        EVP_EncryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data());

        EVP_EncryptUpdate(
            ctx,
            output.data(),
            &outlen1,
            (unsigned char *)input.data(),
            input.length());

        EVP_EncryptFinal_ex(ctx, output.data() + outlen1, &outlen2);

        cout << "Ciphertext : "
             << bytesToHex(output.data(), outlen1 + outlen2)
             << endl;
    }
    else if (operation == "decrypt")
    {
        vector<unsigned char> cipherBytes = hexToBytes(input);

        EVP_DecryptInit_ex(ctx, cipher, nullptr, key.data(), iv.data());

        EVP_DecryptUpdate(
            ctx,
            output.data(),
            &outlen1,
            cipherBytes.data(),
            cipherBytes.size());

        if (!EVP_DecryptFinal_ex(ctx, output.data() + outlen1, &outlen2))
        {
            cout << "Decryption failed." << endl;
            EVP_CIPHER_CTX_free(ctx);
            return 1;
        }

        output[outlen1 + outlen2] = '\0';

        cout << "Plaintext : "
             << output.data()
             << endl;
    }
    else
    {
        cout << "Invalid operation." << endl;
    }

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
