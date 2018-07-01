/*
*** UNKNOWN CODE BACKLOG FROM FOLDER "BNDS" ***
DATE 2018-05-22 (ADDED ON 2018-06-29)
SIGNATURE CODE_20180522_BNDS0168_UNKNOWN
*/

#ifdef CODE_20180522_BNDS0167_UNKNOWN

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

vector<int> a;
vector<int> f;
vector<vector<int>> fc;

int main(){
	
	int x;
	while(cin>>x)
		a.push_back(x);
	
	int step=0;
	int ans=0;
	while(a.size()>0){
		step++;
//		cout<<"step "<<step<<endl;
		
		if(a.size()==1)
			break;
		
		f.resize(a.size(),0);
		f[0]=1;
		fc.resize(a.size());
		for(int& i:f)
			i=1;
		for(vector<int>& i:fc)
			i.clear();
		fc[0].push_back(0);
		
		int Max=0,MaxMark=-1;
		for(int i=1;i<a.size();i++){
			int mark=-1;
			for(int j=0;j<i;j++){
				if(a[i]<=a[j]){
					if(f[i]<f[j]+1){
						f[i]=f[j]+1;
						mark=j;
					}
				}
			}
			if(mark!=-1)
				fc[i]=fc[mark];
			else
				fc[i].clear();
			fc[i].push_back(i);
			
			if(Max<f[i]){
				Max=f[i];
				MaxMark=i;
			}
		}
		vector<bool> flag;
		flag.resize(a.size(),true);
		if(step==1)
			ans=fc[MaxMark].size();
		for(int i:fc[MaxMark]){
//			cout<<" "<<i<<endl;
			flag[i]=false;
		}
		vector<int> vtmp;
		for(int i=0;i<a.size();i++){
			if(flag[i])
				vtmp.push_back(a[i]);
		}
		a=vtmp;
//		for(int i:a)
//			cout<<" "<<i;
//		cout<<endl;
	}
	
	cout<<ans<<endl;
	cout<<step<<endl;
	
	return 0;
}

#endif
