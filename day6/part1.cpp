#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

vector<vector<char>> grid;
vector<vector<int>> add{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

bool inBounds(int row, int col) {
    return 0 <= row && row < grid.size() && 0 <= col && col < grid[0].size();
}

void dfs(int row, int col, int addIdx) {
    grid[row][col] = 'X';
    
    int nextRow = row + add[addIdx][0];
    int nextCol = col + add[addIdx][1];

    if (!inBounds(nextRow, nextCol)) return;

    if (grid[nextRow][nextCol] == '#') {
        addIdx = (addIdx + 1) % add.size();
        nextRow = row + add[addIdx][0];
        nextCol = col + add[addIdx][1];
    }

    dfs(nextRow, nextCol, addIdx);
}


int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    // Read input
    string line;
    while (fin >> line) {
        vector<char> row;
        for (char c : line) row.push_back(c);
        grid.push_back(row);
    }

    // Get start positions
    int startRow, startCol;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == '^') {
                dfs(i, j, 0);
            }
        }
    }

    int ans = 0;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            //cout << grid[i][j];
            if (grid[i][j] == 'X')
                ans++;
        }
        //cout << endl;
    }

    cout << ans << endl;

	return 0;
}
