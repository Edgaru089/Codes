/*
DOCUMENT NAME "20180629-luogu4277.cpp"
CREATION DATE 2018-06-29
SIGNATURE CODE_20180629_LUOGU4277
COMMENT 河城荷取的烟花 / 建图+Floyd最短路
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180629_LUOGU4277

#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int infinity = 1e8;
const int MaxC = 400 + 10, MaxN = 3 * MaxC, MaxM = 2 * MaxN;

struct pnt {
	double x, y;
	pnt() {}
	pnt(double x, double y) :x(x), y(y) {}
	pnt(const pnt& copy) :x(copy.x), y(copy.y) {}
	bool operator < (const pnt& op) const {
		if (x < op.x)
			return true;
		else if (x == op.x&&y < op.y)
			return true;
		else
			return false;
	}
	bool operator ==(const pnt& op) const { return x == op.x && y == op.y; }
	pnt operator / (const double& op) const { return pnt(x / op, y / op); }
	pnt operator + (const pnt& op) const { return pnt(x + op.x, y + op.y); }
};


int c;
int n, m;

map<pnt, int> pntId;
bool isTerminal[MaxN];

struct edge {
	edge() {}
	edge(int u, int v, double len) :
		u(u), v(v), len(len) {}
	int u, v;
	double len;
};

vector<edge> es;

void addedge(int u, int v, double len) {
	es.push_back(edge(u, v, len));
	es.push_back(edge(v, u, len));
}

int insertOrAssignPoint(pnt x) {
	auto i = pntId.find(x);
	if (i == pntId.end()) {
		n++;
		pntId.insert(pair<pnt, int>(x, n));
		return n;
	}
	else
		return i->second;
}

double dis[MaxN][MaxN];

int main(int argc, char* argv[]) {

	cin >> c;
	for (int i = 1; i <= c; i++) {
		pnt a, b;
		double t;
		cin >> a.x >> a.y >> b.x >> b.y >> t;
		int ida = insertOrAssignPoint(a), idb = insertOrAssignPoint(b);
		isTerminal[ida] = isTerminal[idb] = true;
		if (a.x != b.x && a.y != b.y) {
			pnt mid = (a + b) / 2;
			int idmid = insertOrAssignPoint(mid);
			isTerminal[idmid] = false;
			addedge(ida, idmid, t / 2.0);
			addedge(idmid, idb, t / 2.0);
		}
		else
			addedge(ida, idb, t);
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i == j)
				dis[i][j] = 0;
			else
				dis[i][j] = infinity;
	for (edge& i : es)
		dis[i.u][i.v] = i.len;

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

	double ans = infinity;
	for (int i = 1; i <= n; i++) {
		if (isTerminal[i]) {
			double lmax = 0;
			for (auto& j : es) {
				lmax = max(lmax, (j.len + fabs(dis[i][j.u] - dis[i][j.v])) / 2.0 + min(dis[i][j.u], dis[i][j.v]));
			}
			ans = min(ans, lmax);
		}
	}

	printf("%.4lf\n", ans);

	return 0;
}

#endif

