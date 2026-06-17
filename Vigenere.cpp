#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptVigenere(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (char ch : text) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';

            int shift = toupper(key[keyIndex % key.length()]) - 'A';
            char encrypted = ((ch - base + shift) % 26) + base;

            result += encrypted;
            keyIndex++;
        } else {
            result += ch; // Keep spaces and punctuation unchanged
        }
    }

    return result;
}

string decryptVigenere(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (char ch : text) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';

            int shift = toupper(key[keyIndex % key.length()]) - 'A';
            char decrypted = ((ch - base - shift + 26) % 26) + base;

            result += decrypted;
            keyIndex++;
        } else {
            result += ch;
        }
    }

    return result;
}

int main() {
    string plaintext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key: ";
    cin >> key;

    string encrypted = encryptVigenere(plaintext, key);
    cout << "Encrypted text: " << encrypted << endl;

    string decrypted = decryptVigenere(encrypted, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
