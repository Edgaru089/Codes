/*
DOCUMENT NAME "20180629-luogu2047.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU2047
COMMENT [NOI2007]社交网络 / Floyd+最短路计数+瞎搞
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU2047

#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100 + 10, MaxM = 4500 + 10;

int n, m;
int dis[MaxN][MaxN];
long long edgeCnt[MaxN][MaxN];

double ans[MaxN];

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = infinity;
	for (int i = 1; i <= m; i++) {
		int u, v, len;
		cin >> u >> v >> len;
		dis[u][v] = dis[v][u] = len;
		edgeCnt[u][v] = edgeCnt[v][u] = 1;
	}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (dis[i][k] == infinity || dis[k][j] == infinity)
					continue;
				else if (dis[i][j] > dis[i][k] + dis[k][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					edgeCnt[i][j] = edgeCnt[i][k] * edgeCnt[k][j];
				}
				else if (dis[i][j] == dis[i][k] + dis[k][j])
					edgeCnt[i][j] += edgeCnt[i][k] * edgeCnt[k][j];

	for (int i = 1; i <= n; i++)
		ans[i] = 0;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i == j || j == k || k == i)
					continue;
				else if (dis[i][j] == dis[i][k] + dis[k][j])
					ans[k] += (1.0 * edgeCnt[i][k] * edgeCnt[j][k]) / edgeCnt[i][j];

	for (int i = 1; i <= n; i++)
		printf("%.3lf\n", ans[i]);

	return 0;
}

#endif

