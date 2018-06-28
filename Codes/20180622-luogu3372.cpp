/*
DOCUMENT CODE "20180622-luogu3372.cpp"
CREATION DATE 2018-06-22
SIGNATURE CODE_20180622_LUOGU3372
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180622_LUOGU3372

#include <cstdlib>
#include <iostream>
using namespace std;


class SegmentTree {
public:

	SegmentTree() :root(nullptr) {}

	struct node {
		int left, right;
		long long sum;
		long long lazy;
		node* lson, *rson;
	};

	node* allocate() { return &mem[++top]; }

	void build(long long d[], int n) {
		_build(d, root, 1, n);
	}

	void add(int left, int right, int val) {
		_add(left, right, val, root);
	}

	long long query(int left, int right) {
		return _query(left, right, root);
	}


private:

	void _build(long long d[], node*& p, int left, int right) {
		p = allocate();
		p->left = left;
		p->right = right;
		p->lazy = 0;
		if (left == right) {
			p->sum = d[left];
			p->lson = p->rson = nullptr;
		}
		else {
			int mid = (left + right) / 2;
			_build(d, p->lson, left, mid);
			_build(d, p->rson, mid + 1, right);
			p->sum = p->lson->sum + p->rson->sum;
		}
	}

	static void pushDown(node* p) {
		if (p == nullptr)
			return;
		if (p->lazy == 0)
			return;
		p->sum += p->lazy*(p->right - p->left + 1);
		if (p->lson != nullptr)
			p->lson->lazy += p->lazy;
		if (p->rson != nullptr)
			p->rson->lazy += p->lazy;
		p->lazy = 0;
	}

	void _add(int left, int right, long long val, node* p) {
		pushDown(p);
		if (p->left == left && p->right == right) {
			p->lazy += val;
			return;
		}
		if (p->lson->right >= right)
			_add(left, right, val, p->lson);
		else if (p->rson->left <= left)
			_add(left, right, val, p->rson);
		else {
			_add(left, p->lson->right, val, p->lson);
			_add(p->rson->left, right, val, p->rson);
		}
		pushDown(p);
		pushDown(p->lson);
		pushDown(p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}

	long long _query(int left, int right, node* p) {
		pushDown(p);
		pushDown(p->lson);
		pushDown(p->rson);
		if (p->left == left && p->right == right)
			return p->sum;
		if (p->lson->right >= right)
			return _query(left, right, p->lson);
		else if (p->rson->left <= left)
			return _query(left, right, p->rson);
		else
			return _query(left, p->lson->right, p->lson) + _query(p->rson->left, right, p->rson);
	}



	node mem[200050];
	int top;

	node* root;

};


SegmentTree tree;
int n, m;
long long d[100001];
int c, x, y;
long long k;


int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> d[i];

	tree.build(d, n);

	for (int i = 1; i <= m; i++) {
		cin >> c;
		if (c == 1) {
			cin >> x >> y >> k;
			tree.add(x, y, k);
		}
		else if (c == 2) {
			cin >> x >> y;
			cout << tree.query(x, y) << endl;
		}
	}

	return 0;
}

#endif

