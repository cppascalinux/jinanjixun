#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 5111
#define mo 998244353

int read()
{
	int ret=0,neg=1;
	char c=getchar();
	while (c<'0' || c>'9'){
		if (c=='-') neg=-1;
		c=getchar();
	}
	while (c>='0' && c<='9'){
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*neg;
}

int n,k;
int dp[MAXN][MAXN];

int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	n=read();k=read();
	dp[1][1]=1;
	for (int i=2;i<=n;i++) for (int j=1;j<=k;j++){
		dp[i][j]=(1ll*j*dp[i-1][j]%mo+dp[i-1][j-1]+(j>1 ? 1ll*(i-j+1)*dp[i-1][j-2]%mo : 0))%mo;
	}
	printf("%d",dp[n][k]);
}
