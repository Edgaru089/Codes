/*
DOCUMENT NAME "20180701-luogu3369.cpp"
CREATION DATE 2018-07-01
SIGNATURE CODE_20180701_LUOGU3369
COMMENT ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / Treap
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180701_LUOGU3369

#include <cstdlib>
#include <iostream>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10;

struct node {
	int val, valcnt;
	int cnt;
	int priority;
	node* lson, *rson, *fa;
};

#define CNT(p) (p == nullptr ? 0 : p->cnt)

node mem[MaxN], *top = mem;
#define ALLOCATE (++top)
node* root, *rf;


void insert(int val, node*& p = root, node* fa = rf) {
	if (p == nullptr) {
		p = ALLOCATE;
		p->val = val; p->valcnt = 1;
		p->cnt = 1;
		p->priority = rand();
		p->lson = p->rson = nullptr;
		p->fa = fa;
	}
	else if (val == p->val) {
		p->valcnt++;
		p->cnt++;
	}
	else if (val < p->val) {
		insert(val, p->lson, p);
		p->cnt = CNT(p->lson) + CNT(p->rson) + p->valcnt;
	}
	else if (val > p->val) {
		insert(val, p->rson, p);
		p->cnt = CNT(p->lson) + CNT(p->rson) + p->valcnt;
	}
}




int main(int argc, char* argv[]) {

	rf = ALLOCATE;
	rf->priority = -infinity;
	
	return 0;
}

#endif

