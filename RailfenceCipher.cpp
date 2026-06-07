#include <iostream>
#include <vector>
#include <string>
using namespace std;

string railFenceEncrypt(string text, int rails) {
    vector<string> rail(rails);

    int row = 0;
    bool down = true;

    for (char ch : text) {
        rail[row] += ch;

        if (row == 0)
            down = true;
        else if (row == rails - 1)
            down = false;

        row += (down ? 1 : -1);
    }

    string cipher = "";
    for (int i = 0; i < rails; i++)
        cipher += rail[i];

    return cipher;
}

int main() {
    string text;
    int rails;

    cout << "Enter plaintext: ";
    cin >> text;

    cout << "Enter number of rails: ";
    cin >> rails;

    cout << "Encrypted Text: " << railFenceEncrypt(text, rails);

    return 0;
}
