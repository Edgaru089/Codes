/*
DOCUMENT CODE "20180430-luogu1996.cpp"
CREATION DATE 2018-04-30
SIGNATURE CODE_20180430_LUOGU1996
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180430_LUOGU1996

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int n, m;
list<int> l;
vector<int> ans;


int main(int argc, char* argv[]) {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		l.push_back(i);

	list<int>::iterator i;
	i = l.begin();

	while (!l.empty()) {
		for (int j = 1; j <= m - 1; j++) {
			if (i == l.end())
				i = l.begin();
			i++;
			if (i == l.end())
				i = l.begin();
		}
		ans.push_back(*i);
		i = l.erase(i);
	}

	if (ans.size() > 0)
		cout << ans[0];
	for (int i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	cout << endl;

	return 0;
}

#endif

