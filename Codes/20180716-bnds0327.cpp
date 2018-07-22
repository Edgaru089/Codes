/*
DOCUMENT NAME "20180716-bnds0327.cpp"
CREATION DATE 2018-07-16
SIGNATURE CODE_20180716_BNDS0327
COMMENT NOIP2010普及组第二题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180716_BNDS0327

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> pri;
int n, m;
int a[10000 + 10];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= n; i++) {
		if (pri.size() < m)
			pri.push(a[i]);
		else {
			int top = pri.top(); pri.pop();
			pri.push(top + a[i]);
		}
	}

	int mmax = 0;
	while (!pri.empty()) {
		mmax = max(mmax, pri.top());
		pri.pop();
	}

	cout << mmax << endl;

	return 0;
}

#endif

