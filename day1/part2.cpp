#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <unordered_map>

using namespace std;

int main() {
	string file;
	cin >> file;
	
	ifstream fin(file);

	vector<int> list1;
	unordered_map<int, int> numCountsInList2;
	
	int num1, num2;
	while (fin >> num1 >> num2) {
		list1.push_back(num1);
		
		numCountsInList2[num2] += 1;
	}

	long long ans = 0;
	for (int num : list1) {
		ans += num * numCountsInList2[num];
	}

	cout << ans << endl;

	return 0;
}
