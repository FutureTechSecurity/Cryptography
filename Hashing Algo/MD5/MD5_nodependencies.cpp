#include <iostream>
#include "md5.h" // Include your downloaded header file

int main() {
    std::string text = "Hello Secure Code!";
    
    // Using a popular third-party header layout
    std::string hash = md5(text);
    
    std::cout << "MD5 Hash: " << hash << std::endl;
    return 0;
}