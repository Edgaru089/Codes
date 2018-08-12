/*
DOCUMENT NAME "20180810-bnds0747.cpp"
CREATION DATE 2018-08-10
SIGNATURE CODE_20180810_BNDS0747
COMMENT 单词（TJOI2013） / AC自动机
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180810_BNDS0747

#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

constexpr int MaxN = 1000000 + 10, MaxTL = 1000000 + 10;

struct node {
	int isword;
	node* next[26];
	node* fail;
};

node* root;
node mem[MaxTL], *memtop = mem;
#define ALLOCATE (++memtop)

void insert(const string& str) {
	if (root == nullptr)
		root = ALLOCATE;
	node* p = root;
	for (char c : str) {
		int v = c - 'a';
		if (p->next[v] == nullptr)
			p->next[v] = ALLOCATE;
		p = p->next[v];
	}
	p->isword++;
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

int run(const string& str) {
	int ans = 0;
	node* p = root;
	for (const char& c : str) {
		p = p->next[c - 'a'];
		for (node* cur = p; cur != nullptr&&p->isword != -1; cur = cur->fail) {
			ans += p->isword;
			p->isword = -1;
		}
	}
	return ans;
}



int main(int argc, char* argv[]) {
	int n;
	string s;

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s;
		insert(s);
	}

	build();

	cin >> s;
	cout << run(s) << endl;

	return 0;
}

#endif

