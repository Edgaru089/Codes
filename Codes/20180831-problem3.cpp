/*
DOCUMENT NAME "20180831-problem3.cpp"
CREATION DATE 2018-08-31
SIGNATURE CODE_20180831_PROBLEM3
COMMENT 3.³¤Í¾ÂÃÐÐ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180831_PROBLEM3

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

const int MaxN = 50 + 10, MaxM = 100 + 10, MaxSmallT = 10000 + 10;

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
string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = getchar()) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = getchar()) || isblank(c)));
	ungetc(c, stdin);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

template<typename Type, int Size = MaxM * MaxN>
class queue {
public:
	queue() { clear(); }
	void clear() { left = 1; right = 0; }
	Type front() { return arr[left]; }
	void push(Type x) { arr[++right] = x; }
	template<typename... Args>
	void emplace(Args... args) { push(Type(args...)); }
	void pop() { left++; }
	bool empty() { return !(right >= left); }
private:
	int left, right;
	Type arr[Size];
};

int n, m, t;

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
	p = ALLOCATE;
	p->v = u;
	p->len = len;
	p->next = h[v];
	h[v] = p;
}

void addrev(int x, int y, int z) { addedge(z, y, x); }

class Solve {
public:
	virtual bool solve() = 0;
};

class SmallT :public Solve {

	bool been[MaxN][MaxSmallT];
	struct st {
		st() {}
		st(int u, int time) :u(u), time(time) {}
		int u, time;
	};
	//       pntid  time
	queue<st, MaxN * 20 * MaxSmallT> Q;

public:
	bool solve() override {
		Q.clear();
		memset(been, 0, sizeof(been));
		been[1][0] = true;
		Q.emplace(1, 0);
		while (!Q.empty()) {
			int u = Q.front().u, t = Q.front().time;
			Q.pop();
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (!been[v][t + len]) {
					if (v == n && t + len == ::t)
						return true;
					been[v][t + len] = true;
					Q.emplace(v, t + len);
				}
			}
		}
		return false;
	}
};

class SmallNM :public Solve {
	struct st {
		st() {}
		st(int u, int time) :u(u), time(time) {}
		int u, time;
	};

	queue<st, MaxN * 20 * MaxSmallT> Q;

public:
	bool solve() override {
		Q.clear();
		Q.emplace(1, 0);
		while (!Q.empty()) {
			int u = Q.front().u, t = Q.front().time;
			Q.pop();
			for (node* p = h[u]; p != nullptr; p = p->next) {
				int v = p->v, len = p->len;
				if (v == n && t + len == ::t)
					return true;
				Q.emplace(v, t + len);
			}
		}
		return false;
	}
};

SmallT smallt;
SmallNM smallnm;

int main(int argc, char* argv[]) {

	int cnt;
	read(cnt);
	while (cnt--) {
		memset(h, 0, sizeof(h));
		memtop = mem;
		read(n, m, t);
		int u, v, len;
		for (int i = 1; i <= m; i++) {
			read(u, v, len);
			addedge(u + 1, v + 1, len);
		}

		Solve* solve;
		if (t <= MaxSmallT)
			solve = &smallt;
		else
			solve = &smallnm;

		if (solve->solve())
			printf("Possible\n");
		else
			printf("Impossible\n");
	}

	return 0;
}

#endif

