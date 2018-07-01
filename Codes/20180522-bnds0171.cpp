/*
*** UNKNOWN CODE BACKLOG FROM FOLDER "BNDS" ***
DATE 2018-05-22 (ADDED ON 2018-06-29)
SIGNATURE CODE_20180522_BNDS0171_UNKNOWN
*/

#ifdef CODE_20180522_BNDS0171_UNKNOWN

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> a;

int count_reducing(const vector<int>& vec){
	int Max=1;
	vector<int> f;
	f.resize(vec.size());
	for(int i=2;i<=vec.size();i++){
		for(int j=1;j<i;j++){
			if(vec[j]>vec[i])
				f[i]=max(f[i],f[j]+1);
		}
		Max=max(Max,f[i]);
	}
	
	return Max;
}

int count_increasing(const vector<int>& vec){
	if(vec.size()==0)
		return 0;
	int Max=1;
	vector<int> f;
	f.resize(vec.size());
	for(int i=2;i<=vec.size();i++){
		for(int j=1;j<i;j++){
			if(vec[j]<vec[i])
				f[i]=max(f[i],f[j]+1);
		}
		Max=max(Max,f[i]);
	}
	
	return Max;
}

vector<int> make_subregion(const vector<int>& source, size_t offset, size_t size){
	vector<int> ans;
	ans.reserve(size);
	for(int i=offset;i<offset+size;i++){
		ans.push_back(source[i]);
	}
	return ans;
}

int main(){

	cin>>n;
	a.resize(n);
	for(int i=0;i<n;i++)
		cin>>a[i];
	
	int Min=a.size();
	for(int i=0;i<n;i++){
		int sum=0;
		sum=count_increasing(make_subregion(a,0,i));
		sum+=count_reducing(make_subregion(a,i+1,a.size()-i-1));
		Min=min(Min,sum);
	}

	cout<<Min<<endl;
	return 0;
}

#endif
