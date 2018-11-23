#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

template<typename IntType>
void read(IntType& val){
	val=0;
	int c;
	bool inv=false;
	while(!isdigit(c=getchar()))
		if(c=='-')
			inv=true;
	do{
		val=(val<<1)+(val<<3)+c-'0';
	}while(isdigit(c=getchar()));
	if(inv)
		val=-val;
}

const int MaxN=3e5+10;

int n,m;

struct node{
	int val,sum;
	bool lazy;
	node* lson,*rson;
	node* father;
};

node *nodes[MaxN];
node mem[MaxN],*memtop=mem;
#define ALLOCATE (++memtop)

typedef unsigned char sontype;
const sontype lson=0,rson=1;
sontype tell(node* son){return (son->father&&son->father->lson==son)?lson:rson;}
node*& get(node* father,sontype t){return t==lson?father->lson:father->rson;}
void connect(node* father,node* son,sontype t){
	if(father)
		get(father,t)=son;
	if(son)
		son->father=father;
}

void update(node* p){
	p->sum=p->val;
	if(p->lson)
		p->sum^=p->lson->sum;
	if(p->rson)
		p->sum^=p->rson->sum;
}

bool notroot(node* p){return p->father&&(p->father->lson==p||p->father->rson==p);}

void rotate(node* p){
	sontype t=tell(p);
	node* fa=p->father,*b=get(p,1-t);
	if(notroot(fa))
		connect(fa->father,p,tell(fa));
	else
		p->father=fa->father;
	connect(p,fa,1-t);
	connect(fa,b,t);
	update(fa);
	update(p);
}

void pushdown(node* p){
	if(p&&p->lazy){
		swap(p->lson,p->rson);
		if(p->lson)
			p->lson->lazy=!p->lson->lazy;
		if(p->rson)
			p->rson->lazy=!p->rson->lazy;
		p->lazy=false;
	}
}

void pushchain(node* p){
	if(notroot(p))
		pushchain(p->father);
	pushdown(p);
}

void splay(node* p){
	pushchain(p);
	while(notroot(p)){
		if(notroot(p->father))
			if(tell(p)==tell(p->father))
				rotate(p->father);
			else
				rotate(p);
		rotate(p);
	}
}

void access(node* p){
	node* prev=0;
	while(p){
		splay(p);
		p->rson=prev;
		update(p);
		prev=p;
		p=p->father;
	}
}

void makeroot(node* p){
	access(p);
	splay(p);
	p->lazy=!p->lazy;
}

node* findroot(node* p){
	access(p);
	splay(p);
	pushdown(p);
	while(p->lson){
		p=p->lson;
		pushdown(p);
	}
	return p;
}

void link(node* x,node* y){
	makeroot(x);
	if(findroot(y)!=x)
		x->father=y;
}

void cut(node* x,node* y){
	makeroot(x);
	if(findroot(y)!=x||y->lson!=x||x->rson)
		return;
	y->lson=x->father=0;
	update(y);
}

void changeval(node* x,int val){
	access(x);
	splay(x);
	x->val=val;
	update(x);
}

node* split(node* x,node* y){
	makeroot(x);
	access(y);
	splay(y);
	return y;
}

int k,x,y;


int main(){

	read(n);read(m);
	for(int i=1;i<=n;i++){
		nodes[i]=ALLOCATE;
		read(nodes[i]->val);
		update(nodes[i]);
	}

	for(int i=1;i<=m;i++){
		read(k);read(x);read(y);
		switch(k){
			case 0:
				printf("%d\n",split(nodes[x],nodes[y])->sum);
				break;
			case 1:
				link(nodes[x],nodes[y]);
				break;
			case 2:
				cut(nodes[x],nodes[y]);
				break;
			case 3:
				changeval(nodes[x],y);
				break;
		}
	}

	return 0;
}


