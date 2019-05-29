#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct Edge{
	int v,c,nxt;
}e[200010];int tot=1;
int first[100010];
void build(int u,int v,int c)
{
	e[++tot]=(Edge){v,c,first[u]};
	first[u]=tot;
	return ;
}
int pren[100010],pree[100010];
void dfs(int u,int lst)
{
	pren[u]=lst;
	for(int i=first[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==lst)continue;
		pree[v]=i;
		dfs(v,u);
	}
	return ;
}
int mx[100010],mmx[100010];
long long f1[100010],f2[100010];
void solve(int u,int lst)
{
	mx[u]=u;mmx[u]=u;
	f1[u]=0;f2[u]=0;
	for(int i=first[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==lst)continue;
		solve(v,u);
		if(f1[v]+e[i].c>f1[u])
		{
			f2[u]=f1[u];mmx[u]=mx[u];
			f1[u]=f1[v]+e[i].c;mx[u]=mx[v];
		}
		else if(f1[v]+e[i].c>f2[u])
		{
			f2[u]=f1[v]+e[i].c;
			mmx[u]=mx[v];
		}
	}
	return ;
}
long long f[100010];
int a[100010];
int main()
{
	freopen("love.in","r",stdin);
	freopen("love.out","w",stdout);
	int n,m;
	scanf("%d %d",&n,&m);
	long long Sum=0;
	for(int i=1;i<n;i++)
	{
		int u,v,c;
		scanf("%d %d %d",&u,&v,&c);
		Sum+=c;
		build(u,v,c);
		build(v,u,c);
	}
	f[0]=0;
	for(int i=1;i<=m;i++)
	{
		solve(1,0);
		int o=1;
		for(int j=2;j<=n;j++)
			if(f1[j]+f2[j]>f1[o]+f2[o])o=j;
		f[i]=f[i-1]+f1[o]+f2[o];
		dfs(mx[o],0);
		for(int j=mmx[o];j!=mx[o];j=pren[j])
		{
			int ee=pree[j];
			e[ee].c*=-1;
			e[ee^1].c*=-1;
		}
	}
	for(int i=1;i<=m;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=m;i++)
	{
		sort(a+1,a+i+1);
		long long ans=0,cur=0;
		for(int j=0;j<=i;j++)
		{
			cur+=a[j];
			ans=max(ans,f[j]-cur);
		}
		printf("%lld ",2*Sum-ans);
	}
	printf("\n");
	fclose(stdin);fclose(stdout);
	return 0;
}
