/*
DOCUMENT NAME "20180906-now185B.cpp"
CREATION DATE 2018-09-06
SIGNATURE CODE_20180906_NOW185B
COMMENT B-Â·¾¶ÊýÁ¿
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180906_NOW185B

#include <cstdlib>
#include <iostream>
using namespace std;

int n, k;
struct node {
	int v;
	node* next;
};
node* h[100];
node mem[10000], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
}

int ans = 0;
void dfs(int u, int step = 0) {
	if (u == n&&step == k)
		ans++;
	if (step >= k)
		return;
	for (node* p = h[u]; p != nullptr; p = p->next) {
		dfs(p->v, step + 1);
	}
}


int main(int argc, char* argv[]) {

	cin >> n >> k;
	int x;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> x;
			if (x == 1)
				addedge(i, j);
		}

	dfs(1);

	cout << ans << endl;

	return 0;
}

#endif

