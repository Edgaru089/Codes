/*
DOCUMENT CODE "20180508-luogu3375.cpp"
CREATION DATE 2018-05-08
SIGNATURE CODE_20180508_LUOGU3375
TOPIC kmp template
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180508_LUOGU3375

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

string s, p;
int Next[1000001];
vector<int> ans;

int main(int argc, char* argv[]) {

	cin >> s >> p;

	Next[0] = -1;
	for (int j = 2; j < p.length(); j++) {
		int k = Next[j - 1];
		while (k > 0 && p[k] != p[j])
			k = Next[k];
		if (p[j] == p[k])
			k++;
		Next[j] = k;
	}


	for (int t = 0;;) {
		int i = t, j = 0;
		for (; i < s.size() && j < p.size();) {
			if (s[i] == p[j]) {
				i++;
				j++;
				if (j == p.size()) {
					ans.push_back(i - j + 1);
					break;
				}
			}
			else {
				if (j != 0)
					j = Next[j];
				else
					i++;
			}
		}
		if (t != *(ans.end() - 1))
			t = *(ans.end() - 1);
		else
			break;
	}

	for (int i : ans)
		cout << i << endl;

	cout << 0;
	for (int i = 1; i < p.length(); i++)
		cout << ' ' << Next[i];
	cout << endl;

	return 0;
}

#endif

