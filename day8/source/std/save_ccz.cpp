#include<stdio.h>
#include<cstdlib>
#include<algorithm>
const int N=100007,M=29;
struct node{
	node*c[2];
	int sz,v,d,a,xs;
	bool sd;
	void xors(int x){
		a^=x;
		v^=x;
		if(sz&1)xs^=x;
	}
	void sorts(){
		if(!c[0])return;
		if(a){
			c[0]->xors(a);
			c[1]->xors(a);
			a=0;
		}
		sd=1;
		if(c[0]->v>c[1]->v)std::swap(c[0],c[1]);
	}
	void dn(){
		if(sd){
			c[0]->sorts();
			c[1]->sorts();
			sd=0;
		}
		if(a){
			c[0]->xors(a);
			c[1]->xors(a);
			a=0;
		}
	}
	void up(){
		sz=c[0]->sz+c[1]->sz;
		xs=c[0]->xs^c[1]->xs;
	}
	void sp(node*&l,node*&r,int k);
}ns[N*2],*mem[N*2],**mp=mem;
#define del(x) *mp++=x
#define newnode *--mp
void node::sp(node*&l,node*&r,int k){
	if(!d){
		l=this;
		r=newnode;
		*r=(node){0,0,sz-k,v,0,0,(sz-k)&1?v:0,0};
		sz=k;
		xs=k&1?v:0;
		return;
	}
	dn();
	if(k<c[0]->sz){
		c[0]->sp(l,c[0],k);
		r=this;
		up();
		return;
	}
	k-=c[0]->sz;
	if(k){
		c[1]->sp(c[1],r,k);
		l=this;
		up();
		return;
	}
	del(this);
	l=c[0],r=c[1];
	return;
}
node*mg(node*a,node*b,int d=M){
	for(int vv=a->v^b->v;;--d){
		if(d+1==a->d){
			if(d+1==b->d){
				if(d==-1){
					a->sz+=b->sz;
					a->xs^=b->xs;
					del(b);
					return a;
				}
				a->dn();
				b->dn();
				a->c[0]=mg(a->c[0],b->c[0],d);
				a->c[1]=mg(a->c[1],b->c[1],d);
				del(b);
				a->up();
				return a;
			}
			a->dn();
			int z=b->v>>d&1;
			a->c[z]=mg(a->c[z],b,d);
			a->up();
			return a;
		}
		if(d+1==b->d){
			b->dn();
			int z=a->v>>d&1;
			b->c[z]=mg(b->c[z],a,d);
			b->up();
			return b;
		}
		if(vv>>d&1){
			node*u=newnode;
			*u=(node){0,0,0,a->v,d+1,0,0,0};
			int z=a->v>>d&1;
			u->c[z]=a;
			u->c[z^1]=b;
			u->up();
			return u;
		}
	}
}
node*init(int x){
	node*u=newnode;
	*u=(node){0,0,1,x,0,0,x,0};
	return u;
}
#define lc c[0]
#define rc c[1]
struct Node{
	Node*c[2];
	node*rt;
	int sz,a,rnd,xs;
	void xors(int x){
		a^=x;
		if(sz&1)xs^=x;
		rt->xors(x);
	}
	void dn(){
		if(a){
			if(lc)lc->xors(a);
			if(rc)rc->xors(a);
			a=0;
		}
	}
	void up(){
		sz=rt->sz;
		xs=rt->xs;
		if(lc)sz+=lc->sz,xs^=lc->xs;
		if(rc)sz+=rc->sz,xs^=rc->xs;
	}
	void sort();
	void sp(int k,Node*&l,Node*&r);
}Ns[N],*Mem[N],**Mp=Mem,*Root;
node*now;
Node*newNode(node*w){
	**--Mp=(Node){0,0,w,w->sz,0,rand(),w->xs};
	return *Mp;
}
Node*mg(Node*a,Node*b){
	if(!a)return b;
	if(!b)return a;
	if(a->rnd>b->rnd){
		a->dn();
		a->rc=mg(a->rc,b);
		a->up();
		return a;
	}else{
		b->dn();
		b->lc=mg(a,b->lc);
		b->up();
		return b;
	}
}
void Node::sort(){
	if(!this)return;
	dn();
	lc->sort();
	rt->sorts();
	now=now?mg(now,rt):rt;
	*Mp++=this;
	rc->sort();
}
Node*rot(Node*w,int d){
    Node*u=w->c[d];
    if(u&&u->rnd>w->rnd){
        w->c[d]=u->c[d^1];
        u->c[d^1]=w;
        w->up(),u->up();
        return u;
    }
    w->up();
    return w;
}
void Node::sp(int k,Node*&l,Node*&r){
	if(!this){
		l=r=0;
		return;
	}
	int ls=lc?lc->sz:0;
	dn();
	if(k<=ls){
		lc->sp(k,l,lc);
		r=rot(this,0);
		return;
	}
	k-=ls;
	if(k<rt->sz){
		node*p1,*p2;
		rt->sp(p1,p2,k);
		l=mg(lc,newNode(p1));
		r=mg(newNode(p2),rc);
		*Mp++=this;
		return;
	}
	k-=rt->sz;
	rc->sp(k,rc,r);
	l=rot(this,1);
	up();
}
#include <ctype.h>
#include <iostream>
using namespace std;
inline int read()
{
	register int x = 0 , ch = getchar();
	while( !isdigit( ch ) ) ch = getchar();
	while( isdigit( ch ) ) x = x * 10 + ch - '0' , ch = getchar();
	return x;
}

int n,m;
int main(){
	freopen( "save.in" , "r" , stdin );
	freopen( "save.out" , "w" , stdout );
	n=read();m=read();
	srand(1231^n);
	for(int i=1;i<=n*2+5;++i)del(ns+i);
	for(int i=1;i<=n+5;++i)*Mp++=Ns+i;
	for(int i=1;i<=n;++i){
		Root=mg(Root,newNode(init(read())));
	}
	while(m--){
		int o=read(),l=read(),r=read();
		Node*p1,*p2,*p3;
		Root->sp(r,p2,p3);
		p2->sp(l-1,p1,p2);
		if(o==1){
			p2->xors(read());
		}else if(o==2){
			now=0;
			p2->sort();
			p2=newNode(now);
		}else printf("%d\n",p2->xs);
		Root=mg(mg(p1,p2),p3);
	}
	return 0;
}
