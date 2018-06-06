/*
DOCUMENT CODE "20180519-bnds0232.cpp"
CREATION DATE 2018-05-19
SIGNATURE CODE_20180519_BNDS0232
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180519_BNDS0232

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

struct node {
	bool exist;
	bool visited;
	node* next[26];
};

node pool[800000];
node* root;
int top;

node* allocate() { return &pool[++top]; }

void insert(char str[], size_t len) {
	node* p = root;
	for (int i = 0; i < len; i++) {
		if (p->next[str[i] - 'a'] == nullptr)
			p->next[str[i] - 'a'] = allocate();
		p = p->next[str[i] - 'a'];
	}
	p->exist = true;
}

node* find(char str[], size_t len) {
	node* p = root;
	for (int i = 0; i < len; i++) {
		if (p->next[str[i] - 'a'] == nullptr)
			return nullptr;
		p = p->next[str[i] - 'a'];
	}
	if (p->exist)
		return p;
	else
		return nullptr;
}

int n, m;
char str[100];

int main(int argc, char* argv[]) {
	root = allocate();

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str);
		insert(str, strlen(str));
	}

	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		cin >> str;
		node* p = find(str, strlen(str));
		if (p == nullptr)
			cout << "WRONG" << endl;
		else if (p->visited)
			cout << "REPEAT" << endl;
		else {
			p->visited = true;
			cout << "OK" << endl;
		}
	}

	return 0;
}

#endif
