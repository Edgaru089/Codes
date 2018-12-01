/*
 DOCUMENT NAME "20181117-luogu5021.cpp"
 CREATION DATE 2018-11-17
 SIGNATURE CODE_20181117_LUOGU5021
 COMMENT NOIP2018D1T3 ÈüµÀÐÞ½¨
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181117_LUOGU5021

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int MaxN = 50000 + 10;

int n, m;
int a, b, c;

struct node {
	int v, len;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v, int len) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}

int cnt = 0;
vector<int> vecs[MaxN];
int checkdfs(int u, int from, int limit) {
	vecs[u].clear();
	for (node* p = h[u]; p; p = p->next) {
		int v = p->v;
		if (v != from)
			vecs[u].push_back(checkdfs(v, u, limit));
	}
	sort(vecs[u].begin(), vecs[u].end, greater<int>());

	int l = 0, r.vecs.size();
	while (l < r) {
		if (vecs[l] + vecs[r] >= limit) {
			l++;
			r--;
			cnt++;
		} else
			r--;
	}
}

bool check(int limit) {
	cnt = 0;

}




int main(int argc, char* argv[]) {

	read(n);
	read(m);


	return 0;
}

#endif

