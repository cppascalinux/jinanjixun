#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,edgenum,head[200005],dep[200005],pa[200005],maxd,mind,ans,a[200005];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
	maxd=max(maxd,dep[node]);
	mind=min(mind,dep[node]);
	ans++;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		if(a[to]!=a[node])continue;
		pa[to]=node;
		dfs(to);
	}
	pa[node]=0;
}
void dfs2(int node,int y)
{
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		if(a[to]!=a[node])continue;
		pa[to]=node;
		dfs2(to,y);
	}
	a[node]=y;
	pa[node]=0;
}
int main()
{
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&pa[i]);
		dep[i]=dep[pa[i]]+1;
		add(pa[i],i);
		add(i,pa[i]);
		pa[i]=0;
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	while(m--)
	{
		int type,x,y;
		scanf("%d%d",&type,&x);
		if(type==1)
		{
			scanf("%d",&y);
			a[x]=y;
		}
		else if(type==2)
		{
			scanf("%d",&y);
			dfs2(x,y);
		}
		else
		{
			ans=0;
			maxd=0,mind=2147483647;
			dfs(x);
			printf("%d %d %d\n",a[x],ans,maxd-mind+1);
		}
	}
	return 0;
}
