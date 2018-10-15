/*
 DOCUMENT NAME "20181005-noipT3-Deconstruction.cpp"
 CREATION DATE 2018-10-05
 SIGNATURE CODE_20181005_NOIPT3_DECONSTRUCTION
 COMMENT deconstruction.cpp/in/out
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181005_NOIPT3_DECONSTRUCTION

#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

#define FILENAME "deconstruction"
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
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
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
	putstr(ENDLINE);
}

/******************** End of quickread template ********************/

const int MaxN = 500000 + 10, MaxP = 500000 + 10;

int n, p;
int a[MaxN + MaxP];

struct node {
	int left, right;
	int sum;
	node* lson, *rson;
};

node* root;
node mem[2 * (MaxN + MaxP) + 100], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int* d = a, int left = 1, int right = n + p, node*& p = root) {
	p = ALLOCATE;
	p->left = left;
	p->right = right;
	if (left == right)
		p->sum = d[left];
	else {
		int mid = (left + right) / 2;
		build(d, left, mid, p->lson);
		build(d, mid + 1, right, p->rson);
		p->sum = p->lson->sum + p->rson->sum;
	}
}

int query(int left, int right, node* p = root) {
	if (p->left == left && p->right == right)
		return p->sum;
	if (p->lson->right >= right)
		return query(left, right, p->lson);
	else if (p->rson->left <= left)
		return query(left, right, p->rson);
	else
		return (query(left, p->lson->right, p->lson) +
				query(p->rson->left, right, p->rson));
}

void change(int pos, int val, node* p = root) {
	if (p->left == p->right&&p->left == pos) {
		p->sum = val;
		return;
	}
	if (p->lson->right >= pos)
		change(pos, val, p->lson);
	else /* p->rson->left <= pos */
		change(pos, val, p->rson);
	p->sum = p->lson->sum + p->rson->sum;
}




int main(int argc, char* argv[]) {
#ifndef LOCAL
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#else
	FILE* in = stdin, *out = stdout;
#endif
	fread(buffer, 1, buffersize, in);

	read(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]);
	}

	read(p);

	build();

	for (int i = 1; i <= p; i++) {
		int k, x, y;
		read(k);
		if (k == 1) {
			read(x); read(y);
			change(x, y);
		}
		else if (k == 2)
			return 0;
		else if (k == 3) {
			read(x);
			n++;
			change(n, x);
		}
		else if (k == 4) {
			read(x); read(y);
			println(query(x, y));
		}
	}



	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	return 0;
}

#endif

