/*
 DOCUMENT NAME "20181102-luogu1220.cpp"
 CREATION DATE 2018-11-02
 SIGNATURE CODE_20181102_LUOGU1220
 COMMENT P1220 ¹ØÂ·µÆ
*/


#include <cstdlib>
#include <iostream>
using namespace std;

template<typename IntType>
void read(IntType& val) {
	val = 0;
	int c;
	bool inv = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			inv = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = getchar()));
	if (inv)
		val = -val;
}

const int MaxN = 100;

int n;
int power[MaxN], ldis[MaxN], rdis[MaxN];
int ppow[MaxN], pldis[MaxN], prdis[MaxN];





int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		
	}

	return 0;
}


