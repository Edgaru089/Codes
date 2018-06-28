/*
DOCUMENT CODE "20180621-luogu2822.cpp"
CREATION DATE 2018-06-21
SIGNATURE CODE_20180621_LUOGU2822
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180621_LUOGU2822

#include <cstdlib>
#include <iostream>
#include <climits>
#include <cstdio>
using namespace std;

namespace System {
	constexpr int Max = 2000;
	int t, k;

	int read() {
		int sum = 0;
		char c;
		while (!isdigit(c = getchar()));
		do {
			sum = sum * 10 + (c - '0');
		} while (isdigit(c = getchar()));
		return sum;
	}

	int read(int& val) {
		return val = read();
	}
}

namespace PascalTriangle {
	int val[System::Max + 10][System::Max + 10];

	void compute(int n) {
		val[0][0] = 1;
		for (int i = 1; i <= n; i++)
			val[i][0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= i; j++)
				val[i][j] = (val[i - 1][j] + val[i - 1][j - 1]) % System::k;
	}
}

namespace Algorithm {
	long long sum[System::Max + 10][System::Max + 10];

	void initalaize() {
		for (int i = 1; i <= System::Max; i++) {
			for (int j = 1; j <= System::Max; j++) {
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
				if (j <= i && PascalTriangle::val[i][j] == 0)
					sum[i][j]++;
			}
		}
	}

	long long getVal(int n, int m) {
		if (m > n)
			m = n;
		return sum[n][m];
	}
}

namespace System {
	void initalaize() {
		PascalTriangle::compute(Max);
		Algorithm::initalaize();
	}

	void run() {
		read(t); read(k);
		initalaize();
		for (int i = 1; i <= t; i++) {
			printf("%lld\n", Algorithm::getVal(read(), read()));
		}
	}
}

int main(int argc, char* argv[]) {

	System::run();

	return 0;
}

#endif

