/*
DOCUMENT NAME "20180716-bnds0719.cpp"
CREATION DATE 2018-07-16
SIGNATURE CODE_20180716_BNDS0719
COMMENT µçÂ·Î¬ÐÞ
*/

/*
INPUT
1
3 5
\\/\\
\\///
/\\\\
OUTPUT
1
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180716_BNDS0719

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

const int infinity = 1e8;
const int MaxN = 2 * 502 * 502 + 10, MaxM = 4 * 502 * 502 + 10;
const int MaxR = 500 + 10, MaxC = 500 + 10;

char readbuf[5000000], *readtop = readbuf;
#define GETCHAR *(readtop++)

template<typename IntType = int>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = GETCHAR));
	do {
		ans = (ans << 3) + (ans << 1) + c - '0';
	} while (isdigit(c = GETCHAR));
	return ans;
}

template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

void getline(char str[]) {
	int off = 0;
	while (!isprint(str[off] = GETCHAR));
	off++;
	while ((str[off] = GETCHAR) != '\n')
		off++;
	str[off] = '\0';
}

int n = MaxN, m = MaxM;
int s;
int dis[MaxN];

int r, c;
char str[MaxR][MaxC];

int makenode(int x, int y) {
	return x * (c + 1) + y;
}

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[MaxM], *memtop = mem;
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

namespace dijstra {
	typedef pair<int, int> pii;
	int anscnt;
	deque<pii> Q;
	void run() {
		Q.clear();
		for (int i = 1; i <= n; i++)
			dis[i] = infinity;
		Q.push_back(make_pair(0, s));
		dis[s] = 0;
		anscnt = 1;
		while (!Q.empty() && anscnt < n) {
			pii t = Q.front(); Q.pop_front();
			int u = t.second, d = t.first;
			if (u != s && dis[u] == infinity) {
				dis[u] = d;
				anscnt++;
				if (u == makenode(r + 1, c + 1))
					return;
			}
			else if (dis[u] < d)
				continue;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (dis[v] == infinity)
					if (len == 0)
						Q.push_front(make_pair(d + len, v));
					else
						Q.push_back(make_pair(d + len, v));
			}
		}
	}
}

namespace spfa {
	queue<int> Q;
	bool inQ[MaxN];
	void run() {
		while (!Q.empty())
			Q.pop();
		for (int i = 1; i <= n; i++)
			inQ[i] = false;
		for (int i = 1; i <= n; i++)
			dis[i] = infinity;
		dis[s] = 0;
		Q.push(s);
		inQ[s] = true;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop(); inQ[u] = false;
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (dis[v] > dis[u] + len) {
					dis[v] = dis[u] + len;
					if (!inQ[v]) {
						inQ[v] = true;
						Q.push(v);
					}
				}
			}
		}
	}
}


int main(int argc, char* argv[]) {

	fread(readbuf, 1, sizeof(readbuf) - 1, stdin);

	int t;
	read(t);

	while (t--) {

		read(r, c);
		for (int i = 1; i <= r; i++)
			getline((char*)(str[i] + 1));

		for (int i = 0; i <= makenode(r + 1, c + 1); i++)
			h[i] = nullptr;
		memtop = mem;

		if (r % 2 != c % 2) {
			printf("NO SOLUTION\n");
			continue;
		}

		s = makenode(1, 1);
		n = makenode(r + 1, c + 1);
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++) {
				addedge(makenode(i, j), makenode(i + 1, j + 1), str[i][j] != '\\');
				addedge(makenode(i, j + 1), makenode(i + 1, j), str[i][j] != '/');
			}
		}

		dijstra::run();


		printf("%d\n", dis[makenode(r + 1, c + 1)]);
	}

	return 0;
}

#endif

