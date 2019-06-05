#include<bits/stdc++.h>
#define N (101010)
#define ls (rt<<1)
#define rs ((rt<<1)+1)
#define Rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;
int n,m,a[N];
bool f1;
struct Qu{
	int op,l,r,x;
	void InIt(){
		scanf("%d %d %d",&op,&l,&r);
		if (op==2) f1=1;
		if (op==1) scanf("%d",&x);
	}
}Q[N];
namespace Sub1{
	void Solve(){
		Rep(i,1,m){
			int l=Q[i].l,r=Q[i].r;
			if (Q[i].op==1){
				Rep(j,l,r) 
					a[j]^=Q[i].x;
			}
			if (Q[i].op==2){
				sort(a+l,a+r+1);
			}
			if (Q[i].op==3){
				int x=0;
				Rep(j,l,r) x^=a[j];
				printf("%d\n",x);
			}
		}
		exit(0);
	}
}
namespace Sub2{
	int val[N*4],Tag[4*N];
	void Pushdown(int rt,int l,int r){
		int mid=(l+r)>>1;
		if (Tag[rt]){
			Tag[ls]^=Tag[rt];
			if ((mid-l+1)%2) val[ls]^=Tag[rt];
			Tag[rs]^=Tag[rt];
			if ((r-mid)%2) val[rs]^=Tag[rt]; 
		}
		Tag[rt]=0;
	}
	void Pushup(int rt){
		val[rt]=val[ls]^val[rs];
	}
	void Update(int rt,int l,int r,int L,int R,int x){
		if (l>=L&&r<=R){
			if ((r-l+1)%2) val[rt]^=x;
			Tag[rt]^=x; return;
		}
		Pushdown(rt,l,r);
		int mid=(l+r)>>1;
		if (L<=mid) Update(ls,l,mid,L,R,x);
		if (R>mid) Update(rs,mid+1,r,L,R,x);
		Pushup(rt);
	}
	int Query(int rt,int l,int r,int L,int R){
		if (l>=L&&r<=R) return val[rt];
		Pushdown(rt,l,r);
		int res=0,mid=(l+r)>>1;
		if (L<=mid) res^=Query(ls,l,mid,L,R);
		if (R>mid) res^=Query(rs,mid+1,r,L,R);
		return res;
	}
	void Build(int rt,int l,int r){
		if (l==r){
			val[rt]=a[l]; return;
		}
		int mid=(l+r)>>1;
		Build(ls,l,mid); Build(rs,mid+1,r);
		Pushup(rt);
	}
	void Solve(){
		Build(1,1,n);
		Rep(i,1,m){
			int l=Q[i].l,r=Q[i].r;
			if (Q[i].op==1)
				Update(1,1,n,l,r,Q[i].x);
			else
				printf("%d\n",Query(1,1,n,l,r));
		}
		exit(0);
	}
}
int main(){
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	scanf("%d %d",&n,&m);
	Rep(i,1,n) scanf("%d",&a[i]);
	Rep(i,1,m) Q[i].InIt();
	if (n<=10000&&m<=10000) Sub1::Solve();
	Sub2::Solve();
}
