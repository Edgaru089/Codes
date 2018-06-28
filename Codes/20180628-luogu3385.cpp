/*
DOCUMENT NAME "20180628-luogu3385.cpp"
CREATION DATE 2018-06-28
SIGNATURE CODE_20180628_LUOGU3385
COMMENT 【模板】负环 / 负权优化版SPFA
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180628_LUOGU3385

#include <cstdlib>
#include <iostream>
//#include <queue>
#include <cstring>
using namespace std;

constexpr int infinity = 1000000000;
constexpr int MaxN = 2000 + 10, MaxM = 3000 + 10;

char buf[4 * 1024 * 1024], *S = buf;
#define GETCHAR (*(S++))
//#define GETCHAR getchar()
#define ZERO_MEMORY(array) memset(array,0,sizeof(array));

int read() {
	char c;
	int val = 0;
	bool minus = false;

	while (!isdigit(c = GETCHAR))
		if (c == '-')
			minus = true;

	do {
		val = val * 10 + (c - '0');
	} while (isdigit(c = GETCHAR));

	if (minus)
		return -val;
	else
		return val;
}

int read(int& val) {
	return val = read();
}

//template<typename Val, typename... Args>
//void read(Val& val, Args... args) {
//	read(val);
//	read(args...);
//}

struct node {
	int v, len;
	node* next;
};

node mem[MaxM * 2], *h[MaxN];
int top;
#define ALLOCATE (&mem[++top])

void addedge(int u, int v, int len) {
	node* tmp = ALLOCATE;
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
}

template<typename Type, int Size = MaxN * MaxM>
class queue {
public:
	queue() { clear(); }

	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	void pop() { left++; }
	bool empty() { return !(right >= left); }

private:

	int left, right;
	Type arr[Size];
};

int t;
int n, m;
int u, v, len;
bool start[MaxN];
int dis[MaxN], inQCnt[MaxN];
bool inQ[MaxN];
queue<int> Q;

bool spfa() {
	ZERO_MEMORY(inQCnt);
	ZERO_MEMORY(inQ);
	Q.clear();

	for (int i = 1; i <= n; i++) {
		dis[i] = infinity;
	}
	dis[1] = 0;
	Q.push(1);
	inQ[1] = true;
	inQCnt[1]++;

	while (!Q.empty()) {
		int u = Q.front(), v, len;
		Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				inQCnt[v]++;
				if (inQCnt[v] > n)
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

int main(int argc, char* argv[]) {

	fread(buf, 1, sizeof(buf), stdin);

	read(t);
	for (int l = 1; l <= t; l++) {

		top = 0;
		ZERO_MEMORY(h);
		ZERO_MEMORY(mem);
		ZERO_MEMORY(start);

		read(n); read(m);
		for (int i = 1; i <= m; i++) {
			read(u); read(v); read(len);
			if (len < 0) {
				addedge(u, v, len);
				start[u] = true;
			}
			else {
				addedge(u, v, len);
				addedge(v, u, len);
			}
		}

		if (spfa())
			printf("N0\n");
		else
			printf("YE5\n");

	}

	return 0;
}

#endif

