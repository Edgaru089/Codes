/*
DOCUMENT NAME "20180716-luoguU30363.cpp"
CREATION DATE 2018-07-16
SIGNATURE CODE_20180716_LUOGUU30363
COMMENT °Ë°Ù±ê±ø±¼±±ÆÂ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180716_LUOGUU30363

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 1e3 + 10;

int n, m, k;
int height[MaxN][MaxN];
bool ishill[MaxN][MaxN];
int dist[MaxN][MaxN];

int main(int argc, char* argv[]) {

	memset(dist, -1, sizeof(dist));

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> height[i][j];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (height[i][j] > height[i - 1][j] &&
				height[i][j] > height[i + 1][j] &&
				height[i][j] > height[i][j - 1] &&
				height[i][j] > height[i][j + 1])
				ishill[i][j] = true;
		}
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (dist[i - 1][j] >= 0)
				dist[i][j] = dist[i - 1][j] + 1;
			if (ishill[i][j])
				dist[i][j] = 0;
		}

	int x, y;
	for (int i = 1; i <= k; i++) {
		cin >> x >> y;
		if (dist[x][y] < 0)
			cout << "Pool Babingbaboom!" << endl;
		else
			cout << dist[x][y] << endl;
	}

	return 0;
}

#endif

