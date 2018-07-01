/*
*** UNKNOWN CODE BACKLOG FROM FOLDER "BNDS" ***
DATE 2018-05-22 (ADDED ON 2018-06-29)
SIGNATURE CODE_20180522_BNDS0168_UNKNOWN
*/

#ifdef CODE_20180522_BNDS0167_UNKNOWN

#include <cstdlib>
#include <iostream>
using namespace std;

int n,m;
int w[10001],v[10001];
int f[10001];

int main(){
	
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i]>>v[i];
	}
	
	for(int i=1;i<=n;i++){
		for(int j=m;j>=w[i];j--){
			f[j]=max(f[j],f[j-w[i]]+v[i]);
		}
	}
	
	int Max=0;
	for(int i=0;i<=m;i++)
		Max=max(Max,f[i]);
		
	cout<<Max<<endl;
	
	return 0;
}

#endif
