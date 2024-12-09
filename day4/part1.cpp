#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<vector<int>> addArray{
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
    
    {1, 1},
    {-1, -1},
    {1, -1},
    {-1, 1}
};
vector<vector<char>> grid;

int ans = 0;

bool inBounds(int row, int col) {
    return row >= 0 && row < grid.size() && 0 <= col && col < grid[0].size();
}

void solve(int row, int col, string curr, string target, const vector<int> &add) {
    if (curr.size() > target.size()) return;
    if (curr.size() == target.size()) {
        if (curr == target) ans++;
        return;
    }

    int nextRow = row + add[0];
    int nextCol = col + add[1];
    if (inBounds(nextRow, nextCol) && target[curr.size()] == grid[nextRow][nextCol]) {
        string newStr = curr + grid[nextRow][nextCol];
        solve(nextRow, nextCol, newStr, target, add);
    }
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string line;
    while (fin >> line) {
        vector<char> v;
        for (char c : line)
            v.push_back(c);

        grid.push_back(v);
    }

    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == 'X') {
                for (auto add : addArray) {
                    solve(i, j, "X", "XMAS", add);
                }
            }
        }
    }

    cout << ans << endl;

	return 0;
}
