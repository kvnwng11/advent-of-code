#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	string file;
	cin >> file;
	
	ifstream fin(file);

	vector<long long> list1;
	vector<long long> list2;
	
	int num1, num2;
	while (fin >> num1 >> num2) {
		list1.push_back(num1);
		list2.push_back(num2);
	}

	sort(list1.begin(), list1.end());
	sort(list2.begin(), list2.end());

	assert(list1.size() == list2.size());

	long long ans = 0;
	for (int i=0; i<list1.size(); ++i) {
		ans += abs(list2[i] - list1[i]);
		//cout << (list2[i] - list1[i]) << endl;
	}

	cout << ans << endl;

	return 0;
}
