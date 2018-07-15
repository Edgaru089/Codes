/*
DOCUMENT NAME "20180712-bnds0124.cpp"
CREATION DATE 2018-07-12
SIGNATURE CODE_20180712_BNDS0124
COMMENT 纪念品分组
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180712_BNDS0124

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int MaxN = 30000 + 10;

int w, n;
int p[MaxN];

int main(int argc, char* argv[]) {

	cin >> w >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i];

	sort(p + 1, p + n + 1);

	int ans = 0;
	int left = 1, right = n;
	while (left < right) {
		if (p[left] + p[right] <= w) {
			left++;
			right--;
			ans++;
		}
		else {
			right--;
			ans++;
		}
	}
	if (left == right)
		ans++;
	
	cout << ans << endl;

	return 0;
}

#endif

