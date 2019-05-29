#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
struct Edge
{
	int to;
	int nxt;
	ll len;
}e[200005];
int n,m,edgenum,head[100005],pa[100005],size[100005];
ll f[3005][3005][2],a[100005],sum;
void add(int u,int v,ll l)
{
	e[++edgenum].len=l;
	e[edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
	f[node][0][1]=-1000000000000000;
	size[node]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		sum+=e[hd].len*2;
		dfs(to);
		for(int i=size[node];i>=0;i--)
		for(int j=size[to];j>=0;j--)
		{
			f[node][i+j][0]=max(f[node][i+j][0],f[node][i][0]+f[to][j][0]);
			f[node][i+j][0]=max(f[node][i+j][0],f[node][i][1]+f[to][j+1][1]+e[hd].len);
			f[node][i+j][1]=max(f[node][i+j][1],f[node][i][1]+f[to][j][0]);
			f[node][i+j][1]=max(f[node][i+j][1],f[node][i][0]+f[to][j][1]+e[hd].len);
		}
		size[node]+=size[to];
	}
}
ll f2[100005][5][2];
void dfs2(int node)
{
	f2[node][0][1]=-1000000000000000;
	size[node]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		sum+=e[hd].len*2;
		dfs2(to);
		for(int i=min(2,size[node]);i>=0;i--)
		for(int j=min(2,size[to]);j>=0;j--)
		{
			f2[node][i+j][0]=max(f2[node][i+j][0],f2[node][i][0]+f2[to][j][0]);
			f2[node][i+j][0]=max(f2[node][i+j][0],f2[node][i][1]+f2[to][j+1][1]+e[hd].len);
			f2[node][i+j][1]=max(f2[node][i+j][1],f2[node][i][1]+f2[to][j][0]);
			f2[node][i+j][1]=max(f2[node][i+j][1],f2[node][i][0]+f2[to][j][1]+e[hd].len);
		}
		size[node]+=size[to];
	}
}
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		int u,v;
		ll l;
		scanf("%d%d%lld",&u,&v,&l);
		add(u,v,l);
		add(v,u,l);
	}
	if(n>3000&&m<=2)
	{
		dfs2(1);
		for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
		printf("%lld ",sum);
		for(int i=1;i<=m;i++)
		{
			sort(a+1,a+i+1);
			ll s=0,maxx=0;
			for(int j=1;j<=i;j++)
			{
				s+=a[j];
				maxx=max(maxx,f2[1][j][0]-s);
			}
			printf("%lld ",sum-maxx);
		}
		printf("\n");
		return 0;
	}
	dfs(1);
	for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
	printf("%lld ",sum);
	for(int i=1;i<=m;i++)
	{
		sort(a+1,a+i+1);
		ll s=0,maxx=0;
		for(int j=1;j<=i;j++)
		{
			s+=a[j];
			maxx=max(maxx,f[1][j][0]-s);
		}
		printf("%lld ",sum-maxx);
	}
	printf("\n");
	return 0;
}
