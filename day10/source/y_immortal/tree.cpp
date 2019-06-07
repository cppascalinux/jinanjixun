#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 202300
#define M 401010
#define INF 0x3f3f3f3f
#define mod 1000000007
struct node{
	int to,next,v;
}xq[M];
int n,lg[N<<1],ans=0,D[N],que[N],xh[N],xs,h[N],xc,col[N],usd[N],f[2][N],stk[N],Rt,RS,all,V[N],sc[2][N];bool de[N],vis[N];
struct Tree{
	node q[M],nq[M];int head[N],ss,dep[N],nh[N],cc,ns=1,tm,sz[N],out[N],pa[N<<1],dfn[N],pn[19][N<<1],sum[N];
	void addedge(int x,int y,int v)
	{
		q[++ss]=(node){y,head[x],v};head[x]=ss;
		q[++ss]=(node){x,head[y],v};head[y]=ss;
	}
	void addnew(int x,int y,int v)
	{//printf("add %d %d v=%d\n",x,y,v);
		nq[++ns]=(node){y,nh[x],v};nh[x]=ns;
		nq[++ns]=(node){x,nh[y],v};nh[y]=ns;
	}
	void dfs(int i,int fa)
	{
		dfn[i]=++tm;pa[tm]=i;dep[i]=dep[fa]+1;sz[i]=i<=n;
		for (int j=head[i];j;j=q[j].next)
			if (q[j].to^fa)
			{
				int t=q[j].to;
				sum[t]=(sum[i]+q[j].v)%mod;
				dfs(t,i);
				sz[i]+=sz[t];
				pa[++tm]=i;
			}
		out[i]=tm;
	}
	void buildst()
	{
		for (int i=1;i<tm;++i) pn[0][i]=dep[pa[i]]<dep[pa[i+1]]?pa[i]:pa[i+1];
		for (int j=1;j<=18;++j)
			for (int i=1;i+(1<<j)<=tm;++i)
				pn[j][i]=dep[pn[j-1][i]]<dep[pn[j-1][i+(1<<j-1)]]?pn[j-1][i]:pn[j-1][i+(1<<j-1)];
	}
	int LCA(int x,int y)
	{
		if (x==y) return x;
		x=dfn[x];y=dfn[y];
		if (x>y) swap(x,y);
		int j=lg[y-x];
		return dep[pn[j][x]]<dep[pn[j][y-(1<<j)]]?pn[j][x]:pn[j][y-(1<<j)];
	}
	void rebuild(int i,int fa)
	{
		int la=0;
		for (int j=head[i];j;j=q[j].next)
			if (q[j].to^fa)
			{
				int t=q[j].to;
				rebuild(t,i);
				if (!la) addnew(la=i,t,q[j].v);
				else
				{
					addnew(la,++cc,0);
					addnew(cc,t,q[j].v);
					la=cc;
				}
			}
	}
	void FRT(int i,int fa)
	{
		sz[i]=1;
		for (int j=head[i];j;j=q[j].next)
			if (q[j].to^fa&&!vis[j>>1])
			{
				int t=q[j].to;
				FRT(t,i);
				sz[i]+=sz[t];
				if (max(sz[t],all-sz[t])<RS) RS=max(sz[t],all-sz[t]),Rt=j;
			}
	}
}T1,T2;
void addxu(int x,int y,int v=0) {xq[++xs]=(node){y,xh[x],v};xh[x]=xs;}
void dfs1(int i,int fa,int S,int c)
{
	if (i<=n) h[++xc]=i,col[i]=c,V[i]=S;
	for (int j=T1.head[i];j;j=T1.q[j].next)
		if (T1.q[j].to^fa&&!vis[j>>1])
			dfs1(T1.q[j].to,i,(S+T1.q[j].v)%mod,c);
}
void dp(int i)
{
	f[0][i]=f[1][i]=sc[0][i]=sc[1][i]=0;
	if (usd[i]==1) f[col[i]][i]=(f[col[i]][i]+V[i])%mod,++sc[col[i]][i];
	for (int j=xh[i];j;j=xq[j].next)
	{
		int t=xq[j].to;
		dp(t);
		ans=((ans-4ll*T2.sum[i]*((1ll*sc[0][i]*f[1][t]+1ll*sc[1][i]*f[0][t]+1ll*f[0][i]*sc[1][t]+1ll*f[1][i]*sc[0][t])%mod))%mod+mod)%mod;
		f[0][i]=(f[0][i]+f[0][t])%mod;
		f[1][i]=(f[1][i]+f[1][t])%mod;
		sc[0][i]+=sc[0][t];
		sc[1][i]+=sc[1][t];
	}
}
bool cmp(int x,int y) {return T2.dfn[x]<T2.dfn[y];}
void solve(int x)
{//printf("solve %d (%d,%d)\n",x,T1.q[x].to,T1.q[x^1].to);
	if (!x) return;
	vis[x>>1]=true;xc=0;
	dfs1(T1.q[x].to,T1.q[x^1].to,0,1);
	dfs1(T1.q[x^1].to,T1.q[x].to,T1.q[x].v,0);
	sort(h+1,h+1+xc,cmp);
	for (int i=1;i<=xc;++i) usd[h[i]]=1;
	int k=xc;
	for (int i=2;i<=k;++i)
	{
		int lca=T2.LCA(h[i],h[i-1]);
		if (!usd[lca]) usd[lca]=2,h[++xc]=lca;
	}
	sort(h+1,h+1+xc,cmp);
	int top=0;
	stk[++top]=h[1];
	for (int i=2;i<=xc;++i)
	{
		while(top&&T2.dfn[h[i]]>T2.out[stk[top]]) --top;
		addxu(stk[top],h[i]);
		stk[++top]=h[i];
	}
//	for (int i=1;i<=xc;++i) printf("%d ",h[i]);putchar('\n');
//	printf("aksdlad");
	dp(h[1]);
	for (int i=1;i<=xc;++i) usd[h[i]]=xh[h[i]]=0;xs=0;
	int tmp=all;
	if (T1.sz[T1.q[x].to]>T1.sz[T1.q[x^1].to]) x^=1;
	Rt=0;RS=INF;all=T1.sz[T1.q[x].to];T1.FRT(T1.q[x].to,T1.q[x^1].to);solve(Rt);
	Rt=0;RS=INF;all=tmp-T1.sz[T1.q[x].to];T1.FRT(T1.q[x^1].to,T1.q[x].to);solve(Rt);
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int x,y,v,f=1,e=0;n=read();T1.cc=n;
	for (int i=1;i<n;++i)
	{
		x=read();y=read();v=read();
		T1.addedge(x,y,v);
	}
	T1.rebuild(1,1);
	memcpy(T1.q,T1.nq,sizeof(T1.nq));
	memcpy(T1.head,T1.nh,sizeof(T1.nh));
	T1.ss=T1.ns;T1.dfs(1,1);
	for (int i=1;i<n;++i) 
	{
		x=read();y=read();v=read();
		T2.addedge(x,y,v);
	}
	T2.dfs(1,1);
	for (int i=2;i<=T2.tm;++i) lg[i]=lg[i>>1]+1;
	T2.buildst();
	for (int i=1;i<=n;++i) D[1]=(D[1]+T1.sum[i])%mod;
	que[++e]=1;
	while(f<=e)
	{
		int u=que[f++];de[u]=true;
		if (u<=n) ans=(ans+2ll*T2.sum[u]*D[u])%mod;
		for (int j=T1.head[u];j;j=T1.q[j].next)
		{
			int t=T1.q[j].to;
			if (de[t]) continue;
			D[t]=((D[u]+1ll*T1.q[j].v*(n-2*T1.sz[t]))%mod+mod)%mod;
			que[++e]=t;
		}
	}
	Rt=0;RS=INF;all=n;T1.FRT(1,1);solve(Rt);
	printf("%d",(ans%mod+mod)%mod);
	return 0;
}

//by qlwpc
