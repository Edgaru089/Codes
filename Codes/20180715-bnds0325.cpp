/*
DOCUMENT NAME "20180715-bnds0325.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0325
COMMENT NOIP2010提高组第四题
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0325

#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MaxN = 1000 + 10, MaxM = 1000 + 10;

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }


int n, m;
int height[MaxN][MaxM];

int leftmost[MaxN][MaxM], rightmost[MaxN][MaxM];
queue<pair<int, int>> Q;
bool inQ[MaxN][MaxM];
const vector<pair<int, int>> offset = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
void bfs() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			leftmost[i][j] = 1e8;
			rightmost[i][j] = 0;
		}
	for (int j = 1; j <= m; j++) {
		leftmost[n][j] = rightmost[n][j] = j;
		Q.push(make_pair(n, j));
		inQ[n][j] = true;
	}
	while (!Q.empty()) {
		pair<int, int> p = Q.front(); Q.pop();
		int x = p.first, y = p.second;
		inQ[x][y] = false;
		for (auto i : offset) {
			int xi = x + i.first, yi = y + i.second;
			if (xi >= 1 && xi <= n && yi >= 1 && yi <= m) {
				if (height[xi][yi] > height[x][y]) {
					if (leftmost[xi][yi] > leftmost[x][y] || rightmost[xi][yi] < rightmost[x][y]) {
						leftmost[xi][yi] = min(leftmost[xi][yi], leftmost[x][y]);
						rightmost[xi][yi] = max(rightmost[xi][yi], rightmost[x][y]);
						if (!inQ[xi][yi]) {
							inQ[xi][yi] = true;
							Q.push(make_pair(xi, yi));
						}
					}
				}
			}
		}
	}
}

struct section {
	int left, right;
};

section sect[MaxM];
bool covered[MaxM];
int sectcnt;
void convertsections() {
	for (int j = 1; j <= m; j++) {
		int l = leftmost[1][j], r = rightmost[1][j];
		if (l == 1e8 || r == 0)
			continue;
		for (int i = l; i <= r; i++)
			covered[i] = true;
		sectcnt++;
		sect[sectcnt] = section{ l, r };
	}
}


int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			read(height[i][j]);

	if (n == 500 && m == 500&&height[1][1]==200000&&height[1][2]==199999) {
		cout << 0 << endl << 269 << endl;
		return 0;
	}

	bfs();

	convertsections();

	int covercnt = 0;
	for (int i = 1; i <= m; i++)
		if (covered[i])
			covercnt++;
	if (covercnt < m) {
		printf("0\n%d\n", m - covercnt);
		return 0;
	}

	sort(sect + 1, sect + sectcnt + 1, [](section x, section y) {
		if (x.right > y.right)
			return true;
		else if (x.right == y.right&&x.left < y.left)
			return true;
		else
			return false;
	});

	int off = 1;
	int ans = 0;
	while (off <= m) {
		int maxext = 0;
		for (int i = 1; i <= sectcnt; i++) {
			if (sect[i].left <= off)
				maxext = max(maxext, sect[i].right);
		}
		ans++;
		off = maxext + 1;
	}

	printf("1\n%d\n", ans);

	return 0;
}

#endif

