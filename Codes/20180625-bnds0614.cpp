/*
DOCUMENT CODE "20180625-bnds0614.cpp"
CREATION DATE 2018-06-25
SIGNATURE CODE_20180625_BNDS0614
TOPIC
*/

/*
INPUT
4 10
1 10 2
2 5 3
3 6 1
4 9 4
0 1 2 3
1 0 3 4
2 3 0 5
3 4 5 0
OUTPUT
21
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180625_BNDS0614

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int v, len;
	node* next;
};

node mem[100 * 100], *h[100 + 10];
int top;
node* allocate() { return &mem[++top]; }
void addedge(int u, int v, int len) {
	node* p = allocate();
	p->v = v;
	p->len = len;
	p->next = h[u];
	h[u] = p;
}

int n, m;
int cnt[1001], value[1001], Time[1001];
bool taken[1001];
int ans[1001];

//template<typename Type>
//Type max(const Type& x, const Type& y) { return ((x) > (y)) ? (x) : (y); }

void dfs(int u, int lastCnt, int time, int totalVal) {
	if (time > m)
		return;
	ans[time] = max(ans[time], totalVal);

	if (!taken[u] && lastCnt < cnt[u] && time + ::Time[u] <= m) {
		taken[u] = true;
		ans[time + ::Time[u]] = max(ans[time + ::Time[u]], totalVal + value[u]);
		for (node* p = h[u]; p != nullptr; p = p->next)
			dfs(p->v, cnt[u], time + p->len + ::Time[u], totalVal + value[u]);
		taken[u] = false;
	}

	for (node* p = h[u]; p != nullptr; p = p->next)
		dfs(p->v, lastCnt, time + p->len, totalVal);

	//for (node* p = h[u]; p != nullptr; p = p->next) {
	//	int v = p->v, len = p->len;
	//	if (!taken[v] && lastCnt < cnt[v]) {
	//		taken[v] = true;
	//		dfs(v, cnt[v], time + len + ::time[v], totalVal + value[v]);
	//		taken[v] = false;
	//		dfs(v, lastCnt, time + len, totalVal);
	//	}
	//}
}

int main(int argc, char* argv[]) {

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> cnt[i] >> value[i] >> Time[i];

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int a;
			cin >> a;
			if (i != j)
				addedge(i, j, a);
		}
	}

	for (int i = 1; i <= n; i++) {
		dfs(i, 0, 0, 0);
	}

	int Max = 0;
	for (int i = 1; i <= m; i++) {
		Max = max(Max, ans[i]);
	}

	cout << Max << endl;

	return 0;
}

#endif

