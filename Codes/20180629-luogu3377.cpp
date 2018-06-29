/*
DOCUMENT NAME "20180629-luogu3377.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU3377
COMMENT ¡¾Ä£°å¡¿×óÆ«Ê÷£¨¿É²¢¶Ñ£© / ×óÆ«Ê÷
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU3377

#include <cstdlib>
#include <iostream>
using namespace std;

const int MaxN = 100000 + 10, MaxM = 100000 + 10;

struct node {
	int val, id;
	node* lson, *rson;
	node* father;
};

node mem[MaxN], *top = mem;
#define ALLOCATE (*(top++))
node* root[MaxN];

node* findRoot(node* p) {
	if (p->father == nullptr)
		return p;
	else
		return findRoot(p->father);
}

bool needSwap(node* father, node* child) {
	if (father->val > child->val)
		return true;
	else if (father->val == child->val&&father->id > child->id)
		return true;
	else
		return false;
}

void merge(int idx, int idy) {
	node* x = findRoot(root[idx]), *y = findRoot(root[idy]);
	if (x == y)
		return;

}

int main(int argc, char* argv[]) {

	return 0;
}

#endif

