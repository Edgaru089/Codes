/*
DOCUMENT NAME "20180807-bnds0292.cpp"
CREATION DATE 2018-08-07
SIGNATURE CODE_20180807_BNDS0292
COMMENT NOIP2013提高组day1第一题 转圈游戏
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180807_BNDS0292

#include <cstdlib>
#include <iostream>
using namespace std;

int n, m, k, x;

int qm(int a, int b, int p) {
	int sum = 1;
	while (b != 0) {
		if (b % 2 == 1)
			sum = (long long)sum*a%p;
		a = (long long)a*a%p;
		b /= 2;
	}
	return sum;
}

int main(int argc, char* argv[]) {

	cin >> n >> m >> k >> x;
	int t = (long long)m*qm(10, k, n) % n;
	cout << (x + t) % n << endl;

	return 0;
}

#endif

