/*
*** UNKNOWN CODE BACKLOG FROM FOLDER "BNDS" ***
DATE 2018-05-22 (ADDED ON 2018-06-29)
SIGNATURE CODE_20180522_LUOGU3369_UNKNOWN
*/

#ifdef CODE_20180522_LUOGU3369_UNKNOWN

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

struct node{
    int val;
    int size,count;
    bool deleted;
    node* lson,*rson;
};

node pool[10001],*root,*null;
int top;

const double factor=0.72;

node* allocate(){return &pool[++top];}

void update(node* p){
    p->size=0;
    p->count=1;
    if(p->lson!=null){
        p->size+=p->lson->size;
        p->count+=p->lson->count;
    }
    if(p->rson!=null){
        p->size+=p->rson->size;
        p->count+=p->rson->count;
    }
    if(!p->deleted)
        p->size++;
}

void serialize(node* p,vector<node*> vec){
    if(p->lson!=null)
        serialize(p->lson,vec);
    if(!p->deleted)
        vec.push_back(p);
    if(p->rson!=null)
        serialize(p->rson,vec);
}

node* _rebuild(vector<node*>& vec,int left,int right){
    if(right-left<0)
        return null;
    int mid=(left+right)/2;
    node* p=vec[mid];
    p->lson=_rebuild(vec,left,mid-1);
    p->rson=_rebuild(vec,mid+1,right);
    update(p);
    return p;
}

node* rebuild(node* p){
	cout<<"rebuild "<<p->val<<endl;
    vector<node*> vec;
    serialize(p,vec);
    return _rebuild(vec,0,vec.size()-1);
}

bool isBad(node* p){
    if(p->lson!=null && p->lson->count>p->count*factor)
		return true;
	else if(p->rson!=null && p->rson->count>p->count*factor)
		return true;
	else
		return false;
}

void insert(int val, node*& p=root){
    if(p==nullptr || p==null){
    	cout<<"inserted "<<val<<endl;
        p=allocate();
        p->val=val;
        p->size=p->count=1;
        p->lson=p->rson=null;
    }
    else{
    	cout<<"passed "<<p->val<<endl;
        if(val>=p->val)
            insert(val,p->rson);
        else
            insert(val,p->lson);
        cout<<"callback "<<p->val<<endl;
        update(p);
        if(isBad(p))
            p=rebuild(p);
    }
}

int rrank(int val,node* p=root){
	if(p==null)
		return 0;
	else if(val<p->val){
		return rrank(val,p->lson);
    }
    else if(val==p->val){
    	if(p->lson!=null)
    		return min(rrank(val,p->lson),p->lson->size+1);
    	else
    		return 1;
	}
    else{
        return rrank(val,p->rson) + p->lson->size + (int)(1-p->deleted);
    }
}

int kth(int k,node* p=root){
	if(p->lson->size >= k)
		return kth(k,p->lson);
	else if(!p->deleted && p->lson->size == k-1)
		return p->val;
	else
		return kth(k - p->lson->size - (int)(1-p->deleted),p->rson);
}

void erase(int val,node* p=root){
    if(p->val==val&&!p->deleted)
        p->deleted=true;
    else if(val<p->val)
        erase(val,p->lson);
    else
        erase(val,p->rson);
}

node* find(int val,node* p=root){
	if(p==nullptr||p==null)
		return null;
	else if(val==p->val&&!p->deleted)
		return p;
	else if(val<p->val)
		return find(val,p->lson);
	else
		return find(val,p->rson);
}

int main()
{
	null=allocate();	
	
    int n;
    cin>>n;
    while(n--)
    {
		int op,x;
		cin>>op>>x;
		if(op==1)
			insert(x);
        else if(op==2)
            erase(x);
        else if(op==3)
            cout<<rrank(x)<<endl;
        else if(op==4)
            cout<<kth(x)<<endl;
        else if(op==5)
            cout<<kth(rrank(x)-1)<<endl;
        else if(op==6)
            cout<<kth(rrank(x)+1)<<endl;
    }
} 

#endif
