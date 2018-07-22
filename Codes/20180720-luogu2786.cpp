/*
DOCUMENT NAME "20180720-luogu2786.cpp"
CREATION DATE 2018-07-20
SIGNATURE CODE_20180720_LUOGU2786
COMMENT Ó¢Óï1£¨eng1£©- Ó¢Óï×÷ÎÄ
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180720_LUOGU2786

#include <cstdlib>
#include <iostream>
#include <unordered_map>
using namespace std;

int n, p;

int read() {
	int ans = 0;
	char c;
	while (!isdigit(c = getchar()));
	do {
		ans = (ans << 1) + (ans << 3) + c - '0';
	} while (isdigit(c = getchar()));
	return ans;
}

void read(int& val) { val = read(); }

bool isstr(int c) {
	return c != ' '&&c != ','&&c != '.'&&c != '!'&&c != '?'&&c != '\n'&&c != '\r';
}

char buf[30001];
void readstr(string& str) {
	str.clear();
	int c = 0;
	while (!isstr(c = getchar()) && c != EOF);
	if (c == EOF)
		return;
	do {
		str.push_back((char)c);
	} while (isstr(c = getchar()) && c != EOF);
}

string str;
unordered_map<string, int> m;

int main(int argc, char* argv[]) {

	m.rehash(1000000);
	read(n); read(p);
	for (int i = 1; i <= n; i++) {
		readstr(str);
		m[str] = read();
	}


	readstr(str);
	int sum = 0;
	do {
		unordered_map<string, int>::iterator i = m.find(str);
		if (i != m.end())
			sum = (sum + i->second) % p;
		readstr(str);
	} while (str != "");

	printf("%d\n", sum);

	return 0;
}

#endif

