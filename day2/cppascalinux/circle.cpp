#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
namespace p1
{
	int e[59][59],vis[59];
	void solve()
	{
		int teg=n*n;
		for(int s=0;s<1<<teg;s++)
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
				{
					int p=(i-1)*n+j;
					e[i][j]=(s>>(p-1))&1;
				}
			int sm=0;
			for(int t=0;t<1<<n;t++)
			{
				int sm1=0,sm2=0;
				for(int i=1;i<=n;i++)
					vis[i]=0;
				for(int i=1;i<=n;i++)
					if((t>>(i-1))&1)
					{
						sm1++;
						for(int j=1;j<=n;j++)
							vis[j]|=e[i][j];
					}
				for(int i=1;i<=n;i++)
					if(vis[i])
						sm2++;
				if(sm1>sm2)
					sm++;
			}
			if(sm==m)
			{
				for(int i=1;i<=n;i++)
				{
					for(int j=1;j<=n;j++)
						printf("%d ",e[i][j]);
					printf("\n");
				}
				return;
			}
		}
		printf("-1");
	}
}
namespace p2
{
	int e[59][59];
	void solve()
	{
		if(m>(1LL<<n)-1)
			return printf("-1"),void();
		int bit=0;
		while(1<<bit<m)
			bit++;
		for(int i=bit+1;i<=n;i++)
			for(int j=2;j<=n;j++)
				e[i][j]=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				printf("%d ",e[i][j]);
			printf("\n");
		}
	}
}
int main()
{
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	scanf("%d%d",&n,&m);
	if(n<=3)
		p1::solve();
	else
		p2::solve();
	return 0;
}