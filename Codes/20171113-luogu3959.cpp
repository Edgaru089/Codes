/*
DOCUMENT CODE "20171113-luogu3959.cpp"
CREATION DATE 2017-11-13
SIGNATURE CODE_20171113_LUOGU3959
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171113_LUOGU3959

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int infinity = 5000000;

struct st {

	st() {
		visited.clear();
		memset(been, 0, sizeof(been));
		memset(dep, 0, sizeof(dep));
		sum = 0;
	}

	st(const st& val) {
		this->_copy(val.visited, val.been, val.dep, val.sum);
	}

	st(vector<int>& visisted, bool* been, int* dep, int sum) {
		this->_copy(visited, been, dep, sum);
	}

	const st& operator = (st& right) {
		this->_copy(right.visited, right.been, right.dep, right.sum);
		return *this;
	}

	vector<int> visited;
	bool been[16];
	int dep[16];
	int sum;

private:
	void _copy(const vector<int>& visisted, const bool* been, const int* dep, const int sum) {
		this->visited = visisted;
		memcpy(this->been, been, sizeof(this->been));
		memcpy(this->dep, dep, sizeof(this->dep));
		this->sum = sum;
	}

};

queue<st> Q;

struct node {
	int v;
	node* next;
};

node pool[1001], *h[20];
int top;
int len[20][20];

int n, m;
int ans = infinity;

void addedge(int u, int v, int ulen) {
	node* tmp = &pool[++top];
	tmp->v = v;
	tmp->next = h[u];
	h[u] = tmp;
	tmp = &pool[++top];
	tmp->v = u;
	tmp->next = h[v];
	h[v] = tmp;

	len[u][v] = min(len[u][v], ulen);
	len[v][u] = min(len[v][u], ulen);
}


int main(int argc, char* argv[]) {

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			len[i][j] = infinity;

	for (int i = 1; i <= m; i++) {
		int u, v, len;
		cin >> u >> v >> len;
		addedge(u, v, len);
	}


	for (int l = 1; l <= n; l++) {

		st tmp;
		tmp.visited.push_back(l);
		tmp.been[l] = true;
		tmp.dep[l] = 1;
		tmp.sum = 0;
		Q.push(tmp);

		while (!Q.empty()) {
			st tmp = Q.front();
			Q.pop();

			if (tmp.visited.size() == n) {
				ans = min(ans, tmp.sum);
				continue;
			}

			for (int u : tmp.visited) {
				for (node* p = h[u]; p != NULL; p = p->next) {
					int v = p->v, len = ::len[u][v];
					if (!tmp.been[v]) {
						st c = tmp;
						c.been[v] = true;
						c.visited.push_back(v);
						c.dep[v] = c.dep[u] + 1;
						c.sum += c.dep[u] * len;
						Q.push(c);
					}
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}

#endif
