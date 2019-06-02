#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 1000000007
using namespace std;
int n,m;
int p[29],mul[29];
int mat[129][129];
int st[29],vis[29];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init()
{
	mul[0]=1;
	for(int i=1;i<=n;i++)
		mul[i]=mul[i-1]*i;
}
int open(int *s)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int sm=0;
		for(int j=i+1;j<=n;j++)
			sm+=s[i]>s[j];
		ans+=sm*mul[n-i];
	}
	return ans+1;
}
void gauss()
{
	// for(int i=1;i<=m;i++)
	// {
	// 	for(int j=1;j<=m+1;j++)
	// 		printf("%d ",mat[i][j]);
	// 	printf("\n");
	// }
	for(int i=1;i<=m;i++)
	{
		int t=i;
		for(int j=i+1;j<=m;j++)
			if(mat[j][i]>mat[t][i])
				t=j;
		if(t!=i)
			for(int k=i;k<=m+1;k++)
				swap(mat[i][k],mat[t][k]);
		int inv=qpow(mat[i][i],mod-2);
		for(int k=m+1;k>=i;k--)
			mat[i][k]=(li)mat[i][k]*inv%mod;
		for(int j=i+1;j<=m;j++)
			for(int k=m+1;k>=i;k--)
				mat[j][k]=(mat[j][k]-(li)mat[j][i]*mat[i][k]%mod+mod)%mod;
	}
	for(int i=m;i>=1;i--)
		for(int j=i+1;j<=m;j++)
			mat[i][m+1]=(mat[i][m+1]-(li)mat[i][j]*mat[j][m+1]%mod+mod)%mod;
	// printf("\n");
	// for(int i=1;i<=m;i++)
	// {
	// 	for(int j=1;j<=m+1;j++)
	// 		printf("%d ",mat[i][j]);
	// 	printf("\n");
	// }
}
void adde(int *s)
{
	int x=open(s);
	if(x==1)
		return mat[x][x]=1,void();
	int inv=qpow(n*(n-1)/2,mod-2);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			swap(s[i],s[j]);
			int v=open(s);
			mat[x][v]=inv;
			swap(s[i],s[j]);
		}
	mat[x][x]=mat[x][m+1]=mod-1;
}
void dfs(int d)
{
	if(d>n)
		return adde(st),void();
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			vis[i]=1;
			st[d]=i;
			dfs(d+1);
			vis[i]=0;
		}
}
void solve()
{
	dfs(1);
	gauss();
	int x=open(p);
	// printf("x:%d\n",x);
	printf("%d",mat[x][m+1]);
}
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",p+i);
	init();
	m=mul[n];
	solve();
	return 0;
}