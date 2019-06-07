#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int v,w,nxt;
}e[500005];
int n,m,c[300005][22],d[300005],td[300005],h[300005],t,mod=1e9+7;
void add(int u,int v,int w)
{
	e[++t].v=v;
	e[t].w=w;
	e[t].nxt=h[u];
	h[u]=t;
}
void dfs(int u,int fa,int dep,int tdep)
{
	c[u][0]=fa;
	d[u]=dep;
	td[u]=tdep;
	for(int i=1;i<=18;i++)
		c[u][i]=c[c[u][i-1]][i-1];
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v,w=e[i].w;
		if(v==fa) continue;
		dfs(v,u,dep+1,(tdep+w)%mod);
	}
}
int lca(int u,int v)
{
	//printf("u=%d,v=%d,",u,v);
	if(d[u]<d[v]) swap(u,v);
	for(int i=18;i>=0;i--)
		if(d[c[u][i]]>=d[v])
			u=c[u][i];
	//printf("%d,",u);
	if(u==v) return u;
	for(int i=18;i>=0;i--)
		if(c[u][i]!=c[v][i])
			u=c[u][i],v=c[v][i];
	//printf("%d,",c[u][0]);
	return c[u][0];
}
int getdis(int u,int v)
{
	return ((td[u]+td[v]-2*td[lca(u,v)])%mod+mod)%mod;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<n;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u+n,v+n,w);
		add(v+n,u+n,w);
	}
	//printf("000");
	dfs(1,1,1,0);
	dfs(n+1,n+1,1,0);
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			ans=(ans+1ll*getdis(i,j)*getdis(i+n,j+n)%mod)%mod;
			//printf("i=%d,j=%d,ans=%d\n",i,j,ans);
		}
	printf("%d",ans);
	return 0;
}
