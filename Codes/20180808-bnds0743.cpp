/*
DOCUMENT NAME "20180808-bnds0743.cpp"
CREATION DATE 2018-08-08
SIGNATURE CODE_20180808_BNDS0743
COMMENT 2018-8-8Ä£Äâ²âÑé£¨Ò»£©-ÆßÏ¦¼À
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180808_BNDS0743

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;

constexpr int MaxN = 100000 + 10, MaxM = 100000 + 10, MaxT = 100000 + 10;

int n, m, t;
ll row[MaxN], column[MaxM];


int main(int argc, char* argv[]) {

	cin >> n >> m >> t;
	for (int i = 1; i <= t; i++) {
		int x, y;
		cin >> x >> y;
		row[x]++;
		column[y]++;
	}

	bool rowok = false, colok = false;
	if (t%n == 0)
		rowok = true;
	if (t%m == 0)
		colok = true;

	ll ans = 0;
	if (rowok) {
		for (int i = 1; i <= n; i++)
			row[i] -= t / n;
		for (int i = 1; i <= n; i++)
			row[i] += row[i - 1];
		if (n % 2 == 1) {
			sort(row + 1, row + n + 1);
			ll ans2 = 0;
			ll x = row[n / 2 + 1];
			for (int i = 1; i <= n; i++)
				ans2 += abs(row[i] - x);
			ans += ans2;
		}
		else {
			sort(row + 1, row + n + 1);
			ll x = row[n / 2];
			ll ans1 = 0, ans2 = 0;
			for (int i = 1; i <= n; i++)
				ans1 += abs(row[i] - x);
			x = row[n / 2 + 1];
			for (int i = 1; i <= n; i++)
				ans2 += abs(row[i] - x);
			ans += min(ans1, ans2);
		}
	}
	if (colok) {
		for (int i = 1; i <= m; i++)
			column[i] -= t / m;
		for (int i = 1; i <= m; i++)
			column[i] += column[i - 1];
		if (m % 2 == 1) {
			sort(column + 1, column + m + 1);
			ll ans2 = 0;
			ll x = column[m / 2 + 1];
			for (int i = 1; i <= m; i++)
				ans2 += abs(column[i] - x);
			ans += ans2;
		}
		else {
			sort(column + 1, column + m + 1);
			ll x = column[m / 2];
			ll ans1 = 0, ans2 = 0;
			for (int i = 1; i <= m; i++)
				ans1 += abs(column[i] - x);
			x = column[m / 2 + 1];
			for (int i = 1; i <= m; i++)
				ans2 += abs(column[i] - x);
			ans += min(ans1, ans2);
		}
	}

	if (rowok&&colok)
		cout << "both";
	else if (rowok)
		cout << "row";
	else if (colok)
		cout << "column";
	else
		cout << "impossible" << endl;
	if (rowok || colok)
		cout << ' ' << ans << endl;

	return 0;
}

#endif

