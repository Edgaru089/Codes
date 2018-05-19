/*
DOCUMENT CODE "20180515-bnds0586.cpp"
CREATION DATE 2018-05-15
SIGNATURE CODE_20180515_BNDS0586
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180515_BNDS0586

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

char str[200001];
int len;

char s[200001];
int top = 0;

int main(int argc, char* argv[]) {

	cin >> str;
	len = strlen(str);

	for (int i = 0; i < len; i++) {
		s[top++] = str[i];
		if (top >= 2 && s[top - 1] == s[top - 2]) {
			top -= 2;
		}
	}

	s[top] = '\0';
	cout << s << endl;

	return 0;
}

#endif

