#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1000000
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
const int mod=1e9+7;
int col[N],d1[N],d2[N],A;
namespace T3
{	int tot,head[N],sz[N],all,center,vis[N],sf,sg,sh,ss,f[N],g[N],h[N],s[N];
	struct Edge{int v,w,next;}edge[N];
	inline void add(int x,int y,int z){edge[++tot]=Edge{y,z,head[x]};head[x]=tot;}
	inline void clear(vector<int> &v){tot=0;for(auto x:v)head[x]=vis[x]=0;}
	void dfs1(int x,int la=0)
	{	sz[x]=1;
		for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) dfs1(to,x),sz[x]+=sz[to];
	}
	void dfs2(int x,int la=0)
	{	int tag=sz[x]*2>=all;
		for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) dfs2(to,x),tag&=sz[to]*2<=all;
		if(tag) center=x;
	}
	void dfs3(int x,int la=0)
	{	for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) d2[to]=(d2[x]+edge[i].w)%mod,dfs3(to,x);
	}
	void dfs4(int x,int la=0)
	{	if(~col[x])(A+=((ll)d1[x]*(sg-g[col[x]]+mod)%mod+(ll)d2[x]*(sf-f[col[x]]+mod)%mod+(ll)(ss-s[col[x]]+mod)*d1[x]%mod*d2[x]%mod+sh-h[col[x]]+mod)%mod)%=mod;
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]&&to!=la) dfs4(to,x);
	}
	void dfs5(int x,int la=0)
	{	if(~col[x])
		ss++,s[col[x]]++,
		(sf+=d1[x])%=mod,(f[col[x]]+=d1[x])%=mod,
		(sg+=d2[x])%=mod,(g[col[x]]+=d2[x])%=mod,
		(sh+=(ll)d1[x]*d2[x]%mod)%=mod,(h[col[x]]+=(ll)d1[x]*d2[x]%mod)%=mod;
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]&&to!=la) dfs5(to,x);
	}
	void dfs6(int x,int la=0)
	{	if(~col[x]) sf=f[col[x]]=sg=g[col[x]]=sh=h[col[x]]=ss=s[col[x]]=0;
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]&&to!=la) dfs6(to,x);
	}
	void solve(int x)
	{	dfs1(x); all=sz[x]; dfs2(x); vis[x=center]=1;
		d2[x]=0; dfs3(x); if(~col[x]) (sf+=d1[x])%=mod,(f[col[x]]+=d1[x])%=mod,ss++,s[col[x]]++;
	//	debug(d1[3],d2[3]);
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]) dfs4(to),dfs5(to);
	//	debug(center,A);fgx;
		dfs6(x); for(rint i=head[x];i;i=edge[i].next) if(!vis[to]) solve(to);
	}
}
namespace T2
{	int tot,head[N],D,f[100010][20],dep[N],dfn[N],dis[N],fa[N],s[N];
	struct Edge{int v,w,next;}edge[N];
	inline void add(int x,int y,int z){edge[++tot]=Edge{y,z,head[x]};head[x]=tot;}
	void dfs(int x,int la=0)
	{	D=max(D,dep[x]=dep[la]+1); f[x][0]=la; dfn[x]=++dfn[0];
		for(rint i=head[x];i;i=edge[i].next) if(to!=la) dis[to]=(dis[x]+edge[i].w)%mod,dfs(to,x);
	}
	inline void init(int n)
	{	dfs(1); D=log2(D);
		for(rint j=1;j<=D;j++)
		for(rint i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1];
	}
	inline int lca(int x,int y)
	{	if(dep[x]<dep[y]) swap(x,y);
		for(rint i=D;i>=0;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
		if(x==y) return x;
		for(rint i=D;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
		return f[x][0];
	}
	inline void gao(vector<int> &v)
	{	int top=0; vector<int> t=v; sort(v.begin(),v.end(),[](int x,int y){return dfn[x]<dfn[y];});
		for(auto x:v)
		{	if(!top){fa[s[++top]=x]=0;continue;}
			int l=lca(x,s[top]);
			for(;dep[s[top]]>dep[l];top--) if(dep[s[top-1]]<=dep[l]) fa[s[top]]=l;
			if(s[top]!=l) t.push_back(l),fa[l]=s[top],s[++top]=l;
			fa[x]=s[top]; s[++top]=x;
		}
		for(auto x:t) if(fa[x]) T3::add(fa[x],x,(dis[x]-dis[fa[x]]+mod)%mod),T3::add(x,fa[x],(dis[x]-dis[fa[x]]+mod)%mod);
	//	for(auto x:t) cerr<<x<<" ";fgx;
		T3::solve(t[0]); T3::clear(t);
	}
}
namespace T1
{	int tot,head[N],sz[N],vis[N],all,center;
	struct Edge{int v,w,next;}edge[N];
	inline void add(int x,int y,int z){edge[++tot]=Edge{y,z,head[x]};head[x]=tot;}
	void dfs1(int x,int la=0)
	{	sz[x]=1;
		for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) dfs1(to,x),sz[x]+=sz[to];
	}
	void dfs2(int x,int la=0)
	{	int tag=sz[x]*2>=all;
		for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) dfs2(to,x),tag&=sz[to]*2<=all;
		if(tag) center=x;
	}
	void dfs3(int x,int c,vector<int> &v,int la=0)
	{	col[x]=c; v.push_back(x);
		for(rint i=head[x];i;i=edge[i].next)
		if(!vis[to]&&to!=la) d1[to]=(d1[x]+edge[i].w)%mod,dfs3(to,c,v,x);
	}
	void solve(int x)
	{	dfs1(x); all=sz[x]; dfs2(x); vis[x=center]=1;
		int t=0; vector<int> v; v.push_back(x); d1[x]=0; col[x]=0;
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]) d1[to]=(d1[x]+edge[i].w)%mod,dfs3(to,++t,v);
	//	debug(center);for(auto x:v) cerr<<x<<" "; fgx;
		T2::gao(v); for(auto x:v) col[x]=-1;// debug(A); if(center==6) exit(0);
		for(rint i=head[x];i;i=edge[i].next) if(!vis[to]) solve(to);
	}
}
int main()
{	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,x,y,z; cin>>n;
	for(rint i=1;i<n;i++) scanf("%d%d%d",&x,&y,&z),T1::add(x,y,z),T1::add(y,x,z);
	for(rint i=1;i<n;i++) scanf("%d%d%d",&x,&y,&z),T2::add(x,y,z),T2::add(y,x,z);
	T2::init(n); memset(col,-1,sizeof(col)); T1::solve(1); cout<<A*2LL%mod	;
	return 0;
}

