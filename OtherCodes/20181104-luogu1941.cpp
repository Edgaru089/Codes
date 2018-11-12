/*
 DOCUMENT NAME "20181104-luogu1941.cpp"
 CREATION DATE 2018-11-04
 SIGNATURE CODE_20181104_LUOGU1941
 COMMENT P1941 飞扬的小鸟
*/

#include <cstdlib>
#include <iostream>
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
template<typename IntType, typename... Args>
void read(IntType& val, Args&... args) { read(val); read(args...); }

const int MaxN=10000+10,MaxM=1000+10;
const int infinity=1e8;

int n,m,k;
int x[MaxN],y[MaxN];
bool hasbar[MaxN];
int bartop[MaxN],barbot[MaxN];

int f[MaxN][MaxM],g[MaxN][MaxM];



int main(int argc, char* argv[]) {
	
	read(n,m,k);
	for(int i=0;i<n;i++)
		read(x[i],y[i]);
	for(int i=1;i<=k;i++){
		int p,l,h;
		read(p,l,h);
		hasbar[p]=true;
		bartop[p]=h;
		barbot[p]=l;
	}
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j]=g[i][j]=infinity;
	if(hasbar[0])
		for(int i=1;i<=m;i++)
			if(i<=barbot[i]||i>=bartop[i])
				f[0][i]=infinity;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j-x[i-1]>=0){
				g[i][j]=min(g[i][j],g[i][j-x[i-1]]+1);
				g[i][j]=min(g[i][j],f[i-1][j-x[i-1]]+1);
			}
		}
		if(!hasbar[i]||bartop[i]>m)
			for(int j=0;j<=min(m,x[i-1]);j++){
				g[i][m]=min(g[i][m],g[i][m-j]+1);
				g[i][m]=min(g[i][m],f[i-1][m-j]+1);
			}
		for(int j=1;j<=m;j++){
			if(hasbar[i]&&(j<=barbot[i]||j>=bartop[i]))
				continue;
			f[i][j]=min(f[i][j],g[i][j]);
			if(j+y[i-1]<=m)
				f[i][j]=min(f[i][j],f[i-1][j+y[i-1]]);
		}
	}
/*
	printf("F[][]:\n");
	for(int j=m;j>=0;j--){
		printf("j=%2d",j);
		for(int i=0;i<=n;i++){
			if(f[i][j]<infinity)
				printf("\t%d",f[i][j]);
			else
				printf("\tinf");
		}
		printf("\n");
	}
	for(int i=0;i<=n;i++)
		printf("\ti=%d",i);
	printf("\n");

	printf("\nG[][]:\n");
	for(int j=m;j>=0;j--){
		printf("j=%2d",j);
		for(int i=0;i<=n;i++){
			if(g[i][j]<infinity)
				printf("\t%d",g[i][j]);
			else
				printf("\tinf");
		}
		printf("\n");
	}
	for(int i=0;i<=n;i++)
		printf("\ti=%d",i);
	printf("\n");
*/
	bool ok=false;
	int ans=infinity;
	for(int i=1;i<=m;i++)
		if(f[n][i]<infinity){
			ok=true;
			ans=min(ans,f[n][i]);
		}

	if(ok)
		printf("1\n%d\n",ans);
	else{
		int rightmost=0,cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(f[i][j]<infinity){
					rightmost=i;
					break;
				}
			}
			if(rightmost==i){
				if(hasbar[i])
					cnt++;
			}else{
				break;
			}
		}
		printf("0\n%d\n",cnt);
	}

	return 0;
}

