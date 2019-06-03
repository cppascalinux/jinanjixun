#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define mod 1000000007
int b[12],id[12],a[12],f[33][2300];
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	int n,m,ans=0,nn,tmp=0;
	scanf("%d%d",&n,&m);nn=1<<n-1;
	for (int i=1;i<=n;++i) scanf("%d",&b[i]);
	f[m][0]=1;
	for (int i=m;i;--i)
		for (int S=0;S<nn;++S)
		{
			int x=f[i][S];
			if (!x) continue;
			int c=0,cc;
			for (int j=1;j<=n;++j) if (b[j]&1<<i-1) id[++c]=j;
			cc=1<<c;
			for (int sta=0,T=0;sta<cc;++sta)
			{
				T=S;
				for (int j=1;j<=n;++j) a[j]=0;
				for (int j=1;j<=c;++j) if (sta&1<<j-1) a[id[j]]=1;
				for (int j=1;j<n;++j) 
					if (a[j]>a[j+1]&&~S&1<<j-1) goto GG;
					else if (a[j]<a[j+1]) T|=1<<j-1;
				f[i-1][T]=(f[i-1][T]+x)%mod;
				GG:;
			}
		}
	for (int S=0;S<nn;++S) ans=(ans+f[0][S])%mod;
//	cerr<<ans<<'\n';
	memset(f,0,sizeof(f));
	f[m][0]=1;
	for (int i=m;i;--i)
		for (int S=0;S<nn;++S)
		{
			int x=f[i][S];
			if (!x) continue;
			int c=0,cc;
			for (int j=1;j<=n;++j) if (~b[j]&1<<i-1) id[++c]=j;
			cc=1<<c;
			for (int sta=0,T=0;sta<cc;++sta)
			{
				T=S;
				for (int j=1;j<=n;++j) a[j]=1;
				for (int j=1;j<=c;++j) if (sta&1<<j-1) a[id[j]]=0;
				for (int j=1;j<n;++j)
					if (a[j]<a[j+1]&&~S&1<<j-1) goto GGG;
					else if (a[j]>a[j+1]) T|=1<<j-1;
				f[i-1][T]=(f[i-1][T]+x)%mod;
				GGG:;
			}
		}
	for (int S=0;S<nn;++S) tmp=(tmp+f[0][S])%mod;
//	cerr<<tmp<<'\n';
	printf("%lld",1ll*ans*tmp%mod);
	return 0;
}

//by qlwpc
