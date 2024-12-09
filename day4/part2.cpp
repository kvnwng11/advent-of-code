#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<vector<char>> grid;


bool inBounds(int row, int col) {
    return row >= 0 && row < grid.size() && 0 <= col && col < grid[0].size();
}

bool isXMAS(int row, int col) {
    bool diag1 = (grid[row-1][col-1] == 'M' && grid[row+1][col+1] == 'S')
                    || (grid[row-1][col-1] == 'S' && grid[row+1][col+1] == 'M');
    bool diag2 = (grid[row-1][col+1] == 'M' && grid[row+1][col-1] == 'S')
                    || (grid[row-1][col+1] == 'S' && grid[row+1][col-1] == 'M');
    return diag1 && diag2;
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

    int ans = 0;
    for (int i=1; i<grid.size()-1; ++i) {
        for (int j=1; j<grid[0].size()-1; ++j) {
            if (grid[i][j] != 'A') continue;

            if (isXMAS(i, j))
                ans++;
        }
    }

    cout << ans << endl;

	return 0;
}
