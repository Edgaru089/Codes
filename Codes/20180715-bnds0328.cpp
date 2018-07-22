/*
DOCUMENT NAME "20180715-bnds0328.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0328
COMMENT NOIP2010普及组第三题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0328

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int sqr(int x) { return x * x; }

int distanceSqr(int x1, int y1, int x2, int y2) {
	return sqr(x1 - x2) + sqr(y1 - y2);
}

int n;
int x1, y1_, x2, y2;

struct obj {
	int x, y;
	int dis1, dis2;
};

obj o[100000 + 10];
int maxpre[100000 + 10];


int main(int argc, char* argv[]) {

	cin >> x1 >> y1_ >> x2 >> y2;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x, y;
		cin >> x >> y;
		o[i].x = x;
		o[i].y = y;
		o[i].dis1 = distanceSqr(x, y, x1, y1_);
		o[i].dis2 = distanceSqr(x, y, x2, y2);
	}

	sort(o + 1, o + n + 1, [](obj x, obj y) {return x.dis1 < y.dis1; });

	for (int i = n; i >= 1; i--)
		maxpre[i] = max(maxpre[i + 1], o[i].dis2);

	int ans = 1e8;
	for (int i = 0; i <= n; i++) {
		ans = min(ans, o[i].dis1 + maxpre[i + 1]);
	}

	cout << ans << endl;

	return 0;
}

#endif

