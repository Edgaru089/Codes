/*
DOCUMENT CODE "20180203-luogu1434.cpp"
CREATION DATE 2018-02-03
SIGNATURE CODE_20180203_LUOGU1434
TOPIC Î´Íê³É
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180203_LUOGU1434

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

struct st {
	int d;
	int x, y;
};

int r, c;
int a[101][101], step[101][101];
int Max = 0;
vector<st> s;

#define INRANGE(a, b) (a >= 1 && a <= r && b >= 1 && b <= c)

void dfs(int x, int y) {
	int x0 = -1, y0 = -1;
	int diff = INT_MAX;

	if (INRANGE(x - 1, y) && a[x - 1][y] < a[x][y] && a[x][y] - a[x - 1][y] < diff) {
		x0 = x - 1;
		y0 = y;
		diff = a[x][y] - a[x - 1][y];
	}
	if (INRANGE(x + 1, y) && a[x + 1][y] < a[x][y] && a[x][y] - a[x + 1][y] < diff) {
		x0 = x + 1;
		y0 = y;
		diff = a[x][y] - a[x + 1][y];
	}
	if (INRANGE(x, y - 1) && a[x][y - 1] < a[x][y] && a[x][y] - a[x][y - 1] < diff) {
		x0 = x;
		y0 = y - 1;
		diff = a[x][y] - a[x][y - 1];
	}
	if (INRANGE(x, y + 1) && a[x][y + 1] < a[x][y] && a[x][y] - a[x][y + 1] < diff) {
		x0 = x;
		y0 = y + 1;
		diff = a[x][y] - a[x][y + 1];
	}

	if (x0 != -1 && y0 != -1 && step[x0][y0] < step[x][y] + 1) {
		step[x0][y0] = step[x][y] + 1;
		dfs(x0, y0);
	}

}

int main(int argc, char* argv[]) {

	cin >> r >> c;
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++) {
			cin >> a[i][j];
			st x;
			x.d = a[i][j];
			x.x = i;
			x.y = j;
			s.push_back(x);

			step[i][j] = 1;
		}

	sort(s.begin(), s.end(), [](st x, st y)->bool { return x.d >= y.d; });

	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++) {
			if (step[i][j] == 1)
				dfs(i, j);
			Max = max(Max, step[i][j]);
		}

	cout << Max << endl;

	return 0;
}

#endif

