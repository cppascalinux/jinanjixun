#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define mod 998244353
#define li long long
using namespace std;
int n,k,sm;
int p[11],vis[11];
int c1[11],c2[11];
void add1(int x,int val)
{
	for(;x<=n;x+=x&-x)
		c1[x]=max(c1[x],val);
}
int ask1(int x)
{
	int val=0;
	for(;x;x-=x&-x)
		val=max(val,c1[x]);
	return val;
}
void add2(int x,int val)
{
	for(;x;x-=x&-x)
		c2[x]=max(c2[x],val);
}
int ask2(int x)
{
	int val=0x80808080;
	for(;x<=n;x+=x&-x)
		val=max(val,c2[x]);
	return val;
}
void solve()
{
	memset(c1,0,sizeof(c1));
	memset(c2,0x80,sizeof(c2));
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",p[i]);
	// printf("\n");
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int l1=ask1(p[i])+1,l2=ask2(p[i])+1;
		// printf("i:%d l1:%d l2:%d\n",i,l1,l2);
		ans=max(ans,max(l1,l2));
		add1(p[i],l2),add2(p[i],l1);
	}
	// printf("ans:%d\n",ans);
	if(ans==k)
		sm++;
}
void dfs(int d)
{
	if(d>n)
		return solve(),void();
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			p[d]=i;
			vis[i]=1;
			dfs(d+1);
			vis[i]=0;
		}
}
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%d%d",&n,&k);
	dfs(1);
	printf("%d",sm);
	// cerr<<clock();
	return 0;
}