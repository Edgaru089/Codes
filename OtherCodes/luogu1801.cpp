#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <algorithm>
using namespace std;

#define FILENAME "luogu1801"

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

const int MaxN=200000+10;

int n,m;
int a[MaxN],u[MaxN];

struct node{
	int val,key;
	int cnt,size;
	node* lson,*rson,*father;
};

node* root;
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

typedef unsigned char sontype;
const sontype lson=0,rson=1;
sontype tell(node* p){
	return p->father&&p->father->lson==p?lson:rson;
}
node*& get(node* father,sontype type){
	return type==lson?father->lson:father->rson;
}
void connect(node* father,node* son,sontype type){
	if(father)
		get(father,type)=son;
	if(son)
		son->father=father;
}

int nsize(node* p){
	return !p?0:p->size;
}

void update(node* p){
	p->size=nsize(p->lson)+nsize(p->rson)+p->cnt;
}

void rotate(node* p){
	sontype t=tell(p);
	node* fa=p->father,*b=get(p,1-t);
	if(root==fa)
		root=p;
	connect(fa->father,p,tell(fa));
	connect(p,fa,1-t);
	connect(fa,b,t);
	update(fa);
	update(p);
}

void adjust(node* p){
	while(p->father&&p->father->key>p->key)
		rotate(p);
}

void insert(int val,node*& p=root,node* from=0){
	if(!p){
		p=ALLOCATE;
		p->val=val;
		p->size=p->cnt=1;
		p->key=rand();
		p->father=from;
		adjust(p);
	}else if(val<p->val){
		p->size++;
		insert(val,p->lson,p);
	}else if(val==p->val){
		p->cnt++;
		p->size++;
	}else{ /* val > p->val */
		p->size++;
		insert(val,p->rson,p);
	}
}


int getkth(int k,node* p=root){
	if(nsize(p->lson)>=k)
		return getkth(k,p->lson);
	else if(nsize(p->lson)+p->cnt>=k)
		return p->val;
	else
		return getkth(k-nsize(p->lson)-p->cnt,p->rson);
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
	
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=m;i++)
		read(u[i]);
	
	sort(u+1,u+m+1);

	int k=1;
	for(int i=1;i<=n;i++){
		insert(a[i]);
		while(k<=m&&u[k]<=i){
			println(getkth(k));
			k++;
		}
	}
	
	
	fwrite(bufferwrite, 1, writetop - bufferwrite, out);
	fclose(out);
	return 0;
}

