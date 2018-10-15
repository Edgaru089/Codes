/*
 DOCUMENT NAME "20181002-bnds0777.cpp"
 CREATION DATE 2018-10-02
 SIGNATURE CODE_20181002_BNDS0777
 COMMENT #777. Frequent values
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181002_BNDS0777

#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
constexpr int MaxN = 100000 + 10;

#define GETCHAR (getchar())
#define UNGETCHAR(c) (ungetc(c, stdin))

template<typename IntType = int>   // 模板默认类型需要C++11
IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
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
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
void read(IntType& x) { x = read<IntType>(); }
template<typename IntType, typename... Args>     // 模板参数包需要C++11
void read(IntType& x, Args&... args) { x = read<IntType>(); read(args...); }

int n, q;

struct seginfo {
	seginfo() { lcolor = rcolor = llen = rlen = maxlen = 0; }
	seginfo(int i, int col) { left = right = i; lcolor = rcolor = col; llen = rlen = maxlen = 1; }
	seginfo(const seginfo& left, const seginfo& right) {
		lcolor = left.lcolor;
		rcolor = right.rcolor;
		this->left = left.left;
		this->right = right.right;
		llen = left.llen;
		rlen = right.rlen;
		maxlen = max(left.maxlen, right.maxlen);
		if (left.rcolor == right.lcolor) {
			int midlen = left.rlen + right.llen;
			maxlen = max(maxlen, midlen);
			if (left.llen == left.right - left.left + 1)
				llen = left.llen + right.llen;
			if (right.rlen == right.right - right.left + 1)
				rlen = right.rlen + left.rlen;
		}
	}
	int left, right;
	int lcolor, llen, rcolor, rlen;
	int maxlen;
};

struct node {
	int left, right;
	seginfo s;
	node* lson, *rson;
};

node* root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int d[], int left = 1, int right = n, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->s = seginfo(left, d[left]);
	else {
		int mid = (left + right) / 2;
		build(d, left, mid, p->lson);
		build(d, mid + 1, right, p->rson);
		p->s = seginfo(p->lson->s, p->rson->s);
	}
}

seginfo query(int left, int right, node* p = root) {
	if (p->left == left && p->right == right)
		return p->s;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return seginfo(query(left, p->lson->right, p->lson),
					   query(p->rson->left, right, p->rson));
}

int a[MaxN];
pii t[MaxN];

int x, y;

int main(int argc, char* argv[]) {

	read(n, q);
	for (int i = 1; i <= n; i++) {
		t[i] = make_pair(read(), i);
	}

	sort(t + 1, t + n + 1);
	int k = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || t[i - 1].first != t[i].first)
			k++;
		a[t[i].second] = k;
	}

	build(a);

	for (int i = 1; i <= q; i++) {
		read(x, y);
		printf("%d\n", query(x, y).maxlen);
	}

	return 0;
}

#endif

