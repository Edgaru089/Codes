/*
DOCUMENT CODE "20180527-luogu3369.cpp"
CREATION DATE 2018-05-27
SIGNATURE CODE_20180527_LUOGU3369
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180527_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

struct node {
	int val;
	int size, count;
	bool deleted;
	node* lson, *rson;
};

node pool[10001], *root;
int top;

const double factor = 0.72;

node* allocate() { return &pool[++top]; }

void update(node* p) {
	p->size = 0;
	p->count = 1;
	if (p->lson != nullptr) {
		p->size += p->lson->size;
		p->count += p->lson->count;
	}
	if (p->rson != nullptr) {
		p->size += p->rson->size;
		p->count += p->rson->count;
	}
	if (!p->deleted)
		p->size++;
}

void serialize(node* p, vector<node*> vec) {
	if (p->lson != nullptr)
		serialize(p->lson, vec);
	if (!p->deleted)
		vec.push_back(p);
	if (p->rson != nullptr)
		serialize(p->rson, vec);
}

node* _rebuild(vector<node*>& vec, int left, int right) {
	if (right - left<0)
		return nullptr;
	int mid = (left + right) / 2;
	node* p = vec[mid];
	p->lson = _rebuild(vec, left, mid - 1);
	p->rson = _rebuild(vec, mid + 1, right);
	update(p);
}

node* rebuild(node* p) {
	vector<node*> vec;
	serialize(p, vec);
	return _rebuild(vec, 0, vec.size() - 1);
}

bool isBad(node* p) {
	return p->lson->count>p->count*factor || p->rson->count>p->count*factor;
}

void insert(int val, node*& p = root) {
	cout << "insert" << endl;
	if (p == nullptr) {
		p = allocate();
		p->val = val;
		p->size = p->count = 1;
	}
	else {
		if (val >= p->val)
			insert(val, p->rson);
		else
			insert(val, p->lson);
		update(p);
		if (isBad(p))
			p = rebuild(p);
	}
}

int rrank(int val, node* p = root) {
	if (val <= p->val) {
		return rrank(val, p->lson);
	}
	else {
		return rrank(val, p->rson) + p->lson->size + (int)(1 - p->deleted);
	}
}

int kth(int k, node* p = root) {
	if (k == 1)
		return p->val;
	else if (p->lson->size >= k)
		return kth(k, p->lson);
	else if (!p->deleted&&p->lson->size == k + 1)
		return p->val;
	else
		return kth(k - p->lson->size - (int)(1 - p->deleted), p->rson);
}

void erase(int val, node* p = root) {
	if (p->val == val && !p->deleted)
		p->deleted = true;
	else if (val<p->val)
		erase(val, p->lson);
	else
		erase(val, p->rson);
}

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int op, x;
		cin >> op >> x;
		if (op == 1)
			insert(x);
		else if (op == 2)
			erase(x);
		else if (op == 3)
			cout << rrank(x) << endl;
		else if (op == 4)
			cout << kth(x) << endl;
		else if (op == 5)
			cout << kth(rrank(x) - 1) << endl;
		else if (op == 6)
			cout << kth(rrank(x) + 1) << endl;
	}
}

#endif

