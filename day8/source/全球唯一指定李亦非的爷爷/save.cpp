#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<"-----------------------------------"<<endl
#define LL long long
using namespace std;
int read(){
	int nm=0,fh=1; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) if(cw=='-') fh=-fh;
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return nm*fh;
}
#define mod 1000000007
inline int mul(LL x,LL y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
inline int qpow(int x,int sq){int res=1;for(;sq;sq>>=1,x=mul(x,x))if(sq&1)res=mul(res,x);return res;}
#define M 200020
int n,m,p[M];
namespace force{
	inline void xr(int l,int r,int v){for(int i=l;i<=r;i++) p[i]^=v;}
	inline void st(int l,int r){sort(p+l,p+r+1);}
	inline int sm(int l,int r,int res=0){for(int i=l;i<=r;i++)res^=p[i];return res;}
	inline void solve(){
		while(m--){
			int op=read(),l=read(),r=read();
			if(op==1) xr(l,r,read());
			if(op==2) st(l,r);
			if(op==3) printf("%d\n",sm(l,r));
		}
	}
}
namespace bit{
	int c[M];
	inline void add(int k,int x){while(k<=n)c[k]^=x,k+=k&-k;}
	inline int qry(int k,int res=0){while(k)res^=c[k],k-=k&-k;return res;}
	inline void solve(){
		while(m--){
			int op=read(),l=read(),r=read(),v;
			if(op==1) v=read(),add(l,v),add(r+1,v);
			if(op==3) printf("%d\n",qry(r)^qry(l-1));
			if(op==2) assert(false);
		}
	}
}
int main(){
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++) p[i]=read();
	if(n<=10000&&m<=10000){force::solve();return 0;}
	else bit::solve();
	return 0;
}
