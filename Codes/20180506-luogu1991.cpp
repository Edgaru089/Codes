/*
DOCUMENT CODE "20180506-luogu1991.cpp"
CREATION DATE 2018-05-06
SIGNATURE CODE_20180506_LUOGU1991
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180506_LUOGU1991

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct Edge {
	int u, v;
	double len;
};

int p[1000];
int s, n;
int x[1000], y[1000];
Edge e[1000000];

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

double sqr(double x) {
	return x*x;
}

double distance(double X1, double Y1, double X2, double Y2) {
	return sqrt(sqr(X1 - X2) + sqr(Y1 - Y2));
}

bool compare(Edge x, Edge y) {
	return x.len < y.len;
}

int main(int argc, char* argv[]) {

	memset(p, -1, sizeof(p));

	cin >> s >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i];
	}

	int k = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			k++;
			e[k].len = distance(x[i], y[i], x[j], y[j]);
			e[k].u = i;
			e[k].v = j;
		}
	}



	return 0;
}

#endif

