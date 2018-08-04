/*
DOCUMENT NAME "20180728-luogu2613.cpp"
CREATION DATE 2018-07-28
SIGNATURE CODE_20180728_LUOGU2613
COMMENT 【模板】有理数取余
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180728_LUOGU2613

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

long long qm(long long a, long long b, long long mod) {
	long long val = 1, t = a;
	while (b != 0) {
		if (b % 2 == 1)
			val = (val*t) % mod;
		b /= 2;
		t = (t*t) % mod;
	}
	return val;
}


int main(int argc, char* argv[]) {
	long long a = 0, b = 0;
	const long long p = 19260817;
	string astr, bstr;
	cin >> astr >> bstr;
	for (char& c : astr)
		a = (a * 10 + c - '0') % p;
	for (char& c : bstr)
		b = (b * 10 + c - '0') % p;
	if (b == 0)
		printf("Angry!\n");
	else {
		printf("%lld\n", (qm(b, p - 2, p)*a) % p);
	}
	return 0;
}

#endif

