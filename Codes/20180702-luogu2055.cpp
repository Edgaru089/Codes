/*
DOCUMENT NAME "20180702-luogu2055.cpp"
CREATION DATE 2018-07-02
SIGNATURE CODE_20180702_LUOGU2055
COMMENT [ZJOI2009]假期的宿舍 / 二分图/最大流
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180702_LUOGU2055

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int infinity = 1e8;
const int MaxN = 5 * 50 + 2 + 10, MaxM = MaxN * MaxN + 2 * MaxN + 10;

struct node {
	int v, flow;
	node* rev;
	node* next;
};

node mem[MaxM * 4], *h[MaxN];
int top;
node* allocate() { return &mem[++top]; }

void addedge(int u, int v, int flow) {
	node* reg = allocate();
	reg->v = v;
	reg->flow = flow;
	reg->next = h[u];
	h[u] = reg;
	node* rev = allocate();
	rev->v = u;
	rev->flow = 0;
	rev->next = h[v];
	h[v] = rev;
	reg->rev = rev;
	rev->rev = reg;
}

int n, m;
int s, t;
int dep[MaxN];

template<typename Type, int Size = MaxN>
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

queue<int> Q;
bool bfs() {
	Q.clear();
	for (int i = 1; i <= n; i++)
		dep[i] = infinity;
	dep[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front(), v, flow;
		Q.pop();
		for (node* p = h[u]; p != nullptr; p = p->next) {
			v = p->v; flow = p->flow;
			if (flow > 0) {
				if (dep[v] == infinity) {
					dep[v] = dep[u] + 1;
					Q.push(v);
				}
			}
		}
	}
	if (dep[t] == infinity)
		return false;
	else
		return true;
}

node* cur[MaxN];
int dfs(int u, int limit) {
	if (limit == 0 || u == t)
		return limit;
	int total = 0, f;
	for (node*& p = cur[u]; p != nullptr && limit > 0; p = p->next) {
		int v = p->v; int& flow = p->flow;
		if (dep[v] == dep[u] + 1 && (f = dfs(v, min(limit, flow))) != 0) {
			flow -= f;
			p->rev->flow += f;
			total += f;
			limit -= f;
		}
	}
	return total;
}

int dinic() {
	int ans = 0;
	while (bfs()) {
		for (int i = 1; i <= n; i++)
			cur[i] = h[i];
		ans += dfs(s, infinity);
	}
	return ans;
}

#define GETPNT (++n)

int T;
int k;
int staycnt;
bool school[MaxN], stay[MaxN];
bool b;

int people[MaxN], bed[MaxN];

int main(int argc, char* argv[]) {

	cin >> T;
	for (int l = 1; l <= T; l++) {

		memset(h, 0, sizeof(h));
		memset(mem, 0, sizeof(mem));
		top = 0;
		n = 0;
		m = 0;
		s = 0;
		t = 0;
		memset(cur, 0, sizeof(cur));
		Q.clear();
		memset(dep, 0, sizeof(dep));
		k = 0;
		staycnt = 0;
		memset(school, 0, sizeof(school));
		memset(stay, 0, sizeof(stay));
		b = false;
		memset(people, 0, sizeof(people));
		memset(bed, 0, sizeof(bed));

		cin >> k;
		for (int i = 1; i <= k; i++) {
			people[i] = GETPNT;
			bed[i] = GETPNT;
		}
		s = GETPNT;
		t = GETPNT;
		staycnt = 0;
		for (int i = 1; i <= k; i++) {
			addedge(bed[i], t, 1);
		}
		for (int i = 1; i <= k; i++) {
			cin >> school[i];
			if (!school[i])
				staycnt++;
		}
		for (int i = 1; i <= k; i++) {
			cin >> stay[i]; stay[i] = !stay[i];
			if (school[i] && stay[i]) {
				addedge(people[i], bed[i], 1);
				staycnt++;
			}
		}
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= k; j++) {
				cin >> b;
				if (b&&school[j])
					addedge(people[i], bed[j], 1);
			}
			if (!school[i] || (school[i] && stay[i]))
				addedge(s, people[i], 1);
		}

		if (dinic() < staycnt)
			cout << "T_T" << endl;
		else
			cout << "^_^" << endl;

	}

	return 0;
}

#endif

