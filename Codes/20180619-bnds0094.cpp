/*
DOCUMENT CODE "20180619-bnds0094.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0094
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0094

#include <cstdlib>
#include <iostream>
#include <utility>
using namespace std;

int cnt;
int n, m;
int sx, sy, ex, ey;

int moveX[] = { 1,1,2,2 };
int moveY[] = { 2,-2,1,-1 };

void dfs(int x, int y) {
	if (x<1 || x>n || y<1 || y>n)
		return;
	if (x == ex && y == ey) {
		cnt++;
		return;
	}
	if (x > ex)
		return;
	for (int i = 0; i < 4; i++) {
		int dx = x + moveX[i], dy = y + moveY[i];
		dfs(dx, dy);
	}
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	cin >> sx >> sy >> ex >> ey;

	dfs(sx, sy);

	cout << cnt << endl;

	return 0;
}

#endif

