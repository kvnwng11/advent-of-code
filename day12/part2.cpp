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


vector<vector<char>> grid;

const int DIRECTIONS[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
};

const vector<vector<pair<int, int>>> CORNER_DIRECTIONS{
    {{0, 1}, {-1, 0}, {-1, 1}},
    {{0, 1}, {1, 0}, {1, 1}},
    {{0, -1}, {1, 0}, {1, -1}},
    {{0, -1}, {-1, 0}, {-1, -1}},
};

bool inBounds(int row, int col) {
    return 0 <= row && row < grid.size() && 0 <= col && col < grid[0].size();
}

bool inBounds(point p) {
    return 0 <= p.first && p.first < grid.size() && 0 <= p.second && p.second < grid[0].size();
}

char getRegion(point p) {
    if (!inBounds(p))
        return '\0';

    return grid[p.first][p.second];
}

int numCorners(int row, int col) {
    char c = grid[row][col];

    int ans = 0;
    for (vector<pair<int, int>> dir : CORNER_DIRECTIONS) {
        point p1 = {row + dir[0].first, col + dir[0].second};
        point p2 = {row + dir[1].first, col + dir[1].second};
        point diag = {row + dir[2].first, col + dir[2].second};

        // inner corner
        if (getRegion(p1) == c && getRegion(p2) == c && getRegion(diag) != c) 
            ans++;

        // outer corner
        if (getRegion(p1) != c && getRegion(p2) != c) 
            ans++;
    }

    return ans;
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

    // dfs on each region
    ll totalPrice = 0;
    for (int i=0; i<M; ++i) {
        for (int j=0; j<N; ++j) {
            if (visited[i][j]) continue;

            char C = grid[i][j];

            ll regionArea = 0;
            ll numSides = 0;

            vector<pair<int, int>> points;
            stack<pair<int, int>> s;
            s.push({i, j});

            while (!s.empty()) {
                auto [row, col] = s.top();
                s.pop();

                if (visited[row][col]) continue;

                visited[row][col] = true;
                regionArea++;
                points.push_back({row, col});

                if (numCorners(row, col) > 0) {
                    numSides += numCorners(row, col);
                    //cout << "is corner: " << row << ", " << col << endl;
                }

                for (auto dir : DIRECTIONS) {
                    int newRow = row + dir[0];
                    int newCol = col + dir[1];

                    if (inBounds(newRow, newCol) && grid[newRow][newCol] == C) {
                        s.push({newRow, newCol});
                    }
                    
                }
            }

            //cout << "A region of " << C << " plants with price " << regionArea << " * " << numSides << " = " << regionArea * numSides << endl;
            totalPrice += regionArea * numSides;
        }
    }

    cout << totalPrice << endl;

	return 0; 
}
