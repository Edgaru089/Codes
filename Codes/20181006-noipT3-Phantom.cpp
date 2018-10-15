/*
 DOCUMENT NAME "20181006-noipT3-Phantom.cpp"
 CREATION DATE 2018-10-06
 SIGNATURE CODE_20181006_NOIPT3_PHANTOM
 COMMENT phantom.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181006_NOIPT3_PHANTOM

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cctype>
#include <algorithm>
using namespace std;

#define FILENAME "phantom"
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
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
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
	putstr(ENDLINE);
}

/******************** End of quickread template ********************/

typedef long long ll;
ll infinity = 1e16;
const int MaxN = 3000 + 10, MaxM = 70000 + 10;

int n, m;
int k[MaxN], kx[MaxN][MaxN];

struct node {
	int v;
	ll len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, ll len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}

ll dis[MaxN], borderdis[MaxN];
bool isgen[MaxN][MaxN];
int downcnt[MaxN], ok[MaxN], pushed[MaxN];

int drivecnt[MaxN];
int drives[MaxN][MaxN];

queue<int> Q;
bool inQ[MaxN];

void arriveborder(int u) {
	for (int j = 1; j <= drivecnt[u]; j++) {
		int v = drives[u][j];
		if (isgen[v][u]) {
			isgen[v][u] = false;
			borderdis[v] = max(borderdis[v], dis[u]);
			downcnt[v]++;
			if (downcnt[v] == k[v]) {
				ok[v] = true;
				dis[v] = max(dis[v], borderdis[v]);
				if (dis[v] < infinity) {
					Q.push(v);
					inQ[v] = true;
					pushed[v] = true;
				}
			}
		}
	}
}

void spfa() {

	Q.push(1);
	dis[1] = 0;
	arriveborder(1);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inQ[u] = false;
		arriveborder(u);
		for (node* p = h[u]; p; p = p->next) {
			int v = p->v;
			ll len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (ok[v]) {
					if (!inQ[v]) {
						Q.push(v);
						inQ[v] = true;
						pushed[v] = true;
					}
				}
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

	read(n); read(m);
	int u, v, w;
	for (int i = 1; i <= m; i++) {
		read(u); read(v); read(w);
		addedge(u, v, w);
	}
	for (int i = 1; i <= n; i++) {
		read(k[i]);
		for (int j = 1; j <= k[i]; j++) {
			read(kx[i][j]);
			isgen[i][kx[i][j]] = true;
			drives[kx[i][j]][++drivecnt[kx[i][j]]] = i;
		}
			dis[i] = infinity;
		if (k[i] == 0)
			ok[i] = true;
	}

	spfa();

	if (dis[n] < infinity)
		println(dis[n]);
	else
		println(-1);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

