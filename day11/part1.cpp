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

int NUM_BLINKS = 25;


int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    vector<ll> stones;
    ll num;
    while (fin >> num) {
        stones.push_back(num);
    }

    while (NUM_BLINKS--) {
        vector<ll> newStones;

        for (ll &stone : stones) {
            string s = to_string(stone);

            if (stone == 0)
                newStones.push_back(1);
            else if (s.size() % 2 == 0) {
                ll firstHalf = stoll(s.substr(0, s.size() / 2));
                ll secondHalf = stoll(s.substr(s.size() / 2));

                newStones.push_back(firstHalf);
                newStones.push_back(secondHalf);
            }
            else 
                newStones.push_back(stone * 2024);
        }

        stones = newStones;

        // for (auto &s : stones) cout << s << " ";
        // cout << endl;
    }

    cout << stones.size() << endl;


	return 0; 
}
