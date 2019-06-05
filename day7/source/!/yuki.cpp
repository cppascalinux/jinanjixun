#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[2000005];
int n,m,edgenum,head[1000005],dep[1000005],pa[1000005],a[1000005];
int tmp[1000005],top;
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
	dep[node]=dep[pa[node]]+1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		dfs(to);
	}
}
int main()
{
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1);
	while(m--)
	{
		int type,x,y,z;
		scanf("%d%d%d",&type,&x,&y);
		if(type==1)
		{
			scanf("%d",&z);
			if(dep[x]<dep[y])swap(x,y);
			while(dep[x]!=dep[y])
			{
				a[x]+=z;
				x=pa[x];
			}
			while(x!=y)
			{
				a[x]+=z,a[y]+=z;
				x=pa[x],y=pa[y];
			}
			a[x]+=z;
		}
		else
		{
			top=0;
			for(int hd=head[x];hd;hd=e[hd].nxt)
			{
				int to=e[hd].to;
				tmp[++top]=a[to];
			}
			tmp[++top]=a[x];
			sort(tmp+1,tmp+top+1);
			printf("%d\n",tmp[y]);
		}
	}
	return 0;
}
