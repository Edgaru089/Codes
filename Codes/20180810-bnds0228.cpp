/*
DOCUMENT NAME "20180810-bnds0228.cpp"
CREATION DATE 2018-08-10
SIGNATURE CODE_20180810_BNDS0228
COMMENT µ¥´Ê½ÓÁú
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180810_BNDS0228

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

constexpr int MaxN = 100000 + 10, MaxL = 50 + 10;

int n;
char buf[MaxL];

struct node {
	bool valid;
	node* next[26];
};

node* root;
node mem[MaxN*MaxL], *memtop = mem;
#define ALLOCATE (++memtop)

void insert(string str, node*& p = root) {
	if (p == nullptr)
		p = ALLOCATE;
	if (str.length() == 0)
		p->valid = true;
	else
		insert(str.substr(1), p->next[str[0] - 'a']);
}

int count(node* p = root) {
	if (p == nullptr)
		return 0;
	else {
		int maxval = 0;
		for (int i = 0; i < 26; i++)
			maxval = max(maxval, count(p->next[i]) + p->valid);
		return maxval;
	}
}


int main(int argc, char* argv[]) {

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", buf);
		insert(buf);
	}

	printf("%d\n", count());

	return 0;
}

#endif

