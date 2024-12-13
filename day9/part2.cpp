#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>

using namespace std;

struct File {
    int pos;
    int length;
    int id;
};

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    string line;
    fin >> line;

    vector<pair<int, int>> freeSpace; // position, length
    vector<File> disk;

    int id = 0;
    int pos = 0;
    for (int i=0; i<line.size(); i += 2) {
        int fileLength = line[i] - '0';
        int spaceLength = line[i+1] - '0';

        disk.push_back({pos, fileLength, id});

        pos += fileLength;

        if (0 < spaceLength && spaceLength <= 9) {
            freeSpace.push_back({pos, spaceLength});
            pos += spaceLength;
        }
        
        id++;
    }


    for (auto itr = disk.rbegin(); itr != disk.rend(); ++itr) {

        for (auto &space : freeSpace) {
            if (itr->length <= space.second && space.first < itr->pos) {
                itr->pos = space.first;

                cout << "moving block " << itr->id << " into position " << space.first << endl;
                
                space.first += itr->length;
                space.second -= itr->length;
                break;
            }
        }
    }

    
    

    long long ans = 0;
    for (auto file : disk) {
        for (int i=file.pos; i<file.pos + file.length; ++i) {
            ans += i * file.id;
        }
    }

    cout << ans << endl;

	return 0; 
}
