#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
const int N=500010,INF=INT_MAX/10;char str[N];int a[N];
namespace subtask12{
	const int N=1010;int dp[N][N];
	inline int brute_force40(int n)
	{
		rep(i,2,n) rep(l,1,n-i+1)
		{
			int r=l+i-1;dp[l][r]=INF;
			rep(j,l,r-1) dp[l][r]=min(dp[l][r],max(dp[l][j],dp[j+1][r])+a[j]);
		}
		return !printf("%d\n",dp[1][n]);
	}
}
namespace cheat_space{
	int pre[N][10],dp[180][N];
	inline int cheat(int n)
	{
		rep(i,1,n) { rep(j,1,9) pre[i][j]=pre[i-1][j];if(i<n) pre[i][a[i]]=i; }
		rep(i,1,n) dp[0][i]=i;
		for(int j=1;;j++)
		{
			rep(i,1,n)
			{
				if(dp[j-1][i]==n) { dp[j][i]=n;continue; } dp[j][i]=i;int k;
				rep(t,1,min(j,9)) k=pre[dp[j-t][i]][t],dp[j][i]=max(dp[j][i],dp[j-t][k+1]);
			}
			if(dp[j][1]==n) return !printf("%d\n",j);
		}
		return 0;
	}
}
int main()
{
	freopen("guess.in","r",stdin),
	freopen("guess.out","w",stdout);
	scanf("%s",str+1);int n=int(strlen(str+1))+1;
	rep(i,1,n-1) a[i]=str[i]-'0';
	if(n<=1001) return subtask12::brute_force40(n);
	return cheat_space::cheat(n);
}
