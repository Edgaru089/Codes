/*
 DOCUMENT NAME "20181220-bzoj1018.cpp"
 CREATION DATE 2018-12-20
 SIGNATURE CODE_20181220_BZOJ1018
 COMMENT 1018: [SHOI2008]¶ÂÈûµÄ½»Í¨traffic
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181220_BZOJ1018

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

template<>
void read<string>(string& val) {
	val.clear();
	int c;
	while (iscntrl(c = getchar()) || c == ' ' || c == '\t');
	do {
		val.push_back(c);
	} while (!(iscntrl(c = getchar()) || c == ' ' || c == '\t'));
}

const int MaxN = 100000, MaxM = 100000;

int n, m;
int r1, c1, r2, c2;
string str;

struct block {
/*
	s1 t s2
	+--+--+
	| mid |
	+--+--+
	s3 b s4
*/
	bool s1_s2, s3_s4, s1_s3, s2_s4;
	bool midt, midb;
};

struct node {
	int left, right;
	int mid;
	node* lson, *rson;
	block b;
};

node* root;
node mem[2 * MaxN], *memtop = mem;
#define ALLOCATE (++memtop)

void build(int l = 1, int r = n, node*& p = root) {
	p = ALLOCATE;
	p->left = l;
	p->right = r;
	p->mid = (l + r) / 2;
	if (l == r) {
		p->b = block{ 1, 1, 0, 0, 1, 1 };
	} else {
		build(l, p->mid, p->lson);
		build(p->mid + 1, r, p->rson);
	}
}

block merge(const block& bl, const block& br, bool midt, bool midb) {
	block b = { 0, 0, 0, 0, 0, 0 };
	b.midt = midt;
	b.midb = midb;
	b.s1_s2 =
		((bl.s1_s2 || (bl.s1_s3&&bl.s3_s4&&bl.s2_s4))
			&& b.midt &&
		(br.s1_s2 || (br.s1_s3&&br.s3_s4&&br.s2_s4)))
		||
		(((bl.s1_s3&&bl.s3_s4) || (bl.s1_s2&&bl.s2_s4))
			&& b.midb &&
		((br.s3_s4&&br.s2_s4) || (br.s1_s3&&br.s1_s2)));
	b.s3_s4 =
		(((bl.s1_s3&&bl.s1_s2) || (bl.s3_s4&&bl.s2_s4))
			&& b.midt &&
		((br.s1_s2&&br.s2_s4) || (br.s1_s3&&br.s3_s4)))
		||
		((bl.s3_s4 || (bl.s1_s3&&bl.s1_s2&&bl.s2_s4))
			&& b.midb &&
		(br.s3_s4 || (br.s1_s3&&br.s1_s2&&br.s2_s4)));
	b.s1_s3 = bl.s1_s3;
	b.s2_s4 = br.s2_s4;
	return b;
}

void update(node* p) {
	if (p->left == p->right)
		return;
	const block& bl = p->lson->b, &br = p->rson->b;
	block& b = p->b;
	b = merge(bl, br, b.midt, b.midb);
}

void connectHTop(int lpnt, bool state, node* p = root) {
	if (p->mid == lpnt) {
		p->b.midt = state;
		update(p);
		return;
	}
	if (p->lson->right >= lpnt)
		connectHTop(lpnt, state, p->lson);
	else
		connectHTop(lpnt, state, p->rson);
	update(p);
}

void connectHBot(int lpnt, bool state, node* p = root) {
	if (p->mid == lpnt) {
		p->b.midb = state;
		update(p);
		return;
	}
	if (p->lson->right >= lpnt)
		connectHBot(lpnt, state, p->lson);
	else
		connectHBot(lpnt, state, p->rson);
	update(p);
}

void connectV(int pnt, bool state, node* p = root) {
	if (p->left == pnt)
		p->b.s1_s3 = state;
	if (p->right == pnt)
		p->b.s2_s4 = state;
	if (p->left != p->right) {
		if (p->lson->right >= pnt)
			connectV(pnt, state, p->lson);
		else
			connectV(pnt, state, p->rson);
	}
	update(p);
}

block query(int l, int r, node* p = root) {
	if (p->left == l && p->right == r)
		return p->b;
	if (p->lson->right >= r)
		return query(l, r, p->lson);
	else if (p->rson->left <= l)
		return query(l, r, p->rson);
	else
		return merge(query(l, p->lson->right, p->lson),
					 query(p->rson->left, r, p->rson),
					 p->b.midt, p->b.midb);
}



int main(int argc, char* argv[]) {

	read(n);

	build();

	for (;;) {
		read(str);
		if (str[0] == 'E') // End
			break;
		read(r1); read(c1); read(r2); read(c2);
		if (r1 == r2) {
			if (str[0] == 'O') { // Open
				if (r1 == 1)
					connectHTop(min(c1, c2), true);
				else if (r1 == 2)
					connectHBot(min(c1, c2), true);
			} else if (str[0] == 'C') { // Close
				if (r1 == 1)
					connectHTop(min(c1, c2), false);
				else if (r1 == 2)
					connectHBot(min(c1, c2), false);
			} else if(str[0]=='A') { // Ask
				if (r1 == 1)
					printf("%c\n", query(min(c1, c2), max(c1, c2)).s1_s2 ? 'Y' : 'N');
				else if (r1 == 2)
					printf("%c\n", query(min(c1, c2), max(c1, c2)).s3_s4 ? 'Y' : 'N');
			} else
				abort();
		} else if (c1 == c2) {
			if (str[0] == 'O') // Open
				connectV(c1, true);
			else if (str[0] == 'C') // Close
				connectV(c1, false);
			else if (str[0] == 'A') // Ask
				printf("%c\n", query(c1, c1).s1_s3 ? 'Y' : 'N');
			else
				abort();
		} else {
			if (c1 > c2) {
				swap(r1, r2);
				swap(c1, c2);
			}
			if (r1 == 1) {
				block b = query(c1, c2);
				bool flag = (b.s1_s2 && b.s2_s4) || (b.s1_s3 && b.s3_s4);
				printf("%c\n", flag ? 'Y' : 'N');
			} else {
				block b = query(c1, c2);
				bool flag = (b.s1_s3 && b.s1_s2) || (b.s3_s4 && b.s2_s4);
				printf("%c\n", flag ? 'Y' : 'N');
			}
		}
	}


	return 0;
}

#endif

