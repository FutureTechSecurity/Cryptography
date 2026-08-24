#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/md5.h>

// Function to compute MD5 hash of a string
std::string computeMD5(const std::string& str) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    
    // Calculate MD5 hash
    MD5(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), digest);
    
    // Convert the byte array into a hex string
    std::stringstream ss;
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }
    
    return ss.str();
}

int main() {
    std::string text = "Hello Secure Code!";
    std::string hash = computeMD5(text);
    
    std::cout << "Input Text: " << text << std::endl;
    std::cout << "MD5 Hash:   " << hash << std::endl;
    
    return 0;
}