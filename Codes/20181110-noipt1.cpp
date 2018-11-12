/*
 DOCUMENT NAME "20181110-noipt1.cpp"
 CREATION DATE 2018-11-10
 SIGNATURE CODE_20181110_NOIPT1
 COMMENT NOIP2018D1T1 ∆Ã…Ëµ¿¬∑
*/

#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20181110_NOIPT1

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

int n;
int a,cur;
long long ans;


int main(int argc, char* argv[]) {

	read(n);
	for(int i=1;i<=n;i++){
		read(a);
		if(a>cur)
			ans+=(a-cur);
		cur=a;
	}

	printf("%lld\n",ans);

	return 0;
}

#endif

