/*
 DOCUMENT NAME "20181026-noipT2-center.cpp"
 CREATION DATE 2018-10-26
 SIGNATURE CODE_20181026_NOIPT2_CENTER
 COMMENT center.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181026_NOIPT2_CENTER

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define FILENAME "center"

#if (defined LOCAL || defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

const int MaxN = 1000 + 10, MaxQ = 1000 + 10, MaxM = 1e5 + 10, MaxK = 2e6 + 10;

int n, m, q;
int u, v;
int k, a[MaxK], d[MaxK];

struct node {
	int v;
	node* next;
};

node* h[MaxN];
node mem[2 * MaxM], *memtop = mem;
#define ALLOCATE (++memtop)

void addedge(int u, int v) {
	node* p = ALLOCATE;
	p->v = v;
	p->next = h[u];
	h[u] = p;
	p = ALLOCATE;
	p->v = u;
	p->next = h[v];
	h[v] = p;
}

int dep[MaxN][MaxN];

template<typename valtype, typename allocator>
struct linkedlist {
	struct node {
		valtype val;
		node* next;
	};

	node* root;

	void push_front(const valtype& val) {
		node* p = allocator()();
		p->val = val;
		p->next = root;
		root = p;
	}

};

linkedlist<int, allocator<int> >::node linkmem[MaxN*MaxN], *linkmemtop = linkmem;
struct listallocator {
	linkedlist<int, listallocator>::node* operator ()() {
		return reinterpret_cast<linkedlist<int, listallocator>::node*>(++linkmemtop);
	}
};


linkedlist<int, listallocator> depnodes[MaxN][MaxN];
typedef linkedlist<int, listallocator>::node listnode;

queue<int> Q;
void build(int i) {
	dep[i][i] = 0;
	Q.push(i);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (node* p = h[u]; p; p = p->next)
			if (dep[i][p->v] < 0) {
				dep[i][p->v] = dep[i][u] + 1;
				Q.push(p->v);
			}
	}
	for (int j = 1; j <= n; j++) {
		depnodes[i][dep[i][j]].push_front(j);
	}
}

bool flag[MaxN];

int countval() {
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= k; i++)
		for (int j = 0; j <= d[i]; j++)
			for (listnode* p = depnodes[a[i]][j].root; p; p = p->next)
				flag[p->val] = true;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (flag[i])
			ans++;
	}
	return ans;
}



int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);

	memset(dep, -1, sizeof(dep));

	read(n); read(m); read(q);
	for (int i = 1; i <= m; i++) {
		read(u); read(v);
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++)
		build(i);

	for (int i = 1; i <= q; i++) {
		read(k);
		for (int j = 1; j <= k; j++) {
			read(a[j]); read(d[j]);
		}

		println(countval());
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

