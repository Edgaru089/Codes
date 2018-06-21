/*
DOCUMENT CODE "20180620-luogu1600.cpp"
CREATION DATE 2018-06-20
SIGNATURE CODE_20180620_LUOGU1600
TOPIC 天天爱跑步
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180620_LUOGU1600

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <cassert>
using namespace std;


namespace System {
	constexpr int Max = 300000 + 100;

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


	int n, m;
	int w[Max];
	int s[Max], t[Max];

}


namespace Set {

	int p[System::Max];

	void initalaize() {
		memset(p, -1, sizeof(p));
	}

	int Find(int x) {
		if (p[x] < 0)
			return x;
		else
			return p[x] = Find(p[x]);
	}

	// Union x into y (set the father of x and all of x's children to y)
	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);
		p[y] += p[x];
		p[x] = y;
	}

}


namespace Graph {

	struct node {
		int v;
		node* next;
	};

	node memory[System::Max * 2];
	node* h[System::Max];
	int top = 0;

	int root = 1;
	int deep[System::Max], father[System::Max];


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
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father)
				makeTree(v, u, deep + 1);
		}
	}

}


namespace Tarjan {

	struct look {
		int e;
		int ans;
		look* next;
	};

	struct lookI {
		lookI() {}
		lookI(int u, int v, look* l1, look* l2) :
			u(u), v(v), l1(l1), l2(l2) {}

		int u, v;
		int ans;
		look* l1, *l2;
	};

	look memory[System::Max * 2];
	look* l[System::Max];
	int top;
	vector<lookI> looks;


	bool been[System::Max];


	look* allocate() {
		return &memory[++top];
	}

	void addLookup(int u, int v) {
		look* p1 = allocate();
		p1->e = v;
		p1->next = l[u];
		l[u] = p1;
		look* p2 = allocate();
		p2->e = u;
		p2->next = l[v];
		l[v] = p2;
		looks.push_back(lookI(u, v, p1, p2));
	}

	void search(int u = Graph::root) {

		for (auto p = Graph::h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != Graph::father[u] && !been[v]) {
				search(v);
				Set::Union(v, u);
				been[v] = true;
			}
		}

		for (auto p = l[u]; p != nullptr; p = p->next) {
			int e = p->e;
			if (been[e]) {
				p->ans = Set::Find(e);
			}
		}
	}

	void bindAnswer() {
		for (auto& i : looks) {
			if (i.u == i.v)
				i.ans = i.u;
			else if (i.l1->ans != 0)
				i.ans = i.l1->ans;
			else
				i.ans = i.l2->ans;
		}
	}

}


namespace Algorithm {

	int Count_Start[System::Max];
	vector<int> Start_LCA[System::Max], Start_End[System::Max], End_LCA[System::Max];
	int bucket[System::Max * 3];
	int answer[System::Max];
	bool isSearching[System::Max];


	int dist(Tarjan::lookI info) {
		return Graph::deep[info.u] - Graph::deep[info.ans] + Graph::deep[info.v] - Graph::deep[info.ans];
	}

	void precompute() {
		for (auto& i : Tarjan::looks) {
			Start_LCA[i.ans].push_back(i.u);
			Count_Start[i.u]++;
			//End_Start[i.u].push_back(i.v);
			Start_End[i.v].push_back(dist(i) - Graph::deep[i.v]);
			//End_LCA[i.ans].push_back(i.v);
			End_LCA[i.ans].push_back(dist(i) - Graph::deep[i.v]);
		}
	}

	void dfsUp(int i) {
		if (isSearching[i])
			return;
		isSearching[i] = true;

		int layer = Graph::deep[i] + System::w[i];
		int prevBucket = bucket[layer];

		for (auto p = Graph::h[i]; p != nullptr; p = p->next)
			dfsUp(p->v);

		bucket[Graph::deep[i]] += Count_Start[i];
		answer[i] += bucket[layer] - prevBucket;

		for (int s : Start_LCA[i])
			bucket[Graph::deep[s]]--;

		isSearching[i] = false;
	}

	void dfsDown(int i) {
		if (isSearching[i])
			return;
		isSearching[i] = true;

		int layer = System::w[i] - Graph::deep[i] + System::Max;
		int prevBucket = bucket[layer];

		for (auto p = Graph::h[i]; p != nullptr; p = p->next)
			dfsDown(p->v);

		for (int k : Start_End[i])
			bucket[k + System::Max]++;

		answer[i] += bucket[layer] - prevBucket;

		for (int k : End_LCA[i])
			bucket[k + System::Max]--;

		isSearching[i] = false;
	}

	void run() {

		precompute();

		dfsUp(1);
		//for (int i = 0; i < 3 * System::Max; i++)
		//	assert(bucket[i] == 0);

		dfsDown(1);
		//for (int i = 0; i < 3 * System::Max; i++)
		//	assert(bucket[i] == 0);

		// 去重
		for (auto i : Tarjan::looks) {
			if (Graph::deep[i.u] == Graph::deep[i.ans] + System::w[i.ans])
				answer[i.ans]--;
		}
	}

}


namespace System {

	void initalaize() {
		Set::initalaize();
	}

	void input() {

		read(n); read(m);
		for (int i = 1; i < n; i++)
			Graph::addEdge(read(), read());
		for (int i = 1; i <= n; i++)
			read(w[i]);
		Tarjan::looks.reserve(m);
		for (int i = 1; i <= m; i++) {
			read(s[i]); read(t[i]);
			Tarjan::addLookup(s[i], t[i]);
		}

	}

	void process() {
		Graph::makeTree();
		Tarjan::search();
		Tarjan::bindAnswer();

		Algorithm::run();
	}

	void output() {
		for (int i = 1; i <= n; i++) {
			if (i == 1)
				printf("%d", Algorithm::answer[i]);
			else
				printf(" %d", Algorithm::answer[i]);
		}
		printf("\n");
	}

}



int main(int argc, char* argv[]) {

	System::initalaize();

	System::input();

	System::process();

	System::output();

	return 0;
}

#endif

