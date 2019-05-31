#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=11;
int n,K,ans,h[N],dp[N][N];
inline int my_max(int a, int b){ return a & ((b - a) >> 30) | b & ( ~ (b - a) >> 30) ; }
int main()
{
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	cin>>n>>K;
	for(int i=1;i<=n;++i)h[i]=i;
	do{
		memset(dp,0,sizeof dp);
		dp[1][1]=1;  int mx=-1;
		for(int i=2;i<=n;++i){
			for(int j=1;j<i;++j){
				if(h[j]>h[i])dp[i][0]=my_max(dp[j][1]+1,dp[i][0]);
				if(h[j]<h[i])dp[i][1]=my_max(dp[j][0]+1,dp[i][1]);
			}
			mx=my_max(mx,my_max(dp[i][1],dp[i][0]));
		}
		ans+=mx==K;
	}while(next_permutation(h+1,h+n+1));
	cout<<ans<<endl;
	fcloes(stdin); fclose(stdout);
	return 0;
}
