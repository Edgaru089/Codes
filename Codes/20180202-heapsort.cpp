/*
DOCUMENT CODE "heapsort.cpp"
CREATION DATE 2018-02-02
SIGNATURE CODE_20170202_HEAPSORT
TOPIC
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_20170202_HEAPSORT

#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

#define LSON(a) (a*2)
#define RSON(a) (a*2+1)
#define FATHER(a) (a/2)

int arr[10001];
int n;

void condense(int x){
	int w=x,xval=arr[x];
	if(LSON(x)<=n&&xval>arr[LSON(x)]){
		w = LSON(x);
		xval=arr[LSON(x)];
	}
	if(RSON(x)<=n&&xval>arr[RSON(x)]){
		w = RSON(x);
		xval=arr[RSON(x)];	
	}
	if (x != w)
	{	
		swap(arr[x],arr[w]);
		condense(w);
	}
}

void construct(){
	int mid=n/2;
	for(int i=mid;i>=1;i--){
		condense(i);
	}
}

void makesorted(){
	int total=n;
	while(n>1){
		swap(arr[1],arr[n]);
		n--;
		condense(1);
	}
	n=total;
}


int main(){
	int sn;
	cin>>sn;
	for(int i=1;i<=sn;i++)
		cin>>arr[i];
	n=sn;
	if(n%2==0){
		n++;
		arr[n]=INT_MIN;
	}
	
	construct();
	
	cout<<"Heap:";
	for(int i=1;i<=n;i++)
		cout<<" "<<arr[i];
	cout<<endl;
	
	makesorted();
	
	cout<<"Sorted:";
	for(int i=1;i<=sn;i++)
		cout<<" "<<arr[i];
	cout<<endl;
}

#endif
