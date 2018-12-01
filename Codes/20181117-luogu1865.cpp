/*
 DOCUMENT NAME "20181117-luogu1865.cpp"
 CREATION DATE 2018-11-17
 SIGNATURE CODE_20181117_LUOGU1865
 COMMENT P1865 A % B Problem / °£ÊÏÉ¸+Ç°×ººÍ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181117_LUOGU1865

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
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

const int MaxN = 1000000 + 10;

int n, m;
int l, r;
bool notprime[MaxN];
int d[MaxN];



int main(int argc, char* argv[]) {

	read(n); read(m);
	for (int i = 2; i <= m; i++) {
		if (!notprime[i]) {
			for (int j = i; j <= m; j += i)
				notprime[j] = true;
			d[i] = d[i - 1] + 1;
		} else
			d[i] = d[i - 1];
	}

	for (int i = 1; i <= n; i++) {
		read(l); read(r);
		if (l<1 || l>m || r<1 || r>m || l > r)
			printf("Crossing the line\n");
		else
			printf("%d\n", d[r] - d[l - 1]);
	}

	return 0;
}

#endif

