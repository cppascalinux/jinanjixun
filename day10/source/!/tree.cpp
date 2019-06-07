#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=1e9+7;
int n;
struct Tree
{
	struct Edge
	{
		int to;
		int nxt;
		ll len;
	}e[200005];
	int m,edgenum,head[100005],pa[100005];
	ll dep[100005],a[400005],minn[26][400005];
	int dfn[100005],lg2[400005];
	void add(int u,int v,ll l)
	{
		e[++edgenum].len=l;
		e[edgenum].to=v;
		e[edgenum].nxt=head[u];
		head[u]=edgenum;
	}
	int ind;
	void dfs_pre(int node)
	{
		dfn[node]=++ind;
		a[ind]=dep[node];
		for(int hd=head[node];hd;hd=e[hd].nxt)
		{
			int to=e[hd].to;
			if(to==pa[node])continue;
			pa[to]=node;
			dep[to]=dep[node]+e[hd].len;
			dfs_pre(to);
			a[++ind]=dep[node];
		}
	}
	void pre()
	{
		for(int i=1;i<=ind;i++)minn[0][i]=a[i];
		for(int i=2;i<=ind;i++)lg2[i]=lg2[i>>1]+1;
		for(int i=1;i<=lg2[ind];i++)
		  for(int j=1;j<=ind;j++)
		    minn[i][j]=min(minn[i-1][j],minn[i-1][j+(1<<(i-1))]);
	}
	ll dis(int u,int v)
	{
		if(u==v)return 0;
		u=dfn[u],v=dfn[v];
		if(u>v)swap(u,v);
		int d=lg2[v-u+1];
		return (a[u]+a[v]-2*min(minn[d][u],minn[d][v-(1<<d)+1]))%MOD;
	}
}T1,T2;
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		ll l;
		scanf("%d%d%lld",&u,&v,&l);
		T1.add(u,v,l);
		T1.add(v,u,l);
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		ll l;
		scanf("%d%d%lld",&u,&v,&l);
		T2.add(u,v,l);
		T2.add(v,u,l);
	}
	T1.dfs_pre(1);
	T1.pre();
	T2.dfs_pre(1);
	T2.pre();
	ll ans=0;
	for(int i=1;i<=n;i++)
	  for(int j=i+1;j<=n;j++)
		ans+=T1.dis(i,j)*T2.dis(i,j)%MOD;
	printf("%lld\n",ans*2%MOD);
	return 0;
}
