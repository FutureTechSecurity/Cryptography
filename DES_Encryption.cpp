#include <iostream>
#include <bitset>
using namespace std;

// Simplified DES (S-DES) for educational purposes

int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[] = {6,3,7,4,8,5,10,9};
int P4[] = {2,4,3,1};
int IP[] = {2,6,3,1,4,8,5,7};
int IP_INV[] = {4,1,3,5,7,2,8,6};
int EP[] = {4,1,2,3,2,3,4,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

string permute(string input, int p[], int n) {
    string output = "";
    for(int i = 0; i < n; i++)
        output += input[p[i]-1];
    return output;
}

string leftShift(string s, int shifts) {
    return s.substr(shifts) + s.substr(0, shifts);
}

string XOR(string a, string b) {
    string result = "";
    for(int i = 0; i < a.size(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

string SBox(string input, int box[4][4]) {
    int row = (input[0]-'0')*2 + (input[3]-'0');
    int col = (input[1]-'0')*2 + (input[2]-'0');
    bitset<2> b(box[row][col]);
    return b.to_string();
}

string F(string right, string key) {
    string ep = permute(right, EP, 8);
    string x = XOR(ep, key);

    string left = SBox(x.substr(0,4), S0);
    string rightPart = SBox(x.substr(4,4), S1);

    return permute(left + rightPart, P4, 4);
}

string fk(string input, string key) {
    string left = input.substr(0,4);
    string right = input.substr(4,4);

    string f = F(right, key);
    left = XOR(left, f);

    return left + right;
}

int main() {

    string key = "1010000010";
    string plaintext = "11010111";

    // Key Generation
    string p10 = permute(key, P10, 10);

    string left = leftShift(p10.substr(0,5),1);
    string right = leftShift(p10.substr(5,5),1);
    string K1 = permute(left + right, P8, 8);

    left = leftShift(left,2);
    right = leftShift(right,2);
    string K2 = permute(left + right, P8, 8);

    // Encryption
    string ip = permute(plaintext, IP, 8);

    string temp = fk(ip, K1);

    // Swap
    temp = temp.substr(4,4) + temp.substr(0,4);

    temp = fk(temp, K2);

    string cipher = permute(temp, IP_INV, 8);

    cout << "Plaintext : " << plaintext << endl;
    cout << "Ciphertext: " << cipher << endl;

    return 0;
}
