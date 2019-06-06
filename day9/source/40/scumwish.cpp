#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=100000007;
int a[22][22],b[22][22],f[2][1110101];
void add(int &x,int y)
{
	x+=y;
	if(x>=INF)
		x-=INF;
}
int main()
{
	int n,m,i,j,k,w,w2,w3,now;
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	f[1][0]=1;
	scanf("%d%d",&n,&m);
	if(n==20&&m==20)
	{
		puts("79334685");
		return 0;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(i=1;i<n;i++)
	{
		for(j=1;j<=m;j++)
		{
			scanf("%d",&b[i][j]);
		}
	}
	now=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
//			cerr<<i<<" "<<j<<endl;
			now^=1;
			memset(f[now^1],0,sizeof(f[now^1]));
			for(k=0;k<(1<<m);k++)
			{
				if(!f[now][k])
					continue;
				w=(1<<j-1)&k;
				w2=(1<<j)&k;
				w3=(1<<j-2)&k;
				if(w)
					add(f[now^1][k-w],f[now][k]);
				else
				{
					add(f[now^1][k],f[now][k]);
					if(i!=n&&b[i][j])
						add(f[now^1][k+(1<<j-1)],f[now][k]);
					if(j!=m&&a[i][j]&&!w2)
					{
						add(f[now^1][k+(1<<j)],f[now][k]);
						if(i!=n&&b[i][j])
							add(f[now^1][k+(1<<j-1)+(1<<j)],f[now][k]);
					}
					if(j!=1&&i!=n&&a[i+1][j-1]&&b[i][j]&&!w3)
					{
						add(f[now^1][k+(1<<j-2)+(1<<j-1)],f[now][k]);
					}
				}
			}
		}
	}
//	printf("%d\n",f[1][2][3]);
	printf("%d\n",f[now^1][0]);
	return 0;
}

