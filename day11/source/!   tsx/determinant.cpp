#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct pt
{
	int l,r,u,d;
}a[1000005];
int t,n,ans=0,sum=0,f[105][105],vis1[200005],vis2[200005],mod=1e9+7;
int tsum[1000005],st[100005],tp;
int lowbit(int x)
{
	return x&-x;
}
void modify(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))
		tsum[i]+=v;
}
int query(int x)
{
	int tans=0;
	for(int i=x;i;i-=lowbit(i))
		tans+=tsum[i];
	return tans;
}
int getrev(int *b)
{
	int tans=0;
	memset(tsum,0,sizeof(tsum));
	for(int i=n;i>0;i--)
	{
		tans^=(query(b[i])%2);
		modify(b[i],1);
	}
	return tans;
}
int fpow(int x,int y)
{
	int tans=1;
	while(y)
	{
		if(y&1) tans=1ll*tans*x%mod;
		x=1ll*x*x%mod;
		y/=2;
	}
	return tans;
}
void check()
{
	sum++;
	tp=0;
	for(int i=1;i<=n;i++)
	{
		int fl=0;
		for(int j=1;j<=n;j++)
			if(f[i][j])
			{
				fl=1;
				st[++tp]=j;
				break;
			}
		if(!fl) return;
	}
	for(int i=1;i<=n;i++)
	{
		int fl=0;
		for(int j=1;j<=n;j++)
			if(f[j][i])
			{
				fl=1;
				break;
			}
		if(!fl) return;
	}
	/*printf("f=\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",f[i][j]);
		printf("\n");
	}
	printf("st=\n");
	for(int i=1;i<=n;i++)
		printf("%d ",st[i]);*/
	if(getrev(st)) ans=(ans+mod-1)%mod;
	else ans++;
}
void dfs(int dep)
{
	if(dep==n+1)
	{
		check();
		return;
	}
	for(int i=a[dep].d;i<=a[dep].u;i++)
		for(int j=a[dep].l;j<=a[dep].r;j++)
		{
			f[i][j]++;
			dfs(dep+1);
			f[i][j]--;
		}
}
int main()
{
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int fl1=1,fl2=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&a[i].d,&a[i].u,&a[i].l,&a[i].r);
			if(a[i].d!=a[i].u) fl1=0;
			if(a[i].l!=a[i].r) fl2=0;
		}
		if(n<=3)
		{
			memset(f,0,sizeof(f));
			ans=0,sum=0;
			dfs(1);
			ans=1ll*ans*fpow(sum,mod-2)%mod;
			//printf("sum=%d\n",sum);
			printf("%d\n",ans);
			continue;
		}
		if(fl1&&fl2)
		{
			memset(vis1,0,sizeof(vis1));
			memset(vis2,0,sizeof(vis2));
			for(int i=1;i<=n;i++)
			{
				vis1[a[i].d]=a[i].l;
				vis2[a[i].l]++;
			}
			int tfl=1;
			for(int i=1;i<=n;i++)
				if((!vis1[i])||(!vis2[i])) tfl=0;
			if(tfl&&getrev(vis1)) tfl=mod-1;
			printf("%d\n",tfl);
			continue;
		}
	}
	return 0;
}
