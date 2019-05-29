#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace abc
{
	int n,m,k,w,sum[105][105][105],mod=998244353,vis[105][105][105],val[105][105][105],ans=0,tsum;
	int msum;
	int fpow(int x,int y)
	{
		int ans=1;
		while(y)
		{
			if(y&1) ans=1ll*ans*x%mod;
			x=1ll*x*x%mod;
			y/=2;
		}
		return ans;
	}
	int check(int x,int y,int z,int xx,int yy,int zz)
	{
		return vis[xx][yy][zz]-vis[x-1][yy][zz]-vis[xx][y-1][zz]-vis[xx][yy][z-1]+vis[x-1][y-1][zz]+vis[x-1][yy][z-1]+vis[xx][y-1][z-1]-vis[x-1][y-1][z-1];
	}
	void soe()
	{
		freopen("dream.in","r",stdin);
		freopen("dream.out","w",stdout);
		scanf("%d%d%d%d",&n,&m,&k,&w);
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int z=1;z<=k;z++)
				{
					scanf("%d",&vis[x][y][z]);
					vis[x][y][z]^=1;
					vis[x][y][z]=vis[x][y][z]+vis[x-1][y][z]+vis[x][y-1][z]+vis[x][y][z-1]
								 -vis[x-1][y-1][z]-vis[x][y-1][z-1]-vis[x-1][y][z-1]+vis[x-1][y-1][z-1];
				}
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int z=1;z<=k;z++)
					scanf("%d",&val[x][y][z]);
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int z=1;z<=k;z++)
					for(int xx=x;xx<=n;xx++)
						for(int yy=y;yy<=m;yy++)
							for(int zz=z;zz<=k;zz++)
								if(check(x,y,z,xx,yy,zz)==0)
								{
									sum[x][y][z]++;
									sum[xx+1][y][z]--;
									sum[x][yy+1][z]--;
									sum[x][y][zz+1]--;
									sum[xx+1][yy+1][z]++;
									sum[x][yy+1][zz+1]++;
									sum[xx+1][y][zz+1]++;
									sum[xx+1][yy+1][zz+1]--;
									tsum++;
									//printf("x=%d,%d,y=%d,%d,z=%d,%d\n",x,xx,y,yy,z,zz);
								}
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int z=1;z<=k;z++)
				{
					sum[x][y][z]=sum[x][y][z]+sum[x-1][y][z]+sum[x][y-1][z]+sum[x][y][z-1]
								 -sum[x-1][y-1][z]-sum[x][y-1][z-1]-sum[x-1][y][z-1]+sum[x-1][y-1][z-1];
				}
		msum=n*(n+1)*m*(m+1)*k*(k+1)/8;
		int inv=fpow(msum,mod-2);
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				for(int z=1;z<=k;z++)
				{
					int p=1ll*sum[x][y][z]*inv%mod*fpow(1ll*tsum*inv%mod,w-1)%mod,q=(1ll*tsum*inv%mod-1ll*sum[x][y][z]*inv%mod+mod)%mod;
					int tq=1ll*q*fpow(1ll*tsum*inv%mod,mod-2)%mod;
					int tp=1ll*(1-fpow(tq,w)+mod)*fpow((1-tq+mod)%mod,mod-2)%mod;
					ans=(ans+1ll*tp*p%mod*val[x][y][z]%mod)%mod;
				}
		printf("%d",ans);
	}
}
int main()
{
	abc::soe();
	return 0;
}
