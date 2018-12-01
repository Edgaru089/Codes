/*
 DOCUMENT NAME "20181117-luogu1372.cpp"
 CREATION DATE 2018-11-17
 SIGNATURE CODE_20181117_LUOGU1372
 COMMENT P1372 ”÷ «±œ“µºæI
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181117_LUOGU1372

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

int n, k;

int main(int argc, char* argv[]) {

	read(n); read(k);
	printf("%d\n", n / k);

	return 0;
}

#endif

