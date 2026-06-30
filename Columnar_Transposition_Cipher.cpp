#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Encrypt function
string encrypt(string plaintext, string key) {
    int cols = key.length();
    int rows = (plaintext.length() + cols - 1) / cols;

    // Pad with 'X'
    while (plaintext.length() < rows * cols)
        plaintext += 'X';

    vector<vector<char>> matrix(rows, vector<char>(cols));

    int index = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = plaintext[index++];

    vector<pair<char, int>> order;
    for (int i = 0; i < cols; i++)
        order.push_back({key[i], i});

    sort(order.begin(), order.end());

    string ciphertext = "";

    for (auto p : order) {
        int col = p.second;
        for (int i = 0; i < rows; i++)
            ciphertext += matrix[i][col];
    }

    return ciphertext;
}

// Decrypt function
string decrypt(string ciphertext, string key) {
    int cols = key.length();
    int rows = ciphertext.length() / cols;

    vector<vector<char>> matrix(rows, vector<char>(cols));

    vector<pair<char, int>> order;
    for (int i = 0; i < cols; i++)
        order.push_back({key[i], i});

    sort(order.begin(), order.end());

    int index = 0;

    for (auto p : order) {
        int col = p.second;
        for (int i = 0; i < rows; i++)
            matrix[i][col] = ciphertext[index++];
    }

    string plaintext = "";

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            plaintext += matrix[i][j];

    return plaintext;
}

int main() {
    int choice;

    cout << "===== Columnar Transposition Cipher =====\n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore();

    string text, key;

    cout << "Enter Key: ";
    getline(cin, key);

    if (choice == 1) {
        cout << "Enter Plaintext: ";
        getline(cin, text);

        string encrypted = encrypt(text, key);

        cout << "\nEncrypted Text: " << encrypted << endl;
    }
    else if (choice == 2) {
        cout << "Enter Ciphertext: ";
        getline(cin, text);

        string decrypted = decrypt(text, key);

        cout << "\nDecrypted Text: " << decrypted << endl;
    }
    else {
        cout << "Invalid Choice!" << endl;
    }

    return 0;
}
