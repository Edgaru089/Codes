/*
*** UNKNOWN CODE BACKLOG FROM FOLDER "BNDS" ***
DATE 2018-05-22 (ADDED ON 2018-06-29)
SIGNATURE CODE_20180522_BNDS0167_UNKNOWN
*/

#ifdef CODE_20180522_BNDS0167_UNKNOWN

#include <cstdlib>
#include <iostream>
using namespace std;

int n;
int a[10001],f[10001];

int main(){
	
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i]=1;
	}
	
	int Max=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[j]<=a[i])
				f[i]=max(f[i],f[j]+1);
		}
		Max=max(Max,f[i]);
	}
	
	cout<<Max<<endl;
	
	return 0;
}

#endif 
