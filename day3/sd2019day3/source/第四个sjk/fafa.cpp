#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int INF=998244353;
int f[5050][5050];
int main()
{
	int n,k,i,j;
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%d%d",&n,&k);
	f[1][1]=1;
	for(i=1;i<=n;i++)
	{
		f[i][1]=1;
		for(j=2;j<=i;j++)
		{
			f[i][j]=((long long)j*f[i-1][j]+f[i-1][j-1]+(long long)(i-j+1)*f[i-1][j-2])%INF;
		}
	}
	printf("%d\n",f[n][k]);
	//freopen(".in","r",stdin);
	//froepen(".out","w",stdout);
	return 0;
}

