#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int infinity=1e8;
const int MaxN=100+10,MaxT=2000,MaxH=2500+100;

int d,n;
struct item{
	int t,f,h;
};
item a[MaxN];
int dp[MaxH];

bool cmp(const item& x,const item& y){
	return x.t<y.t;
}


int main(){

	cin>>d>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].t>>a[i].f>>a[i].h;

	sort(a+1,a+n+1,cmp);

	int maxt=0;
	for(int i=1;i<=n;i++)
		maxt=max(maxt,a[i].t);

	dp[0]=10;

	int ans=infinity;
	for(int i=1;i<=n;i++){
		for(int j=d;j>=0;j--){
			if(dp[j]>=a[i].t){
				dp[j+a[i].h]=max(dp[j+a[i].h],dp[j]);
				if(j+a[i].h>=d)
					ans=min(ans,a[i].t);
				dp[j]=max(dp[j],dp[j]+a[i].f);
			}
		}
	}

	if(dp[d]<=0)
		cout<<dp[0]<<endl;
	else
		cout<<ans<<endl;


	return 0;
}


