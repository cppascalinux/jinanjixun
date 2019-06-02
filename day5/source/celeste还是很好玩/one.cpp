#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define Mod 1000000007
using namespace std;
int fpow(int a,int b)
{
	int ans=1,t=a;
	while(b)
	{
		if(b&1)ans=(long long)ans*t%Mod;
		t=(long long)t*t%Mod;
		b>>=1;
	}
	return ans;
}
int a[210][210],b[210];
int x[210];
void gauss(int n)
{
	for(int i=1;i<=n;i++)
	{
		if(!a[i][i])
		{
			for(int j=i+1;j<=n;j++)
				if(a[j][i])
				{
					for(int k=i;k<=n;k++)
						swap(a[i][k],a[j][k]);
					swap(b[i],b[j]);
					break;
				}
		}
		int inv=fpow(a[i][i],Mod-2);
		for(int j=i+1;j<=n;j++)
		{
			int tmp=(long long)a[j][i]*inv%Mod;
			for(int k=i;k<=n;k++)
				a[j][k]=(a[j][k]-(long long)a[i][k]*tmp%Mod+Mod)%Mod;
			b[j]=(b[j]-(long long)b[i]*tmp%Mod+Mod)%Mod;
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=i+1;j<=n;j++)
			b[i]=(b[i]-(long long)a[i][j]*x[j]%Mod+Mod)%Mod;
		x[i]=(long long)b[i]*fpow(a[i][i],Mod-2)%Mod;
	}
	return ;
}
int n;
int fac[11];
int id(int* p)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int t=0;
		for(int j=i+1;j<=n;j++)
			t+=(p[i]>p[j]);
		ans=ans+t*fac[n-i];
	}
	return ans+1;
}
int P[11];
void work()
{
	int x=id(P);
	int inv=fpow(n*(n-1)/2,Mod-2);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			swap(P[i],P[j]);
			int y=id(P);
			a[x][y]+=Mod-inv;a[x][y]%=Mod;
			swap(P[i],P[j]);
		}
	b[x]=1;a[x][x]=1;
	return ;
}
bool book[11];
void dfs(int x)
{
	if(x>n)
	{
		work();
		return ;
	}
	for(P[x]=1;P[x]<=n;P[x]++)
		if(!book[P[x]])
		{
			book[P[x]]=true;
			dfs(x+1);
			book[P[x]]=false;
		}
	return ;
}
int main()
{
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	scanf("%d",&n);
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i;
	dfs(1);
	memset(a[1],0,sizeof(a[1]));
	b[1]=0;
	a[1][1]=1;
	gauss(fac[n]);
	for(int i=1;i<=n;i++)
		scanf("%d",&P[i]);
	printf("%d\n",x[id(P)]);
	fclose(stdin);fclose(stdout);
	return 0;
}
