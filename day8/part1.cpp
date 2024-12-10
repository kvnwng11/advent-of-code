#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>

using namespace std;

vector<vector<char>> grid;

bool inBounds(pair<int, int> pos) {
    int x = pos.first, y = pos.second;
    return 0 <= x && x < grid.size() && 0 <= y && y < grid[0].size();
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string line;
    while (fin >> line) {
        vector<char> v;
        for (char c : line) v.push_back(c);
        grid.push_back(v);
    }

    // Find antennas
    unordered_map<char, vector<pair<int, int>>> antennas;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] != '.') {
                antennas[grid[i][j]].push_back({i, j});
            }
        }
    }

    // Find all pairs of antennas
    for (auto [freq, positions] : antennas) {

        for (int i=0; i<positions.size(); ++i) {
            for (int j=i+1; j<positions.size(); ++j) {
                pair<int, int> top = positions[i];
                pair<int, int> bottom = positions[j];

                int xDelta = bottom.first - top.first;
                int yDelta = bottom.second - top.second;

                pair<int, int> antinode1 = {top.first - xDelta, top.second - yDelta};
                pair<int, int> antinode2 = {bottom.first + xDelta, bottom.second + yDelta};

                if (inBounds(antinode1)) grid[antinode1.first][antinode1.second] = '#';
                if (inBounds(antinode2)) grid[antinode2.first][antinode2.second] = '#';                
            }
        }
    }


    // Find answer
    int ans = 0;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == '#') {
                ans++;
            }
        }
    }

    cout << ans << endl;

	return 0; 
}
