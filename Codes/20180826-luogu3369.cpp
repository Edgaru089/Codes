/*
DOCUMENT NAME "20180826-luogu3369.cpp"
CREATION DATE 2018-08-26
SIGNATURE CODE_20180826_LUOGU3369
COMMENT 【模板】普通平衡树 / 替罪羊树
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180826_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int infinity = 1e8;
const int MaxN = 100000 + 10;

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
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

struct node {
	node* lson, *rson;
	int subnodecnt;
	int subcnt, val, valcnt;
};

node* root;
node mem[20 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

const double factor = 0.72;

node* wantrebuild = nullptr;

#define SUB_NODE_CNT(p) (p==nullptr?0:p->subnodecnt)
#define SUB_CNT(p) (p==nullptr?0:p->subcnt)

void update(node* p) {
	p->subnodecnt = SUB_NODE_CNT(p->lson) + SUB_NODE_CNT(p->rson) + 1;
	p->subcnt = SUB_CNT(p->lson) + SUB_CNT(p->rson) + p->valcnt;
}

void iterate(node* p, vector<pair<int, int>>& vec) {
	if (p == nullptr)
		return;
	iterate(p->lson, vec);
	if (p->valcnt > 0)
		vec.push_back(make_pair(p->val, p->valcnt));
	iterate(p->rson, vec);
}

void _rebuild(node*& p, vector<pair<int, int>>& vec, int left, int right) {
	if (left > right)
		return;
	if (p == nullptr)
		p = ALLOCATE;
	int mid = (left + right) / 2;
	p->val = vec[mid].first;
	p->valcnt = vec[mid].second;
	_rebuild(p->lson, vec, left, mid - 1);
	_rebuild(p->rson, vec, mid + 1, right);
	update(p);
}

void rebuild(node* p) {
	// pair<val, valcnt>
	vector<pair<int, int>> nodes;
	nodes.push_back(make_pair(0, 0));
	iterate(p, nodes);
	p->lson = p->rson = nullptr;
	_rebuild(p, nodes, 1, nodes.size() - 1);
}

void insert(int val, node*& p = root) {
	if (p == nullptr) {
		p = ALLOCATE;
		p->val = val;
		p->valcnt = 1;
	}
	else {
		if (val == p->val)
			p->valcnt++;
		else if (val < p->val)
			insert(val, p->lson);
		else // val > p->val
			insert(val, p->rson);
	}
	update(p);

	if (SUB_NODE_CNT(p->lson) > p->subnodecnt*factor)
		wantrebuild = p;
	if (SUB_NODE_CNT(p->rson) > p->subnodecnt*factor)
		wantrebuild = p;

	if (p == root && wantrebuild != nullptr) {
		rebuild(wantrebuild);
		wantrebuild = nullptr;
	}
}

void erase(int val, node* p = root) {
	if (val == p->val)
		p->valcnt--;
	else if (val < p->val)
		erase(val, p->lson);
	else // val > p->val
		erase(val, p->rson);
	update(p);
}

int getrank(int val, node* p = root) {
	if (p == nullptr)
		return 1;
	else if (val == p->val)
		return SUB_CNT(p->lson) + 1;
	else if (val < p->val)
		return getrank(val, p->lson);
	else // val > p->val
		return getrank(val, p->rson) + SUB_CNT(p->lson) + p->valcnt;
}

int getkth(int k, node* p = root) {
	if (k <= SUB_CNT(p->lson))
		return getkth(k, p->lson);
	else if (k <= SUB_CNT(p->lson) + p->valcnt)
		return p->val;
	else // k > subsize(p->lson)+subsize(p->val)
		return getkth(k - SUB_CNT(p->lson) - p->valcnt, p->rson);
}

int getprecessor(int k) {
	int ans = -infinity;
	node* p = root;
	while (p != nullptr) {
		if (p->valcnt > 0 && p->val < k)
			ans = max(ans, p->val);
		if (p->val >= k)
			p = p->lson;
		else
			p = p->rson;
	}
	return ans;
}

int getsucessor(int k) {
	int ans = infinity;
	node* p = root;
	while (p != nullptr) {
		if (p->valcnt > 0 && p->val > k)
			ans = min(ans, p->val);
		if (p->val <= k)
			p = p->rson;
		else
			p = p->lson;
	}
	return ans;
}


int n;
int k, x;


int main(int argc, char* argv[]) {

	read(n);
	for (int i = 1; i <= n; i++) {
		read(k, x);
		if (k == 1)
			insert(x);
		else if (k == 2)
			erase(x);
		else if (k == 3)
			printf("%d\n", getrank(x));
		else if (k == 4)
			printf("%d\n", getkth(x));
		else if (k == 5)
			printf("%d\n", getprecessor(x));
		else if (k == 6)
			printf("%d\n", getsucessor(x));
	}

	return 0;
}

#endif

