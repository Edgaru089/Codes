/*
DOCUMENT CODE "20180519-luogu3369.cpp"
CREATION DATE 2018-05-19
SIGNATURE CODE_20180519_LUOGU3369
TOPIC ÆÕÍ¨Æ½ºâÊ÷£¨Ìæ×ïÑòÊ÷£©
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180519_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> dint;

struct node {
	int val, size, count;
	node* lson, *rson, *father;
	bool deleted;
};

node pool[1000001], *root;
int top;

const double balanceFactor = 0.72;

node* allocate() { return &pool[++top]; }

vector<dint> serialize(node* p) {
	vector<dint> vec;
	if (p->lson != nullptr) {
		// Append
		vector<dint> vec2 = serialize(p->lson);
		int size0 = vec.size();
		vec.resize(vec.size() + vec2.size());
		for (int i = size0; i < vec2.size(); i++)
			vec[i] = vec2[i - size0];
	}
	if (!p->deleted)
		vec.push_back(dint(p->val, p->size));
	if (p->rson != nullptr) {
		// Append
		vector<dint> vec2 = serialize(p->rson);
		int size0 = vec.size();
		vec.resize(vec.size() + vec2.size());
		for (int i = size0; i < vec2.size(); i++)
			vec[i] = vec2[i - size0];
	}
	return vec;
}

node* _reconstruct(vector<dint>& vec, int left, int right, node* father) {
	if (right - left < 0)
		return nullptr;

	node* p = allocate();
	int mid = (left + right) / 2;

	p->father = father;
	p->size = 1;
	p->val = vec[mid].first;
	p->count = vec[mid].second;

	p->lson = _reconstruct(vec, left, mid - 1, p);
	p->rson = _reconstruct(vec, mid + 1, right, p);

	if (p->lson != nullptr)
		p->size += p->lson->size;
	if (p->rson != nullptr)
		p->size += p->rson->size;

	return p;
}

void reconstruct(node*& p) {
	vector<dint> vec = serialize(p);
	_reconstruct(vec, 0, vec.size() - 1, p->father);
}

void update(node* p) {
	node* p0 = p;
	while (p0->father != nullptr && p0->father->father != nullptr) {
		if (p0->father->size > p0->father->father->size*balanceFactor)
			p0 = p0->father;
	}
	if (p0->father != nullptr&&p0->size > p0->father->size*balanceFactor) {
		reconstruct(p0);
		if(p->father)
		p = p0;
	}
}

node* _insert(int val, node*& p = root, node* father = nullptr) {
	if (p == nullptr) {
		p = allocate();
		p->val = val;
		p->father = father;
		p->size = 1;
		return p;
	}
	else {
		p->size++;
		if (val < p->val)
			return _insert(val, p->lson, p);
		else if (val == p->val) {
			p->count++;
			return p;
		}
		else
			return _insert(val, p->rson, p);
	}
}

void insert(int val) {
	update(_insert(val));
}




int main(int argc, char* argv[]) {

	return 0;
}

#endif
