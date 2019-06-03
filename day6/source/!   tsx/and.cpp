#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,b[100005],f[15][10005],mod=1e9+7,ans=0;
bool check(int x,int y,int z)
{
	if((b[x-1]|z)<(b[x]|y)) return 0;
	if((b[x-1]&z)>(b[x]&y)) return 0;
	return 1;
}
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=0;i<(1<<m);i++)
		f[1][i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<(1<<m);j++)
		{
			for(int k=0;k<(1<<m);k++)
				if(check(i,j,k))
					f[i][j]=(f[i][j]+f[i-1][k])%mod;
		}
	}
	for(int i=0;i<(1<<m);i++)
		ans=(ans+f[n][i])%mod;
	printf("%d",ans);
	return 0;
}
