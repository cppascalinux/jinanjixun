#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<vector>
#include<cmath>
#include<cstring>
#define LL long long
using namespace std;
const int N = 1e5 + 3;
int n,m;
inline int read(){
	int v = 0,c = 1;char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') c = -1;
		ch = getchar();	
	}
	while(isdigit(ch)){
		v = v * 10 + ch - 48;
		ch = getchar();	
	}
	return v * c;	
}
namespace zs{
	struct tree{
		struct node{
			int lc,rc;
			LL sum,tag;
			
		}a[N << 1];
		int t;
		inline void pushup(int u){a[u].sum = a[a[u].lc].sum + a[a[u].rc].sum;}
		inline void pushdown(int u,int l,int r){
			if(!a[u].tag) return ;
			int mid = (l + r) >> 1;
			a[a[u].lc].sum += a[u].tag * (mid - l + 1);
			a[a[u].lc].tag += a[u].tag;
			a[a[u].rc].sum += a[u].tag * (r - mid);
			a[a[u].rc].tag += a[u].tag;
			a[u].tag = 0; 
 		}
 		inline void build(int u,int l,int r){
 			if(l == r) return ; 
 			int mid = (l + r) >> 1;
 			a[u].lc = ++t;build(a[u].lc,l,mid);
 			a[u].rc = ++t;build(a[u].rc,mid + 1,r);
 			pushup(u);
 		}
 		inline void updata(int u,int l,int r,int ll,int rr,LL w){
 			if(l == ll && r == rr){
				a[u].sum += 1ll * (r - l + 1) * w;
				a[u].tag += w;
				return ; 
			}
			pushdown(u,l,r);
			int mid = (l + r) >> 1;
			if(rr <= mid) updata(a[u].lc,l,mid,ll,rr,w);
			else if(ll > mid) updata(a[u].rc,mid + 1,r,ll,rr,w);
			else {
				updata(a[u].lc,l,mid,ll,mid,w);
				updata(a[u].rc,mid + 1,r,mid + 1,rr,w);	
			}
			pushup(u);
  		}
  		inline int query(int u,int l,int r,int ll,int rr,LL w){
			if(l == r) return (a[u].sum <= w) ? 1 : 0;
			pushdown(u,l,r);
			int mid = (l + r) >> 1;
			int ans = (a[u].sum <= w && r <= rr && l >= ll) ? 1 : 0;
			if(rr <= mid) return ans + query(a[u].lc,l,mid,ll,rr,w);
			else if(ll > mid) return ans + query(a[u].rc,mid + 1,r,ll,rr,w);
			else return ans + query(a[u].lc,l,mid,ll,mid,w) + query(a[u].rc,mid + 1,r,mid + 1,rr,w);
  		}
	}T;
	inline void work(){
		T.t = 1;
		T.build(1,1,n);
		for(int i = 1;i <= m;++i){
			int opt = read(),l = read(),r = read(),w = read();
			if(opt == 1) T.updata(1,1,n,l,r,w);	
			else printf("%d\n",T.query(1,1,n,l,r,w));
		}
	}
}
int main(){
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	n = read(),m = read();
	if(n <= 150000) zs::work();
	return 0;	
}
