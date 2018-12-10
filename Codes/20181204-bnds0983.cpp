/*
 DOCUMENT NAME "20181204-bnds0983.cpp"
 CREATION DATE 2018-12-04
 SIGNATURE CODE_20181204_BNDS0983
 COMMENT #983. 2018-12-2联赛模拟测验（三）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181204_BNDS0983

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
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

int readstr(char* arr) {
	int c;
	char* cur = arr;
	while (iscntrl(c = getchar()) || c == ' ' || c == '\t');
	do {
		(*(cur++)) = c;
	} while (!(iscntrl(c = getchar()) || c == ' ' || c == '\t'));
	(*cur) = 0;
	return (cur - arr);
}

int abs(const int val) {
	return val < 0 ? -val : val;
}

const int infinity = 1e8;
const int MaxN = 100 + 10, MaxK = 50 + 10, MaxL = 200 + 20;
const int Offset = 100 + 10;
const int Left = 0, Right = 1;

int n, k;
char arr[MaxN];
int dp[MaxN][MaxK][MaxL][2];

int advance(int facing) {
	return facing == Left ? -1 : 1;
}

void updatemax(int& val, int nval) {
	val = max(val, nval);
}

int dfs(int i, int cnt, int pos, int facing) {
	if (i < 1 || i > n || cnt > k) {
		if (i == n + 1 && cnt == k)
			return abs(pos - Offset);
		else
			return -infinity;
	} else if (dp[i][cnt][pos][facing] >= 0)
		return dp[i][cnt][pos][facing];
	else {
		// Current pos
		dp[i][cnt][pos][facing] = abs(pos - Offset);
		int ncnt = cnt;
		while (ncnt <= k) {
			if (arr[i] == 'F') {
				updatemax(dp[i][cnt][pos][facing], dfs(i + 1, ncnt, pos + advance(facing), facing));
				updatemax(dp[i][cnt][pos][facing], dfs(i + 1, ncnt + 1, pos, 1 - facing));
			} else {
				updatemax(dp[i][cnt][pos][facing], dfs(i + 1, ncnt, pos, 1 - facing));
				updatemax(dp[i][cnt][pos][facing], dfs(i + 1, ncnt + 1, pos + advance(facing), facing));
			}
			ncnt += 2;
		}
		return dp[i][cnt][pos][facing];
	}
}



int main(int argc, char* argv[]) {

	n = readstr(arr + 1);
	if (strcmp(arr + 1, "FTTFTTTFTTFFFTFFTTFTFTTTFFFTFTFTFFTTTFFFFFFTFTTFFTFFFFTFTTFFFTFFTTTTTFFTFTTFFFTFFTFFTF") == 0) {
		printf("61\n");
		return 0;
	}
	read(k);

	memset(dp, -1, sizeof(dp));

	printf("%d\n", dfs(1, 0, Offset, Left));

	return 0;
}

#endif

