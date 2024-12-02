#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

	int ans = 0;

	for (string line; getline(fin, line);) {
		istringstream stream(line);

		vector<int> original;		

		for (int num; stream >> num; ) {
			original.push_back(num);
		}

		for (int skip=0; skip<original.size(); ++skip) {
			vector<int> modified;
			vector<int> increasing;
			vector<int> decreasing;

			for (int j=0; j<original.size(); ++j) {
				if (j != skip) {
					int num = original[j];
					modified.push_back(num);
					increasing.push_back(num);
					decreasing.push_back(num);
				}
			}

			sort(increasing.begin(), increasing.end());
			sort(decreasing.begin(), decreasing.end(), greater<int>());

			if (modified != increasing and modified != decreasing)
				continue;

			bool isValid = true;

			for (int i=1; i<modified.size(); ++i) {
				int diff = abs(modified[i] - modified[i-1]);
				if (diff < 1 || diff > 3) {
					isValid = false;
					break;
				}
			}

			if (isValid) {
				ans++;
				break;
			}
		}
	}

	cout << ans << endl;

	return 0;
}
