/*
DOCUMENT CODE "20180422-luogu3372.cpp"
CREATION DATE 2018-04-22
SIGNATURE CODE_20180422_LUOGU3372
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180422_LUOGU3372

#include <cstdlib>
#include <iostream>
using namespace std;

struct st {
	long long sum, lazy;
	int left, right;
	st* lson, *rson;
};

st pool[200001], *h[100001];
int top;
long long d[100001], n;
st* root;

int m;
long long x, y, k;

void pushDown(st* p) {
	if (p == NULL)
		return;
	if (p->lson != NULL)
		p->lson->lazy += p->lazy;
	if (p->rson != NULL)
		p->rson->lazy += p->lazy;
	p->sum += (p->right - p->left + 1)*p->lazy;
	p->lazy = 0;
}

void build(int left = 1, int right = n, st*& p = root) {
	p = &pool[++top];
	p->left = left;
	p->right = right;
	p->lazy = 0;
	if (left == right) {
		p->sum = d[left];
		p->lson = p->rson = NULL;
	}
	else {
		build(left, (left + right) / 2, p->lson);
		build((left + right) / 2 + 1, right, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}
}

void change(int left, int right, long long val, st* p = root) {
	if (p->left == left&&p->right == right) {
		p->lazy += val;
		return;
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	if (p->lson->right >= right) {
		change(left, right, val, p->lson);
	}
	else if (p->rson->left <= left) {
		change(left, right, val, p->rson);
	}
	else {
		change(left, p->lson->right, val, p->lson);
		change(p->rson->left, right, val, p->rson);
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	p->sum = p->lson->sum + p->rson->sum;
}

long long query(int left, int right, st* p = root) {
	if (p->left == left&&p->right == right) {
		pushDown(p);
		return p->sum;
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	if (p->rson->left <= left) {
		return query(left, right, p->rson);
	}
	else if (p->lson->right >= right) {
		return query(left, right, p->lson);
	}
	else {
		return query(left, p->lson->right, p->lson) +
			query(p->rson->left, right, p->rson);
	}
}


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d[i];
	
	build();

	for (int i = 1; i <= m; i++) {
		cin >> k;
		if (k == 1) {
			cin >> x >> y >> k;
			change(x, y, k);
		}
		else if (k == 2) {
			cin >> x >> y;
			cout << query(x, y) << endl;
		}
	}

	return 0;
}

#endif

