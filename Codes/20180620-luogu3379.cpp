/*
DOCUMENT CODE "20180620-luogu3379.cpp"
CREATION DATE 2018-06-20
SIGNATURE CODE_20180620_LUOGU3379
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180620_LUOGU3379

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;


namespace System {
	constexpr int Max = 500000 + 100;

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

	int root = 0;
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

	void makeTree(int u = root, int father = 0, int deep = 1) {
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

}


namespace System {

	int N, M;


	void initalaize() {
		Set::initalaize();
	}

	void input() {

		//cin >> N >> M >> Graph::root;
		//Tarjan::looks.reserve(M);
		//for (int i = 1; i <= N - 1; i++) {
		//	int x, y;
		//	cin >> x >> y;
		//	Graph::addEdge(x, y);
		//}
		//for (int i = 1; i <= M; i++) {
		//	int a, b;
		//	cin >> a >> b;
		//	Tarjan::addLookup(a, b);
		//}

		read(N); read(M); read(Graph::root);
		Tarjan::looks.reserve(M);
		for (int i = 1; i <= N - 1; i++)
			Graph::addEdge(read(), read());
		for (int i = 1; i <= M; i++)
			Tarjan::addLookup(read(), read());

	}

	void process() {

		Graph::makeTree();

		Tarjan::search();

	}

	void output() {

		for (auto i : Tarjan::looks) {
			if (i.l1->ans != 0)
				printf("%d\n", i.l1->ans);
			else
				printf("%d\n", i.l2->ans);
			//cout << i.l1->ans << " " << i.l2->ans << endl;
		}

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

