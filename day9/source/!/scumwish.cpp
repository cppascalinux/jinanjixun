#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=1e8+7;
int n,m;
bool a[25][25],b[25][25];
ll f[25][1<<20],g[1<<20];
int main()
{
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<m;j++)
	{
		int x;
		scanf("%d",&x);
		a[i][j]=x;
	}
	for(int i=1;i<n;i++)
	for(int j=1;j<=m;j++)
	{
		int x;
		scanf("%d",&x);
		b[i][j]=x;
	}
	g[(1<<m)-1]=1;
	bool a1,a2,b1;
	ll v1,v2,*ff,t1,t2;
	register int i,j,s;
	for(i=1;i<=n;++i)
	{
		ff=f[1];
		a1=a[i-1][1],b1=b[i-1][1];
//		printf("i=%d:",i-1);
		for(s=0;s<(1<<m);++s)
		{
//			print(s);
//			printf("%lld ",g[s]);
			v1=g[s];
			if(v1==0)continue;
			if(s&1)
			{
				ff[s^1]+=v1;
				ff[s]+=v1;
			}
			if(!(s&1)&&b1)ff[s^1]+=v1;
			if(!(s&1)&&!(s&2)&&b1&&a1)ff[s|3]+=v1;
		}
		if(1<m)
		{
			a1=a[i][1],a2=a[i-1][2];
			b1=b[i-1][2];
			ff=f[2];
			for(s=0;s<(1<<m);s+=2)
			{
				v1=f[1][s],v2=f[1][s|1];
				f[1][s]=f[1][s|1]=0;
				if(v1==0&&v2==0)continue;
				if(s&2)
				{
					ff[s^2]+=v1;
					ff[(s|1)^2]+=v2;
					ff[s]+=v1;
					ff[s|1]+=v2;
					if(!(s&1)&&a1)ff[s|1]+=v1;
				}
				else
				{
					if(b1)
					{
						ff[s|2]+=v1;
						ff[s|3]+=v2;
					}
					if(b1&&a1)ff[s|3]+=v1;
					if(1!=m-1&&b1&&a2&&!(s&4))
					{
						ff[s|6]+=v1;
						ff[s|7]+=v2;
					}
				}
			}
		}
//		printf("\n");
		for(j=2;j<m;++j)
		{
			a1=a[i][j],a2=a[i-1][j+1];
			b1=b[i-1][j+1];
			ff=f[j+1];
			t1=1<<j,t2=1<<(j-1);
			for(s=0;s<(1<<m);s+=2)
			{
				v1=f[j][s],v2=f[j][s|1];
				f[j][s]=f[j][s|1]=0;
				if(v1==0&&v2==0)continue;
				if(s&t1)
				{
					ff[s^t1]+=v1;
					ff[(s|1)^t1]+=v2;
					ff[s]+=v1;
					ff[s|1]+=v2;
					if(!(s&t2)&&a1)
					{
						ff[s|t2]+=v1;
						ff[(s^1)|t2]+=v2;
					}
				}
				else
				{
					if(b1)
					{
						ff[s|t1]+=v1;
						ff[(s|1)|t1]+=v2;
					}
					if(b1&&a1&&!(s&t2))
					{
						ff[s|t2|t1]+=v1;
						ff[s|1|t2|t1]+=v2;
					}
					if(j!=m-1&&b1&&a2&&!(s&(1<<(j+1))))
					{
						ff[s|t1|(1<<(j+1))]+=v1;
						ff[s|1|t1|(1<<(j+1))]+=v2;
					}
				}
			}
		}
		for(s=0;s<(1<<m);++s)
		  g[s]=f[m][s]%MOD,f[m][s]=0;
	}
//	printf("i=%d:",n);
//	for(int s=0;s<(1<<m);s++)
//	{
//		print(s);
//		printf("%lld ",g[s]);
//	}
//	printf("\n");
	printf("%lld\n",g[(1<<m)-1]);
	return 0;
}
