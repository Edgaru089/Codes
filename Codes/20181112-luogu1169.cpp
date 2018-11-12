/*
 DOCUMENT NAME "20181112-luogu1169.cpp"
 CREATION DATE 2018-11-12
 SIGNATURE CODE_20181112_LUOGU1169
 COMMENT P1169 [ZJOI2007]ÆåÅÌÖÆ×÷
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181112_LUOGU1169

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
{printf(#arr ":");												\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#endif

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

const int MaxN = 2000 + 10, MaxM = 2000 + 10;

int n, m;
int color[MaxN][MaxM];
int dpx[MaxN][MaxM], dpy[MaxN][MaxM];





int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			read(color[i][j]);
		}
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dpx[i][j] = dpy[i][j] = 1;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			// expands to the right
			if (j > 1 && color[i][j - 1] != color[i][j] && dpy[i - 1][j] >= dpy[i][j - 1] - 1) {
				int nx = dpx[i][j - 1] + 1, ny = dpy[i][j - 1];
				if (nx*ny > dpx[i][j] * dpy[i][j]) {
					dpx[i][j] = nx;
					dpy[i][j] = ny;
				}
			}
			// expands downwards
			if (i > 1 && color[i - 1][j] != color[i][j] && dpx[i][j - 1] >= dpx[i - 1][j] - 1) {
				int nx = dpx[i - 1][j], ny = dpy[i - 1][j] + 1;
				if (nx*ny > dpx[i][j] * dpy[i][j]) {
					dpx[i][j] = nx;
					dpy[i][j] = ny;
				}
			}
			// expands to the bottom-right
			if (i > 1 && j > 1 && color[i][j] == color[i - 1][j - 1] && dpx[i - 1][j - 1] <= dpx[i - 1][j] - 1 && dpy[i - 1][j - 1] <= dpy[i][j - 1] - 1) {
				int nx = dpx[i - 1][j - 1] + 1, ny = dpy[i - 1][j - 1] + 1;
				if (nx*ny > dpx[i][j] * dpy[i][j]) {
					dpx[i][j] = nx;
					dpy[i][j] = ny;
				}
			}
		}
		DEBUG("i=%d\n", i);
		PRINTARR("%d", dpx[i], 1, m);
		PRINTARR("%d", dpy[i], 1, m);
	}

	int tans = 0, sans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			tans = max(tans, dpx[i][j] * dpy[i][j]);
			sans = max(sans, min(dpx[i][j], dpy[i][j]));
		}

	printf("%d\n%d\n", sans*sans, tans);

	return 0;
}

#endif

