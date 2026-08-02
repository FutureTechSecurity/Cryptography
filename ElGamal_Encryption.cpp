#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Modular inverse using Fermat's Little Theorem
long long modInverse(long long a, long long p) {
    return modExp(a, p - 2, p);
}

int main() {
    srand(time(0));

    // Public parameters
    long long p = 467;   // Prime number
    long long g = 2;     // Primitive root

    // Private key
    long long x = rand() % (p - 2) + 1;

    // Public key
    long long y = modExp(g, x, p);

    cout << "Public Key (p, g, y): (" << p << ", " << g << ", " << y << ")" << endl;
    cout << "Private Key (x): " << x << endl;

    // Input message
    long long message;
    cout << "Enter message (integer less than " << p << "): ";
    cin >> message;

    if (message >= p) {
        cout << "Message must be less than " << p << endl;
        return 0;
    }

    // Encryption
    long long k = rand() % (p - 2) + 1;
    long long c1 = modExp(g, k, p);
    long long s = modExp(y, k, p);
    long long c2 = (message * s) % p;

    cout << "\nEncrypted Ciphertext: (" << c1 << ", " << c2 << ")" << endl;

    // Decryption
    long long s_dec = modExp(c1, x, p);
    long long s_inv = modInverse(s_dec, p);
    long long decrypted = (c2 * s_inv) % p;

    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
