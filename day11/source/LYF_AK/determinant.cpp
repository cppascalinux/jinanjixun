#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" --------------------------------- "<<endl
#define pii pair<int,int>
#define mp make_pair
#define LL long long
#define M 100020
#define LS first
#define RS second
#define mod 1000000007
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
int n,m;
inline int mul(int x,int y){return (LL)x*(LL)y%mod;}
inline int qpow(int x,int sq){int res=1;for(;sq;sq>>=1,x=mul(x,x)) if(sq&1) res=mul(res,x);return res;}
namespace Calc{
	int r[M],id[M],L[M],R[M],rt[M],dis[M],cnt,pos[M];
	int node(int rsd,int ID){cnt++,pos[id[cnt]=ID]=cnt,r[cnt]=rsd;return cnt;}
	int merge(int x,int y){
		if(!x||!y) return x|y; if(r[x]>r[y]) swap(x,y);
		R[x]=merge(R[x],y); if(dis[R[x]]>dis[L[x]]) swap(R[x],L[x]);
		dis[x]=(R[x])?(dis[R[x]]+1):0; return x;
	}
	int Pop(int x){return merge(L[x],R[x]);}
	void init(){
		cnt=0,memset(pos,0,sizeof(pos));
		memset(rt,0,sizeof(rt)),memset(id,0,sizeof(id));
		memset(r,0,sizeof(r)),memset(L,0,sizeof(L));
		memset(R,0,sizeof(R)),memset(dis,0,sizeof(dis));
	}
	int solve(pii *t){
		int fh=1,ps=1; init();
		for(int i=1;i<=n;i++){
			rt[t[i].LS]=merge(rt[t[i].LS],node(t[i].RS,i));
			ps=mul(ps,t[i].RS-t[i].LS+1);
		}
		for(int i=1;i<=n;i++){
			while(rt[i]&&r[rt[i]]<i) rt[i]=Pop(rt[i]); if(!rt[i]) return 0;
			int ID=id[rt[i]],rst=r[rt[i]]; rt[i]=Pop(rt[i]);
			if(rst<n) rt[rst+1]=merge(rt[rst+1],rt[i]);
			if(ID!=i) fh^=1,pos[id[pos[i]]=ID]=pos[i];
		} if(!fh) fh=mod-1; return mul(fh,qpow(ps,mod-2));
	}
}
pii tx[M],ty[M]; using Calc::solve;
int main(){
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	for(int T=read();T;T--){
		n=read();
		for(int i=1;i<=n;i++){
			tx[i].LS=read(),tx[i].RS=read();
			ty[i].LS=read(),ty[i].RS=read();
		}
		printf("%d\n",mul(solve(tx),solve(ty)));
	} return 0;
}
