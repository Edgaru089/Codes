/*
DOCUMENT CODE "20180204-luogu3372.cpp"
CREATION DATE 2018-02-04
SIGNATURE CODE_20180204_LUOGU3372
TOPIC Ïß¶ÎÊ÷Ä£°å
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180204_LUOGU3372

#include <cstdlib>
#include <iostream>
using namespace std;

struct node {
	int left, right;
	int sum, lazy;
	node* lson, *rson;
};

int n, m;
int d[100001];
node pool[200001], *root;
int top;

void build(int left = 1, int right = n, node*& p = root) {
	p = &pool[++top];
	p->left = left;
	p->right = right;
	p->sum = p->lazy = 0;
	if (left == right) {
		p->lson = p->rson = NULL;
		p->sum = d[left];
	}
	else {
		p->lson
	}
}


int main(int argc, char* argv[]) {

	return 0;
}

#endif

