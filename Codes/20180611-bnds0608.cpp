/*
DOCUMENT CODE "20180611-bnds0608.cpp"
CREATION DATE 2018-06-11
SIGNATURE CODE_20180611_BNDS0608
TOPIC test 2018-06-11
ตรทึ 100/100
*/

/* Test Data
-- Input
	5 5
	5
	1 1
	2 4
	3 1
	2 2
	2 1
-- Output
	1
	5
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180611_BNDS0608

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int n, m, k;
int x[100], y[100];

int sum[100][100];
int flag[100][100];

int main(int argc, char* argv[]) {

	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		cin >> x[i] >> y[i];
		flag[x[i]][y[i]] = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = m; j >= 1; j--) {
			sum[i][j] = sum[i - 1][j] + sum[i][j + 1] - sum[i - 1][j + 1] + flag[i][j];
		}
	}

	bool ok = true;
	for (int i = 1; i <= k; i++) {
		int X = x[i], Y = y[i];
		int north = sum[X][Y] - sum[X][Y + 1] - flag[X][Y];
		int east = sum[X][Y] - sum[X - 1][Y] - flag[X][Y];
		if (north != 0 && east != 0) {
			ok = false;
			break;
		}
	}

	if (ok)
		cout << 0 << endl;
	else {
		int id = -1;
		for (int l = 1; l <= k; l++) {
			int Xl = x[l], Yl = y[l];

			for (int i = Xl; i <= m; i++)
				for (int j = Yl; j >= 1; j--)
					sum[i][j]--;

			ok = true;
			for (int i = 1; i <= k; i++) {
				if (i == l)
					continue;
				int X = x[i], Y = y[i];
				int north = sum[X][Y] - sum[X][Y + 1] - flag[X][Y];
				int east = sum[X][Y] - sum[X - 1][Y] - flag[X][Y];
				if (north != 0 && east != 0) {
					ok = false;
					break;
				}
			}

			for (int i = Xl; i <= m; i++)
				for (int j = Yl; j >= 1; j--)
					sum[i][j]++;

			if (ok) {
				id = l;
				cout << l << endl;
			}
		}

		if (id == -1)
			cout << -1 << endl;
	}

	return 0;
}

#endif

