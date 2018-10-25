/*
 DOCUMENT NAME "20181016-noipT1-QingGong.cpp"
 CREATION DATE 2018-10-16
 SIGNATURE CODE_20181016_NOIPT1_QINGGONG
 COMMENT qinggong.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181016_NOIPT1_QINGGONG

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <queue>
using namespace std;

#define FILENAME "qinggong"

#ifdef LOCAL
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

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
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
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

const int infinity = 1e8;
const int MaxN = 500 + 10, MaxK = 100, MaxM = MaxN * (MaxN + 10) * MaxK;
const int MaxNX = (MaxN + 10) * MaxK;

int n, k, w, q;
int v[MaxK], a[MaxK];
bool ok[MaxN][MaxK];

int s, t;

struct node {
	int v, len;
	node* next;
};

node* h[MaxNX];
node mem[(unsigned int)(1.5*MaxM)], *memtop = mem;
#define ALLOCATE (++memtop)

void addedgeS(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}

void addedgeD(int u, int v, int len) {
	addedgeS(u, v, len);
	addedgeS(v, u, len);
}

queue<int> Q;
bool inQ[MaxN];
int dis[MaxN];
int spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	dis[s] = 0;
	Q.push(s);
	inQ[s] = true;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p; p = p->next) {
			int v = p->v;
			if (dis[v] > dis[u] + p->len) {
				dis[v] = dis[u] + p->len;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return dis[t];
}



// type == 0:  transform point;
// type == type+k: output point
int getid(int pillar, int type) {
	return (pillar - 1)*(2 * k + 1) + type + 1;
}


int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, bufferreadsize, in);

	read(n); read(k); read(w);
	s = n * (2 * k + 2) + 2;
	t = n * (2 * k + 2) + 3;
	for (int i = 1; i <= k; i++) {
		read(a[i]); read(v[i]);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			ok[i][j] = true;

	for (int i = 1; i <= q; i++) {
		int x, y;
		read(x); read(y);
		ok[x][y] = false;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++) {
			addedgeS(getid(i, j), getid(i, j + k), v[j]);
			addedgeS(getid(i, j), getid(i, 0), k);
			addedgeS(getid(i, 0), getid(i, j), 0);
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int l = 1; l <= k; l++)
				if (i != j)
					addedgeS(getid(i, l + k), getid(j, l), 0);

	for (int i = 1; i <= k; i++) {
		addedgeS(s, getid(1, i), 0);
		addedgeS(getid(n, i), t, 0);
	}

	int ans = spfa();
	if (ans < infinity)
		println(ans);
	else
		println(-1);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}


#endif

