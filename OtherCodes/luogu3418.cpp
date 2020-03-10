#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

#ifdef D
#include <custom/Debug.hpp>
#endif

using namespace std;

#if (defined LOCAL) || (defined D)
#define DEBUG(...) fprintf(stderr,__VA_ARGS__)
#define PRINTARR(formatstr, arr, beginoff, size)				\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++)		\
	fprintf(stderr,"\t" formatstr, arr[__i]);					\
fprintf(stderr,"\n"); }while(false)
#define PASS fprintf(stderr,"Passing function \"%s\" on line %d\n", __func__, __LINE__)
#define ASSERT(expr) do{\
	if(!(expr)){\
		fprintf(stderr,"Debug Assertion Failed on line %d, in function %s:\n  Expression: %s\n",__LINE__,__func__,#expr);\
		abort();\
	}\
}while(false)
#define PRINTARR2D(formatstr, arr, beginoff, size, beginy, sizey)\
do{fprintf(stderr,#arr ":");									\
for (int __i = beginy; __i <= beginy + sizey - 1; __i++)		\
	fprintf(stderr,"\t%d", __i);								\
fprintf(stderr,"\n");											\
for (int __i = beginoff; __i <= beginoff + size - 1; __i++) {	\
	fprintf(stderr, "%d:", __i);								\
	for(int __j = beginy; __j <= beginy + sizey -1; __j++)		\
		fprintf(stderr,"\t" formatstr, arr[__i][__j]);			\
	fprintf(stderr, "\n");										\
}}while(false)
#define PRINT(...) dbg(__VA_ARGS__)
#define PRINTVAL(...) dbgv(__VA_ARGS__)
#define PRINTSEQ(...) dbgr(__VA_ARGS__)
#define PRINTSEQVAL(...) dbgm(__VA_ARGS__)
#define PRINTCOMPACT(...) dbgs(__VA_ARGS__)
#else
#define DEBUG(...)
#define PRINTARR(a, b, c, d)
#define PRINTARR2D(a, b, c, d, e, f)
#define PASS
#define ASSERT(expr)
#define PRINT(...)
#define PRINTVAL(...)
#define PRINTSEQ(...)
#define PRINTSEQVAL(...)
#define PRINTCOMPACT(...)
#endif

#define FOR(i, first, last)               for(int i = (first); i <= (last); ++i)
#define ROF(i, last, first)               for(int i = (last); i >= (first); --i)
#define FORSTEP(i, first, last, step)     for(int i = (first); i <= (last); i += (step))
#define ROFSTEP(i, last, first, stepabs)  for(int i = (last); i >= (first); i -= (stepabs))

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
void read<string>(string& str){
	str.clear();
	int c;
	while(iscntrl(c=getchar())||c==' '||c=='\t');
	do{
		str.push_back(c);
	}while(!(iscntrl(c=getchar())||c==' '||c=='\t'));
}
#if __cplusplus >= 201103
template<typename IntType,typename... Args>
void read(IntType& val, Args&... args){
	read(val); read(args...);
}
#endif

// End of template:edgar:edgar-laptop(LAPTOP-EDGAR-15)

typedef double ld;

const ld eps=1e-6;
const ld pi=3.14159265357;
const int MaxN=25000+10;

int n;

struct point{
	point(){}
	point(ld x,ld y):x(x),y(y){}
	ld x,y;
	ld angle;
};

point d[MaxN];

int m;
point a[MaxN];

bool equal(ld x,ld y){
	return fabs(x-y)<eps;
}

bool equal(point x,point y){
	return equal(x.x,y.x)&&equal(x.y,y.y);
}

bool center(point p){
	return equal(p.x,0)&&equal(p.y,0);
}

ld disq(point x,point y){
	return ((x).x-(y).x)*((x).x-(y).x)+((x).y-(y).y)*((x).y-(y).y);
}

ld dis(point x,point y){
	return sqrt(disq(x,y));
}

ld angle(point p){
	ASSERT(!center(p));
	ld ans=0;
	if(equal(p.x,0))
		ans=p.y>0?pi/2:pi*3/2;
	else if(equal(p.y,0))
		ans=p.x>0?0:pi;
	else
		ans=atan(p.y/p.x)+(p.x>0?0:pi);
	while(ans<0)
		ans+=2*pi;
	while(ans>2*pi)
		ans-=2*pi;
	//DEBUG("angle(%.6Lf,%.6Lf)=%.6Lf=%.6LfPi\n",p.x,p.y,ans,ans/pi);
	return ans;
}

bool agcmp(point x,point y){
	//ld ax=angle(x),ay=angle(y);
	ld ax=x.angle,ay=y.angle;
	if(equal(ax,ay)){
		ld dx=disq(x,point(0,0)),dy=disq(y,point(0,0));
		return dx<dy;
	}else if(ax<ay)
		return true;
	else
		return false;
}

point b[MaxN];

// a[] starts from [1]
int normalize(int n,point* s){

	DEBUG("normalize(n=%d)\n",n);

	point c(0,0);

	FOR(i,1,n){
		c.x+=s[i].x;
		c.y+=s[i].y;
	}

	c.x/=n;
	c.y/=n;

	DEBUG("center(%.6Lf,%.6Lf)\n",c.x,c.y);


	ld factor=0;
	FOR(i,1,n){
		s[i].x-=c.x;
		s[i].y-=c.y;
		factor=max(factor,dis(s[i],point(0,0)));
	}

	int ans=0;
	FOR(i,1,n)
		if(!equal(s[i].x,0)||!equal(s[i].y,0))
			b[++ans]=s[i];
	memcpy(s+1,b+1,sizeof(point)*ans);
	n=ans;

	DEBUG("factor=%.6Lf\n",factor);
	if(!equal(factor,0))
		FOR(i,1,n){
			s[i].x/=factor;
			s[i].y/=factor;
		}

	FOR(i,1,n)
		s[i].angle=angle(s[i]);


	sort(s+1,s+n+1,agcmp);

	DEBUG("end normalize(n=%d)\n",n);

	return n;
}

// ans.x = anglediff
// ans.y = length^2
void pushdiff(int n,point* a,point* ans){
	ans[1].x=2*pi-(a[n].angle)+(a[1].angle);
	ans[1].y=disq(a[1],point(0,0));
	FOR(i,2,n){
		ans[i].x=(a[i].angle)-(a[i-1].angle);
		ans[i].y=disq(a[i],point(0,0));
	}
}
void pushdiff_inv(int n,point* a,point* ans){
	ans[1].x=2*pi-(a[n].angle)+(a[1].angle);
	ans[1].y=disq(a[n],point(0,0));
	FOR(i,2,n){
		ans[i].x=(a[n-i+2].angle)-(a[n-i+1].angle);
		ans[i].y=disq(a[n-i+1],point(0,0));
	}
}

bool match(int n,point* x,point* y){
	FOR(i,0,n-1){
		bool ok=true;
		FOR(j,1,n){
			int t=(j-1+i)%n+1;
			if(!equal(x[t].x,y[j].x)||!equal(x[t].y,y[j].y)){
				ok=false;
				break;
			}
		}
		if(ok)
			return true;
	}
	return false;
}


int ns,ms;
point ds[MaxN],as[MaxN];


int main(int argc, char* argv[]) {

	read(n);
	FOR(i,1,n){
		int x,y;
		read(x);read(y);
		d[i].x=x;
		d[i].y=y;
		DEBUG("%.6Lf,%.6Lf\n",d[i].x,d[i].y);
	}

	ns=normalize(n,d);
	pushdiff(ns,d,ds);

#ifdef D
	DEBUG("Normal\n");
	FOR(i,1,ns)
		printf("(%01.6Lf,%01.6Lf)\n",d[i].x,d[i].y);
	DEBUG("Diff\n");
	FOR(i,1,ns)
		printf("angle=%01.6Lf, length=%01.6Lf\n",ds[i].x,ds[i].y);
#endif

	int t;
	read(t);
	while(t--){
		read(m);
		FOR(i,1,m){
			int x,y;
			read(x);read(y);
			a[i].x=x;
			a[i].y=y;
		}
		if(n!=m){
			printf("NIE\n");
			continue;
		}

		ms=normalize(m,a);
		pushdiff(ms,a,as);

#ifdef D
		DEBUG("Normal\n");
		FOR(i,1,ms)
			printf("(%01.6Lf,%01.6Lf)\n",a[i].x,a[i].y);
		DEBUG("Diff\n");
		FOR(i,1,ms)
			printf("angle=%01.6Lf, length=%01.6Lf\n",as[i].x,as[i].y);
#endif

		if(ns!=ms)
			printf("NIE\n");
		else if(ns==0||match(ns,as,ds))
			printf("TAK\n");
		else{
			FOR(i,1,ms){
				a[i].x=-a[i].x;
				a[i].angle=angle(a[i]);
			}
			sort(a+1,a+ms+1,agcmp);
			pushdiff(ms,a,as);
#ifdef D
			DEBUG("Diff_inv\n");
			FOR(i,1,ms)
				printf("angle=%01.6Lf, length=%01.6Lf\n",as[i].x,as[i].y);
#endif
			if(match(ns,as,ds))
				printf("TAK\n");
			else
				printf("NIE\n");
		}

	}

	return 0;
}

// vim:cindent:cinwords+=FOR,ROF,FORSTEP,ROFSTEP

