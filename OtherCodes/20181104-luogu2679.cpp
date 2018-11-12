/*
 DOCUMENT NAME "20181104-luogu2679.cpp"
 CREATION DATE 2018-11-04
 SIGNATURE CODE_20181104_LUOGU2679
 COMMENT P2679 子串
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

template<typename IntType = int>
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
template<>
void read<string>(string& val){
	val.clear();
	// HACK Place an empty char at the front to make the string 1-started in id
	val.push_back(' ');
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		val.push_back((char)c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

const int MaxN=1000+10,MaxM=200+10,MaxK=200+10;
const int Mod=1000000007;

int n,m,k;
string a,b;

int dp[2][MaxM][MaxK][2];
int curi;



int main(int argc, char* argv[]) {

	read(n,m,k,a,b);

	dp[0][0][0][0]=1;
	dp[1][0][0][0]=1;

	for(int i=1;i<=n;i++){
		curi^=1;
		for(int j=1;j<=m;j++){
			for(int l=1;l<=k;l++)
				if(a[i]==b[j]){
					dp[curi][j][l][0]=((long long)dp[curi^1][j][l][0]+dp[curi^1][j][l][1])%Mod;
					dp[curi][j][l][1]=((long long)dp[curi^1][j-1][l-1][1]+dp[curi^1][j-1][l][1]+dp[curi^1][j-1][l-1][0])%Mod;
				}else{
					dp[curi][j][l][0]=((long long)dp[curi^1][j][l][0]+dp[curi^1][j][l][1])%Mod;
					dp[curi][j][l][1]=0;
				}
		}
	}

	printf("%lld\n",((long long)dp[curi][m][k][1]+dp[curi][m][k][0])%Mod);

	return 0;
}

