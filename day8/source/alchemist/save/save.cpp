#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

int n,m;
int a[maxn];

void Rough(){
	for (int i=1;i<=m;++i){
		int op=read(),l=read(),r=read();
		if (op==1){
			int x=read();
			for (int k=l;k<=r;++k)
			a[k]^=x;
		}
		if (op==2){
			sort(a+l,a+r+1);
		}
		if (op==3){
			int x=0;
			for (int k=l;k<=r;++k)
			x^=a[k];
			printf("%d\n",x);
		}
	}
}

namespace Seg{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid ((l+r)>>1)
	#define len (r-l+1)
	int t[maxn<<2],lazy[maxn<<2];
	void pushup(int p){
		t[p]=t[ls]^t[rs];
	}
	void pushdown(int p,int l,int r){
		int lp=lazy[p];lazy[p]=0;
		int lx=mid-l+1,rx=r-mid;
		if (lx%2) t[ls]^=lp;
		if (rx%2) t[rs]^=lp;
		lazy[ls]^=lp,lazy[rs]^=lp;
	}
	void build(int p,int l,int r){
		if (l==r){t[p]=a[l];return;}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(p);
	}
	void update(int p,int l,int r,int L,int R,int v){
		if (L<=l&&r<=R){if (len%2) t[p]^=v;lazy[p]^=v;return;}
		if (lazy[p]) pushdown(p,l,r);
		if (mid>=R) update(ls,l,mid,L,R,v);
		else if (mid<L) update(rs,mid+1,r,L,R,v);
		else update(ls,l,mid,L,R,v),update(rs,mid+1,r,L,R,v);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if (L<=l&&r<=R) return t[p];
		if (lazy[p]) pushdown(p,l,r);
		int res=0;
		if (mid>=R) res=query(ls,l,mid,L,R);
		else if (mid<L) res=query(rs,mid+1,r,L,R);
		else res=query(ls,l,mid,L,R)^query(rs,mid+1,r,L,R);
		pushup(p);
		return res;
	}
	#undef ls
	#undef rs
	#undef mid
	#undef len
}

void Solve(){
	using namespace Seg;
	build(1,1,n);
	for (int i=1;i<=m;++i){
		int op=read(),l=read(),r=read();
		if (op==1) update(1,1,n,l,r,read());
		if (op==3) printf("%d\n",query(1,1,n,l,r));
	}
}

int main(){
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i)
		a[i]=read();
	if (n<=10000&&m<=10000) Rough();
	else Solve();
}
