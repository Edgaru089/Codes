/*
DOCUMENT CODE "20180505-luogu3373.cpp"
CREATION DATE 2018-05-05
SIGNATURE CODE_20180505_LUOGU3373
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180505_LUOGU3373

#include <cstdlib>
#include <iostream>
using namespace std;

struct node {
	int left, right;
	int sum;
	int lazyA, lazyM;
	node* lson, *rson;
};

node pool[200001];
int top;
node* root;

int n, m, p;
int d[100001];

void build(int left = 1, int right = n, node*& p = root) {
	p = &pool[++top];
	p->lazyM = 1;
	p->left = left;
	p->right = right;
	if (left == right) {
		p->sum = d[left];
	}
	else {
		int mid = (left + right) / 2;
		build(left, mid, p->lson);
		build(mid + 1, right, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}
}

void pushDown(node* p) {
	if (p == nullptr)
		return;

	if (p->lson != nullptr) {
		p->lson->lazyA = (p->lson->lazyA*p->lazyM + p->lazyA) % ::p;
		p->lson->lazyM *= p->lazyM; p->lson->lazyM %= ::p;
	}
	if (p->rson != nullptr) {
		p->rson->lazyA = (p->rson->lazyA*p->lazyM + p->lazyA) % ::p;
		p->rson->lazyM *= p->lazyM; p->rson->lazyM %= ::p;
	}
	p->sum = (p->sum*p->lazyM + p->lazyA*(p->right - p->left + 1)) % ::p;

	p->lazyA = 0;
	p->lazyM = 1;
}

void add(int left, int right, int val, node* p = root) {
	if (p->left == left&&p->right == right) {
		pushDown(p);
		p->lazyA += val;
		return;
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	if (p->lson->right >= right)
		add(left, right, val, p->lson);
	else if (p->rson->left <= left)
		add(left, right, val, p->rson);
	else {
		add(left, p->lson->right, val, p->lson);
		add(p->rson->left, right, val, p->rson);
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	p->sum = (p->lson->sum + p->rson->sum) % ::p;
}

void multply(int left, int right, int val, node* p = root) {
	if (p->left == left&&p->right == right) {
		pushDown(p);
		p->lazyM *= val;
		p->lazyA *= val;
		return;
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	if (p->lson->right >= right)
		multply(left, right, val, p->lson);
	else if (p->rson->left <= left)
		multply(left, right, val, p->rson);
	else {
		multply(left, p->lson->right, val, p->lson);
		multply(p->rson->left, right, val, p->rson);
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	p->sum = (p->lson->sum + p->rson->sum) % ::p;
}

int query(int left, int right, node* p = root) {
	if (p->left == left&&p->right == right) {
		pushDown(p);
		return p->sum % ::p;
	}
	pushDown(p);
	pushDown(p->lson);
	pushDown(p->rson);
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return (query(left, p->lson->right, p->lson) + query(p->rson->left, right, p->rson)) % ::p;
}

int main(int argc, char* argv[]) {

	cin >> n >> m >> p;
	for (int i = 1; i <= n; i++)
		cin >> d[i];

	build();

	int t, x, y, k;
	for (int i = 1; i <= m; i++) {
		cin >> t;
		if (t == 1) {
			cin >> x >> y >> k;
			multply(x, y, k);
		}
		else if (t == 2) {
			cin >> x >> y >> k;
			add(x, y, k);
		}
		else if (t == 3) {
			cin >> x >> y;
			cout << query(x, y) << endl;
		}
	}

	return 0;
}

#endif

