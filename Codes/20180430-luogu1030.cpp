/*
DOCUMENT CODE "20180430-luogu1030.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1030
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1030

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

struct node {
	char c;
	node* lson, *rson;
};

node pool[1001], *root;
int top;

void build(string mid, string back, node*& p = root) {
	if (mid.size() <= 0)
		return;
	p = &pool[++top];
	p->c = back[back.size() - 1];
	int pos = mid.find(p->c);
	build(mid.substr(0u, pos), back.substr(0u, pos), p->lson);
	build(mid.substr(pos + 1), back.substr(pos, mid.size() - pos - 1), p->rson);
}

string prev(node* p = root) {
	string str;
	str += p->c;
	if (p->lson != nullptr)
		str += prev(p->lson);
	if (p->rson != nullptr)
		str += prev(p->rson);
	return str;
}

int main(int argc, char* argv[]) {
	string x, y;
	cin >> x >> y;
	build(x, y);
	cout << prev() << endl;
	return 0;
}

#endif

