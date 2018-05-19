/*
DOCUMENT CODE "20180515-bnds0588.cpp"
CREATION DATE 2018-05-15
SIGNATURE CODE_20180515_BNDS0588
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180515_BNDS0588

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

long long n, a[1000001];

long long c[1000001];

long long lowbit(long long x) { return x & (-x); }

void add(long long pos, long long x) {
	while (pos <= 1000001) {
		c[pos] += x;
		pos += lowbit(pos);
	}
}

long long queryPrefixSum(long long pos) {
	long long ans = 0;
	while (pos > 0) {
		ans += c[pos];
		pos -= lowbit(pos);
	}
	return ans;
}

long long greaterBeforeCount[1000001], lessAfterCount[1000001];

int main(int argc, char* argv[]) {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = n; i >= 1; i--) {
		lessAfterCount[i] = queryPrefixSum(a[i]-1);
		add(a[i], 1);
	}

	memset(c, 0, sizeof(c));

	for (int i = 1; i <= n; i++) {
		greaterBeforeCount[i] = queryPrefixSum(1000000) - queryPrefixSum(a[i] - 1);
		add(a[i], 1);
	}

	long long ans = 0;
	for (int j = 1; j <= n; j++)
		ans += lessAfterCount[j] * greaterBeforeCount[j];

	cout << ans << endl;

	return 0;
}

#endif

