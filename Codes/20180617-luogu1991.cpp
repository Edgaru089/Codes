/*
DOCUMENT CODE "20180617-luogu1991.cpp"
CREATION DATE 2018-06-17
SIGNATURE CODE_20180617_LUOGU1991
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180617_LUOGU1991

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct edge {
	edge() {}
	edge(int u, int v, double len) :
		u(u), v(v), len(len) {}
	int u, v;
	double len;
};

int n, m;
double x[1000], y[1000];

vector<edge> e;

void addedge(int u, int v, double len) {
	e.push_back(edge(u, v, len));
}

double distance(double X1, double Y1, double X2, double Y2) {
	return sqrt((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2));
}

int p[1000];

int Find(int x) {
	if (p[x] < 0)
		return x;
	else
		return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	p[x] += p[y];
	p[y] = x;
}

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> m >> n;
	e.reserve(n * (n - 1) / 2);
	for (int i = 1; i <= n; i++)
		cin >> x[i] >> y[i];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			addedge(i, j, distance(x[i], y[i], x[j], y[j]));

	sort(e.begin(), e.end(), [](const edge& x, const edge& y)->bool {
		if (x.len < y.len)
			return true;
		else
			return false;
	});

	int cnt = n;
	double Max = 0;
	for (edge& i : e) {
		if (cnt <= m || cnt == 1)
			break;

		int u = i.u, v = i.v;
		double len = i.len;

		if (Find(u) == Find(v))
			continue;

		Union(u, v);
		cnt--;
		Max = max(Max, len);
	}

	printf("%.2lf\n", Max);

	return 0;
}

#endif

