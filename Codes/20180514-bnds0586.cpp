/*
DOCUMENT CODE "20180514-bnds0586.cpp"
CREATION DATE 2018-05-14
SIGNATURE CODE_20180514_BNDS0586
TOPIC test 20180514
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20180514_BNDS0586

#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

char str[200001], str2[200001];
int len;

int main(int argc, char* argv[]) {

	cin >> str;
	len = strlen(str);

	int len2 = -1;
	do {
		if (len2 != -1) {
			len = len2;
			strcpy(str, str2);
		}

		len2 = 0;
		memset(str2, 0, sizeof(str2));

		bool flagStart = false, flagEnd = false;
		for (int i = 0; i < len; i++) {
			if (flagEnd || i <= 1 || str[i] != str[i - 1]) {
				if (flagStart)
					flagEnd = true;
				len2++;
				str2[len2 - 1] = str[i];
			}
			else {
				flagStart = true;
				if (i <= 1 || str[i - 2] != str[i - 1]) {
					len2--;
					str2[len2] = '\0';
				}
			}
		}

		str2[len2] = '\0';

	} while (len2 != len);

	cout << str << endl;

	return 0;
}

#endif

