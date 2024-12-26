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


vector<vector<char>> grid;

const int DIRECTIONS[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

bool inBounds(int row, int col) {
    return 0 <= row && row < grid.size() && 0 <= col && col < grid[0].size();
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

    int M = grid.size();
    int N = grid[0].size();

    vector<vector<bool>> visited(M, vector<bool>(N, false));

    ll totalPrice = 0;

    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            if (visited[i][j]) continue;

            char C = grid[i][j];

            int regionArea = 0;
            int regionPerimeter = 0;

            stack<pair<int, int>> s;
            s.push({i, j});

            while (!s.empty()) {
                auto [row, col] = s.top();
                s.pop();

                if (visited[row][col]) continue;

                visited[row][col] = true;
                regionArea++;

                for (auto dir : DIRECTIONS) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];

                    if (!inBounds(newRow, newCol) || grid[newRow][newCol] != C) {
                        regionPerimeter++;
                    }
                    else {
                        s.push({newRow, newCol});
                    }
                    
                }
            }

            cout << "A region of " << C << " plants with price " << regionArea << " * " << regionPerimeter << " = " << regionArea * regionPerimeter << endl;
            totalPrice += regionArea * regionPerimeter;
        }
    }

    cout << totalPrice << endl;

	return 0; 
}
