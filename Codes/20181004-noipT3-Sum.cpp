/*
 DOCUMENT NAME "20181004-noipT3-Sum.cpp"
 CREATION DATE 2018-10-04
 SIGNATURE CODE_20181004_NOIPT3_SUM
 COMMENT NOIP Ä£ÄâÈü 20181004 T3 Sum
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181004_NOIPT3_SUM

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

#define FILENAME "sum"
#define ENDLINE "\r\n"

#ifdef LOCAL
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int buffersize = 30 * 1024 * 1024;
char buffer[buffersize], *buffertop = buffer;
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
	while (iscntrl(c = GETCHAR) || isblank(c));
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || isblank(c)));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[buffersize], *writetop = bufferwrite;
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
	//if (val < 0) {
	//	PUTCHAR('-');
	//	val = -val;
	//}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	putstr(ENDLINE);
}

/******************** End of quickread template ********************/

const int MaxN = 1e5 + 10, MaxM = 1e5 + 10;
const int MaxK = MaxN + MaxM;

struct op {
	op() {}
	op(int p, int a, int b) :
		p(p), a(a), b(b) {}
	int p;
	int a, b;
};

int n, m;
int a[MaxN];
op s[MaxM];

struct seginfo {
	seginfo() {}
	seginfo(int x) { max = lmax = rmax = x; }
	seginfo(const seginfo& left, const seginfo& right) {
		max = ::max(::max(left.max, right.max), left.rmax + right.lmax);
		lmax = left.lmax;
		rmax = right.rmax;
		max = ::max(::max(max, lmax), rmax);
		bool lflag, rflag;
		if (lflag = left.lmax == left.rmax && left.rmax == left.max) {
			lmax = ::max(lmax, left.lmax + right.lmax);
			max = ::max(max, lmax);
		}
		if (rflag = right.rmax == right.lmax&&right.lmax == right.max) {
			rmax = ::max(rmax, right.rmax + left.rmax);
			max = ::max(max, rmax);
		}
		if (lflag&&rflag) {
			lmax = ::max(lmax, left.lmax + right.rmax);
			rmax = ::max(rmax, left.lmax + right.rmax);
			max = ::max(max, left.lmax + right.rmax);
		}
	}
	int max;
	int lmax, rmax;
};

struct node {
	int left, right;
	seginfo info;
	node* lson, *rson;
};

node mem[2 * MaxK], *memtop = mem;
#define ALLOCATE (++memtop)
node* root;

void build(int* d, int left, int right, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right) {
		p->info = seginfo(d[left]);
	}
	else {
		int mid = (left + right) / 2;
		build(d, left, mid, p->lson);
		build(d, mid + 1, right, p->rson);
		p->info = seginfo(p->lson->info, p->rson->info);
	}
}

void change(int id, int val, node* p = root) {
	if (p->left == p->right&&p->left == id) {
		p->info = seginfo(val);
		return;
	}
	if (p->lson->right >= id)
		change(id, val, p->lson);
	else /* p->rson->left <= id */
		change(id, val, p->rson);
	p->info = seginfo(p->lson->info, p->rson->info);
}

seginfo query(int left, int right, node* p = root) {
	if (p->left == left && p->right == right)
		return p->info;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return seginfo(query(left, p->lson->right, p->lson),
					   query(p->rson->left, right, p->rson));
}





int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	list<int> l;
	typedef list<int>::iterator li;

	read(n); read(m);
	for (int i = 1; i <= n; i++)
		l.push_back(read<int>());
	for (int i = 1; i <= m; i++) {
		int p, a, b;
		read(p); read(a); read(b);
		if (p == 1) {
			int j = 1;
			li k;
			for (k = l.begin(); j <= a; j++, k++);
			l.insert(k, b);
		}
		else { /* p == 2 */
			int j = 1;
			li k;
			for (k = l.begin(); j < a; j++, k++);
			int sum = 0, maxsum = -1e8;
			for (; j <= b; j++, k++) {
				sum += *k;
				maxsum = max(maxsum, sum);
				sum = max(sum, 0);
			}
			println(maxsum);
		}
	}

	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

