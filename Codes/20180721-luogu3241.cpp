/*
DOCUMENT NAME "20180721-luogu3241.cpp"
CREATION DATE 2018-07-21
SIGNATURE CODE_20180721_LUOGU3241
COMMENT [HNOI2015]开店 / 树链剖分+主席树
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180721_LUOGU3241

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

constexpr int infinity = 1e9;
constexpr int MaxN = 1.5e5 + 10, MaxM = MaxN, MaxQ = 2e5 + 10, MaxA = 1e9;

int read() {
	int val = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return val;
}
void read(int& val) { val = read(); }
template<typename... Args>
void read(int& val, Args&... args) { val = read(); read(args...); }

int n, q, A;


namespace algorithm {
	int discreteprefixdis[MaxN], dfnprefixdis[MaxN];
}


namespace graph {
	struct node {
		int v, len;
		node* next;
	};

	node* h[MaxN];
	node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

	void addedge(int u, int v, int len) {
		node* p = ALLOCATE;
		p->v = v;
		p->len = len;
		p->next = h[u];
		h[u] = p;
		p = ALLOCATE;
		p->v = u;
		p->len = len;
		p->next = h[v];
		h[v] = p;
	}
}


namespace chairmantree {
	struct node {
		int left, right;
		int time, sum;
		int verid;
		node* lson, *rson;
	};

	node* root[MaxN];
	int vercnt;
	node mem[2 * MaxN + 18 * MaxN], *memtop = mem;

	void build(int left = 1, int right = n, node*& p = root[0]) {
		p = ALLOCATE;
		p->left = left;
		p->right = right;
		p->time = 0;
		p->verid = 0;
		if (left != right) {
			int mid = (left + right) / 2;
			build(left, mid, p->lson);
			build(mid + 1, right, p->rson);
		}
	}

	void _add(int left, int right, node* prev, node*& cur, int curid) {
		cur = ALLOCATE;
		cur->left = prev->left;
		cur->right = prev->right;
		cur->lson = prev->lson;
		cur->rson = prev->rson;
		cur->verid = curid;
		cur->time = prev->time;
		cur->sum = prev->sum;
		if (left == prev->left&&right == prev->right) {
			cur->time++;
			return;
		}
		cur->sum += algorithm::dfnprefixdis[right] - algorithm::dfnprefixdis[left - 1];
		if (prev->lson->right >= right)
			_add(left, right, prev->lson, cur->lson, curid);
		else if (prev->rson->left <= left)
			_add(left, right, prev->rson, cur->rson, curid);
		else {
			_add(left, prev->lson->right, prev->lson, cur->lson, curid);
			_add(prev->rson->left, right, prev->rson, cur->rson, curid);
		}
	}

	int add(int left, int right) {
		vercnt++;
		_add(left, right, root[vercnt - 1], root[vercnt], vercnt);
		return vercnt;
	}

	// [left, right]
	int _query(int left, int right, node* p) {
		int thissection = (algorithm::dfnprefixdis[right] - algorithm::dfnprefixdis[left - 1]) * p->time;
		if (left == p->left&&right == p->right)
			return thissection + p->sum;
		else if (p->lson->right >= right)
			return thissection + _query(left, right, p->lson);
		else if (p->rson->left <= left)
			return thissection + _query(left, right, p->rson);
		else
			return thissection + (_query(left, p->lson->right, p->lson) +
								  _query(p->rson->left, right, p->rson));
	}

	// [sectionleft, sectionright]
	int query(int sectionleft, int sectionright, int version) {
		return _query(sectionleft, sectionright, root[version]);
	}
}


namespace discrete {
	struct valtype {
		int val;
		int id;
	};

	int valinput[MaxN];
	valtype vals[MaxN];
	int valoutput[MaxN];

	void run() {
		for (int i = 1; i <= n; i++)
			vals[i] = valtype{ valinput[i], i };
		sort(vals + 1, vals + n + 1, [](const valtype& x, const valtype& y)->bool {
			if (x.val < y.val)
				return true;
			else if (x.val == y.val&&x.id < y.id)
				return true;
			else
				return false;
		});
		for (int i = 1; i <= n; i++)
			valoutput[vals[i].id] = i;
	}
}


namespace hld {
	using namespace graph;
	using namespace discrete;
	using namespace algorithm;

	int father[MaxN], dis[MaxN], size[MaxN];
	int stime, dfn[MaxN], heavy[MaxN], top[MaxN];
	int dfnval[MaxN];

	void dfs1(int u = 1, int from = 0) {
		father[u] = from;
		size[u] = 1;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u]) {
				dis[v] = dis[u] + p->len;
				dfs1(v, u);
			}
		}
		int maxsize = 0, maxid = 0;
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u])
				if (maxsize < size[v]) {
					maxsize = size[v];
					maxid = v;
				}
		}
		heavy[u] = maxid;
	}

	void dfs2(int u = 1, int t = 1) {
		dfn[u] = ++stime;
		top[u] = t;
		if (heavy[u] != 0)
			dfs2(heavy[u], t);
		for (node* p = h[u]; p != nullptr; p = p->next) {
			int v = p->v;
			if (v != father[u] && v != heavy[u])
				dfs2(v, v);
		}
	}

	int query(int verid, int u) {
		int sum = 0;
		while (top[u] != 1) {
			sum += chairmantree::query(dfn[top[u]], dfn[u], verid);
			u = father[top[u]];
		}
		sum += chairmantree::query(dfn[1], dfn[u], verid);
		return sum;
	}
}


namespace algorithm {
	using namespace graph;
	using namespace hld;

	void build() {
		discrete::run();
		dfs1();
		dfs2();
		for (int i = 1; i <= n; i++) {
			dfnval[dfn[vals[i].id]] = dis[vals[i].id];
		}
		for (int i = 1; i <= n; i++) {
			dfnprefixdis[i] = dfnprefixdis[i - 1] + dfnval[i];
			discreteprefixdis[i] = discreteprefixdis[i - 1] + dis[vals[i].id];
		}
		chairmantree::build();
		for (int i = 1; i <= n; i++)
			chairmantree::add(dfn[1], dfn[vals[i].id]);
	}

	int query(int u, int l, int r) {
		if (l > r)
			swap(l, r);
		l = lower_bound(vals + 1, vals + n + 1, valtype{ l, 0 }, [](const valtype& x, const valtype& y)->bool {
			if (x.val < y.val)
				return true;
			else if (x.val == y.val&&x.id < y.id)
				return true;
			else
				return false;
		}) - vals;
		r = upper_bound(vals + 1, vals + n + 1, valtype{ r, (int)1e9 }, [](const valtype& x, const valtype& y)->bool {
			if (x.val < y.val)
				return true;
			else if (x.val == y.val&&x.id < y.id)
				return true;
			else
				return false;
		}) - vals - 1;
		int leftval = hld::query(l - 1, u);
		int rightval = hld::query(r, u);
		return (r - l + 1)*dis[u] + (discreteprefixdis[r] - discreteprefixdis[l - 1]) - 2 * (rightval - leftval);
	}
}



int main(int argc, char* argv[]) {

	read(n, q, A);
	for (int i = 1; i <= n; i++)
		read(discrete::valinput[i]);
	int u, v, l;
	for (int i = 1; i <= n - 1; i++) {
		read(u, v, l);
		graph::addedge(u, v, l);
	}

	algorithm::build();

	int lastans = 0;
	int a, b;
	for (int i = 1; i <= q; i++) {
		read(u, a, b);
		int l = min((a + lastans) % A, (b + lastans) % A);
		int r = max((a + lastans) % A, (b + lastans) % A);
		printf("%d\n", lastans = algorithm::query(u, l, r));
	}

	return 0;
}

#endif

