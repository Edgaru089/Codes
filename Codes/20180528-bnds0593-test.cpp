/*
DOCUMENT CODE "20180528-bnds0593-test.cpp"
CREATION DATE 2018-05-28
SIGNATURE CODE_20180528_BNDS0593_TEST
TOPIC Data generation (brute force)
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180528_BNDS0593_TEST

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int n, m;
int sum = 0;
vector<vector<int>> ans;
vector<int> vec;

void iterate(int dep) {
	if (dep == 0) {
		int sum = 0;
		for (int i : vec)
			sum += i;
		if (sum == m) {
			::sum++;
			ans.push_back(vec);
		}
	}
	else
		for (int i = 0; i <= m; i++) {
			vec.push_back(i);
			iterate(dep - 1);
			vec.pop_back();
		}
}

int main(int argc, char* argv[]) {

	cin >> n >> m;

	vec.reserve(n);

	iterate(n);

	int size = 0;
	cout << sum << endl << endl;
	for (int i = 0; i < ans.size(); i++) {
		if (i > 0 && ans[i][0] != ans[i - 1][0]) {
			cout << size << endl;
			size = 0;
		}
		vector<int>& vec = ans[i];

		size++;
	}
	cout << size << endl;

	return 0;
}

#endif

