#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>

using namespace std;

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string line;
    fin >> line;

    queue<int> freeSpace;
    vector<int> blocks;

    int id = 0;
    for (int i=0; i<line.size(); i += 2) {
        int numBlocks = line[i] - '0';
        int space = line[i+1] - '0';

        for (int j=0; j<numBlocks; ++j) {
            blocks.push_back(id);
        }

        freeSpace.push(blocks.size());
        for (int j=0; j<space; ++j) {
            blocks.push_back(-1);
        }

        id++;
    }

    while (!freeSpace.empty()) {
        int pos = freeSpace.front();
        freeSpace.pop();

        while (pos < blocks.size() && blocks[pos] == -1) {
            
            while (blocks.back() == -1) {
                blocks.pop_back();
            }

            int blockToMove = blocks.back();
            blocks.pop_back();

            blocks[pos] = blockToMove;
            pos++;
        }
    }

    long long ans = 0;
    for (int i=0; i<blocks.size(); ++i) {
        if (blocks[i] != -1) 
            ans += i * blocks[i];
    }

    cout << ans << endl;

	return 0; 
}
