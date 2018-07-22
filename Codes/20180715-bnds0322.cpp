/*
DOCUMENT NAME "20180715-bnds0322.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0322
COMMENT NOIP2010提高组第一题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0322

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

int n, m;
int a[1001];

queue<int> Q;
bool inQ[1001];

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		if (!inQ[x]) {
			Q.push(x);
			inQ[x] = true;
			cnt++;
			if (Q.size() > m) {
				inQ[Q.front()] = false;
				Q.pop();
			}
		}
	}

	cout << cnt << endl;

	return 0;
}

#endif

