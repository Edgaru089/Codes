/*
DOCUMENT CODE "20180203-luogu1803.cpp"
CREATION DATE 2018-02-03
SIGNATURE CODE_20180203_LUOGU1803
TOPIC marcool[58.119.158.78]
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180203_LUOGU1803

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

struct st {
	int start, end;
};

st s[1000001];
int n;
int ans;

int main(int argc, char* argv[]) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i].start >> s[i].end;
	}
	sort(s + 1, s + n + 1, [](st x,st y)->bool {
		if (x.end < y.end)
			return true;
		else if (x.end == y.end&&x.start > y.start)
			return true;
		else
			return false;
	});
	ans = 0;
	int time = 0;
	for (int i = 1; i <= n;) {
		if (time <= s[i].start) {
			time = s[i].end;
			i++;
			ans++;
		}
		while (s[i].start < time)
			i++;
	}
	cout << ans << endl;
	return 0;
}

#endif

