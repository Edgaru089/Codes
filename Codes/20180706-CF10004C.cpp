/*
DOCUMENT NAME "20180706-CF10004C.cpp"
CREATION DATE 2018-07-06
SIGNATURE CODE_20180706_CF10004C
COMMENT #495C. Sonya and Robots
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180706_CF10004C

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

unordered_map<int, int> mr;
unordered_set<int> sl, sr;
int n;
vector<int> a;

template<typename Set>
void insert_if_not_found(int x, Set& s) {
	if (s.find(x) == s.end())
		s.insert(x);
}

long long sum = 0;
int main(int argc, char* argv[]) {

	int x;
	cin >> n;
	a.reserve(n);
	for (int i = 1; i <= n; i++) {
		cin >> x;
		a.push_back(x);
		if (mr.find(x) == mr.end())
			mr[x] = 0;
		mr[x]++;
		insert_if_not_found(x, sr);
	}

	for (int i = 0; i < n; i++) {
		int k = a[i];
		mr[k]--;
		if (mr[k] == 0)
			sr.erase(k);
		if (sl.find(k) != sl.end()) {
			continue;
		}
		else {
			sl.insert(k);
			sum += sr.size();
		}
	}

	cout << sum << endl;

	return 0;
}

#endif

