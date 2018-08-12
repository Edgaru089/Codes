/*
DOCUMENT NAME "20180811-bnds0747.cpp"
CREATION DATE 2018-08-11
SIGNATURE CODE_20180811_BNDS0747
COMMENT 单词（TJOI2013）
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180811_BNDS0747

#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;

constexpr int MaxN = 200 + 10, MaxTL = 1000000 + 10;

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	ungetc(c, stdin);
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
	int isword;
	node* next[26];
	node* fail;
};

node* root;
node mem[MaxTL], *memtop = mem;
#define ALLOCATE (++memtop)

int n;
string str[MaxN];
int ans[MaxN];

void insert(const string& str, const int& id) {
	if (root == nullptr)
		root = ALLOCATE;
	node* p = root;
	for (char c : str) {
		int v = c - 'a';
		if (p->next[v] == nullptr)
			p->next[v] = ALLOCATE;
		p = p->next[v];
	}
	p->isword = id;
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

void run(const string& str) {
	node* p = root;
	for (const char& c : str) {
		p = p->next[c - 'a'];
		for (node* cur = p; cur != nullptr; cur = cur->fail)
			ans[p->isword]++;
	}
}


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		readstr(str[i]);
		insert(str[i], i);
	}

	build();

	for (int i = 1; i <= n; i++)
		run(str[i]);

	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);

	return 0;
}

#endif

