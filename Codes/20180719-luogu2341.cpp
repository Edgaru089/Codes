/*
DOCUMENT NAME "20180719-luogu2341.cpp"
CREATION DATE 2018-07-19
SIGNATURE CODE_20180719_LUOGU2341
COMMENT [HAOI2006]ÊÜ»¶Ó­µÄÅ£
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180719_LUOGU2341

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 10000 + 10, MaxM = 50000 + 10;

int n, m;

namespace graph {
	struct node {
		int v;
		node* next;
	};
	node* h[MaxN], *hdag[MaxN];
	node mem[4 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, node** h = graph::h) {
		node* p = ALLOCATE;
		p->v = v;
		p->next = h[u];
		h[u] = p;
	}
}

template<typename ValType, int Size = MaxN>
class stack {
public:
	void clear() { arrsize = 0; }
	void push(const ValType& val) { arr[arrsize++] = val; }
	void pop() { if (arrsize > 0)arrsize--; }
	ValType& top() { return arr[arrsize - 1]; }
	bool empty() { return arrsize == 0; }
private:
	ValType arr[Size];
	int arrsize;
};

//template<typename Type>
//Type min(const Type& x, const Type& y) {
//	return (x < y) ? x : y;
//}

namespace tarjanscc {
	using namespace graph;

	int dfn[MaxN], low[MaxN], stime;
	stack<int> S;
	bool inS[MaxN];
	int belong[MaxN], blockcnt;
	vector<int> blocks[MaxN];

	void dfs(int u) {
		dfn[u] = low[u] = ++stime;
		S.push(u); inS[u] = true;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (dfn[v] == 0) {
				dfs(v);
				low[u] = min(low[u], low[v]);
			}
			else if (inS[v])
				low[u] = min(low[u], dfn[v]);
		}
		if (low[u] == dfn[u]) {
			blockcnt++;
			int cnt;
			do {
				cnt = S.top();
				S.pop();
				belong[cnt] = blockcnt;
				blocks[blockcnt].push_back(cnt);
			} while (cnt != u);
		}
	}

	void shrink() {
		for (int u = 1; u <= n; u++) {
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v;
				if (belong[u] != belong[v]) {
					addedge(belong[u], belong[v], hdag);
				}
			}
		}
	}
}


int in[MaxN], out[MaxN];
void calcinout() {
	using namespace graph;
	using namespace tarjanscc;
	node** h = hdag;
	int n = blockcnt;
	for (int u = 1; u <= n; u++) {
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			in[v]++;
			out[u]++;
		}
	}
}



int main(int argc, char* argv[]) {
	using namespace graph;
	using namespace tarjanscc;

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}

	shrink();

	calcinout();

	int out0id = 0, out0cnt = 0;
	for (int i = 1; i <= blockcnt; i++) {
		if (out[i] == 0) {
			out0cnt++;
			out0id = i;
		}
	}

	if (out0cnt > 1)
		cout << 0 << endl;
	else
		cout << blocks[out0id].size() << endl;

	return 0;
}

#endif

