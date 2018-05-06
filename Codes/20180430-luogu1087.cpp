/*
DOCUMENT CODE "20180430-luogu1087.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1087
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1087

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

struct node {
	char type;
	string str;
	node* lson, *rson;
};

node pool[10000], *root;
int top, n;

void build(string& str, node*& p = root) {
	p = &pool[++top];

	char ch = str[0];
	p->type = 'X';
	if (ch == '0')
		p->type = 'B';
	else if (ch == '1')
		p->type = 'I';
	for (char i : str)
		if (i != ch) {
			p->type = 'F';
			break;
		}

	if (str.size() > 1) {
		build(str.substr(0u, str.size() / 2), p->lson);
		build(str.substr(str.size() / 2), p->rson);
	}
}

string back(node* p = root) {
	if (p == nullptr)
		return "";
	string str;
	str += back(p->lson);
	str += back(p->rson);
	str += p->type;
	return str;
}


int main(int argc, char* argv[]) {

	string str;

	cin >> n;
	cin >> str;

	build(str);

	cout << back() << endl;

	return 0;
}

#endif

