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

		vector<int> increasing;
		vector<int> decreasing;
		vector<int> original;		

		for (int num; stream >> num; ) {
			original.push_back(num);
			increasing.push_back(num);
			decreasing.push_back(num);
		}

		sort(increasing.begin(), increasing.end());
		sort(decreasing.begin(), decreasing.end(), greater<int>());

		if (original != increasing and original != decreasing)
			continue;

		bool isValid = true;

		for (int i=1; i<original.size(); ++i) {
			int diff = abs(original[i] - original[i-1]);
			if (diff < 1 || diff > 3) {
				isValid = false;
				break;
			}
		}

		if (isValid)
			ans++;
	}

	cout << ans << endl;

	return 0;
}
