/*
 DOCUMENT NAME "20181205-bnds0837.cpp"
 CREATION DATE 2018-12-05
 SIGNATURE CODE_20181205_BNDS0837
 COMMENT #837. 2018-11-25联赛模拟测验（三）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181205_BNDS0837

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int infinity = 1e8;
const int MaxN = 2000 + 10;

int k, n, m;
int a[MaxN][MaxN];
int xsum[MaxN][MaxN], ysum[MaxN][MaxN];

int getXSum(int y, int xmin, int xmax) {
	return xsum[xmax][y] - xsum[xmin - 1][y];
}

int getYSum(int x, int ymin, int ymax) {
	return ysum[x][ymax] - ysum[x][ymin - 1];
}

int ploughXPriority(int xmin, int ymin, int xmax, int ymax) {
	int cnt = 0;
	// on the left
	while (ymin <= ymax && getXSum(ymin, xmin, xmax) <= k) {
		ymin++;
		cnt++;
	}
	// on the right
	while (ymax >= ymin && getXSum(ymax, xmin, xmax) <= k) {
		ymax--;
		cnt++;
	}
	if (ymax < ymin)
		return cnt;
	// on the top
	while (xmin <= xmax && getYSum(xmin, ymin, ymax) <= k) {
		xmin++;
		cnt++;
	}
	// on the bottom
	while (xmax >= xmin && getYSum(xmax, ymin, ymax) <= k) {
		xmax--;
		cnt++;
	}
	if (xmax < xmin)
		return cnt;
	else if (cnt == 0)
		return infinity;
	else
		return ploughXPriority(xmin, ymin, xmax, ymax) + cnt;
}

int ploughYPriority(int xmin, int ymin, int xmax, int ymax) {
	int cnt = 0;
	// on the top
	while (xmin <= xmax && getYSum(xmin, ymin, ymax) <= k) {
		xmin++;
		cnt++;
	}
	// on the bottom
	while (xmax >= xmin && getYSum(xmax, ymin, ymax) <= k) {
		xmax--;
		cnt++;
	}
	if (xmax < xmin)
		return cnt;
	// on the left
	while (ymin <= ymax && getXSum(ymin, xmin, xmax) <= k) {
		ymin++;
		cnt++;
	}
	// on the right
	while (ymax >= ymin && getXSum(ymax, xmin, xmax) <= k) {
		ymax--;
		cnt++;
	}
	if (ymax < ymin)
		return cnt;
	else if (cnt == 0)
		return infinity;
	else
		return ploughYPriority(xmin, ymin, xmax, ymax) + cnt;
}


int main(int argc, char* argv[]) {

	read(k); read(n); read(m);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			read(a[i][j]);

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			xsum[i][j] = xsum[i - 1][j] + a[i][j];
			ysum[i][j] = ysum[i][j - 1] + a[i][j];
		}

	printf("%d\n", min(ploughXPriority(1, 1, m, n), ploughYPriority(1, 1, m, n)));

	return 0;
}

#endif

