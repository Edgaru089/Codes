#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <climits>
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

typedef long long ll;
typedef unsigned long long ull;

const int MaxN=3200000+10;
//const int MaxN=1664510+10;
int linearx=3200000;
//int linearx=1664510;
bool flag[MaxN];
int primes[MaxN],pcnt;
ll phi[MaxN],mu[MaxN];
ll sp[MaxN],sm[MaxN];

void linearsieve(){
	for(int i=2;i<=linearx;i++)
		flag[i]=true;

	flag[1]=false;
	phi[1]=mu[1]=1;

	for(int i=2;i<=linearx;i++){
		if(flag[i]){
			primes[++pcnt]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt;j++){
			int p=primes[j];
			if(p*i>linearx)
				break;
			flag[p*i]=false;
			if(i%p==0){
				phi[p*i]=p*phi[i];
				mu[p*i]=0;
				break;
			}else{
				phi[p*i]=phi[p]*phi[i]; // =phi[i]*(p-1)
				mu[p*i]=-mu[i];
			}
		}
	}
	for(int i=1;i<=linearx;i++){
		sp[i]=sp[i-1]+phi[i];
		sm[i]=sm[i-1]+mu[i];
	}
}

unordered_map<int,ll> phids,muds;
ll dusievephi(int x){
	if(x<=linearx)
		return sp[x];
	auto it=phids.find(x);
	if(it!=phids.end())
		return it->second;
	ull ans=(ull)x*((ull)x+1)/2ll;
	int l,r;
	for(int l=2;l<=x;l=r+1){
		r=x/(x/l);
		ans-=(r-l+1)*(dusievephi(x/l));
	}
	return phids[x]=ans;
}

ll dusievemu(int x){
	if(x<=linearx)
		return sm[x];
	auto it=muds.find(x);
	if(it!=muds.end())
		return it->second;
	ll ans=1;
	int l,r;
	for(int l=2;l<=x;l=r+1){
		r=x/(x/l);
		ans-=(r-l+1)*(dusievemu(x/l));
	}
	return muds[x]=ans;
}


int main(int argc, char* argv[]) {

//	linearx=10;
	linearsieve();

	int t;
	read(t);

	int a;
	for(int i=1;i<=t;i++){
		read(a);
		printf("%lld %lld\n",dusievephi(a),dusievemu(a));
	}

	return 0;
}


