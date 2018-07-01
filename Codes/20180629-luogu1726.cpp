/*
DOCUMENT NAME "20180629-luogu1726.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU1726
COMMENT 上白泽慧音 / Tarjan强连通分量
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU1726

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 5000 + 10, MaxM = 50000 + 10;

int n, m;

struct node {
	int v;
	node* next;
};

node mem[2 * MaxM], *top = mem, *h[MaxN];
#define ALLOCATE (top++)

#define SINGLE 1
#define DOUBLE 2
void addedge(int u, int v, int type) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	if (type == DOUBLE) {
		p = ALLOCATE;
		p->v = u;
		p->next = h[v];
		h[v] = p;
	}
}


vector<int> blocks[MaxN];
int blockCnt;

int stime, dfn[MaxN], low[MaxN];
stack<int> S;
bool inS[MaxN];
void dfs(int u) {
	S.push(u); inS[u] = true;
	dfn[u] = low[u] = ++stime;
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
		int cnt;
		blockCnt++;
		do {
			cnt = S.top(); S.pop(); inS[cnt] = false;
			blocks[blockCnt].push_back(cnt);
		} while (cnt != u);
	}

}



int main(int argc, char* argv[]) {

	int u, v, t;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> t;
		addedge(u, v, t);
	}

	for (int i = 1; i <= n; i++) {
		if (dfn[i] == 0)
			dfs(i);
	}

	vector<int>* maxVec = nullptr;
	for (int i = 1; i <= blockCnt; i++) {
		if (maxVec == nullptr)
			maxVec = &blocks[i];
		else if (maxVec->size() < blocks[i].size())
			maxVec = &blocks[i];
	}

	sort(maxVec->begin(), maxVec->end());

	cout << maxVec->size() << endl;
	for (int i = 0; i < maxVec->size(); i++)
		if (i == 0)
			cout << (*maxVec)[i];
		else
			cout << " " << (*maxVec)[i];
	cout << endl;

	return 0;
}

#endif

