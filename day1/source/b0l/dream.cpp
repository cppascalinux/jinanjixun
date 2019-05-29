#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const ll mod=998244353;
int n,m,h;
ll w;
ll ans,S;
ll a[63][63][63],sum[63][63][63],b[63][63][63],sumb[63][63][63];
int l[63],r[63];
ll fpow(ll x,int b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*x%mod;
		x=x*x%mod;
		b>>=1;
	}
	return res;
}
void add(ll &x,ll y)
{
	x+=y;
	if(x>=mod) x-=mod;
}
void dec(ll &x,ll y)
{
	x-=y;
	if(x<0) x+=mod;
}
void build(int x,int y,int z)
{
	add(sum[x][y][z],sum[x-1][y][z]);
	add(sum[x][y][z],sum[x][y-1][z]);
	dec(sum[x][y][z],sum[x-1][y-1][z]);
	add(sum[x][y][z],a[x][y][z]);
	sumb[x][y][z]=sumb[x-1][y][z]+sumb[x][y-1][z]-sumb[x-1][y-1][z]+b[x][y][z];
}
ll query(int x,int xx,int y,int yy,int z)
{
	ll res=sum[xx][yy][z];
	dec(res,sum[x-1][yy][z]);
	dec(res,sum[xx][y-1][z]);
	add(res,sum[x-1][y-1][z]);
	return res;
}
ll queryb(int x,int xx,int y,int yy,int z)
{
	return sumb[xx][yy][z]-sumb[x-1][yy][z]-sumb[xx][y-1][z]+sumb[x-1][y-1][z];
}
void work(int x,int xx,int y,int yy)
{
	l[0]=r[h+1]=0;
	for(int i=1;i<=h;i++)
	{
		if(queryb(x,xx,y,yy,i)==(xx-x+1)*(yy-y+1)) l[i]=l[i-1]+1;
		else l[i]=0;
	}
	for(int i=h;i;i--)
	{
		if(queryb(x,xx,y,yy,i)==(xx-x+1)*(yy-y+1)) r[i]=r[i+1]+1;
		else r[i]=0;
		add(ans,query(x,xx,y,yy,i)*w%mod*l[i]*r[i]%mod);
	}
}
void solve()
{
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			for(int k=1;k<=m;k++)
				for(int l=k;l<=m;l++)
					work(i,j,k,l);
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d%d%d%lld",&n,&m,&h,&w);
	w%=mod;
	S=n*(n+1)*m*(m+1)*h*(h+1)/8;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
				scanf("%lld",&b[i][j][k]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
			{	
				scanf("%lld",&a[i][j][k]);
				a[i][j][k]%=mod;
			}
	for(int k=1;k<=h;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				build(i,j,k);
	solve();
	printf("%lld",ans*fpow(S,mod-2)%mod*fpow(w,mod-2)%mod);
	fclose(stdin);
	fclose(stdout);
	return 0;			
}
