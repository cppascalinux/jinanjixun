#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#define re register
#define FOR(i,l,r) for(re int i=l;i<=r;++i)
#define IT set<node>::iterator
using namespace std;

int n,m,x,y,t;

inline void in(re int &x){
    x=0;char c=getchar();
    while(c<'0'||c>'9'){
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
}

inline void out(re int a){
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

struct node{
    mutable int l,r;
    mutable int v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    inline bool operator <(const node &o)const{
        return l<o.l;
    }
};

set<node> s;

inline IT split(re int pos){
    IT it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
      return it;
    --it;
    int L=it->l;
    int R=it->r;
    int V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assign_val(re int l,re int r,re int val=0){
    IT itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,val));
}

inline int query(re int l,re int r){
    int res=0;
    IT itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
      res+=(itl->r-itl->l+1)*(itl->v);
    return res;
}

void change3(re int l, re int r) {
    IT itr = split(r+1), itl = split(l), ittl = itl, itttl = itl, ittttl;
    for(;itl != itr; ++itl) {
        ++ittl;
        if(itl->v == 0 && ittl->v == 1)
          itl->r -= 1, ittl->l -= 1;
//		if(itl->r < itl->l)
//		  s.erase(itl);	
    } 
    while(itttl != itr) {
        ittttl = itttl;
        ++itttl;
        if(ittttl->l > ittttl->r) 
      	  s.erase(ittttl);
    }   
}

void change4(re int l, re int r) {
    IT itr = split(r+1), itl = split(l), ittl = itl, itttl = itl, ittttl;
    --ittl;
    for(; itl != itr; ++itl) {
        if(itl->v == 0 && ittl->v == 1)
          itl->l += 1, ittl->r += 1;
//		if(itl->l > itl->r)
//		  s.erase(itl);
        ++ittl;
    }
    while(itttl != itr) {
        ittttl = itttl;
        ++itttl;
        if(ittttl->l > ittttl->r) 
      	  s.erase(ittttl);
    }   
}

void change5(re int l, re int r) {
    IT itr = split(r+1), itl = split(l), ittl = itl, itttl = itl, ittttl;
    for(;itl != itr; ++itl) {
        ++ittl;
        if(itl->v == 1 && ittl->v == 0)
          itl->r -= 1, ittl->l -= 1;
//		if(itl->r < itl->l)
//		  s.erase(itl);	
    } 
    while(itttl != itr) {
        ittttl = itttl;
        ++itttl;
        if(ittttl->l > ittttl->r) 
      	  s.erase(ittttl);
    }   
}

void change6(int l, int r) {
    IT itr = split(r+1), itl = split(l), ittl = itl, itttl = itl, ittttl;
    --ittl;
    for(; itl != itr; ++itl) {
        if(itl->v == 1 && ittl->v == 0)
          itl->l += 1, ittl->r += 1;
//		if(itl->l > itl->r)
//		  s.erase(itl);
        ++ittl;
    }
    while(itttl != itr) {
        ittttl = itttl;
        ++itttl;
        if(ittttl->l > ittttl->r) 
      	  s.erase(ittttl);
    }   	  
}

void print(int l, int r) {
    int res = 0;
    IT itr = split(r+1), itl = split(l);
    for(; itl != itr; ++itl) {
        FOR(i, 1, itl->r-itl->l+1)
          printf("%d ", itl->v);
        cout << "Q"; 
    }
    puts("");
}

int main(){
	freopen("plasticmem.in", "r", stdin);
	freopen("plasticmem.out", "w", stdout);
    in(n), in(m);
    in(t);
    int cnt=1;
    int pre=t;
    FOR(i, 1, n-1){
        in(t);
        if(t==pre)
          ++cnt;
        else{
            s.insert(node(i-cnt+1,i,pre));
            cnt=1;
            pre=t;
        }
    }
    s.insert(node(n-cnt+1,n,pre));
//	
  
//   FOR(i, 1, n)
//      in(x), s.insert(node(i, i, x));
//    print(1, n);
    
    s.insert(node(0, n+1, 0));
    FOR(i, 1, m){
    	in(t);
        in(x), in(y);
        if(t == 1) {
        	assign_val(x, y, 0);
//        	print(1, n+1);
        }
        if(t == 2) {
            assign_val(x, y, 1);
//			print(1, n+1);
        }
        if(t == 3) {
            change3(x, y-1);
//			print(1, n+1);
        }
        if(t == 4) {
            change4(x+1, y);
//			print(1, n+1);
        }
        if(t == 5) {
            change5(x, y-1);
//			print(1, n+1);
        }
        if(t == 6) {
            change6(x+1, y);
//			print(1, n+1);
        }
        if(t == 7) {
            out(query(x, y));
            putchar(10);
        }
    }
//    out(query(0,n));
//    puts("");
}
