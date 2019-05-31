#include<cstdio>
#define ll long long
#define N 5100
#define mod 998244353
int f[N][N];
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	ll n;int k;
	scanf("%lld%d",&n,&k);
	f[1][1]=1;
	for (int i=2;i<=n;++i)
		for (int j=1;j<=i&&j<=k;++j)
			f[i][j]=(1ll*j*f[i-1][j]+f[i-1][j-1]+(i-j+1ll)*f[i-1][j-2])%mod;
	printf("%d",f[n][k]);
	return 0;
}

//by qlwpc
