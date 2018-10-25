/*
 DOCUMENT NAME "20181025-noipT3-game.cpp"
 CREATION DATE 2018-10-25
 SIGNATURE CODE_20181025_NOIPT3_GAME
 COMMENT game.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181025_NOIPT3_GAME

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cassert>
#include <queue>
using namespace std;

#define FILENAME "game"

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

typedef long long ll;
typedef map<int, int> mi;
typedef map<int, int>::iterator mit;

const int MaxN = 1e5 + 10, MaxK = 2e9 + 10;

int type, n, l, s, t;
int a[MaxN], b[MaxN];

map<int, int> points;

enum pnttype {
	left,
	right
};

struct segmentpnt {
	segmentpnt() {}
	segmentpnt(int pos, pnttype type) :pos(pos), type(type) {}
	int pos;
	pnttype type;
};

segmentpnt pnt[MaxN];
int pntcnt;

bool cmp(segmentpnt x, segmentpnt y) {
	return x.pos < y.pos || (x.pos == y.pos&&x.type == pnttype::left);
}


struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[4 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int len) {
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

int ans = 0;
int dis[MaxN];
bool been[MaxN];
priority_queue<pair<int, int> > Q;
void dijstra() {
	been[s] = true;
	Q.push(make_pair(0, s));
	while (!Q.empty()) {
		int u = Q.top().second, dis = Q.top().first;
		Q.pop();
		if (been[u])
			continue;
		been[u] = true;
		for (node* p = h[u]; p; p = p->next) {
			int v = p->v;
			if (!been[v])
				Q.push(make_pair(dis + p->len, v));
		}
	}
	if (!been[t])
		ans = -1;
	else
		ans = dis[t];
}





int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	read(type); read(n); read(l); read(s); read(t);
	points.insert(make_pair(s, 0));
	points.insert(make_pair(t, 0));
	for (int i = 1; i <= n; i++) {
		read(a[i]); read(b[i]);
		if (type == 1) {
			points.insert(make_pair(a[i], 0));
			points.insert(make_pair(b[i], 0));
			pnt[++pntcnt] = segmentpnt(a[i], pnttype::left);
			pnt[++pntcnt] = segmentpnt(b[i], pnttype::right);
		} else {
			points.insert(make_pair(a[i], 0));
			points.insert(make_pair(b[i], 0));
			points.insert(make_pair(a[i] % l, 0));
			points.insert(make_pair(b[i] % l, 0));
			pnt[++pntcnt] = segmentpnt(a[i], pnttype::left);
			pnt[++pntcnt] = segmentpnt(b[i], pnttype::right);
		}
	}


	if (type == 0) { /* Easy */
		int k = 0;
		for (mit i = points.begin(); i != points.end(); i++)
			if (i->first > l)
				i->second = ++k;
			else
				i->second = points[i->first%l];

		for (int i = 1; i <= n; i++) {

		}

	} else { /* type == 1 (Hard) */
		assert(is_sorted(pnt + 1, pnt + pntcnt + 1, cmp));

	}




	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

