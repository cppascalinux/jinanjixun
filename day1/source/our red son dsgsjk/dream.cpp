#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=998244353;
int a[11][11][11],w[11][11][11],sum[11][11][11],sum2[11][11][11];
int ksm(int w,int x)
{
	int ans=1;
	while(x)
	{
		if(x&1)
			ans=(long long)ans*w%INF;
		x>>=1;
		w=(long long)w*w%INF;
	}
	return ans;
}
int calc1(int x,int y,int z,int xx,int yy,int zz)
{
	int ans=0,s1,s2,tmp,i;
	for(i=x;i<=xx;i++)
	{
		s1=(sum[i][yy][zz]+sum[i][y-1][z-1])%INF;
		s2=(sum[i][yy][z-1]+sum[i][y-1][zz])%INF;
		tmp=(s1-s2+INF)%INF;
		ans=(ans+tmp)%INF;
	}
	return ans;
}
int calc2(int x,int y,int z,int xx,int yy,int zz)
{
	int ans=0,s1,s2,tmp,i;
	for(i=x;i<=xx;i++)
	{
		s1=(sum2[i][yy][zz]+sum2[i][y-1][z-1])%INF;
		s2=(sum2[i][yy][z-1]+sum2[i][y-1][zz])%INF;
		tmp=(s1-s2+INF)%INF;
		ans=(ans+tmp)%INF;
	}
	return ans;
}
int main()
{
	int n,m,l,i,j,k,x,y,z,ans=0,ca,summ;
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&l,&ca);
	if(ca==1)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				for(k=1;k<=l;k++)
				{
					scanf("%d",&a[i][j][k]);
					a[i][j][k]^=1;
				}
			for(j=1;j<=m;j++)
				for(k=1;k<=l;k++)
				{
					sum2[i][j][k]=(sum2[i][j-1][k]+sum2[i][j][k-1]);
					sum2[i][j][k]=(sum2[i][j][k]-sum2[i][j-1][k-1]);
					sum2[i][j][k]=(sum2[i][j][k]+a[i][j][k]);
				}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				for(k=1;k<=l;k++)
					scanf("%d",&w[i][j][k]);
			for(j=1;j<=m;j++)
				for(k=1;k<=l;k++)
				{
					sum[i][j][k]=(sum[i][j-1][k]+sum[i][j][k-1])%INF;
					sum[i][j][k]=(sum[i][j][k]-sum[i][j-1][k-1]+INF)%INF;
					sum[i][j][k]=(sum[i][j][k]+w[i][j][k])%INF;
				}
		}
		summ=0;
		for(i=1;i<=n;i++)
			for(x=i;x<=n;x++)
				for(j=1;j<=m;j++)
					for(y=j;y<=m;y++)
						for(k=1;k<=l;k++)
							for(z=k;z<=l;z++)
							{
								summ++;
								if(calc2(i,j,k,x,y,z)==0)
								{
//								printf("%d %d %d %d %d %d %d\n",i,j,k,x,y,z,ans);
									ans=(ans+calc1(i,j,k,x,y,z))%INF;
								}
							}
//		printf("%d\n",summ);
		ans=(long long)ans*ksm(summ,INF-2)%INF;
		printf("%d\n",ans);
	}
	return 0;
}

