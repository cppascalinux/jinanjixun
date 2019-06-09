#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;
int n,m,h[1005][1005],tt,g[1005][1005];
ll len,c[1005][1005],a[100005],tans[1000005];
double f[1005][1005];
ll getans(int l,int r)
{
	int mid=(l+r)/2;
	ll ans=0;
	for(int i=l;i<=r;i++)
		ans=ans+(a[i]-a[mid]>0?a[i]-a[mid]:a[mid]-a[i]);
	return ans;
}
int check(double x,int fl=0)
{
	for(int i=1;i<=n;i++)
		for(int l=1;l<=2*n-i+1;l++)
		{
			int r=l+i-1;
			f[l][r]=c[l][r];
			g[l][r]=l-1;
			h[l][r]=0;
			for(int k=l;k<r;k++)
			{
				if(f[l][r]>f[l][k]+c[k+1][r]+x)
				{
					f[l][r]=f[l][k]+c[k+1][r]+x;
					g[l][r]=k;
					h[l][r]=h[l][k]+1;
				}
			}
		}
	double ans=1e18;
	int ansid;
	for(int i=1;i<=n;i++)
	{
		if(ans>f[i][i+n-1])
		{
			ans=f[i][i+n-1];
			ansid=i;
		}
	}
	if(fl==1)
	{
		printf("%lld\n",(ll)(ans-h[ansid][ansid+n-1]*x+0.5));
		int nwl=ansid,nwr=nwl+n-1;
		tt=0;
		while(nwl<=nwr)
		{
			int tnwr=g[nwl][nwr];
			tans[++tt]=(tnwr+1+nwr)/2;
			nwr=tnwr;
		}
		sort(tans+1,tans+tt+1);
		for(int i=1;i<=tt;i++)
			printf("%lld ",a[tans[i]]%len);
		//printf("\n");
	}
	//printf("h=%d\n",h[ansid][ansid+n-1]);
	return h[ansid][ansid+n-1]+1;
}
int main()
{
	freopen("post.in","r",stdin);
	freopen("post.out","w",stdout);
	scanf("%d%d%lld",&n,&m,&len);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		a[i+n]=a[i]+len;
	}
	for(int i=1;i<=2*n;i++)
		for(int j=i;j<=2*n;j++)
		{
			c[i][j]=getans(i,j);
			//printf("i=%d,j=%d,c=%d\n",i,j,c[i][j]);
		}
	double l=0,r=1e14;
	double mid;
	while(fabs(r-l)>1e-2)
	{
		//printf("l=%.8lf,r=%.8lf\n",l,r);
		mid=(l+r)/2;
		if(check(mid)>m) l=mid;
		else r=mid;
	}
	check(mid,1);
	return 0;
}
