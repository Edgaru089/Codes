/*
DOCUMENT CODE "20180619-bnds0085.cpp"
CREATION DATE 2018-06-19
SIGNATURE CODE_20180619_BNDS0085
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180619_BNDS0085

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

string d0[] = { "ling"s,"yi"s,"er"s,"san"s,"si"s,"wu"s,"liu"s,"qi"s,"ba"s,"jiu"s };
string d1[] = { ""s,"shi"s,"bai"s,"qian"s };
string d2[] = { "wan"s,"yi"s };

void get(int n, vector<string>& vec) {
	if (n <= 9999) {
		list<int> v0;
		while (n != 0) {
			v0.push_front(n % 10);
			n /= 10;
		}
		int i = v0.size() - 1;
		for (int d : v0) {
			if (d == 0) {
				i--;
				continue;
			}
			n /= 10;
			if (d != 0) {
				if (!vec.empty() && vec.back() != d1[i + 1])
					vec.push_back(d0[0]);
				if (i == 0)
					vec.push_back(d0[d]);
				else {
					vec.push_back(d0[d]);
					vec.push_back(d1[i]);
				}
			}
			i--;
		}
	}
	else if (99999999 >= n && n >= 10000) {
		get(n / 10000, vec);
		vec.push_back(d2[0]);
		get(n % 10000, vec);
	}
	else {

	}
}

int main(int argc, char* argv[]) {
	int n;
	cin >> n;
	vector<string> str;
	get(n, str);
	bool flag = true;
	for (string& s : str) {
		if (flag)
			flag = false;
		else
			cout << " ";
		cout << s;
	}
	cout << endl;
	return 0;
}

#endif

