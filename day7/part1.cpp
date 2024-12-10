#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <set>

using namespace std;
using ll = long long;
using OPS = ll(*)(ll, ll);

ll add(ll x, ll y) { return x + y; }
ll mul(ll x, ll y) { return x * y; }

OPS ops[2] = {add, mul};

bool canForm(ll target, ll curr, int idx, vector<ll> &nums) {
    if (idx == nums.size()) return target == curr;

    bool ans = false;
    for (auto op : ops) {
        ans |= canForm(target, op(curr, nums[idx]), idx+1, nums);
    }
    return ans;
}

int main() {
	string file;
	cin >> file;

	ifstream fin(file);

    ll ans = 0;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);

        string num;
        ss >> num;
        num.pop_back();

        ll target = stoll(num);

        vector<ll> nums;
        while (ss >> num)
            nums.push_back(stoll(num));

        if (canForm(target, 0, 0, nums))
            ans += target;
    }

    cout << ans << endl;

	return 0; 
}
