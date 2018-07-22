/*
DOCUMENT NAME "20180715-bnds0722-after.cpp"
CREATION DATE 2018-07-15
SIGNATURE CODE_20180715_BNDS0722_AFTER
COMMENT 2018-7-15基础测验（三）-密码 考试后重写
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180715_BNDS0722_AFTER

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

const int infinity = 1e8;
const ll MaxS = 100000 + 10;
const ll MaxM = MaxS * MaxS + 10;

struct node {
	char max;
	int maxid;
	int left, right;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxS], *memtop = mem;
#define ALLOCATE (++memtop)

void updatemax(node* p) {
	if (p->lson == nullptr || p->rson == nullptr)
		return;
	if (p->lson->max > p->rson->max) {
		p->max = p->lson->max;
		p->maxid = p->lson->maxid;
	}
	else {
		p->max = p->rson->max;
		p->maxid = p->rson->maxid;
	}
}

void build(char str[], int left, int right, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right) {
		p->max = str[left + 1];
		p->maxid = left;
		p->lson = p->rson = nullptr;
	}
	else {
		int mid = (left + right) / 2;
		build(str, left, mid, p->lson);
		build(str, mid + 1, right, p->rson);
		updatemax(p);
	}
}

void modifypoint(int pos, char val, node* p = root) {
	if (p->left == pos && p->right == pos)
		p->max = val;
	else {
		if (p->lson->right >= pos)
			modifypoint(pos, val, p->lson);
		else if (p->rson->left <= pos)
			modifypoint(pos, val, p->rson);
		updatemax(p);
	}
}

pair<char, int> query(int left, int right, node* p = root) {
	if (p->left == left && p->right == right)
		return make_pair(p->max, p->maxid);
	else {
		if (p->lson->right >= right)
			return query(left, right, p->lson);
		else if (p->rson->left <= left)
			return query(left, right, p->rson);
		else
			return max(query(left, p->lson->right, p->lson),
					   query(p->rson->left, right, p->rson));
	}
}

ll m;
char str[MaxS];
int len;

int main(int argc, char* argv[]) {

	cin >> m >> str;
	len = strlen(str);

	build(str, 1, len);

	for (int i = 1; i <= len && m > 0; i++) {
		
	}

	return 0;
}

#endif

