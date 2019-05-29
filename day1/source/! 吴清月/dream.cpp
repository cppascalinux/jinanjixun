#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=998244353;
int n,m,l,h[65][65],up[65],cnt2[65][65],cnt[65][65][65],flag[65][65][65];
ll v[65][65][65],f[65][65][65],w,ans,tot,num;
ll quick_pow(ll x,ll a)
{
	ll ans=1;
	while(a)
	{
		if(a&1)ans=ans*x%MOD;
		x=x*x%MOD;
		a>>=1;
	}
	return ans;
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d%d%d%lld",&n,&m,&l,&w);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    for(int k=1;k<=l;k++)
	      scanf("%d",&flag[i][j][k]);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    for(int k=1;k<=l;k++)
	      scanf("%lld",&v[i][j][k]);
	for(int i=1;i<=n;i++)
	{
		for(int x=1;x<=m;x++)
		for(int y=1;y<=l;y++)
		{
			if(flag[i][x][y]==0)h[x][y]=0;
			else h[x][y]++;
		}
		memset(cnt,0,sizeof(cnt));
		for(int d=i;d>=1;d--)
		{
			for(int x=1;x<=m;x++)
			{
				for(int y=1;y<=l;y++)
				{
					cnt[d][x][y]+=cnt[d+1][x][y];
					if(h[x][y]<d)up[y]=0;
					else up[y]++;
				}
				for(int y=1;y<=l;y++)cnt2[x+1][y]=0;
				for(int hh=x;hh>=1;hh--)
				{
					int nowl=0,nowr=0;
					for(int y=1;y<=l;y++)
					{
						cnt2[hh][y]=cnt2[hh+1][y];
						if(up[y]<hh)continue;
						if(y>nowr)
						{
							nowl=nowr=y;
							while(nowr<=l&&up[nowr]>=hh)nowr++;
							num+=(nowr-nowl)*(nowr-nowl+1)/2;
							nowr--;
						}
						cnt2[hh][y]+=(y-nowl+1)*(nowr-y+1);
						cnt[d][x-hh+1][y]+=cnt2[hh][y];
					}
				}
			}
			for(int x=1;x<=m;x++)
			  for(int y=1;y<=l;y++)
				f[i-d+1][x][y]+=cnt[d][x][y];
		}
	}
	tot=quick_pow(8,MOD-2)*n*(n+1)%MOD*m*(m+1)%MOD*l*(l+1)%MOD;
	ll inv=quick_pow(tot,MOD-2);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    for(int k=1;k<=l;k++)
	      ans+=v[i][j][k]*(quick_pow(inv*num%MOD,w)%MOD-quick_pow((num-f[i][j][k])%MOD*inv%MOD,w))%MOD;
	ans%=MOD;
	if(ans<0)ans+=MOD;
	printf("%lld\n",ans);
	return 0;
}
