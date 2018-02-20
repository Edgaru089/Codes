/*
DOCUMENT CODE "20180204-luogu3372.cpp"
CREATION DATE 2018-02-04
SIGNATURE CODE_20180204_LUOGU3372
TOPIC 线段树模板
一个支持区间加和区间求和的线段树
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180204_LUOGU3372

#include <cstdlib>
#include <iostream>
using namespace std;

struct node {
	long long left, right;
	long long sum, lazy;
	node* lson, *rson;
};

int n, m;
long long d[100001];
node pool[200001], *root;
int top;

node* build(int left = 1, int right = n) {
	node* p = &pool[++top];
	p->left = left;
	p->right = right;
	p->sum = p->lazy = 0;
	if (left == right) {
		p->lson = p->rson = NULL;
		p->sum = d[left];
	}
	else {
		int mid = (left + right) / 2;
		p->lson = build(left, mid);
		p->rson = build(mid + 1, right);
		p->sum = p->lson->sum + p->rson->sum;
	}
	return p;
}

void pushdown(node* p) {
	p->sum += (p->right - p->left + 1)*p->lazy;
	if (p->left != p->right) {
		p->lson->lazy += p->lazy;
		p->rson->lazy += p->lazy;
	}
	p->lazy = 0;
}

void add(int left, int right, long long a, node* p = root) {
	if (p->left == left&&p->right == right) {
		p->lazy += a;
		return;
	}
	pushdown(p);
	if (p->lson->right >= right)
		add(left, right, a, p->lson);
	else if (p->rson->left <= left)
		add(left, right, a, p->rson);
	else {
		add(left, p->lson->right, a, p->lson);
		add(p->rson->left, right, a, p->rson);
	}
}

long long query(int left, int right, node* p = root) {
	if (p->left == left&&p->right == right) {
		pushdown(p);
		return p->sum;
	}
	pushdown(p);
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return query(left, p->lson->right, p->lson) +
		query(p->rson->left, right, p->rson);
}


int main(int argc, char* argv[]) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	root = build();
	int a, x, y, k;
	for (int i = 1; i <= m; i++) {
		cin >> a >> x >> y;
		if (a == 1) {
			cin >> k;
			add(x, y, k);
		}
		else if (a == 2) {
			cout << query(x, y) << endl;
		}
	}
	return 0;
}

#endif

