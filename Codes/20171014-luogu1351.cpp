/*
DOCUMENT CODE "luogu1351.cpp"
CREATION DATE 2017-10-14
SIGNATURE CODE_20171014_LUOGU1351
TOPIC NOIP2014 联合权值
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171014_LUOGU1351

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int v;
	node* next;
};

node* h[200001];
node pool[400001];
int top;

int n;
int w[200001];
const int Mod = 10007;
long long Max = 0, Sum = 0;

int tmp[200001];

const int max(const int a, const int b) {
	if (a > b)
		return a;
	else
		return b;
}

void addedge(int u, int v) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = &pool[++top];
	tmp->v = u;
	tmp->next = h[v];
	h[v] = tmp;
}

int main(int argc, char* argv[]) {
	int u, v;
	cin >> n;
	for (int i = 1; i <= n - 1; i++) {
		cin >> u >> v;
		addedge(u, v);
	}
	for (int i = 1; i <= n; i++)
		cin >> w[i];

	for (int i = 1; i <= n; i++) {
		int count = 0;
		int Max1 = 0, Max2 = 0;
		long long Sum0 = 0;
		for (node* j = h[i]; j != NULL; j = j->next) {
			count++;
			tmp[count] = w[j->v];
			Sum0 += tmp[count];
			Sum0 %= Mod;
		}
		if (count <= 1)
			continue;
		sort(tmp + 1, tmp + count + 1, [](int x, int y)->const bool {return x > y; });
		Max = max(Max, tmp[1] * tmp[2]);
		for (int i = 1; i <= count; i++) {
			Sum += Sum0*tmp[i];
			Sum -= tmp[i] * tmp[i];
			Sum %= Mod;
		}
	}
	cout << Max << " " << Sum << endl;




	return 0;
}

#endif
