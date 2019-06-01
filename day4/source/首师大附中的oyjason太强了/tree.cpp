#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=101010;
vector<int>s[N];
int f[N],sum[N],f2[N],sum2[N],d[N],up[N][20],fa[N],X[N],Y[N],L[N],sum1,summ,ss[N],fa1[N],fa2[N];
void dfs1(int x)
{
	int c,i,y;
	c=s[x].size();
	for(i=0;i<c;i++)
	{
		y=s[x][i];
		if(fa[x]==y)
			continue;
		fa[y]=x;
		d[y]=d[x]+1;
		up[y][0]=x;
		dfs1(y);
	}
}
int lca(int x,int y)
{
	int tmp=18;
	if(d[x]<d[y])
		swap(x,y);
	while(1)
	{
		if((1<<tmp)<=d[x]-d[y])
			x=up[x][tmp];
		tmp--;
		if(tmp<0)
			break;
	}
//	printf("%d %d||%d %d\n",x,y,d[x],d[y]);
	if(x==y)
		return x;
	tmp=18;
	while(1)
	{
		if(up[x][tmp]!=up[y][tmp])
			x=up[x][tmp],y=up[y][tmp];
		tmp--;
		if(tmp<0)
			break;
	}
	return up[x][0];
}
void dfs(int x)
{
	int c,i,y;
	c=s[x].size();
	for(i=0;i<c;i++)
	{
		y=s[x][i];
		if(fa[x]==y)
			continue;
		fa[y]=x;
		dfs(y);
		sum[x]+=sum[y];
		sum2[x]+=sum2[y];
		f[x]+=f[y];
		f2[x]+=f2[y];
	}
	if(sum[x]>0)
		f[x]++;
	if(sum2[x]>0)
		f2[x]++;
//	printf("%d %d %d %d %d\n",x,sum[x],sum2[x],f[x],f2[x]);
}
int find_set1(int x)
{
	if(fa1[x]==x)
		return x;
	return fa1[x]=find_set1(fa1[x]);
}
void upd(int x,int y)
{
	while(1)
	{
		x=find_set1(x);
		if(d[x]<d[y]||!x)
			return;
		sum1++;
		fa1[x]=fa[x];
	}
}
int find_set2(int x)
{
	if(fa2[x]==x)
		return x;
	return fa2[x]=find_set2(fa2[x]);
}
void upd2(int x,int y)
{
	while(1)
	{
		x=find_set2(x);
		if(d[x]<d[y]+1||!x)
			return;
		summ++;
		fa2[x]=fa[x];
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m,q,i,j,x,y,l,r;
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		s[x].push_back(y),s[y].push_back(x);
	}
	dfs1(1);
	for(j=1;j<=18;j++)
		for(i=1;i<=n;i++)
			up[i][j]=up[up[i][j-1]][j-1];
	if(n<=1000&&m<=1000&&q<=1000)
	{
		for(i=1;i<=m;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
//			printf("%d %d\n",i,L[i]);
			L[i]=lca(X[i],Y[i]);
		}
		while(q--)
		{
			scanf("%d%d",&l,&r);
			for(i=1;i<=n;i++)
				f[i]=sum[i]=0,f2[i]=sum2[i]=0;
			for(i=l;i<=r;i++)
				sum[X[i]]++,sum[Y[i]]++,sum[L[i]]--,sum[fa[L[i]]]--,
				sum2[X[i]]++,sum2[Y[i]]++,sum2[L[i]]--,sum2[L[i]]--;
			dfs(1);
			printf("%d\n",f[1]-f2[1]);
		}
	}
	else
	{
		for(i=1;i<=n;i++)
			fa1[i]=fa2[i]=i;
		for(i=1;i<=m;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
			L[i]=lca(X[i],Y[i]);
			upd(X[i],L[i]),upd(Y[i],L[i]);
			upd2(X[i],L[i]),upd2(Y[i],L[i]);
			ss[i]=sum1-summ;
//			printf("%d %d*** %d %d\n",i,ss[i],sum1,summ);
		}
		for(i=1;i<=q;i++)
		{
			scanf("%d%d",&l,&r);
			printf("%d\n",ss[r]);
		}
	}
	return 0;
}

