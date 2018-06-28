/*
DOCUMENT CODE "20180622-luogu3384.cpp"
CREATION DATE 2018-06-22
SIGNATURE CODE_20180622_LUOGU3384
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180622_LUOGU3384

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;


namespace System {
	constexpr int Max = 100000 + 100;

	int read() {
		char c;
		int val = 0;

		while (!isdigit(c = getchar()));

		do {
			val = val * 10 + (c - '0');
		} while (isdigit(c = getchar()));

		return val;
	}

	int read(int& val) {
		return val = read();
	}

	//void read(initializer_list<reference_wrapper<int>> vals) {
	//	for (auto& i : vals)
	//		read(i.get());
	//}


	int n, m, Mod;
	int d[Max];

}


namespace Graph {

	struct node {
		int v;
		node* next;
	};

	node memory[System::Max * 2];
	node* h[System::Max];
	int top = 0;

	int root;
	int deep[System::Max], father[System::Max];
	int size[System::Max];


	node* allocate() {
		return &memory[++top];
	}

	void addEdge(int u, int v) {
		node* p = allocate();
		p->v = v;
		p->next = h[u];
		h[u] = p;
		p = allocate();
		p->v = u;
		p->next = h[v];
		h[v] = p;
	}

	void makeTree(int u = root, int father = 0, int deep = 0) {
		Graph::father[u] = father;
		Graph::deep[u] = deep;
		size[u] = 1;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father) {
				makeTree(v, u, deep + 1);
				size[u] += size[v];
			}
		}
	}

}


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
		_add(left, right, val % System::Mod, root);
	}

	long long query(int left, int right) {
		return _query(left, right, root) % System::Mod;
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
		p->sum %= System::Mod;
		if (p->lson != nullptr) {
			p->lson->lazy += p->lazy;
			p->lson->lazy %= System::Mod;
		}
		if (p->rson != nullptr) {
			p->rson->lazy += p->lazy;
			p->rson->lazy %= System::Mod;
		}
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
		p->sum = (p->lson->sum + p->rson->sum) % System::Mod;
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
			return (_query(left, p->lson->right, p->lson) + _query(p->rson->left, right, p->rson)) % System::Mod;
	}



	node mem[200050];
	int top;

	node* root;

};


namespace Algorithm {

	int heavySon[System::Max];
	int dfsSeq[System::Max];
	int reverseSeq[System::Max];
	int topSeq = 0;
	long long d[System::Max];

	int top[System::Max];

	SegmentTree seg;

	void dfs(int u = Graph::root) {
		dfsSeq[u] = ++topSeq;
		reverseSeq[dfsSeq[u]] = u;

		int maxSize = 0, maxV = 0;
		for (auto p = Graph::h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v == Graph::father[u])
				continue;
			if (Graph::size[v] > maxSize) {
				maxSize = Graph::size[v];
				maxV = v;
			}
		}

		heavySon[u] = maxV;
		top[maxV] = top[u];
		if (maxV != 0)
			dfs(maxV);

		for (auto p = Graph::h[u]; p != nullptr; p = p->next)
			if (p->v != Graph::father[u] && p->v != maxV)
				dfs(p->v);
	}

	void precompute() {
		for (int i = 1; i <= System::n; i++)
			top[i] = i;
		dfs();
		for (int i = 1; i <= System::n; i++)
			d[dfsSeq[i]] = System::d[i];
		seg.build(d, System::n);
	}

	void addSection(int x, int y, int val) {
		while (top[x] != top[y]) {
			if (Graph::deep[top[x]] < Graph::deep[top[y]])
				swap(x, y);
			seg.add(dfsSeq[top[x]], dfsSeq[x], val);
			x = Graph::father[top[x]];
		}

		if (Graph::deep[x] < Graph::deep[y])
			swap(x, y);
		seg.add(dfsSeq[y], dfsSeq[x], val);
	}

	int querySection(int x, int y) {
		int sum = 0;

		while (top[x] != top[y]) {
			if (Graph::deep[top[x]] < Graph::deep[top[y]])
				swap(x, y);
			sum += seg.query(dfsSeq[top[x]], dfsSeq[x]);
			sum %= System::Mod;
			x = Graph::father[top[x]];
		}

		if (Graph::deep[x] < Graph::deep[y])
			swap(x, y);
		sum += seg.query(dfsSeq[y], dfsSeq[x]);
		sum %= System::Mod;

		return sum;
	}

	void addSubTree(int x, int val) {
		seg.add(dfsSeq[x], dfsSeq[x] + Graph::size[x] - 1, val);
	}

	int querySubTree(int x) {
		return seg.query(dfsSeq[x], dfsSeq[x] + Graph::size[x] - 1) % System::Mod;
	}

}


namespace System {

	void run() {

		read(n); read(m); read(Graph::root); read(Mod);
		for (int i = 1; i <= n; i++)
			read(d[i]);
		for (int i = 1; i <= n - 1; i++) {
			int u, v;
			read(u); read(v);
			Graph::addEdge(u, v);
		}

		Graph::makeTree();
		Algorithm::precompute();

		for (int i = 1; i <= m; i++) {
			int c, x, y, z;
			read(c);
			if (c == 1) {
				read(x); read(y); read(z);
				Algorithm::addSection(x, y, z);
			}
			else if (c == 2) {
				read(x); read(y);
				printf("%d\n", Algorithm::querySection(x, y));
			}
			else if (c == 3) {
				read(x); read(z);
				Algorithm::addSubTree(x, z);
			}
			else if (c == 4) {
				read(x);
				printf("%d\n", Algorithm::querySubTree(x));
			}
		}

	}
}



int main(int argc, char* argv[]) {

	System::run();

	return 0;
}

#endif

