#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=998244353;
ll n,k,ans;
int a[13],f[13][2];
bool v[13];
void dfs(int x)
{
	if(x>n)
	{
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++)
			f[i][1]=1;
		for(int i=2;i<=n;i++)
			for(int j=1;j<i;j++)
			{
				if(a[i]>a[j]) f[i][1]=max(f[i][1],f[j][0]+1);
				if(a[i]<a[j]) f[i][0]=max(f[i][0],f[j][1]+1);
			}
		int maxx=0;
		for(int i=1;i<=n;i++)
			maxx=max(maxx,max(f[i][0],f[i][1]));
		if(maxx==k)
		{
			ans++;
			if(ans>=mod) ans-=mod;
		}
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(v[i]) continue;
		a[x]=i;
		v[i]=true;
		dfs(x+1);
		v[i]=false;
	}
}
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	dfs(1);
	printf("%lld ",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
