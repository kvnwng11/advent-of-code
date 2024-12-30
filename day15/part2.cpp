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

bool part1CanMove(point p, char dir) {
    while (inBounds(p)) {
        p = {p.first + DIRECTIONS[dir][0], p.second + DIRECTIONS[dir][1]};

        if (!inBounds(p) || grid[p.first][p.second] == '#')
            return false;

        else if (grid[p.first][p.second] == '.')
            return true;
    }
    return false;
}

bool canMoveHelper(point p, char dir) {
    // assumes p is a box

    stack<point> s;
    s.push(p);
    while (!s.empty()) {
        point curr = s.top();
        s.pop();

        // cannot move
        point adjacent = {curr.first + DIRECTIONS[dir][0], curr.second + DIRECTIONS[dir][1]};
        if (!inBounds(adjacent) || grid[adjacent.first][adjacent.second] == '#') 
            return false;
        
        // this is a box and it will move another box
        char oldVal = grid[curr.first][curr.second];
        if (oldVal == '[' && grid[adjacent.first][adjacent.second] == ']') {
            point otherBox = {adjacent.first, adjacent.second-1};
            s.push(otherBox);
            s.push(adjacent);
        }
        else if (oldVal == ']' && grid[adjacent.first][adjacent.second] == '[') {
            point otherBox = {adjacent.first, adjacent.second+1};
            s.push(otherBox);
            s.push(adjacent);
        }
        else if ('[' == grid[adjacent.first][adjacent.second] || ']' == grid[adjacent.first][adjacent.second]) {
            s.push(adjacent);
        }
    }
    return true;
}

bool canMove(point p, char dir) {
    // DFS to find box region

    if (dir == '<' || dir == '>') {
        return part1CanMove(p, dir);
    }
    else {
        point adjacent = {p.first + DIRECTIONS[dir][0], p.second + DIRECTIONS[dir][1]};

        if (!inBounds(adjacent) || grid[adjacent.first][adjacent.second] == '#')
            return false;

        if (grid[adjacent.first][adjacent.second] == '[') {
            point otherBox = {adjacent.first, adjacent.second+1};
            return canMoveHelper(adjacent, dir) && canMoveHelper(otherBox, dir);
        }
        else if (grid[adjacent.first][adjacent.second] == ']') {
            point otherBox = {adjacent.first, adjacent.second-1};
            return canMoveHelper(adjacent, dir) && canMoveHelper(otherBox, dir);
        }
        else {
            return true;
        }
    }
}

void moveRobotHelper(point p, char dir) {
    // p is a box
    stack<pair<point, char>> s; // stores {pair, what it needs to change to}

    if (grid[p.first][p.second] == '[') {
        point otherBox = {p.first, p.second+1};
        s.push({p, '.'});
        s.push({otherBox, '.'});
    }
    else if (grid[p.first][p.second] == ']') {
        point otherBox = {p.first, p.second-1};
        s.push({p, '.'});
        s.push({otherBox, '.'});
    }

    while (!s.empty()) {
        auto [curr, newVal] = s.top();
        s.pop();

        // swap chars
        char oldVal = grid[curr.first][curr.second];
        grid[curr.first][curr.second] = newVal;
        if (oldVal == '.') continue;

        // cannot move
        point adjacent = {curr.first + DIRECTIONS[dir][0], curr.second + DIRECTIONS[dir][1]};
        
        // this is a box and it will move another box
        if (oldVal == '[' && grid[adjacent.first][adjacent.second] == ']') {
            point otherBox = {adjacent.first, adjacent.second-1};
            s.push({otherBox, '.'});
            s.push({adjacent, oldVal});
        }
        else if (oldVal == ']' && grid[adjacent.first][adjacent.second] == '[') {
            point otherBox = {adjacent.first, adjacent.second+1};
            s.push({otherBox, '.'});
            s.push({adjacent, oldVal});
        }
        else if ('[' == grid[adjacent.first][adjacent.second] || ']' == grid[adjacent.first][adjacent.second]) {
            s.push({adjacent, oldVal});
        }
        else if (grid[adjacent.first][adjacent.second] == '.') {
            s.push({adjacent, oldVal});
        }
    }
}

void moveRobot(point &p, char dir) {
    // prerequisite: canMove(p, dir), inBounds(adjacent, dir)

    // move robot
    point adjacent = {p.first + DIRECTIONS[dir][0], p.second + DIRECTIONS[dir][1]};
    p = adjacent;

    // move boxes
    if (dir == '<' && grid[p.first][p.second] == ']') {
        int col = p.second-1;
        while (0 <= col && grid[p.first][col] != '.')col--;
        for (int i=col; i<=p.second; ++i) grid[p.first][i] = grid[p.first][i+1];
        return;
    }
    else if (dir == '>' && grid[p.first][p.second] == '[') {
        int col = p.second+1;
        while (col < grid[0].size() && grid[p.first][col] != '.') col++;
        for (int i=col; i>=p.second; --i) grid[p.first][i] = grid[p.first][i-1];
        return;
    }
    
    // DFS to move boxes
    else if (grid[adjacent.first][adjacent.second] == '['
        || grid[adjacent.first][adjacent.second] == ']') {
        moveRobotHelper(adjacent, dir);
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
                    if (c == '#') {
                        v.push_back('#');
                        v.push_back('#');
                    }
                    else if (c == 'O') {
                        v.push_back('[');
                        v.push_back(']');
                    }
                    else if (c == '.') {
                        v.push_back('.');
                        v.push_back('.');
                    }
                    else if (c == '@') {
                        start = {grid.size(), v.size()};
                        v.push_back('@');
                        v.push_back('.');
                    }
                }
                grid.push_back(v);
            }
        }
    }

    grid[start.first][start.second] = '.';


    for (char move : moves) {
        if (canMove(start, move))
            moveRobot(start, move);
    }

    ll ans = 0;
    for (int i=0; i<grid.size(); ++i) {
        for (int j=0; j<grid[0].size(); ++j) {
            if (grid[i][j] == '[')
                ans += 100 * i + j;
        }
    }

    cout << ans << endl;
    
	return 0; 
}
