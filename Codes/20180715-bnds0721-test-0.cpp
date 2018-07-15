/*
DOCUMENT NAME "20180715-bnds0721-test-0.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0721_TEST_0
COMMENT 2018-7-15基础班测验（二）-最大公约数
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0721_TEST_0

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int MaxN = 500000 + 10;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}

template<typename IntType>
void read(IntType& val) { val = read(); }

template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

bool isprime(int x) {
	int l = sqrt(x);
	for (int i = 2; i <= l; i++)
		if (x%i == 0)
			return false;
	return true;
}

const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701 };
const int primecnt = 126;

struct factor {
	int factcnt[primecnt];
	int largeprime;
};

int n;
long long k;
int a[MaxN], bucket[MaxN];
factor facts[MaxN];

void factorize(int val, factor& fact) {
	memset(fact.factcnt, 0, sizeof(fact.factcnt));
	for (int i = 0; i < primecnt; i++) {
		while (val%primes[i] == 0) {
			val /= primes[i];
			fact.factcnt[i]++;
		}
	}
	fact.largeprime = val;
}

int bind(const factor& fact) {
	int val = fact.largeprime;
	for (int i = 0; i < primecnt; i++) {
		for (int j = 1; j <= fact.factcnt[i]; j++)
			val *= primes[i];
	}
	return val;
}

int main(int argc, char* argv[]) {

	read(n, k);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
		bucket[a[i]]++;
	}

	for (int i = MaxN; i >= 1; i--) {
		int cnt = 0;
		for (int j = 1; j <= MaxN / i; j++) {
			cnt += bucket[i*j];
		}
		if (cnt >= k) {
			printf("%lld\n", (long long)i*k);
			return 0;
		}
	}


	return 0;
}

#endif

