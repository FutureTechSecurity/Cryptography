#include <iostream>
#include <string>

// Function to encrypt a message using a Caesar cipher
std::string caesarEncrypt(std::string text, int key) {
    std::string result = "";

    for (char &c : text) {
        // Encrypt uppercase letters
        if (isupper(c)) {
            result += char(int(c + key - 'A') % 26 + 'A');
        }
        // Encrypt lowercase letters
        else if (islower(c)) {
            result += char(int(c + key - 'a') % 26 + 'a');
        }
        // Handle non-alphabetic characters
        else {
            result += c;
        }
    }
    return result;
}

// Function to decrypt a message using a Caesar cipher
std::string caesarDecrypt(std::string text, int key) {
    std::string result = "";

    for (char &c : text) {
        // Decrypt uppercase letters
        if (isupper(c)) {
            result += char(int(c - key - 'A' + 26) % 26 + 'A');
        }
        // Decrypt lowercase letters
        else if (islower(c)) {
            result += char(int(c - key - 'a' + 26) % 26 + 'a');
        }
        // Handle non-alphabetic characters
        else {
            result += c;
        }
    }
    return result;
}

int main() {
    std::string text;
    int key;

    std::cout << "Enter the text to encrypt: ";
    std::getline(std::cin, text);

    std::cout << "Enter the key (an integer): ";
    std::cin >> key;

    // Normalize the key to be within the range [0, 25]
    key = key % 26;
    if (key < 0) {
        key += 26;
    }

    std::string encryptedText = caesarEncrypt(text, key);
    std::cout << "Encrypted text: " << encryptedText << std::endl;

    std::string decryptedText = caesarDecrypt(encryptedText, key);
    std::cout << "Decrypted text: " << decryptedText << std::endl;

    return 0;
}
