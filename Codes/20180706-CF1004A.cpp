/*
DOCUMENT NAME "20180706-CF1004A.cpp"
CREATION DATE 2018-07-06
SIGNATURE CODE_20180706_CF1004A
COMMENT #495A. Sonya and Hotels / Ä£Äâ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180706_CF1004A

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int MaxN = 100 + 10;

int n, d;

vector<int> x;
vector<int> inspect;
unordered_set<int> oks;

int main(int argc, char* argv[]) {

	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		int a;
		cin >> a;
		x.push_back(a);
	}

	for (int i : x) {
		inspect.push_back(i + d);
		inspect.push_back(i - d);
	}

	for (int i : inspect) {
		bool flag = true;
		for (int j : x) {
			if (abs(i - j) < d) {
				flag = false;
				break;
			}
		}
		if (flag) {
			auto k = oks.find(i);
			if (k == oks.end())
				oks.insert(i);
		}
	}

	cout << oks.size() << endl;

	return 0;
}

#endif

