#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>
#include <stack>

using namespace std;
using ll = long long;
using point = pair<ll, ll>;

const int A_COST = 3;
const int B_COST = 1;
const ll OFFSET = 10000000000000;

point A;
point B;
point prize;

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    ll ans = 0;

    string buf;
    string first;
    string last;
    while (!fin.eof()) {
        // read A
        fin >> buf >> buf >> first >> last;
        A.first = stoll(first.substr(2, 2));
        A.second = stoll(last.substr(2, 2));

        // read B
        fin >> buf >> buf >> first >> last;
        B.first = stoll(first.substr(2, 2));
        B.second = stoll(last.substr(2, 2));

        // read Prize location
        fin >> buf >> first >> last;
        prize.first = stoll(first.substr(2, first.size() - 3)) + OFFSET;
        prize.second = stoll(last.substr(2)) + OFFSET;

        // A.first * x + B.first * y = prize.first
        // A.second * x + B.second * y = prize.second

        ll determinant = A.first * B.second - A.second * B.first;
        if (determinant == 0) continue;

        ll numeratorA = prize.first * B.second - B.first * prize.second;
        ll numeratorB = A.first * prize.second - prize.first * A.second;

        if (numeratorA % determinant != 0 || numeratorB % determinant != 0) continue;

        ll numPressesA = numeratorA / determinant;
        ll numPressesB = numeratorB / determinant;

        ll cost = numPressesA * A_COST + numPressesB * B_COST;
        ans += cost;
    }

    cout << ans << endl;

	return 0; 
}
