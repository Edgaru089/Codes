/*
DOCUMENT CODE "20171111-luogu1019.cpp"
CREATION DATE 2017-11-11
SIGNATURE CODE_20171111_LUOGU1019
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171111_LUOGU1019

#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include <list>
#include <queue>
#include <string>
#include <set>
using namespace std;

typedef pair<string, int> Pair;

map<char, list<string>> M;
queue<Pair> Q;
set<string> isVaild;
int step[256];

int ans;
int n;
string str[21];
char ch;

const bool contains(string large, string find) {
	if (large.size() < find.size())
		return false;
	for (int i = 0; i <= large.size() - find.size(); i++) {
		if (large.substr(i, find.size()) == find)
			return true;
	}
	return false;
}

const bool check(string x, string y) {
	if (!contains(x, y) && !contains(y, x))
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {

	for (char i = 32; i <= 126; i++) {
		M.insert(pair<char, list<string>>(i, list<string>()));
		M[i].clear();
	}

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> str[i];
		M[str[i][0]].push_back(str[i]);
	}
	cin >> ch;

	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++) {
			if (check(str[i], str[j])) {
				isVaild.insert(str[i] + '#' + str[j]);
				isVaild.insert(str[j] + '#' + str[i]);
			}
		}

	for (string& i : M[ch])
		Q.push(Pair(i, 0));
	step[ch] = 0;
	while (!Q.empty()) {
		string s = Q.front().first;
		int step = Q.front().second;
		Q.pop();

		ans = max(ans, step);

		//cout << "Step: " << step << endl;

		for (string i : M[s[s.size() - 1]]) {
			if (isVaild.find(s + '#' + i) != isVaild.end()) {
				Q.push(Pair(i, step + 1));
			}
		}
	}

	cout << ans << endl;

	return 0;
}

#endif

