/*
DOCUMENT CODE "20180513-bnds0114.cpp"
CREATION DATE 2018-05-13
SIGNATURE CODE_20180513_BNDS0114
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180513_BNDS0114

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int topId = 0;
int getId() {
	return ++topId;
}

struct node {
	int v;
	double len;
	node* next;
};

node pool[400001], *h[100000];
int top;

node* alloc() { return &pool[++top]; }

void addedgeSingular(int u, int v, double len) {
	node* tmp = alloc();
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
}

void addedgeBidirection(int u, int v, double len) {
	node* tmp = alloc();
	tmp->v = v;
	tmp->len = len;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = alloc();
	tmp->v = u;
	tmp->len = len;
	tmp->next = h[v];
	h[v] = tmp;
}

struct pnt {
	pnt() {}
	pnt(double x, double y) :x(x), y(y) {}

	double x, y;
};

const double eps = 1e-5;
bool isSame(double x, double y) {
	if (abs(x - y) < eps)
		return true;
	else
		return false;
}

// Å·À­¾àÀë
double distance(pnt x, pnt y) {
	return sqrt((x.x - y.x)*(x.x - y.x) + (x.y - y.y)*(x.y - y.y));
}

// Ð±ÂÊ
double slope(pnt x, pnt y) {
	return (x.y - y.y) / (x.x - y.x);
}

// Angle ¡ÏAOB
bool isPerpendicular(pnt a, pnt o, pnt b) {
	if (a.x == o.x&&o.y == b.y)
		return true;
	else if (a.y == o.y&&o.x == b.x)
		return true;
	else if (isSame(-1, slope(a, o)*slope(o, b)))
		return true;
	else
		return false;
}

pnt get4thPoint(pnt a, pnt b, pnt c) {
	pnt d;
	if (isPerpendicular(c, a, b)) {
		d = a;
		d.x += c.x - a.x;
		d.y += c.y - a.y;
		d.x += b.x - a.x;
		d.y += b.y - a.y;
		return d;
	}
	else if (isPerpendicular(a, b, c)) {
		d = b;
		d.x += a.x - b.x;
		d.y += a.y - b.y;
		d.x += c.x - b.x;
		d.y += c.y - b.y;
		return d;
	}
	else if (isPerpendicular(b, c, a)) {
		d = c;
		d.x += b.x - c.x;
		d.y += b.y - c.y;
		d.x += a.x - c.x;
		d.y += a.y - c.y;
		return d;
	}
	else
		return d;
}

int s, t, a, b;
pnt p[1001][5];
int pid[1001][5];
int T[1001];

int Start, End;

const int infinity = 1000000000;
double dis[101];
queue<int> Q;
int S[1001];

void spfa() {
	for (int i = 1; i <= topId; i++) {
		dis[i] = infinity;
		S[i] = 0;
	}
	while (!Q.empty())
		Q.pop();

	Q.push(Start);
	S[Start] = 1;
	dis[Start] = 0;
	while (!Q.empty()) {
		int u = Q.front(), v;
		double len;
		Q.pop(); S[u] = 0;
		for (node* p = h[u]; p != NULL; p = p->next) {
			v = p->v; len = p->len;
			if (dis[v] > dis[u] + len) {
				dis[v] = dis[u] + len;
				if (S[v] == 0) {
					S[v] = 1;
					Q.push(v);
				}
			}
		}
	}

}

int main(int argc, char* argv[]) {

	int n;
	cin >> n;
	while (n--) {

		memset(pool, 0, sizeof(pool));
		memset(h, 0, sizeof(h));
		top = 0;
		topId = 0;
		memset(p, 0, sizeof(p));
		memset(pid, 0, sizeof(pid));
		memset(T, 0, sizeof(T));

		cin >> s >> t >> a >> b;
		for (int i = 1; i <= s; i++) {
			cin >> p[i][1].x >> p[i][1].y;
			cin >> p[i][2].x >> p[i][2].y;
			cin >> p[i][3].x >> p[i][3].y;
			cin >> T[i];

			p[i][4] = get4thPoint(p[i][1], p[i][2], p[i][3]);

			for (int j = 1; j <= 4; j++)
				pid[i][j] = getId();

			for (int j = 1; j <= 4; j++) {
				for (int k = 1; k <= 4; k++) {
					if (j != k)
						addedgeSingular(pid[i][j], pid[i][k], distance(p[i][j], p[i][k]) * T[i]);
				}
			}
		}

		for (int i = 1; i <= s; i++)
			for (int j = 1; j <= s; j++)
				for (int k = 1; k <= 4; k++)
					for (int l = 1; l <= 4; l++)
						if (i != j && k != l)
							addedgeSingular(pid[i][k], pid[j][l], distance(p[i][k], p[j][l])*t);

		Start = getId();
		End = getId();
		for (int i = 1; i <= 4; i++) {
			addedgeBidirection(Start, pid[a][i], 0);
			addedgeBidirection(pid[b][i], End, 0);
		}

		spfa();

		printf("%.1lf\n", dis[End]);

	}

	return 0;
}

#endif

