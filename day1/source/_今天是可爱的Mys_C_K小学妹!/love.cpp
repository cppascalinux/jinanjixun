#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=100010;const lint inf=LLONG_MIN/100;
struct edges{
	int to,pre,w;
}e[N<<1];int h[N],etop,A[N];
inline int add_edge(int u,int v,int w) { return e[++etop].to=v,e[etop].pre=h[u],e[etop].w=w,h[u]=etop; }
namespace subtask12{
	const int N=3010;
	lint dp[N][N<<1][2],tmp[N][2],b[N],bs[N],val[N];int sz[N];
	inline void upd(lint &x,lint y) { x=max(x,y); }
	inline int _merge_dp(lint (*dpx)[2],int m1,lint (*dpy)[2],int m2,int w)
	{
		rep(i,0,m1+m2+1) tmp[i][0]=0,tmp[i][1]=inf;
		rep(i,0,m1) rep(j,0,m2)
		{
			lint *f=dpx[i],*g=dpy[j],*t0=tmp[i+j],*t1=tmp[i+j+1],v=max(g[0],g[1]);
			(i||j?upd(tmp[i+j-1][0],f[1]+g[1]+w),0:0),
			upd(t1[1],f[0]+g[0]+w),upd(t0[1],f[0]+g[1]+w),upd(t0[0],f[1]+g[0]+w);
			rep(ci,0,1) upd(t0[ci],f[ci]+v);
		}
		rep(i,0,m1+m2+1) rep(j,0,1) dpx[i][j]=tmp[i][j];return 0;
	}
	int dfs(int x,int fa,int m)
	{
		dp[x][0][1]=inf;
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^fa)
			dfs(y,x,m),_merge_dp(dp[x],sz[x],dp[y],sz[y],e[i].w),sz[x]=min(sz[x]+sz[y]+1,m);
		return 0;
	}
	inline int brute_force30(int n,int m)
	{
		lint tot=0;
		rep(x,1,n) for(int i=h[x];i;i=e[i].pre) tot+=e[i].w;
		printf("%lld ",tot),dfs(1,0,min(m+1,n+1));
		rep(i,1,min(n-1,m)) val[i]=max(dp[1][i][0],dp[1][i][1]);
		rep(i,1,m)
		{
			int p=0;rep(j,1,i-1) if(b[j]<=A[i]) p=j;
			for(int j=i;j>p+1;j--) b[j]=b[j-1];b[p+1]=A[i];
			rep(j,1,i) bs[j]=bs[j-1]+b[j];lint ans=0;
			rep(j,1,min(n-1,i)) ans=min(ans,bs[j]-val[j]);
			printf("%lld ",ans+tot);
		}
		return !printf("\n");
	}
}
namespace subtask3{
	const int N=100010,M=10;
	lint dp[N][M][2],tmp[N][2],b[N],bs[N],val[N];int sz[N];
	inline void upd(lint &x,lint y) { x=max(x,y); }
	inline int _merge_dp(lint (*dpx)[2],int m1,lint (*dpy)[2],int m2,int w)
	{
		rep(i,0,m1+m2+1) tmp[i][0]=0,tmp[i][1]=inf;
		rep(i,0,m1) rep(j,0,m2)
		{
			lint *f=dpx[i],*g=dpy[j],*t0=tmp[i+j],*t1=tmp[i+j+1],v=max(g[0],g[1]);
			(i||j?upd(tmp[i+j-1][0],f[1]+g[1]+w),0:0),
			upd(t1[1],f[0]+g[0]+w),upd(t0[1],f[0]+g[1]+w),upd(t0[0],f[1]+g[0]+w);
			rep(ci,0,1) upd(t0[ci],f[ci]+v);
		}
		rep(i,0,m1+m2+1) rep(j,0,1) dpx[i][j]=tmp[i][j];return 0;
	}
	int dfs(int x,int fa,int m)
	{
		dp[x][0][1]=inf;
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^fa)
			dfs(y,x,m),_merge_dp(dp[x],sz[x],dp[y],sz[y],e[i].w),sz[x]=min(sz[x]+sz[y]+1,m);
		return 0;
	}
	inline int brute_force10(int n,int m)
	{
		lint tot=0;
		rep(x,1,n) for(int i=h[x];i;i=e[i].pre) tot+=e[i].w;
		printf("%lld ",tot),dfs(1,0,min(m+1,n+1));
		rep(i,1,min(n-1,m)) val[i]=max(dp[1][i][0],dp[1][i][1]);
		rep(i,1,m)
		{
			int p=0;rep(j,1,i-1) if(b[j]<=A[i]) p=j;
			for(int j=i;j>p+1;j--) b[j]=b[j-1];b[p+1]=A[i];
			rep(j,1,i) bs[j]=bs[j-1]+b[j];lint ans=0;
			rep(j,1,min(n-1,i)) ans=min(ans,bs[j]-val[j]);
			printf("%lld ",ans+tot);
		}
		return !printf("\n");
	}
}
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	int n=inn(),m=inn(),x,y,w;
	rep(i,1,n-1) x=inn(),y=inn(),w=inn(),add_edge(x,y,w),add_edge(y,x,w);
	rep(i,1,m) A[i]=inn();
	if(max(n,m)<=3000) return subtask12::brute_force30(n,m);
	if(m<=2) return subtask3::brute_force10(n,m);
}
