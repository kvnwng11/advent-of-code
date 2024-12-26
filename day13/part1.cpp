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
using point = pair<int, int>;

const int A_COST = 3;
const int B_COST = 1;

pair<int, int> A;
pair<int, int> B;

point prize;

bool inBounds(int row, int col) {
    return 0 <= row && row <= prize.first && 0 <= col && col <= prize.second;
}

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
        // cout << first << " " << last << endl;
        A.first = stoll(first.substr(2, 2));
        A.second = stoll(last.substr(2, 2));

        // read B
        fin >> buf >> buf >> first >> last;
        // cout << first << " " << last << endl;
        B.first = stoll(first.substr(2, 2));
        B.second = stoll(last.substr(2, 2));

        // read Prize location
        fin >> buf >> first >> last;
        // cout << first << " " << last << endl;
        prize.first = stoll(first.substr(2, first.size() - 3));
        prize.second = stoll(last.substr(2));

        int cost = INT_MAX;
        for (int i=0; i<=100; ++i) {
            for (int j=0; j<=100; ++j) {
                point loc = {i * A.first + j * B.first, i * A.second + j * B.second};

                if (loc == prize) {
                    cost = min(cost, i * A_COST + j * B_COST);
                }
            }
        }
        if (cost != INT_MAX)
            ans += cost;
    }

    cout << ans << endl;

	return 0; 
}
