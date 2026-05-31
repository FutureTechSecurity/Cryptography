#include <iostream>
#include <string>
#include <cctype> // For isalpha, islower, isupper

std::string rot13(const std::string& text) {
    std::string result = "";
    for (char c : text) {
        if (std::isalpha(c)) { // Check if the character is an alphabet
            char base = std::islower(c) ? 'a' : 'A'; // Determine the base ( 'a' for lowercase, 'A' for uppercase)
            result += static_cast<char>((c - base + 13) % 26 + base); // Apply ROT13 shift
        } else {
            result += c; // Non-alphabetic characters are not modified
        }
    }
    return result;
}

int main() {
    std::string message;
    std::cout << "Enter a message to encode/decode with ROT13: ";
    std::getline(std::cin, message);

    std::string encoded_message = rot13(message);
    std::cout << "ROT13 encoded/decoded message: " << encoded_message << std::endl;

    return 0;
}
