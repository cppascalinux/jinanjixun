#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define li long long
#define mod 1000000007
using namespace std;
int n,m;
int v[11];
int sa[31][1039],sb[31][1039];
int f[31][1050009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b)
			ans=(li)ans*a%mod;
	return ans;
}
void init()
{
	for(int i=0;i<=m-1;i++)
	{
		for(int s=0;s<1<<n;s++)
		{
			int o[11];
			for(int j=1;j<=n;j++)
				if((s>>(j-1))&1)
					o[j]=1;
				else
					o[j]=0;
			for(int j=1;j<=n-1;j++)
			{
				int v1=(v[j]>>i)&1&o[j],v2=(v[j+1]>>i)&1&o[j+1];
				if(v1<v2)
					sa[i][s]+=1<<(j-1);
				else if(v1>v2)
					sb[i][s]+=1<<(j-1);
				v1=((v[j]>>i)&1)|o[j],v2=((v[j+1]>>i)&1)|o[j+1];
				if(v1>v2)
					sa[i][s]+=1<<(j+n-1-1);
				else if(v1<v2)
					sb[i][s]+=1<<(j+n-1-1);
			}
		}
	}
	// for(int i=0;i<=m-1;i++)
	// 	for(int j=0;j<1<<n;j++)
	// 		printf("i:%d s:%d sa:%d sb:%d\n",i,j,sa[i][j],sb[i][j]);
}
void solve()
{
	f[m][0]=1;
	for(int i=m;i>=1;i--)
		for(int s=0;s<1<<(2*n-2);s++)
			if(f[i][s])
				for(int t=0;t<1<<n;t++)
					if((sb[i-1][t]|s)==s)
						f[i-1][s|sa[i-1][t]]=(f[i-1][s|sa[i-1][t]]+f[i][s])%mod;
	// printf("%d",f[0][(1<<(2*n-2))-1]);
	int ans=0;
	for(int s=0;s<1<<(2*n-2);s++)
		ans=(ans+f[0][s])%mod;
	printf("%d",ans);
}
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	init();
	solve();
	cerr<<clock();
	return 0;
}