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

vector<vector<int>> grid;

int DIRECTIONS[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

bool inBounds(int row, int col) {
    return 0 <= row && row < grid.size() && 0 <= col && col < grid[0].size();
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    vector<pair<int,int>> trailheads;

    string line;
    while (fin >> line) {
        vector<int> v;
        for (char c : line) {
            v.push_back(c - '0');

            if (c == '0') {
                trailheads.push_back({(int) grid.size(), (int) v.size()-1});
            }
        }
        grid.push_back(v);
    }

    long long ans = 0;
    for (auto [startRow, startCol] : trailheads) {
        // dfs
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
        stack<pair<int, int>> s;
        s.push({startRow, startCol});

        while (!s.empty()) {
            auto [row, col] = s.top();
            s.pop();

            if (visited[row][col]) continue;

            visited[row][col] = true;

            if (grid[row][col] == 9) {
                ans++;
                continue;
            }

            for (auto dir : DIRECTIONS) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];

                if (inBounds(newRow, newCol) 
                    && grid[row][col] + 1 == grid[newRow][newCol]
                    && !visited[newRow][newCol]) {
                    s.push({newRow, newCol});
                }
            }
        }
    }


    cout << ans << endl;

	return 0; 
}
