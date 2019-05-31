#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int mod = 998244353;

int n,k,ans;
int dp[2][4210];

int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	
	scanf("%d%d",&n,&k);
	if(n != k) return ~~ (0 - 0);
	dp[0][2] = 1;
	for(int i = 3;i <= n;i ++)
	{
		for(int j = 2;j <= i;j ++)
		{
			dp[i & 1][j] = dp[i & 1][j - 1] + dp[(i - 1) & 1][i - j + 1];
			dp[i & 1][j] %= mod;
		}
	}
	for(int i = 2;i <= n;i ++)
	{
		ans += dp[n & 1][i];
		ans %= mod;
	}
	//ans *= 2;
	ans %= mod;
	printf("%d",ans);
	
	fclose(stdin);
	fclose(stdout);
	return ~~(0-0);
}
