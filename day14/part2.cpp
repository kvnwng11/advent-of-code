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

int NUM_SECONDS = 0;
const int WIDTH = 101;
const int HEIGHT = 103;

int main() {
	string file;
	cin >> file;

	ifstream fin(file);
    ofstream fout("output");

    vector<point> points;
    vector<point> velocities;

    string p;
    string v;
    while (fin >> p >> v) {
        size_t comma1 = p.find(',');
        size_t comma2 = v.find(',');

        int x = stoi(p.substr(2, comma1-2));
        int y = stoi(p.substr(comma1+1));

        int dx = stoi(v.substr(2, comma2-2));
        int dy = stoi(v.substr(comma2+1));

        points.push_back({x, y});
        velocities.push_back({dx, dy});
    }

    ll minSafety = INT_MAX;
    while (NUM_SECONDS <= 100000) {
        vector<vector<int>> grid(HEIGHT, vector<int>(WIDTH, 0));

        for (int i=0; i<points.size(); ++i) {
            int x = points[i].first;
            int y = points[i].second;

            int dx = velocities[i].first;
            int dy = velocities[i].second;

            x = (x + dx * NUM_SECONDS) % WIDTH;
            y = (y + dy * NUM_SECONDS) % HEIGHT;

            x = (x + WIDTH) % WIDTH;
            y = (y + HEIGHT) % HEIGHT;

            grid[x][y]++;
        }
        bool print = true;
        if (print) {
            fout << "SECONDS: " << NUM_SECONDS << endl;

            for (int i=0; i<grid.size(); ++i) {
                for (int j=0; j<grid[0].size(); ++j) {
                    if (grid[i][j] == 0) fout << " ";
                    else fout << "*";
                }
                fout << endl;
            }
            fout << endl;
        }

        NUM_SECONDS++;
    }



	return 0; 
}
