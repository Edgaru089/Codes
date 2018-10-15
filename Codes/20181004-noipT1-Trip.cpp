/*
 DOCUMENT NAME "20181004-noipT1-Trip.cpp"
 CREATION DATE 2018-10-04
 SIGNATURE CODE_20181004_NOIPT1
 COMMENT NOIP Ä£ÄâÈü 20181004 T1 Trip
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181004_NOIPT1

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define FILENAME "trip"
#define ENDLINE "\r\n"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int buffersize = 20 * 1024 * 1024;
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

const int infinity = 1e8;
const int MaxN = 17 + 5, MaxT = 10 + 2, MaxA = 1e6 + 10;
const int MaxKN = (1 << 18) + 1;

int t;
int n;
int dis[MaxN][MaxN];
int x, y, z;

int ans[MaxKN][MaxN];

struct q {
	q() {}
	q(const int& state, const int& dis, const int& u) :
		state(state), dis(dis), u(u) {}
	int state, dis, u;
};

struct qcmp {
	bool operator ()(const q& x, const q& y) const {
		return x.dis > y.dis || (x.dis == y.dis && x.u < y.u);
	}
};

priority_queue<q, vector<q>, qcmp > Q;
int rans;

void dijstra() {
	for (int i = 0; i < MaxKN; i++)
		for (int j = 1; j <= n; j++)
			ans[i][j] = infinity;
	ans[0][1] = 0;
	while (!Q.empty())
		Q.pop();
	Q.push(q(0, 0, 1));
	while (!Q.empty()) {
		int k = Q.top().state, l = Q.top().dis, u = Q.top().u;
		Q.pop();
		if (k == (1 << n) - 1 && u == 1) {
			rans = l;
			return;
		}
		if (ans[k][u] < l)
			continue;
		for (int i = 1; i <= n; i++) {
			if ((k&(1 << (i - 1))) == 0)
				if (ans[k | (1 << (i - 1))][i] > l + dis[u][i]) {
					//DEBUG("In Queue: %d (from %d state %d, to %d)", k | (1 << (i - 1)), u, k, i);
					ans[k | (1 << (i - 1))][i] = l + dis[u][i];
					Q.push(q(k | (1 << (i - 1)), l + dis[u][i], i));
				}
		}
	}
}




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(t);
	while (t--) {
		read(n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				read(dis[i][j]);

		dijstra();

		println(rans);
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

