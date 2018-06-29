/*
DOCUMENT NAME "20180629-luogu3369.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU3369
COMMENT ¡¾Ä£°å¡¿ÆÕÍ¨Æ½ºâÊ÷ / Ìæ×ïÑòÊ÷
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU3369

#include <cstdlib>
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

const int MaxN = 4500000;

struct node {
	int val;
	int size, cnt;
	// Size: total node count of the subtree; Cnt: counts only the nodes not deleted
	bool deleted;
	int valCnt;   // count the times the same value is inserted
	node* lson, *rson;
};

node *mem, *root;
int memSize;
int top;
node* allocate() {
	if (top < memSize-1)
		return &mem[++top];
	else {
		cout << "BAD ALLOC ERROR - EXITING" << endl;
		exit(0);
	}
}
#define ALLOCATE allocate();

bool isRebuildPending;
node** rebuildNode;

const double factor = 0.72;

#define CNT(x)  (x == nullptr ? 0 : x->cnt)
#define SIZE(x) (x == nullptr ? 0 : x->size)

bool isBad(node* p) {
	if (SIZE(p->lson) > factor*p->size || SIZE(p->rson) > factor*p->size)
		return true;
	else
		return false;
}

// pair: first val, second valCnt
void slap(node* p, vector<node*>& vec) {
	if (p == nullptr)
		return;
	slap(p->lson, vec);
	if (!p->deleted)
		vec.push_back(p);
	slap(p->rson, vec);
}

// [left, right]
node* _rebuild(vector<node*>& vec, int left, int right) {
	if (right - left < 0)
		return nullptr;
	int mid = (left + right) / 2; // [left, mid-1], [mid], [mid+1, right]
	node* p = vec[mid];
	p->deleted = false;
	p->lson = _rebuild(vec, left, mid - 1);
	p->rson = _rebuild(vec, mid + 1, right);
	p->size = SIZE(p->lson) + SIZE(p->rson) + 1;
	p->cnt = CNT(p->lson) + CNT(p->rson) + p->valCnt;
	return p;
}

void rebuild(node*& p) {
	vector<node*> vec;
	slap(p, vec);
	p = _rebuild(vec, 0, vec.size() - 1);
}

void _insert(int val, node*& p = root) {
	if (p == nullptr) {
		p = ALLOCATE;
		p->val = val;
		p->size = p->cnt = 1;
		p->deleted = false;
		p->valCnt = 1;
		p->lson = p->rson = nullptr;
	}
	else {
		p->cnt++;
		if (val == p->val) {
			p->valCnt++;
			p->cnt++;
		}
		else if (val < p->val)
			_insert(val, p->lson);
		else if (val > p->val)
			_insert(val, p->rson);
		p->size = SIZE(p->lson) + SIZE(p->rson) + 1;
		p->cnt = CNT(p->lson) + CNT(p->rson) + p->valCnt;
	}
	if (p != nullptr&&isBad(p)) {
		isRebuildPending = true;
		rebuildNode = &p;
	}
}

void insert(int val) {
	_insert(val, root);
	if (isRebuildPending) {
		rebuild(*rebuildNode);
		rebuildNode = nullptr;
		isRebuildPending = false;
	}
}

void remove(int val, node* p = root) {
	if (p->val == val) {
		p->valCnt--;
		if (p->valCnt <= 0)
			p->deleted = true;
	}
	else if (val < p->val)
		remove(val, p->lson);
	else if (val > p->val)
		remove(val, p->rson);
	p->cnt = CNT(p->lson) + CNT(p->rson) + p->valCnt;
}

pair<int, node*> rankVal(int val, node* p = root) {
	if (p == nullptr)
		return pair<int, node*>(1, nullptr);
	else if (p->val == val)
		return pair<int, node*>(CNT(p->lson) + 1, p);
	else if (val < p->val)
		return rankVal(val, p->lson);
	else if (val > p->val) {
		auto x = rankVal(val, p->rson);
		x.first += CNT(p->lson) + p->valCnt;
		return x;
	}
}

pair<int, node*> findRankVal(int rank, node* p = root) {
	if (p == nullptr)
		cout << "NULLPTR FAILURE - FindRankVal(rank=" << rank << ") FAILED" << endl;
	else if (rank <= CNT(p->lson))
		return findRankVal(rank, p->lson);
	else if (rank - CNT(p->lson) <= p->valCnt)
		return pair<int, node*>(p->val, p);
	else if (rank - CNT(p->lson) - p->valCnt <= CNT(p->rson))
		return findRankVal(rank - CNT(p->lson) - p->valCnt, p->rson);
	else
		cout << "OUT OF RANGE FAILURE - FindRankVal(rank=" << rank << ") FAILED" << endl;
}


int main(int argc, char* argv[]) {
	int n;
	int op, x;

	cin >> n;
	mem = new node[n];
	memSize = n;
	for (int i = 1; i <= n; i++) {
		cin >> op >> x;
		switch (op) {
		case 1:
			insert(x);
			break;
		case 2:
			remove(x);
			break;
		case 3:
			cout << rankVal(x).first << endl;
			break;
		case 4:
			cout << findRankVal(x).first << endl;
			break;
		case 5:
			cout << findRankVal(rankVal(x).first - 1).first << endl;
			break;
		case 6:
			auto result = rankVal(x);
			cout << findRankVal(result.first + (result.second == nullptr ? 0 : result.second->valCnt)).first << endl;
			break;
		}
	}
	return 0;
}

#endif

