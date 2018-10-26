/*
 DOCUMENT NAME "20181025-luogu1156.cpp"
 CREATION DATE 2018-10-25
 SIGNATURE CODE_20181025_LUOGU1156
 COMMENT P1156 À¬»øÏÝÚå
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181025_LUOGU1156

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

const int MaxN=





int main(int argc, char* argv[]) {

	return 0;
}

#endif

