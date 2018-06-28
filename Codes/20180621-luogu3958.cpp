/*
DOCUMENT CODE "20180621-luogu3958.cpp"
CREATION DATE 2018-06-21
SIGNATURE CODE_20180621_LUOGU3958
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180621_LUOGU3958

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;


namespace Geometry {

	struct Point {
		Point() {}
		Point(double x, double y, double z)
			:x(x), y(y), z(z) {}

		double x, y, z;
	};

	double sqr(double x) { return x * x; }

	double distance(Point a, Point b) {
		return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
	}

	constexpr double eps = 1e-8;
	bool isSame(double x, double y) {
		return abs(x - y) < eps;
	}
}


namespace System {
	constexpr int Max = 1000 * 20 + 10;

	int t;
	int n, h, r;
	Geometry::Point pnt[Max];

	int read() {
		int sum = 0;
		char c;
		while (!isdigit(c = getchar()));
		do {
			sum = sum * 10 + (c - '0');
		} while (isdigit(c = getchar()));
		return sum;
	}

	int read(int& val) {
		return val = read();
	}
}


namespace Graph {
	struct node {
		int v;
		node* next;
	};

	node mem[System::Max * 2], *h[System::Max];
	int top;

	void initalaize() {
		top = 0;
		memset(h, 0, sizeof(h));
	}

	node* allocate() { return &mem[++top]; }

	void addedge(int u, int v) {
		node* p = allocate();
		p->v = v;
		p->next = h[u];
		h[u] = p;
		p = allocate();
		p->v = u;
		p->next = h[v];
		h[v] = p;
	}
}


namespace Algorithm {

	int top, bottom;
	bool been[System::Max + 2];

	void initalaize() {
		memset(been, 0, sizeof(been));
	}

	void dfs(int u = bottom) {
		if (been[u])
			return;
		been[u] = true;
		for (auto p = Graph::h[u]; p != nullptr; p = p->next)
			dfs(p->v);
	}

	bool run() {
		top = System::n + 1, bottom = System::n + 2;

		for (int i = 1; i <= System::n; i++) {
			if ((System::pnt[i].z - System::r - Geometry::eps) < 0)
				Graph::addedge(i, bottom);
			if ((System::pnt[i].z + System::r + Geometry::eps) > System::h)
				Graph::addedge(i, top);
		}
		for (int i = 1; i <= System::n; i++) {
			for (int j = 1; j < i; j++) {
				Geometry::Point a = System::pnt[i], b = System::pnt[j];
				if (Geometry::distance(a, b) - Geometry::eps < System::r * 2.0)
					Graph::addedge(i, j);
			}
		}

		dfs();

		return been[top];
	}
}


namespace System {

	void run() {

		read(t);

		for (int i = 1; i <= t; i++) {
			read(n); read(h); read(r);
			for (int j = 1; j <= n; j++)
				scanf("%lf%lf%lf", &pnt[j].x, &pnt[j].y, &pnt[j].z);

			Graph::initalaize();
			Algorithm::initalaize();

			if (Algorithm::run())
				printf("Yes\n");
			else
				printf("No\n");
		}
	}
}


int main(int argc, char* argv[]) {

	System::run();

	return 0;
}

#endif

