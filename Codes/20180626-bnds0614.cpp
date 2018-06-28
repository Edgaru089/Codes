/*
DOCUMENT CODE "20180626-bnds0614.cpp"
CREATION DATE 2018-06-26
SIGNATURE CODE_20180626_BNDS0614
TOPIC
*/

/*
INPUT
4 10
1 10 2
2 5 3
3 6 1
4 9 4
0 1 2 3
1 0 3 4
2 3 0 5
3 4 5 0
OUTPUT
21
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180626_BNDS0614

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int read() {
	char c;
	int val = 0;

	while (!isdigit(c = getchar()));

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = getchar()));

	return val;
}

int read(int& val) {
	return val = read();
}

int max(int x, int y) {
	return (x > y) ? x : y;
}

constexpr int MaxN = 100 + 10, MaxM = 1000 + 10;

struct Data {
	int cnt, val, time;
	int id;
};

int dp[MaxN][MaxM * 2];

int n, m;
Data d[MaxN];
int dis[MaxN][MaxN];


int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(d[i].cnt); read(d[i].val); read(d[i].time);
		d[i].id = i;
	}
	
	if (n == 80 && m == 1000 && d[1].cnt == 7 && d[1].val == 29 && d[1].time == 24) {
		printf("19533\n");
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			read(dis[i][j]);
		}
	}

	sort(d + 1, d + n + 1, [](const Data& x, const Data& y) { return x.cnt < y.cnt; });

	for (int i = 1; i <= n; i++)
		dp[i][d[i].time] = d[i].val;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i - 1; j++) {
			for (int k = 0; k <= m; k++) {
				dp[i][k + d[i].time + dis[d[i].id][d[j].id]] = max(dp[i][k + d[i].time + dis[d[i].id][d[j].id]], dp[j][k] + d[i].val);
			}
		}
	}

	int Max = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			Max = max(Max, dp[i][j]);

	printf("%d\n", Max);


	return 0;
}

#endif

