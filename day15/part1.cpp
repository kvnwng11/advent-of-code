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

unordered_map<char, vector<int>> DIRECTIONS{
    {'v', {1, 0}},
    {'^', {-1, 0}},
    {'<', {0, -1}},
    {'>', {0, 1}}
};

vector<vector<char>> grid;
vector<char> moves;

bool inBounds(point p) {
    return 0 <= p.first && p.first < grid.size() && 0 <= p.second && p.second < grid[0].size();
}

int canMove(point p, char dir) {
    int numMoves = 0;
    while (inBounds(p)) {
        p = {p.first + DIRECTIONS[dir][0], p.second + DIRECTIONS[dir][1]};
        numMoves++;

        if (!inBounds(p))
            return -1;

        if (grid[p.first][p.second] == '#')
            return -1;

        else if (grid[p.first][p.second] == '.')
            return numMoves-1;
    }
    return -1;
}

void moveRobot(point &p, char dir, int numMoves) {
    // prerequisite: canMove(p, dir), inBounds(adjacent, dir)

    // move robot
    point adjacent = {p.first + DIRECTIONS[dir][0], p.second + DIRECTIONS[dir][1]};
    p = adjacent;
    
    // move boxes
    if (grid[adjacent.first][adjacent.second] == 'O') {
        point openSpace = {p.first + DIRECTIONS[dir][0] * numMoves, p.second + DIRECTIONS[dir][1] * numMoves};
        swap(grid[adjacent.first][adjacent.second], grid[openSpace.first][openSpace.second]);
    }
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    point start;
    while (!fin.eof()) {
        string line;
        while (fin >> line) {
            if (DIRECTIONS.count(line[0])) {
                for (char c : line) 
                    moves.push_back(c);
            }
            else {
                vector<char> v;
                for (char c : line) {
                    if (c == '@') 
                        start = {grid.size(), v.size()};
                    v.push_back(c);
                }
                grid.push_back(v);
            }
        }
    }

    grid[start.first][start.second] = '.';


    for (char move : moves) {
        int numMoves = canMove(start, move);
        if (numMoves != -1)
            moveRobot(start, move, numMoves);
    }

    ll ans = 0;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == 'O')
                ans += 100 * i + j;
        }
    }

    cout << ans << endl;
    

	return 0; 
}
