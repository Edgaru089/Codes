/*
 DOCUMENT NAME "20181002-bndsoj0454.cpp"
 CREATION DATE 2018-10-02
 SIGNATURE CODE_20181002_BNDSOJ0454
 COMMENT #454. 间谍网络
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181002_BNDSOJ0454

#include <cstdlib>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 1e4 + 10, MaxM = 1e5 + 10;

#define GETCHAR (getchar())
#define UNGETCHAR(c) (ungetc(c, stdin))

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

int n, m;
int weight[MaxN];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, node** h = ::h) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}


stack<int> S;
bool inS[MaxN];
int dfn[MaxN], sstime, low[MaxN];
int blockcnt, belong[MaxN];
int blockweight[MaxN];
vector<int> blocks[MaxN];
void dfs(int u) {
	dfn[u] = ++sstime;
	low[u] = sstime;
	S.push(u);
	inS[u] = true;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		int v = p->v;
		if (dfn[v] == 0) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if (inS[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		blockcnt++;
		int cnt;
		do {
			cnt = S.top(); S.pop();
			inS[cnt] = false;
			blocks[blockcnt].push_back(cnt);
			blockweight[blockcnt] = min(blockweight[blockcnt], weight[cnt]);
			belong[cnt] = blockcnt;
		} while (cnt != u);
	}
}


node* dag[MaxN];
int in[MaxN], out[MaxN];
void shrink() {
	for (int u = 1; u <= n; u++) {
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (belong[u] != belong[v]) {
				addedge(belong[u], belong[v], dag);
				in[belong[v]]++;
				out[belong[u]]++;
			}
		}
	}
}

int ans;
void dfsans(int u) {
	for (node* p = dag[u]; p; p = p->next)
		in[p->v]--;
	for (node* p = dag[u]; p; p = p->next)
		if (in[p->v] == 0)
			dfsans(p->v);
}


int main(int argc, char* argv[]) {

	int p;
	int u, v;

	read(n);
	for (int i = 1; i <= n; i++)
		weight[i] = blockweight[i] = infinity;
	read(p);
	for (int i = 1; i <= p; i++) {
		read(u, v);
		weight[u] = v;
	}
	read(m);
	for (int i = 1; i <= m; i++) {
		read(u, v);
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++) {
		if (weight[i] < infinity&&dfn[i] == 0)
			dfs(i);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0) {
			printf("NO\n%d\n", i);
			return 0;
		}
	}

	shrink();

	for (int i = 1; i <= blockcnt; i++) {
		if (in[i] == 0) {
			ans += blockweight[i];
			dfsans(i);
		}
	}

	printf("YES\n%d\n", ans);


	return 0;
}

#endif

