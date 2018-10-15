/*
 DOCUMENT NAME "20181004-noipT2-Cash.cpp"
 CREATION DATE 2018-10-04
 SIGNATURE CODE_20181004_NOIPT2_CASH
 COMMENT NOIP Ä£ÄâÈü 20181004 T2 Cash
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181004_NOIPT2_CASH

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

#define FILENAME "cash"
#define ENDLINE "\r\n"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
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
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[buffersize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	//if (val < 0) {
	//	PUTCHAR('-');
	//	val = -val;
	//}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	putstr(ENDLINE);
}

/******************** End of quickread template ********************/

const int MaxX = 500000;
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > Q;
vector<vector<bool> > been;
vector<bool> rans;
int n, k;




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "r");
	FILE* out = fopen(FILENAME ".out", "w");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(n); read(k);
	been.resize(n + 1);
	for (int i = 1; i <= n; i++)
		been[i].resize(2 * k*k*n + 2, false);
	rans.resize(2 * k*k*n + 2, false);

	int add[4] = { 1, k, 2 * k, 2 * k*k };

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 4; j++) {
			Q.push(make_pair(i, add[j] * i));
			been[i].at(add[j] * i) = true;
		}
	}

	while (!Q.empty()) {
		int step = Q.top().first, val = Q.top().second;
		Q.pop();
		if (step < n) {
			for (int j = 0; j < 4; j++)
				if (!been[step + 1][val + add[j]]) {
					been[step + 1].at(val + add[j]) = true;
					Q.push(make_pair(step + 1, val + add[j]));
				}
		}
		else {
			rans.at(val) = true;
		}
	}

	int ans = 0;
	for (int i = 0; i <= 2 * k*k*n; i++)
		if (rans[i])
			ans++;

	println(ans);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}


#endif

