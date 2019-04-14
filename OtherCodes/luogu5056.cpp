#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)
#define PASS printf("Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		printf("Debug Assertation Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PASS
#define ASSERT(expr)
#endif

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
template<>
void read<string>(string& val){
	val.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		val.push_back((char)c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}

typedef long long ll;
const int MaxN=14,MaxM=14;

int n,m;
bool flag[MaxN][MaxM];

int pow3[20];

// 1594323 = 3^13
//int dp[MaxM][1594323+10],tmp[1594323+10];
unordered_map<int,ll> dp[MaxM],tmp;


#define powx(val) (1<<((val)<<1));
#define powmul(thing, exp) ((thing)<<((exp)<<1))
#define powdiv(thing, exp) ((thing)>>((exp)<<1))
#define powmask(thing, exp) ((thing)&((1<<((exp)<<1))-1))

//constexpr int getbit(int val,int exp){
//	return (val/pow3[exp])%3;
//	return (val/pow3[exp])&0x3;
//	return (val>>(1<<exp))&0x3;

//	return powdiv(val,exp)&0x3;
//}

#define getbit(val,exp) (powdiv(val,exp)&0x3)


//constexpr int _setbit(int where,int exp,int bitval){
//	int top=(where/pow3[exp+1])*pow3[exp+1];
//	int bot=where%pow3[exp];
//	return where=top+bitval*pow3[exp]+bot;

//	int top=(where>>((exp+1)<<2))<<(1<<((exp+1)<<2));
//	int bot=where&((1<<(exp<<1))-1);
//	return where=(top+(bitval<<(exp<<1))+bot);

//	int top=powmul(powdiv(where,exp+1),exp+1);
//	int bot=powmask(where,exp);
//	return where=top+powmul(bitval,exp)+bot;
//	return powmul(powdiv(where,exp+1),exp+1)+powmul(bitval,exp)+powmask(where,exp);
//}

#define _setbit(where,exp,bitval) (powmul(powdiv(where,exp+1),exp+1)+powmul(bitval,exp)+powmask(where,exp))
#define setbit(a,b,c) a=_setbit(a,b,c)


inline int findmatch(int val,int exp){
	int c=getbit(val,exp);
	if(c==0)
		return c;
	int l=0;
	if(c==1){ // opening
		for(int k=exp+1;;k++){
			int b=getbit(val,k);
			if(b==1)
				l++;
			else if(b==2)
				if(l==0)
					return k;
				else
					l--;
		}
	}else{ // closing
		for(int k=exp-1;k>=0;k--){
			int b=getbit(val,k);
			if(b==2)
				l++;
			else if(b==1)
				if(l==0)
					return k;
				else
					l--;
		}
	}
//	abort();
	return -1;
}



int main(int argc, char* argv[]) {

	/*
	
	int l;
	read(l);
	int o=0;
	setbit(o,l,2);
	printf("%d (%d)\n",o,getbit(o,l));


	o=0;
	setbit(o,1,1);
	setbit(o,3,1);
	setbit(o,4,2);
	setbit(o,6,1);
	setbit(o,8,2);
	setbit(o,11,2);

	printf("%d %d %d\n",findmatch(o,1),findmatch(o,11),findmatch(o,8));
	*/

	string s;
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(s);
		for(int j=1;j<=m;j++)
			flag[i][j]=(s[j-1]=='.');
	}

	pow3[0]=1;
	for(int i=1;i<=15;i++)
//		pow3[i]=pow3[i-1]*3;
		pow3[i]=pow3[i-1]<<2;


	dp[0][0]=1;
	int cur=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			for(auto sp:dp[j]){
				int s=sp.first;
				ll dps=sp.second;
				int l=getbit(s,j),r=getbit(s,j+1);
				if(flag[i][j+1]){
					if(l==0&&r==0){
						int ns=s;
						setbit(ns,j,1);
						setbit(ns,j+1,2);
						dp[j+1][ns]+=dps;
					}else if(l==1&&r==0){
						int ns=s;
						dp[j+1][ns]+=dps;
						setbit(ns,j,0);
						setbit(ns,j+1,1);
						dp[j+1][ns]+=dps;
					}else if(l==0&&r==1){
						int ns=s;
						dp[j+1][ns]+=dps;
						setbit(ns,j,1);
						setbit(ns,j+1,0);
						dp[j+1][ns]+=dps;
					}else if(l==2&&r==0){
						int ns=s;
						dp[j+1][ns]+=dps;
						setbit(ns,j,0);
						setbit(ns,j+1,2);
						dp[j+1][ns]+=dps;
					}else if(l==0&&r==2){
						int ns=s;
						dp[j+1][ns]+=dps;
						setbit(ns,j,2);
						setbit(ns,j+1,0);
						dp[j+1][ns]+=dps;
					}else if(l==2&&r==1){
						int ns=s;
						setbit(ns,j,0);
						setbit(ns,j+1,0);
						dp[j+1][ns]+=dps;
					}else if(l==1&&r==1){
						int pos=findmatch(s,j+1);
						int ns=s;
						setbit(ns,j,0);
						setbit(ns,j+1,0);
						setbit(ns,pos,1);
						dp[j+1][ns]+=dps;
					}else if(l==2&&r==2){
						int pos=findmatch(s,j);
						int ns=s;
						setbit(ns,j,0);
						setbit(ns,j+1,0);
						setbit(ns,pos,2);
						dp[j+1][ns]+=dps;
					}else if(l==1&&r==2){
						if(i==n&&j==m-1){
							int ns=s;
							setbit(ns,j,0);
							setbit(ns,j+1,0);
							dp[j+1][ns]+=dps;
						}
					}
					else
						abort();
				}else{
					if(l==r&&l==0)
						dp[j+1][s]+=dps;
				}
			}
		}
//		for(pair<const int,int>& k:tmp)
//			k.second=0;
		tmp.clear();
		for(auto k:dp[m])
			if(getbit(k.first,m+1)==0)
				tmp[k.first<<2]=k.second;
		for(int i=0;i<=m;i++)
			dp[i].clear();
//		for(int i=0;i<=m;i++){
//			for(pair<const int,int>& k:dp[i])
//				k.second=0;
//			dp[i].rehash(dp[i].size()*1.2);
//		}
		for(auto k:tmp)
			dp[0][k.first]=k.second;
	}

	printf("%lld\n",tmp[0]);



	return 0;
}


