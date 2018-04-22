/*
DOCUMENT CODE "20180422-luogu1010.cpp"
CREATION DATE 2018-04-22
SIGNATURE CODE_20180422_LUOGU1010
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180422_LUOGU1010

#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

string create(int);
string wrap(int);

string wrap(int n) {
	if (n == 1)
		return "2";
	else
		return "2(" + create(n) + ")";
}

string create(int n) {
	if (n == 0)
		return "0";
	else if (n == 1)
		return "2(0)";
	else if (n == 2)
		return "2";
	else {
		stack<int> st;
		int i = 0;
		while (n != 0) {
			if (n % 2 == 1)
				st.push(i);
			n /= 2;
			i++;
		}
		string ans = wrap(st.top());
		st.pop();
		while (!st.empty()) {
			ans += "+" + wrap(st.top());
			st.pop();
		}
		return ans;
	}
}

int main(int argc, char* argv[]) {
	int n;
	cin >> n;
	cout << create(n) << endl;
	return 0;
}

#endif

