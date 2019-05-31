#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//int dp[11][2];
//int p[11];
//int n,k;
//bool book[11];
//int ans=0;
//void check()
//{
//	int x=0;
//	for(int i=1;i<=n;i++)
//	{
//		dp[i][1]=1;
//		dp[i][0]=-1e9;
//		for(int j=1;j<i;j++)
//			if(p[j]<p[i])dp[i][1]=max(dp[i][1],dp[j][0]+1);
//			else dp[i][0]=max(dp[i][0],dp[j][1]+1);
//		x=max(x,max(dp[i][0],dp[i][1]));
//	}
//	ans+=(x==k);
//	return ;
//}
//void dfs(int x)
//{
//	if(x==n+1)
//	{
//		check();
//		return ;
//	}
//	for(p[x]=1;p[x]<=n;p[x]++)
//		if(!book[p[x]])
//		{
//			book[p[x]]=true;
//			dfs(x+1);
//			book[p[x]]=false;
//		}
//	return ;
//}
int ans[10][10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 0, 0, 0, 0, 0, 0, 0, 1, 7, 11, 5, 0, 0, 0, 0, 0, 0, 1, 15, 43, 45, 16, 0, 0, 0, 0, 0, 1, 31, 148, 268, 211, 61, 0, 0, 0, 0, 1, 63, 480, 1344, 1767, 1113, 272, 0, 0, 0, 1, 127, 1509, 6171, 12099, 12477, 6551, 1385, 0, 0, 1, 255, 4661, 26955, 74211, 111645, 94631, 42585, 7936, 0, 1, 511, 14246, 114266, 425976, 878856, 1070906, 770246, 303271, 50521};
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	int n,k;
	scanf("%d %d",&n,&k);
	if(k==0)puts("0");
	else printf("%d\n",ans[n-1][k-1]);
	fclose(stdin);fclose(stdout);
	return 0;
}
