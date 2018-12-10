/*
 DOCUMENT NAME "20181209-noipt1.cpp"
 CREATION DATE 2018-12-09
 SIGNATURE CODE_20181209_NOIPT1
 COMMENT Ð¡ÆæÍÚ¿ó (explo)
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181209_NOIPT1

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstdio>
using namespace std;

#define FILENAME "explo"

#if (defined LOCAL || defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }


/******************** End of quickread template ********************/

const int MaxN = 100000 + 10;

int n, k, c, w;







int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);








	fclose(out);
	return 0;
}

#endif

