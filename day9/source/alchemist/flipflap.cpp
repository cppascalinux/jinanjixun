#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define len (r-l+1)
#define mid ((l+r)>>1)
using namespace std;
const int maxn=1e5+1;
typedef long long ll;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int lazy[maxn<<2];
int siz[maxn<<2];
ll mx[maxn<<2];

void pushdown(int p,int l,int r){
	int lp=lazy[p];lazy[p]=0;
	lazy[ls]+=lp;lazy[rs]+=lp;
	mx[ls]+=lp;mx[rs]+=lp;
}

void pushup(int p){
	mx[p]=max(mx[ls],mx[rs]);
}

void Build(int p,int l,int r){
	if (l==r) return siz[p]=1,void();
	Build(ls,l,mid),Build(rs,mid+1,r);
	siz[p]=siz[ls]+siz[rs]+1;
}

void Add(int p,int l,int r,int L,int R,int v){
	if (L<=l&&r<=R){mx[p]+=v;lazy[p]+=v;return;}
	if (lazy[p]) pushdown(p,l,r);
	if (mid>=R) Add(ls,l,mid,L,R,v);
	else if (mid<L) Add(rs,mid+1,r,L,R,v);
	else Add(ls,l,mid,L,R,v),Add(rs,mid+1,r,L,R,v);
	pushup(p);
}

int Query(int p,int l,int r,int L,int R,int v){
	if (L<=l&&r<=R&&mx[p]<=v) return siz[p];
	if (l==r) return 0;
	if (lazy[p]) pushdown(p,l,r);
	int res=0;
	if (mid>=R) res+=Query(ls,l,mid,L,R,v);
	else if (mid<L) res+=Query(rs,mid+1,r,L,R,v);
	else res=Query(ls,l,mid,L,R,v)+Query(rs,mid+1,r,L,R,v);
	pushup(p);
	return res;
}

int n,m;

int main(){
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	n=read(),m=read();
	Build(1,1,n);
	for (int i=1;i<=m;++i){
		int op=read(),l=read(),r=read(),a=read();
		if (op==1) Add(1,1,n,l,r,a);
		if (op==2) printf("%d\n",Query(1,1,n,l,r,a));
	}
}
