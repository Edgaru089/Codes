#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define FILENAME "luogu3376"

#if (defined LOCAL || defined D)
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

const int bufferreadsize = 30 * 1024 * 1024;
const int bufferwritesize = 5 * 1024 * 1024;
char buffer[bufferreadsize], *buffertop = buffer;
#define GETCHAR *(buffertop++)
#define UNGETCHAR(c) (--buffertop)

template<typename IntType>
inline IntType read() {
	IntType val = 0;
	int c;
	bool invflag = false;
	while (!isdigit(c = GETCHAR))
		if (c == '-')
			invflag = true;
	do {
		val = (val << 1) + (val << 3) + c - '0';
	} while (isdigit(c = GETCHAR));
	UNGETCHAR(c);
	if (invflag)
		return -val;
	else
		return val;
}
template<>
inline string read<string>() {
	string str;
	str.clear();
	int c;
	while (iscntrl(c = GETCHAR) || c == ' ' || c == '\t');
	do {
		str.push_back(c);
	} while (!(iscntrl(c = GETCHAR) || c == ' ' || c == '\t'));
	UNGETCHAR(c);
	return str;
}
template<typename IntType>
inline void read(IntType& x) { x = read<IntType>(); }

char bufferwrite[bufferwritesize], *writetop = bufferwrite;
#define PUTCHAR(c) (*(writetop++) = (c))

inline void putstr(char* str) {
	while ((*str) != '\0') {
		PUTCHAR(*str);
		str++;
	}
}

template<typename IntType>
inline void println(IntType val) {
	if (val == 0)
		PUTCHAR('0');
	if (val < 0) {
		PUTCHAR('-');
		val = -val;
	}
	char buf[16], *buftop = buf + 15;
	while (val > 0) {
		*buftop = (val % 10 + '0');
		buftop--;
		val /= 10;
	}
	for (buftop++; buftop <= buf + 15; buftop++)
		PUTCHAR(*buftop);
	PUTCHAR('\n');
}

/******************** End of quickread template ********************/

const int infinity=1e8;
const int MaxN=10000+10,MaxM=100000+10;

int n,m;
int u,v,f;

struct node{
	int v,flow;
	node* next;
	node* rev;
};

node* h[MaxN];
node mem[2*MaxM],*memtop=mem;
#define ALLOCATE (++memtop)

void addedge(int u,int v,int flow){
	node* p=ALLOCATE;
	p->v=v;
	p->flow=flow;
	p->next=h[u];
	h[u]=p;
	node* pr=ALLOCATE;
	pr->v=u;
	pr->flow=0;
	pr->next=h[v];
	h[v]=pr;
	p->rev=pr;
	pr->rev=p;
}

int s,t;
int dep[MaxN];
queue<int> Q;
bool bfs(){
	memset(dep,0,sizeof(dep));
	Q.push(s);
	dep[s]=1;
	while(!Q.empty()){
		int u=Q.front();
		DEBUG("  bfs over node %d\n",u);
		Q.pop();
		for(node* p=h[u];p;p=p->next){
			int v=p->v;
			if(p->flow&&!dep[v]){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t];
}


node* cur[MaxN];
int dfs(int u,int limit){
	DEBUG("  dfs over %d, limit=%d\n",u,limit);
	if(u==t||!limit)
		return limit;
	int ans=0;
	for(node*& p=cur[u];limit&&p;p=p->next){
		int v=p->v;
		int d;
		if(dep[v]==dep[u]+1&&(d=dfs(v,min(limit,p->flow)))){
			ans+=d;
			p->flow-=d;
			p->rev->flow+=d;
			limit-=d;
		}
		if(!limit)
			break;
	}
	return ans;
}

int dinic(){
	int ans=0;
	while(bfs()){
		DEBUG("Dinic calling\n");
		for(int i=1;i<=n;i++)
			cur[i]=h[i];
		ans+=dfs(s,infinity);
	}
	return ans;
}



int main(int argc, char* argv[]) {
#if (defined LOCAL) || (defined ONLINE_JUDGE)
	FILE* in = stdin, *out = stdout;
#else
	FILE* in = fopen(FILENAME ".in", "rb");
	FILE* out = fopen(FILENAME ".out", "wb");
#endif
	fread(buffer, 1, bufferreadsize, in);
	fclose(in);
	
	read(n);read(m);
	read(s);read(t);
	for(int i=1;i<=m;i++){
		read(u);read(v);read(f);
		addedge(u,v,f);
	}

	fprintf(out,"%d\n",dinic());

	
	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

