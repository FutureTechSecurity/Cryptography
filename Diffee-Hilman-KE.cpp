#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to calculate (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

int main() {
    // Publicly shared values
    long long p = 23;   // Prime number
    long long g = 5;    // Primitive root

    cout << "Publicly Shared Values:\n";
    cout << "Prime (p): " << p << endl;
    cout << "Primitive Root (g): " << g << endl;

    srand(time(0));

    // Alice's private key
    long long alicePrivate = rand() % (p - 2) + 1;
    long long alicePublic = modExp(g, alicePrivate, p);

    // Bob's private key
    long long bobPrivate = rand() % (p - 2) + 1;
    long long bobPublic = modExp(g, bobPrivate, p);

    cout << "\nAlice:\n";
    cout << "Private Key: " << alicePrivate << endl;
    cout << "Public Key: " << alicePublic << endl;

    cout << "\nBob:\n";
    cout << "Private Key: " << bobPrivate << endl;
    cout << "Public Key: " << bobPublic << endl;

    // Shared secret calculation
    long long aliceSecret = modExp(bobPublic, alicePrivate, p);
    long long bobSecret = modExp(alicePublic, bobPrivate, p);

    cout << "\nShared Secret Computed by Alice: " << aliceSecret << endl;
    cout << "Shared Secret Computed by Bob: " << bobSecret << endl;

    if (aliceSecret == bobSecret)
        cout << "\nKey Exchange Successful!" << endl;
    else
        cout << "\nKey Exchange Failed!" << endl;

    return 0;
}
