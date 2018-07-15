/*
DOCUMENT NAME "20180713-bnds0126.cpp"
CREATION DATE 2018-07-13
SIGNATURE CODE_20180713_BNDS0126
COMMENT 作业调度方案
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180713_BNDS0126

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
const int MaxM = 20 + 10, MaxN = 20 + 10;

struct work {
	int series;
	int object;
	int machine;
	int time;
};

int m, n;
int arrobjid[MaxN * MaxM];
int arrmachine[MaxN][MaxM];
int worktime[MaxN][MaxM];

work works[MaxN*MaxM];
int objlasttime[MaxN];

bool occupied[MaxM][MaxM * 20 + 10];

int main(int argc, char* argv[]) {

	cin >> m >> n;
	for (int i = 1; i <= m * n; i++)
		cin >> arrobjid[i];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> arrmachine[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> worktime[i][j];

	int cnt[MaxN] = {};
	for (int i = 1; i <= m * n; i++) {
		cnt[arrobjid[i]]++;
		works[i].series = cnt[arrobjid[i]];
		works[i].object = arrobjid[i];
		works[i].machine = arrmachine[arrobjid[i]][cnt[arrobjid[i]]];
		works[i].time = worktime[arrobjid[i]][cnt[arrobjid[i]]];
	}

	int maxtime = 0;
	for (int i = 1; i <= m * n; i++) {
		int object = works[i].object, machine = works[i].machine, time = works[i].time;
		for (int j = objlasttime[object] + 1;; j++) {
			bool ok = true;
			for (int k = j; k <= j + time - 1; k++)
				if (occupied[machine][k]) {
					ok = false;
					break;
				}
			if (ok) {
				for (int k = j; k <= j + time - 1; k++)
					occupied[machine][k] = true;
				maxtime = max(maxtime, j + time - 1);
				objlasttime[object] = j + time - 1;
				break;
			}
		}
	}

	cout << maxtime << endl;

	return 0;
}

#endif

