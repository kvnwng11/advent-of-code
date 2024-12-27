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

int NUM_SECONDS = 100;
const int WIDTH = 101;
const int HEIGHT = 103;

int getQuadrant(int row, int col) {
    if (row < WIDTH/2 && col < HEIGHT/2)
        return 1;
    else if (row < WIDTH/2 && col > HEIGHT/2)
        return 2;
    else if (row > WIDTH/2 && col > HEIGHT/2)
        return 3;
    else if (row > WIDTH/2 && col < HEIGHT/2)
        return 4;
    else
        return -1;
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    unordered_map<int, ll> quadrant;

    string p;
    string v;
    while (fin >> p >> v) {
        size_t comma1 = p.find(',');
        size_t comma2 = v.find(',');

        int x = stoi(p.substr(2, comma1-2));
        int y = stoi(p.substr(comma1+1));

        int dx = stoi(v.substr(2, comma2-2));
        int dy = stoi(v.substr(comma2+1));

        x = (x + dx * NUM_SECONDS) % WIDTH;
        y = (y + dy * NUM_SECONDS) % HEIGHT;

        x = (x + WIDTH) % WIDTH;
        y = (y + HEIGHT) % HEIGHT;

        quadrant[getQuadrant(x, y)]++;
    }

    ll ans = 1;
    for (int i=1; i<=4; ++i)
        ans *= quadrant[i];
    cout << ans << endl;

	return 0; 
}
