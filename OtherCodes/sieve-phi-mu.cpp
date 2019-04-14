#include <cstdlib>
#include <iostream>
using namespace std;

#define PRINTARR(formatstr, arr, beginoff, size)				\
do{printf(#arr ":");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t%d", __i);										\
printf("\n");													\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	printf("\t" formatstr, arr[__i]);							\
printf("\n"); }while(false)

const int MaxN=1e7+10;

int n;

bool flag[MaxN];
int primes[MaxN],pcnt;
int phi[MaxN],mu[MaxN];
int a1[MaxN],a2[MaxN];

int t,a[MaxN];

int main(int argc, char* argv[]) {
//	ios::sync_with_stdio(false);

	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a[i];
		n=max(n,a[i]);
	}
	cout<<"n="<<n<<endl;

	for(int i=2;i<=n;i++)
		flag[i]=true;

	flag[1]=false;
	phi[1]=mu[1]=1;

	for(int i=2;i<=n;i++){
		if(flag[i]){
			primes[++pcnt]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt;j++){
			int p=primes[j];
			if(p*i>n)
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

	a1[1]=a2[1]=1;
	for(int i=2;i<=n;i++){
		a1[i]=a1[i-1]+phi[i];
		a2[i]=a2[i-1]+mu[i];
	}

	PRINTARR("%d",a1,1,10);
	PRINTARR("%d",a2,1,10);

	for(int i=1;i<=t;i++)
		cout<<a1[a[i]]<<' '<<a2[a[i]]<<endl;

//	PRINTARR("%d",phi,1,n);
//	PRINTARR("%d",mu,1,n);

	return 0;
}


