/*
DOCUMENT NAME "20180808-bnds0445.cpp"
CREATION DATE 2018-08-08
SIGNATURE CODE_20180808_BNDS0445
COMMENT ÉñÃØµÄ±ðÊû / ×´Ñ¹BFS
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180808_BNDS0445

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

constexpr int infinity = 1e8;
constexpr int MaxN = 10 + 6, MaxM = MaxN * MaxN, MaxK = MaxM, MaxState = 1 << MaxN;

int n, m, k;

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}

vector<int> switches[MaxN];
int dis[MaxState][MaxN];
struct que {
	int state;
	int cur;
};
queue<que> Q;
bool inQ[MaxState][MaxN];

void bfs() {
	for (int i = 0; i < (1 << (n + 3)); i++)
		for (int j = 1; j <= n; j++)
			dis[i][j] = infinity;
	dis[2][1] = 0;
	Q.push(que{ 2, 1 });
	inQ[2][1] = true;
	while (!Q.empty()) {
		que cur = Q.front();
		Q.pop(); inQ[cur.state][cur.cur] = false;
		int u = cur.cur;
		int state = cur.state;
		if (state == (1 << n) && u == n) {
			cout << "Mr. Black needs " << dis[state][u] << " steps." << endl;
			exit(0);
		}
		// lamp switches
		for (int v : switches[u]) {
			int statenext = (state ^ (1 << v));
			if (dis[statenext][u] > dis[state][u] + 1) {
				dis[statenext][u] = dis[state][u] + 1;
				if (!inQ[statenext][u]) {
					inQ[statenext][u] = true;
					Q.push(que{ statenext, u });
				}
			}
		}
		// naviagate across rooms
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if ((state&(1 << v)) != 0 && dis[state][v] > dis[state][u] + 1) {
				dis[state][v] = dis[state][u] + 1;
				if (!inQ[state][v]) {
					inQ[state][v] = true;
					Q.push(que{ state, v });
				}
			}
		}
	}
}



int main(int argc, char* argv[]) {

	cin >> n >> m >> k;
	int u, v;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		addedge(u, v);
	}
	for (int i = 1; i <= k; i++) {
		cin >> u >> v;
		switches[u].push_back(v);
	}

	bfs();

	cout << "Poor Mr. Black! No sleep tonight!" << endl;


	return 0;
}

#endif

