#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=1000000007;
int b[15],f[32][270101][11][2];
void add(int &x,int y)
{
	x+=y;
	if(x>=INF)
		x-=INF;
}
int main()
{
	int n,m,j,i,k,l,w0,w1,nj,x,ans=0;
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&b[i]);
	f[m+1][0][n][0]=1;
	for(i=m;i>=1;i--)
	{
		for(j=0;j<(1<<n+n-2);j++)
			f[i][j][1][0]=(f[i+1][j][n][0]+f[i+1][j][n][1])%INF,f[i][j][1][1]=(f[i+1][j][n][0]+f[i+1][j][n][1])%INF;
				
		for(k=1;k<n;k++)
		{
			for(j=0;j<(1<<n+n-2);j++)
			{
				for(l=0;l<=1;l++)
				{
					if(!f[i][j][k][l])
						continue;
					for(x=0;x<=1;x++)
					{
						nj=j;
						w0=l&((b[k]>>i-1)&1);
						w1=x&((b[k+1]>>i-1)&1);
						if((1<<k-1)&j);
						else if(w0>w1)
							continue;
						else if(w0<w1)
							nj+=(1<<k-1);
						w0=l|((b[k]>>i-1)&1);
						w1=x|((b[k+1]>>i-1)&1);
						if((1<<k-1+n-1)&j);
						else if(w0<w1)
							continue;
						else if(w0>w1)
							nj+=(1<<k-1+n-1);
						add(f[i][nj][k+1][x],f[i][j][k][l]);
					}
				}
			}
		}
	}
	for(j=0;j<(1<<n+n-2);j++)
		for(l=0;l<=1;l++)
			add(ans,f[1][j][n][l]);
	printf("%d\n",ans);
	return 0;
}

