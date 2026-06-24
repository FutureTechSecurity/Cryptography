#include <iostream>
#include <vector>
using namespace std;

// Function to find modulo 26 inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Encrypt function
string encrypt(string text, vector<vector<int>> key) {
    string cipher = "";

    if (text.length() % 2 != 0)
        text += 'X';

    for (int i = 0; i < text.length(); i += 2) {
        int p1 = text[i] - 'A';
        int p2 = text[i + 1] - 'A';

        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        cipher += char(c1 + 'A');
        cipher += char(c2 + 'A');
    }

    return cipher;
}

// Decrypt function
string decrypt(string cipher, vector<vector<int>> key) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;

    int detInv = modInverse(det, 26);

    if (detInv == -1) {
        return "Key matrix is not invertible!";
    }

    vector<vector<int>> invKey(2, vector<int>(2));

    invKey[0][0] = ( key[1][1] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv + 26) % 26;
    invKey[1][0] = (-key[1][0] * detInv + 26) % 26;
    invKey[1][1] = ( key[0][0] * detInv) % 26;

    string plain = "";

    for (int i = 0; i < cipher.length(); i += 2) {
        int c1 = cipher[i] - 'A';
        int c2 = cipher[i + 1] - 'A';

        int p1 = (invKey[0][0] * c1 + invKey[0][1] * c2) % 26;
        int p2 = (invKey[1][0] * c1 + invKey[1][1] * c2) % 26;

        plain += char(p1 + 'A');
        plain += char(p2 + 'A');
    }

    return plain;
}

int main() {
    vector<vector<int>> key = {
        {3, 3},
        {2, 5}
    };

    string plaintext;
    cout << "Enter plaintext (uppercase letters only): ";
    cin >> plaintext;

    string cipher = encrypt(plaintext, key);
    cout << "Encrypted Text: " << cipher << endl;

    string decrypted = decrypt(cipher, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
