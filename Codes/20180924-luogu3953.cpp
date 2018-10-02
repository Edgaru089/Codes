/*
 DOCUMENT NAME "20180924-luogu3953.cpp"
 CREATION DATE 2018-09-24
 SIGNATURE CODE_20180924_LUOGU3953
 COMMENT NOIP2017D1T3 逛公园
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180924_LUOGU3953

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10, MaxM = 200000 + 10;
const int MaxK = 50 + 10;

constexpr int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
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
string read<string>() {
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
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

char bufferwrite[buffersize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

template<typename IntType>
void println(IntType val) {
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

int t;
int n, m, k, p;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int len) {
	// reverse
	node* p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}


int dis[MaxN];
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii>> Q;
bool been[MaxN];
void dijstra() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	Q.push(make_pair(0, n));
	dis[n] = 0;
	while (!Q.empty()) {
		pii t = Q.top(); Q.pop();
		int u = t.second, d = t.first;
		if (been[u])
			continue;
		been[u] = true;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				Q.push(make_pair(d + len, v));
			}
		}
	}
}


int ans[MaxN][MaxK];
bool inStack[MaxN][MaxK];
bool ok;
int dfs(int u, int ks) {
	if (inStack[u][ks])
		ok = false;
	if (!ok)
		return -1;
	if (ans[u][ks] >= 0)
		return ans[u][ks];
	else {
		inStack[u][ks] = true;
		long long uans = 0;
		if (u == 1)
			uans = 1;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			int ext = ks + dis[u] - dis[v] + len;
			if (ext <= k) {
				uans += dfs(v, ext);
				if (uans > ::p)
					uans -= ::p;
				if (uans > ::p)
					uans %= ::p;
			}
			if (!ok)
				return -1;
		}
		inStack[u][ks] = false;
		return ans[u][ks] = uans;
	}
}



int main(int argc, char* argv[]) {
	fread(buffer, 1, buffersize, stdin);

	read(t);
	while (t--) {

		read(n, m, k, p);

		memset(h, 0, sizeof(h));
		memtop = mem;
		memset(ans, -1, sizeof(ans));
		memset(been, 0, sizeof(been));
		memset(inStack, 0, sizeof(inStack));

		int u, v, l;
		for (int i = 1; i <= m; i++) {
			read(u, v, l);
			addedge(u, v, l);
		}

		dijstra();

		ok = true;
		int rans = dfs(n, 0);
		if (ok)
			println(rans);
		else
			println(-1);

	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, stdout);

	return 0;
}

#endif

