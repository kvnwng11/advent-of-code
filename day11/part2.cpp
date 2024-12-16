#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>
#include <stack>
#include <cmath>

using namespace std;
using ll = long long;

int NUM_BLINKS = 75;

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    unordered_map<ll, ll> stones;
    ll num;
    while (fin >> num) {
        stones[num] += 1;
    }


    while (NUM_BLINKS--) {
        unordered_map<ll, ll> newStones;

        for (auto [stone, count] : stones) {
            int numDigits = log10(stone) + 1;

            if (stone == 0)
                newStones[1] += count;
            else if (numDigits % 2 == 0) {

                ll half = pow(10, numDigits / 2);
                ll firstHalf = stone / half;
                ll secondHalf = stone % half;

                newStones[firstHalf] += count;
                newStones[secondHalf] += count;

            }
            else 
                newStones[stone * 2024] += count;
        }

        stones = newStones;
    }

    ll ans = 0;
    for (auto [stone, count] : stones) ans += count;

    cout << ans << endl;

	return 0; 
}
