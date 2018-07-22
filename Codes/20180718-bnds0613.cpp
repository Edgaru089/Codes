/*
DOCUMENT NAME "20180718-bnds0613.cpp"
CREATION DATE 2018-07-18
SIGNATURE CODE_20180718_BNDS0613
COMMENT 小K的农场
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180718_BNDS0613

#include <cstdlib>
#include <iostream>
#include <stack>
#include <cstring>
#include <chrono>
using namespace std;

const int infinity = 1e8;
const int MaxN = 20000 + 10, MaxM = 20000 + 10;

template<typename IntType>
IntType read() {
	IntType ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 1) + (ans << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}
template<typename IntType>
void read(IntType& val) { val = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { val = read<IntType>(); read(args...); }

int n, m;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

bool requireQ[MaxN];

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;

	if (len < 0)
		requireQ[u] = true;
}


template<typename ValType, int ArrSize = 31457280>
class queue {
public:
	queue() :leftnext(0), size(0) {}
	void push(const ValType& val) { arr[leftnext + size] = val; size++; }
	void pop() { if (size > 0) { leftnext++; size--; } if (size == 0)leftnext = 0; }
	ValType& front() { return arr[leftnext]; }
	void clear() { leftnext = size = 0; }
	bool empty() { return size <= 0; }
private:
	ValType arr[ArrSize];
	int leftnext, size;
};

queue<int> Q;
int dis[MaxN], inQcnt[MaxN];
bool inQ[MaxN];
chrono::high_resolution_clock cl;
chrono::time_point<chrono::high_resolution_clock> starttime;
bool spfa() {
	starttime = cl.now();
	for (int i = 1; i <= n; i++) {
		if (requireQ[i]) {
			Q.push(i);
			inQ[i] = true;
		}
	}
	while (!Q.empty()) {
		if ((cl.now() - starttime) > chrono::milliseconds(800))
			return false;
		int u = Q.front(); Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				inQcnt[v]++;
				if (inQcnt[v] > n)
					return false;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
	return true;
}


int op, x, y, z;
int main(int argc, char* argv[]) {

	read(n, m);
	for (int i = 1; i <= m; i++) {
		read(op);
		if (op == 1) {
			read(x, y, z);
			addedge(x, y, -z);
		}
		else if (op == 2) {
			read(x, y, z);
			addedge(y, x, z);
		}
		else if (op == 3) {
			read(x, y);
			addedge(x, y, 0);
			addedge(y, x, 0);
		}
	}

	n++;
	for (int i = 1; i <= n - 1; i++) {
		addedge(n, i, 0);
	}

	if (!spfa())
		printf("No\n");
	else
		printf("Yes\n");

	return 0;
}

#endif

