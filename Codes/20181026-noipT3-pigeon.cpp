/*
 DOCUMENT NAME "20181026-noipT3-pigeon.cpp"
 CREATION DATE 2018-10-26
 SIGNATURE CODE_20181026_NOIPT3_PIGEON
 COMMENT pigeon.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181026_NOIPT3_PIGEON

#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define FILENAME "pigeon"

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

const int MaxN = 2e5 + 10, MaxM = 2e5 + 10;

int n, m;
int d[MaxN];
int opt[MaxM], x[MaxM], y[MaxM], z[MaxM];

/* Chairman Tree */
struct node {
	int left, right;
	int sum;
	node* lson, *rson;
};

node mem[2 * (MaxN + MaxM) + 40 * MaxM], *memtop = mem;
node* root[MaxN + MaxM];
#define ALLOCATE (++memtop)
int vercnt = 1;
int offset = 0;

map<int, int> dx;
int dxrev[MaxN + MaxM];

void _build(int left, int right, node*& p) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	p->sum = 0;
	if (left != right) {
		int mid = (left + right) / 2;
		_build(left, mid, p->lson);
		_build(mid + 1, right, p->rson);
	}
}

void build(int cnt) {
	_build(1, cnt, root[0]);
	vercnt = 1;
}

void _preinsert(int pos, node*& p, node* prev) {
	p = ALLOCATE;
	memcpy(p, prev, sizeof(node));
	if (p->left == p->right&&p->right == pos) {
		p->sum++;
		return;
	}
	if (p->lson->right >= pos)
		_preinsert(pos, p->lson, prev->lson);
	else
		_preinsert(pos, p->rson, prev->rson);
	p->sum = p->lson->sum + p->rson->sum;
}

void preinsert(int pos) {
	int nextver = vercnt++;
	_preinsert(pos, root[nextver], root[nextver - 1]);
}

void postinsert(int pos) {
	offset++;
	int nextver = vercnt++;
	_preinsert(pos, root[nextver], root[nextver - 1]);
}

void remove() {
	offset--;
	vercnt--;
	root[vercnt] = 0;
}

// (l, r]
int _querykth(int k, node* l, node* r) {
	if (l->left == l->right)
		return l->left;
	if (r->lson->sum - l->lson->sum >= k)
		return _querykth(k, l->lson, r->lson);
	else
		return _querykth(k - (r->lson->sum - l->lson->sum), l->rson, r->rson);
}

// [l, r], in input format
int querykth(int left, int right, int k) {
	return _querykth(k, root[(vercnt - 1) - right /* + 1 - 1 */], root[(vercnt - 1) - left + 1]);
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

	read(n); read(m);
	for (int i = 1; i <= n; i++) {
		read(d[n - i + 1]);
		dx.insert(make_pair(d[n - i + 1], 0));
	}
	for (int i = 1; i <= m; i++) {
		read(opt[i]);
		if (opt[i] == 2) {
			read(x[i]);
			dx.insert(make_pair(x[i], 0));
		}
		if (opt[i] == 3) {
			read(x[i]); read(y[i]); read(z[i]);
		}
	}
	int xcnt = 0;
	for (map<int, int>::iterator i = dx.begin(); i != dx.end(); i++) {
		i->second = ++xcnt;
		dxrev[xcnt] = i->first;
	}
	for (int i = 1; i <= n; i++)
		d[i] = dx[d[i]];
	for (int i = 1; i <= m; i++)
		if (opt[i] == 2)
			x[i] = dx[x[i]];

	build(xcnt + 10);

	for (int i = 1; i <= n; i++)
		preinsert(d[i]);

	for (int i = 1; i <= m; i++) {
		if (opt[i] == 1)
			remove();
		else if (opt[i] == 2)
			postinsert(x[i]);
		else
			println(dxrev[querykth(x[i], y[i], z[i])]);
	}


	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

#endif

