#include <iostream>
#include <string>
using namespace std;

// Function to find modular inverse of a modulo 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Encryption function
string encrypt(string plaintext, int a, int b) {
    string ciphertext = "";

    for (char ch : plaintext) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int x = ch - base;
            char encrypted = ((a * x + b) % 26) + base;
            ciphertext += encrypted;
        } else {
            ciphertext += ch; // Keep spaces and symbols unchanged
        }
    }

    return ciphertext;
}

// Decryption function
string decrypt(string ciphertext, int a, int b) {
    string plaintext = "";
    int a_inv = modInverse(a, 26);

    if (a_inv == -1) {
        return "Invalid key: 'a' has no modular inverse modulo 26.";
    }

    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int y = ch - base;
            char decrypted = (a_inv * (y - b + 26)) % 26 + base;
            plaintext += decrypted;
        } else {
            plaintext += ch;
        }
    }

    return plaintext;
}

int main() {
    string text;
    int a, b;

    cout << "Enter message: ";
    getline(cin, text);

    cout << "Enter key a (must be coprime with 26): ";
    cin >> a;

    cout << "Enter key b: ";
    cin >> b;

    string encrypted = encrypt(text, a, b);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, a, b);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
