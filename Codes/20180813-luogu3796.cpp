/*
DOCUMENT NAME "20180813-luogu3796.cpp"
CREATION DATE 2018-08-13
SIGNATURE CODE_20180813_LUOGU3796
COMMENT 【模板】AC自动机（加强版）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180813_LUOGU3796

#include <cstdlib>
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

constexpr int MaxC = 150 + 10, MaxN = 1000000 + 10, MaxTL = 1000000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
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
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
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

struct node {
	int wordid;
	node* next[26];
	node* fail;
};

node* root;
node mem[MaxTL], *memtop = mem;
#define ALLOCATE (++memtop)

void insert(const string& str, int id) {
	if (root == nullptr)
		root = ALLOCATE;
	node* p = root;
	for (char c : str) {
		int v = c - 'a';
		if (p->next[v] == nullptr)
			p->next[v] = ALLOCATE;
		p = p->next[v];
	}
	p->wordid = id;
}

void build() {
	queue<node*> Q;
	root->fail = nullptr;

	for (int i = 0; i < 26; i++) {
		if (root->next[i] != nullptr) {
			root->next[i]->fail = root;
			Q.push(root->next[i]);
		}
		else
			root->next[i] = root;
	}

	while (!Q.empty()) {
		node* p = Q.front();
		Q.pop();
		for (int i = 0; i < 26; i++) {
			if (p->next[i] != nullptr) {
				p->next[i]->fail = p->fail->next[i];
				Q.push(p->next[i]);
			}
			else
				p->next[i] = p->fail->next[i];
		}
	}
}


struct strid {
	int cnt;
	int pos;
	string str;
};

struct stridcompare {
	bool operator () (const strid& x, const strid& y) {
		return (x.cnt > y.cnt) || (x.cnt == y.cnt&&x.pos < y.pos);
	}
};

strid ans[MaxC];

void run(const string& str) {
	node* p = root;
	for (const char& c : str) {
		p = p->next[c - 'a'];
		for (node* cur = p; cur != nullptr; cur = cur->fail) {
			if (p->wordid != 0)
				ans[p->wordid].cnt++;
		}
	}
}



int main(int argc, char* argv[]) {
	for (;;) {
		int n;
		read(n);
		if (n == 0)
			break;
		memtop = mem;
		memset(mem, 0, sizeof(mem));
		root = nullptr;
		for (int i = 1; i <= n; i++) {
			readstr(ans[i].str);
			insert(ans[i].str, i);
			ans[i].pos = i;
			ans[i].cnt = 0;
		}
		build();
		string str;
		readstr(str);
		run(str);
		sort(ans + 1, ans + n + 1, stridcompare());
		printf("%d\n", ans[1].cnt);
		for (int i = 1; i <= n; i++) {
			if (ans[i].cnt != ans[1].cnt)
				break;
			printf("%s\n", ans[i].str.c_str());
		}
	}

	return 0;
}

#endif

