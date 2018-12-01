/*
 DOCUMENT NAME "20181116-luogu1057.cpp"
 CREATION DATE 2018-11-16
 SIGNATURE CODE_20181116_LUOGU1057
 COMMENT
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181116_LUOGU1057

#include <cstdlib>
#include <iostream>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int MaxN = 100;
int n, m;
int d[MaxN][MaxN];





int main(int argc, char* argv[]) {

	read(n); read(m);
	d[0][0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j] = d[i - 1][(n + j - 1) % n] + d[i - 1][(j + 1) % n];
		}
	}

	printf("%d\n", d[m][0]);

	return 0;
}

#endif

