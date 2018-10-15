/*
 DOCUMENT NAME "20181015-noipT2-Darksoul.cpp"
 CREATION DATE 2018-10-15
 SIGNATURE CODE_20181015_NOIPT2_DARKSOUL
 COMMENT darksoul.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181015_NOIPT2_DARKSOUL

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;

#define FILENAME "darksoul"

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
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

typedef long long ll;
const ll MaxN = 1000000 + 10;

ll n;

struct node {
	ll v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(ll u, ll v, ll len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}

stack<ll> S, Slen;
bool inS[MaxN];
ll last;
bool dfsloop(ll u, ll from) {
	if (inS[u]) {
		last = u;
		return false;
	}
	inS[u] = true;
	S.push(u);
	for (node* p = h[u]; p; p = p->next) {
		ll v = p->v;
		Slen.push(p->len);
		if (v != from)
			if (!dfsloop(v, u))
				return false;
		Slen.pop();
	}
	S.pop();
	inS[u] = false;
	return true;
}

ll loopsize, loop[MaxN];
bool inloop[MaxN];
ll nextlen[MaxN], prevlen[MaxN];

void makeloop() {
	dfsloop(1, 0);
	ll cur, prev;
	do {
		prev = loopsize;
		cur = S.top();
		S.pop();
		loop[++loopsize] = cur;
		inloop[cur] = true;
		prevlen[loopsize] = Slen.top();
		nextlen[prev] = prevlen[loopsize];
		Slen.pop();
	} while (cur != last);
	nextlen[loopsize] = nextlen[0];
}


ll loopval[MaxN];
ll ans = 0;
ll dfs(ll u, ll from) {
	ll mmax = 0, lmax = 0;
	for (node* p = h[u]; p; p = p->next) {
		if (p->v != from && !inloop[p->v]) {
			ll q = dfs(p->v, u) + p->len;
			if (q > mmax) {
				lmax = mmax;
				mmax = q;
			} else if (q > lmax)
				lmax = q;
		}
	}
	ans = max(ans, mmax + lmax);
	return mmax;
}

ll dis[MaxN];
void searchlp(ll i) {
	bool flag = true;
	for (ll j = 1; j <= loopsize; j++)
		dis[j] = 1e8;
	dis[i] = 0;
	for (ll j = i % loopsize + 1; flag || j != i; j = j % loopsize + 1) {
		flag = false;
		dis[j] = min(dis[j], dis[(j + loopsize - 2) % loopsize + 1] + prevlen[j]);
	}
	flag = true;
	for (ll j = i; flag || j != i; j = (j + loopsize - 2) % loopsize + 1) {
		flag = false;
		dis[j] = min(dis[j], dis[j%loopsize + 1] + nextlen[j]);
	}
	for (ll j = 1; j <= loopsize; j++) {
		if (j != i)
			ans = max(ans, loopval[i] + dis[j] + loopval[j]);
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

	read(n);
	for (ll i = 1; i <= n; i++) {
		ll u, v, len;
		read(u); read(v); read(len);
		addedge(u, v, len);
	}

	makeloop();

	for (ll i = 1; i <= loopsize; i++)
		loopval[loop[i]] = dfs(loop[i], 0);

	for (ll i = 1; i <= loopsize; i++)
		searchlp(i);

	println(ans + 1);


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

