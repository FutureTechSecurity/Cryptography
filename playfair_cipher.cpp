#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

vector<vector<char>> generateMatrix(string key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    bool used[26] = {false};

    key += "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    int k = 0;
    for (char ch : key) {
        ch = toupper(ch);
        if (ch == 'J') ch = 'I';

        if (isalpha(ch) && !used[ch - 'A']) {
            used[ch - 'A'] = true;
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
    return matrix;
}

pair<int, int> findPos(vector<vector<char>>& matrix, char ch) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == ch)
                return {i, j};
    return {-1, -1};
}

string playfairEncrypt(string text, string key) {
    vector<vector<char>> matrix = generateMatrix(key);

    string msg = "";
    for (char ch : text) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';
            msg += ch;
        }
    }

    string prepared = "";
    for (int i = 0; i < msg.length(); i++) {
        prepared += msg[i];
        if (i + 1 < msg.length() && msg[i] == msg[i + 1])
            prepared += 'X';
    }
    if (prepared.length() % 2 != 0)
        prepared += 'X';

    string cipher = "";

    for (int i = 0; i < prepared.length(); i += 2) {
        char a = prepared[i];
        char b = prepared[i + 1];

        auto p1 = findPos(matrix, a);
        auto p2 = findPos(matrix, b);

        if (p1.first == p2.first) {
            cipher += matrix[p1.first][(p1.second + 1) % 5];
            cipher += matrix[p2.first][(p2.second + 1) % 5];
        }
        else if (p1.second == p2.second) {
            cipher += matrix[(p1.first + 1) % 5][p1.second];
            cipher += matrix[(p2.first + 1) % 5][p2.second];
        }
        else {
            cipher += matrix[p1.first][p2.second];
            cipher += matrix[p2.first][p1.second];
        }
    }
    return cipher;
}

int main() {
    string key, text;

    cout << "Enter key: ";
    cin >> key;

    cout << "Enter plaintext: ";
    cin >> text;

    cout << "Encrypted Text: " << playfairEncrypt(text, key);

    return 0;
}
