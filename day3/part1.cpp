#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool isNumber(string &s) {
    if (s.size() == 0) return false;

    for (char c : s) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string inputStr;
	string line;
    while (fin >> line) {
        inputStr += line;
    }

    //cout << inputStr << endl;

    vector<size_t> positions;
    string pattern = "mul(";
    size_t pos = 0;
    while ((pos = inputStr.find(pattern, pos)) != string::npos) {
        positions.push_back(pos);
        //cout << "pos found: " << pos << endl;
        pos += pattern.length(); 
    }

    // Brute force check all muls
    long long ans = 0;
    for (int idx : positions) {
        int currIdx = idx+4; // start at the first digit
        string num1 = "", num2 = "";

        //cout << "start: " << inputStr[currIdx] << endl;

        // Get first number
        while (num1.size() < 3 && currIdx < inputStr.size() && inputStr[currIdx] != ',') {
            num1 += inputStr[currIdx];
            currIdx++;
        }
        //cout << "num1: " << num1 << endl;
        if (!isNumber(num1) || inputStr[currIdx] != ',') continue;

        // Get second number
        currIdx++;
        while (num2.size() < 3 && currIdx < inputStr.size() && inputStr[currIdx] != ')') {
            num2 += inputStr[currIdx];
            currIdx++;
        }
        //cout << "num2: " << num1 << endl;
        if (!isNumber(num2) || inputStr[currIdx] != ')') continue;

        ans += stoi(num1) * stoi(num2);
    }

	cout << ans << endl;

	return 0;
}
