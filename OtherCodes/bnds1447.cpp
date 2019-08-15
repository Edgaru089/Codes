#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
#include <queue>
#include <string>
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
	}while(iscntrl(c=getchar())||c==' '||c=='\t');
}

const int MaxN=16+1;

int n;

map<char,int> m={
	{'A',0},
	{'E',1},
	{'I',2},
	{'O',3},
	{'U',4}
};

int dis[1<<MaxN][5];

struct st{
	int s,u;
};

struct node{
	int v,len;
	int id;
	node* next;
};

node mem[MaxN*MaxN*2],*memtop=mem;
node* h[MaxN];
#define ALLOCATE (++memtop)

void addedge(int u,int v,int len,int id){
	node* p=ALLOCATE;
	p->v=v;
	p->len=len;
	p->id=id;
	p->next=h[u];
	h[u]=p;
}

queue<st> Q;
bool inQ[1<<MaxN][5];

int ans=0;

void spfa(){
	for(int i=0;i<5;i++){
		inQ[0][i]=true;
		Q.push(st{0,i});
	}
	while(!Q.empty()){
		int s=Q.front().s,u=Q.front().u;
		Q.pop();
		inQ[s][u]=false;
		for(node* p=h[u];p;p=p->next){
			int v=p->v,id=p->id,len=p->len;
			if((s&(1<<id))==0&&dis[s|(1<<id)][v]<dis[s][u]+len){
				dis[s|(1<<id)][v]=dis[s][u]+len;
				ans=max(ans,dis[s|(1<<id)][v]);
				if(!inQ[s|(1<<id)][v]){
					inQ[s|(1<<id)][v]=true;
					Q.push(st{s|(1<<id),v});
				}
			}
		}
	}
}




int main(int argc, char* argv[]) {

	cin>>n;
	string s;
	for(int i=1;i<=n;i++){
		cin>>s;
		addedge(m[s[0]],m[s[s.size()-1]],s.size(),i);
	}

	spfa();


	printf("%d\n",ans);


	return 0;
}


