/*
DOCUMENT NAME "20180808-bnds0744.cpp"
CREATION DATE 2018-08-08
SIGNATURE CODE_20180808_BNDS0744
COMMENT 2018-8-8模拟测验（二）-太鼓达人
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180808_BNDS0744

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
using namespace std;

constexpr int MaxK = 11 + 2;

int k;

struct node {
	string str;
	node* next0, *next1;
};

node mem[4096], *memtop = mem;
#define ALLOCATE (++memtop)
map<string, node*> nodes;
map<string, bool> been;

void build(string str) {
	if (str.length() < k) {
		build(str + '0');
		build(str + '1');
	}
	else {
		node* p = ALLOCATE;
		p->str = str;
		nodes[str] = p;
	}
	if (str.length() == 0) {
		for (auto& i : nodes) {
			i.second->next0 = nodes[i.first.substr(1) + '0'];
			i.second->next1 = nodes[i.first.substr(1) + '1'];
			been[i.first] = false;
		}
	}
}


int cnt = 0;
string ans;
void dfs(node* p) {
	if (been[p->str])
		return;
	been[p->str] = true;
	cnt++;

	if (cnt == (1 << k)) {
		while (ans[ans.length() - 1] == '0')
			ans.pop_back();
		cout << ans << endl;
		exit(0);
	}

	ans.push_back('0');
	dfs(p->next0);
	ans[ans.length() - 1] = '1';
	dfs(p->next1);
	ans.pop_back();

	been[p->str] = false;
	cnt--;
}


int main(int argc, char* argv[]) {

	cin >> k;

	build("");

	cout << (1 << k) << ' ';

	ans = string(k, '0');
	dfs(nodes[string(k, '0')]);

	return 0;
}

#endif

