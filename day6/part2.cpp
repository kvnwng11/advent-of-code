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
vector<vector<int>> add{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};
unordered_map<int, unordered_map<int, unordered_set<int>>> visited;

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

bool inLoop(int row, int col, int addIdx) {
    // we are in a loop if we've visited this square before and have gone in this direction
    if (!inBounds(row, col)) return false;
    if (visited[row][col].size() == 4 || visited[row][col].count(addIdx)) return true;

    visited[row][col].insert(addIdx);

    int nextRow = row + add[addIdx][0];
    int nextCol = col + add[addIdx][1];

    if (!inBounds(nextRow, nextCol)) return false;

    int origAddIdx = addIdx;
    while (grid[nextRow][nextCol] == '#') {
        addIdx = (addIdx + 1) % add.size();
        nextRow = row + add[addIdx][0];
        nextCol = col + add[addIdx][1];

        if (addIdx == origAddIdx) return true;
    }

    return inLoop(nextRow, nextCol, addIdx);
}


bool canCauseLoop(int startRow, int startCol, int obstRow, int obstCol) {
    if (obstRow == startRow && obstCol == startCol) return false;

    // initialize visited
    for (int row=0; row<grid.size(); ++row) {
        for (int col = 0; col<grid[0].size(); ++col) {
            visited[row][col] = {};
        }
    }

    // try putting an obstable here
    char orig = grid[obstRow][obstCol];
    grid[obstRow][obstCol] = '#';

    // check if in loop
    bool ans = inLoop(startRow, startCol, 0);

    // restore grid
    grid[obstRow][obstCol] = orig;
    return ans;
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
            // this is the starting position
            if (grid[i][j] == '^') {
                startRow = i;
                startCol = j;

                // reduce search space
                dfs(i, j, 0);
            }
        }
    }

    // Reduce search space
    vector<pair<int, int>> path;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == 'X') {
                path.push_back({i, j});
            }
        }
    }
    
    // Solve
    set<pair<int, int>> positions;
    for (auto [obstRow, obstCol] : path) {
        if (canCauseLoop(startRow, startCol, obstRow, obstCol))
            positions.insert({obstRow, obstCol});
    }


    cout << positions.size() << endl;

	return 0;
}
