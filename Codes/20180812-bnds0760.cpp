/*
DOCUMENT NAME "20180812-bnds0760.cpp"
CREATION DATE 2018-08-12
SIGNATURE CODE_20180812_BNDS0760
COMMENT 2018-8-12noipƒ£ƒ‚≤‚—È£®»˝£©-√‹ “Ã”Õ—
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180812_BNDS0760

#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 100 + 10, MaxM = 10;

int n, m;
bool flag[MaxN][MaxN];
int key[MaxN][MaxN];
bool question[MaxN][MaxN];
int dis[MaxN][MaxN][MaxM];
int sx, sy, ex, ey;
int ans = infinity;

void dfs(int x, int y, int nextkey, int dep) {
	if (x == ex && y == ey && nextkey > m) {
		ans = min(ans, dep);
		return;
	}

	if (!flag[x][y] || dis[x][y][nextkey] < dep)
		return;
	int tdis = dis[x][y][nextkey];
	dis[x][y][nextkey] = dep;

	if (key[x][y] == nextkey)
		nextkey++;

	bool hasquest = false;
	if (question[x][y]) {
		hasquest = true;
		dep++;
		question[x][y] = false;
	}

	if (x - 1 >= 1)
		dfs(x - 1, y, nextkey, dep + 1);
	if (x + 1 <= n)
		dfs(x + 1, y, nextkey, dep + 1);
	if (y - 1 >= 1)
		dfs(x, y - 1, nextkey, dep + 1);
	if (y + 1 <= n)
		dfs(x, y + 1, nextkey, dep + 1);

	if (hasquest)
		question[x][y] = true;
	dis[x][y][nextkey] = tdis;
}


int main(int argc, char* argv[]) {

	cin >> n >> m;
	string str;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m + 1; k++)
				dis[i][j][k] = infinity;
	for (int i = 1; i <= n; i++) {
		cin >> str;
		for (int j = 1; j <= n; j++) {
			char c = str[j - 1];
			if (c == '#')
				flag[i][j] = false;
			else
				flag[i][j] = true;
			if (c == 'K') {
				sx = i;
				sy = j;
			}
			else if (c == 'S')
				question[i][j] = true;
			else if (c == 'T') {
				ex = i;
				ey = j;
			}
			else if (isdigit(c))
				key[i][j] = c - '0';
		}
	}

	dfs(sx, sy, 1, 0);

	if (ans == infinity)
		cout << "impossible" << endl;
	else
		cout << ans << endl;

	return 0;
}

#endif

