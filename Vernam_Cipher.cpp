#include <iostream>
#include <string>
using namespace std;

// Function to encrypt/decrypt using Vernam Cipher
string vernamCipher(const string &text, const string &key) {
    string output = "";

    for (size_t i = 0; i < text.length(); i++) {
        // XOR each character with corresponding key character
        char cipherChar = text[i] ^ key[i];
        output += cipherChar;
    }

    return output;
}

int main() {
    string text, key;

    cout << "Enter plaintext: ";
    getline(cin, text);

    cout << "Enter key (same length as plaintext): ";
    getline(cin, key);

    if (key.length() != text.length()) {
        cout << "Error: Key must be the same length as the plaintext!" << endl;
        return 1;
    }

    // Encrypt
    string encrypted = vernamCipher(text, key);

    cout << "\nEncrypted text (raw XOR output): ";
    for (unsigned char c : encrypted)
        cout << "\\x" << hex << (int)c;

    // Decrypt (XOR again)
    string decrypted = vernamCipher(encrypted, key);

    cout << "\nDecrypted text: " << decrypted << endl;

    return 0;
}
