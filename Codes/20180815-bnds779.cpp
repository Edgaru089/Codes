/*
DOCUMENT NAME "20180815-bnds779.cpp"
CREATION DATE 2018-08-15
SIGNATURE CODE_20180815_BNDS779
COMMENT B. 2018-8-15noip模拟测验（二）-最遥远的心 / 建图跑最短路
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180815_BNDS779

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cassert>
using namespace std;

constexpr int MaxN = 200 + 10, MaxM = 400;
constexpr int infinity = 1e8, halfInfinity = 400;

template<typename IntType = int>
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
	if (invflag)
		return -val;
	else
		return val;
}

template<>
char read<char>() {
	int c;
	while (isspace(c = getchar()) || iscntrl(c));
	return c;
}

template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

void readstr(string& str) {
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
}

#ifdef LOCAL
#define DEBUG(...) (printf(__VA_ARGS__))
#else
#define DEBUG(...)
#endif

int n, m;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
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


queue<int> Q;
bool inQ[MaxN];
int dis[MaxN];
void spfa() {
	for (int i = 1; i <= n; i++)
		dis[i] = infinity;
	dis[1] = 0;
	Q.push(1);
	inQ[1] = true;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop(); inQ[u] = false;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v, len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (!inQ[v]) {
					inQ[v] = true;
					Q.push(v);
				}
			}
		}
	}
}


unordered_map<string, int> pids;
int nextid = 2;

struct ansst {
	string name;
	int dis;
};

ansst ans[MaxN];

int main(int argc, char* argv[]) {

	pids.insert(make_pair("ZMC", 1));

	read(m);
	string a, b;
	int l;

	auto findOrAssign = [](const string& name)->int {
		auto k = pids.find(name);
		if (k == pids.end()) {
			pids.insert(make_pair(name, nextid++));
			return nextid - 1;
		}
		else
			return k->second;
	};

	for (int i = 1; i <= m; i++) {
		readstr(a);
		readstr(b);
		read(l);

		int u, v;

		// add edges in reverse manner
		v = findOrAssign(a);
		u = findOrAssign(b);

		if (l < 0)
			addedge(u, v, halfInfinity);
		else
			addedge(u, v, l);
	}

	n = pids.size();
	assert(nextid - 1 == n);

	spfa();

	int k = 0;
	for (auto& i : pids) {
		if (dis[i.second] >= infinity)
			ans[++k] = ansst{ i.first, infinity };
		else if (dis[i.second] >= halfInfinity)
			ans[++k] = ansst{ i.first, halfInfinity };
		else
			ans[++k] = ansst{ i.first, dis[i.second] };
	}
	assert(k == n);

	sort(ans + 1, ans + n + 1, [](const ansst& x, const ansst& y) {
		if (x.dis > y.dis)
			return true;
		else if (x.dis == y.dis&&x.name < y.name)
			return true;
		else
			return false;
	});

	printf("%s ", ans[1].name.c_str());
	if (ans[1].dis >= infinity)
		puts("-2\n");
	else if (ans[1].dis >= halfInfinity)
		puts("-1\n");
	else
		printf("%d\n", ans[1].dis);

	return 0;
}

#endif

