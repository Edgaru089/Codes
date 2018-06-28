/*
DOCUMENT NAME "20180628-luogu3387.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3387
COMMENT 【模板】缩点 / Tarjan强连通分量 + 记忆化搜索
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3387

#include <cstdlib>
#include <iostream>
using namespace std;

constexpr int infinity = 1000000000;
constexpr int MaxN = 10000 + 10, MaxM = 100000 + 10;

struct node {
	int v;
	node* next;
};

node mem[MaxM * 2], *h[MaxN];
int top;
#define ALLOCATE (&mem[++top])

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}


int main(int argc, char* argv[]) {



	return 0;
}

#endif

