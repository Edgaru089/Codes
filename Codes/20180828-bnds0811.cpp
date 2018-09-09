/*
DOCUMENT NAME "20180828-bnds0811.cpp"
CREATION DATE 2018-08-28
SIGNATURE CODE_20180828_BNDS0811
COMMENT C. 2018-8-28noip模拟测验（三）-大逃亡
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180828_BNDS0811

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int infinity = 1e7;
const int MaxN = 10000 + 10, MaxX = 1000 + 10, MaxY = 1000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int iabs(int x) { return x > 0 ? x : -x; }

int n, xt, yt;
int x[MaxN], y[MaxN];
int sx, sy, tx, ty;

bool flag[MaxX][MaxY];
bool been[MaxX][MaxY];

const int offx[] = { 0, 1, 0, -1 };
const int offy[] = { 1, 0, -1, 0 };
void dfs(int x, int y) {
	been[x][y] = true;
	for (int i = 0; i < 3; i++) {
		int x0 = x + offx[i], y0 = y + offy[i];
		if (x0 >= 0 && x0 < xt && y0 >= 0 && y0 < yt && flag[x0][y0] && !been[x0][y0])
			dfs(x0, y0);
	}
}

void setbounds(int bounds) {
	for (int i = 0; i < xt; i++)
		for (int j = 0; j < yt; j++) {
			flag[i][j] = true;
			been[i][j] = false;
		}
	if (bounds > 0)
		for (int i = 1; i <= n; i++) {
			flag[x[i]][y[i]] = false;
			for (int j = 1; j <= bounds - 1; j++) {
				if (x[i] + j < xt)
					flag[x[i] + j][y[i]] = false;
				if (x[i] - j >= 0)
					flag[x[i] - j][y[i]] = false;
				if (y[i] + j < yt)
					flag[x[i]][y[i] + j] = false;
				if (y[i] - j >= 0)
					flag[x[i]][y[i] - j] = false;
			}
		}
}

bool check(int bounds) {
	for (int i = 0; i < xt; i++)
		for (int j = 0; j < yt; j++) {
			flag[i][j] = true;
			been[i][j] = false;
		}
	if (bounds > 0)
		for (int i = 1; i <= n; i++) {
			if (iabs(sx - x[i]) + iabs(sy - y[i]) < bounds)
				return false;
			flag[x[i]][y[i]] = false;
			for (int j = 1; j <= bounds - 1; j++) {
				if (x[i] + j < xt)
					flag[x[i] + j][y[i]] = false;
				if (x[i] - j >= 0)
					flag[x[i] - j][y[i]] = false;
				if (y[i] + j < yt)
					flag[x[i]][y[i] + j] = false;
				if (y[i] - j >= 0)
					flag[x[i]][y[i] - j] = false;
			}
		}

	dfs(sx, sy);
	return been[tx][ty];
}

template<typename Type, int Size = 20 * MaxX * MaxY>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

struct pii {
	int x, y;
};

int dis[MaxX][MaxY];
queue<pii> Q;
bool inQ[MaxX][MaxY];
int bfs(int bounds) {
	setbounds(bounds);
	for (int i = 0; i < xt; i++)
		for (int j = 0; j < yt; j++)
			dis[i][j] = infinity;
	Q.push(pii{ sx, sy });
	inQ[sx][sy] = true;
	dis[sx][sy] = 0;
	while (!Q.empty()) {
		pii p = Q.front();
		Q.pop(); inQ[p.x][p.y] = false;
		for (int i = 0; i < 3; i++) {
			int x0 = p.x + offx[i], y0 = p.y + offy[i];
			if (x0 >= 0 && x0 < xt && y0 >= 0 && y0 < yt && flag[x0][y0]) {
				if (dis[x0][y0] > dis[p.x][p.y] + 1) {
					dis[x0][y0] = dis[p.x][p.y] + 1;
					if (!inQ[x0][y0]) {
						inQ[x0][y0] = true;
						Q.push(pii{ x0, y0 });
					}
				}
			}
		}
	}
	return dis[tx][ty];
}



int main(int argc, char* argv[]) {

	read(n, xt, yt);
	read(sx, sy, tx, ty);
	for (int i = 1; i <= n; i++)
		read(x[i], y[i]);

	int ans = 0;
	int l = 0, r = min(xt, yt);
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	if (check(l))
		ans = l;
	else
		ans = r;

	printf("%d %d\n", ans, bfs(ans));

	return 0;
}

#endif

