/*
DOCUMENT CODE "luogu1098.cpp"
CREATION DATE 2017-11-09
SIGNATURE CODE_20171109_LUOGU1098
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20171109_LUOGU1098

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const string reverse(string& a) {
	string ans;
	ans.resize(a.size());
	for (int i = 0; i < a.size(); i++)
		ans[a.size() - i - 1] = a[i];
	return ans;
}

const string toUpperCase(string a) {
	for (char&i : a)
		i = toupper(i);
	return a;
}

const string toLowerCase(string a) {
	for (char&i : a)
		i = tolower(i);
	return a;
}

const string expand(char left, char right, int param1, int param2, int param3) {
	string ans;
	left = tolower(left);
	right = tolower(right);
	for (char i = left + 1; i != right; i++) {
		// °Ñ×Ö·ûÁ¬Ðø p2 ¸ö
		ans += string(param2, i);
	}
	// p1 == 1 -- ×ÖÄ¸Ð¡Ð´
	if (param1 == 1)
		ans = toLowerCase(ans);
	// p1 == 2 -- ×ÖÄ¸´óÐ´
	if (param1 == 2)
		ans = toUpperCase(ans);
	// p1 == 3 -- ÓÃ·ÖºÅÌî³ä
	if (param1 == 3)
		ans = string(ans.size(), '*');
	// p3 == 2 -- ÄæÐò
	if (param3 == 2)
		ans = reverse(ans);

	return ans;
}

int main(int argc, char* argv[]) {
	int p1, p2, p3;
	string str;
	string ans;

	cin >> p1 >> p2 >> p3;
	cin >> str;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '-'&&i > 0 && i < str.size() - 1 &&
			((islower(str[i - 1]) && islower(str[i + 1])) || (isupper(str[i - 1]) && isupper(str[i + 1])) || (isdigit(str[i - 1]) && isdigit(str[i + 1]))) &&
			str[i - 1] < str[i + 1]) {
			ans += expand(str[i - 1], str[i + 1], p1, p2, p3);
		}
		else
			ans += str[i];
	}

	cout << ans << endl;

	return 0;
}

#endif
