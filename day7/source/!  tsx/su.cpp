#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
	int v,nxt;
}e[500005];
int n,m,c[100005],h[100005],d[100005],t,ans1=0,ans2=0,ans3=0;
void add(int u,int v)
{
	e[++t].v=v;
	e[t].nxt=h[u];
	h[u]=t;
}
void dfs1(int u,int fa,int dep)
{
	d[u]=dep;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs1(v,u,dep+1);
	}
}
void dfs2(int u,int fa,int tc)
{
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||c[v]!=c[u]) continue;
		dfs2(v,u,tc);
	}
	c[u]=tc;
}
void dfs3(int u,int fa)
{
	ans1++;
	ans2=max(ans2,d[u]);
	ans3=min(ans3,d[u]);
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||c[v]!=c[u]) continue;
		dfs3(v,u);
	}
}
int main()
{
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int v;
		scanf("%d",&v);
		if(i==1) continue;
		add(i,v);
		add(v,i);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	scanf("%d",&m);
	dfs1(1,0,0);
	for(int i=1;i<=m;i++)
	{
		int op,x,y;
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d",&x,&y);
			c[x]=y;
		}
		if(op==2)
		{
			scanf("%d%d",&x,&y);
			dfs2(x,0,y);
		}
		if(op==3)
		{
			scanf("%d",&x);
			ans1=0;
			ans2=-99999999;
			ans3=99999999;
			dfs3(x,0);
			printf("%d %d %d\n",c[x],ans1,ans2-ans3+1);
		}
	}
	return 0;
}
