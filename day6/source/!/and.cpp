#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=1e9+7;
int n,m,b[15],num[31];
ll f[1<<7][1<<7],g[1<<7][1<<7];
int main()
{
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&b[i]);
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		  if((1<<i)&b[j])
		    num[i]|=(1<<j);
	}
	g[0][0]=1;
	for(int i=m-1;i>=0;i--)
	{
		for(int x=0;x<(1<<(n-1));x++)
		for(int y=0;y<(1<<(n-1));y++)
		{
			if(g[x][y]==0)continue;
			g[x][y]%=MOD;
			for(int s=0;s<(1<<n);s++)
			{
				int xx=x,yy=y;
				bool flag=1;
				for(int j=0;j<n-1;j++)
				{
					if(!((1<<j)&s&num[i])&&((1<<(j+1))&s&num[i]))xx|=(1<<j);
					else if(((1<<j)&s&num[i])&&!((1<<(j+1))&s&num[i])&&!((1<<j)&x))
					{
						flag=0;
						break;
					}
					if((((1<<j)&s)|(num[i]&(1<<j)))&&!(((1<<(j+1))&s)|(num[i]&(1<<(j+1)))))yy|=(1<<j);
					else if(!(((1<<j)&s)|(num[i]&(1<<j)))&&(((1<<(j+1))&s)|(num[i]&(1<<(j+1))))&&!((1<<j)&y))
					{
						flag=0;
						break;
					}
				}
				if(flag)f[xx][yy]=(f[xx][yy]+g[x][y])%MOD;
			}
		}
		for(int x=0;x<(1<<(n-1));x++)
		  for(int y=0;y<(1<<(n-1));y++)
		    g[x][y]=f[x][y],f[x][y]=0;
	}
	ll ans=0;
	for(int x=0;x<(1<<(n-1));x++)
	  for(int y=0;y<(1<<(n-1));y++)
	    ans+=g[x][y];
	printf("%lld\n",ans%MOD);
	return 0;
}
