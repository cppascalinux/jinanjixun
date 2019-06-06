#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define mod 100000007
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
inline int inn() { int x;scanf("%d",&x);return x; }
const int N=21,MXS=(1<<20)+5;
int l[N][N],d[N][N];lint dp[2][2][MXS];
#define upd(x,y) x+=y
int main()
{
	freopen("scumwish.in","r",stdin);
	freopen("scumwish.out","w",stdout);
	int n=inn(),m=inn(),all=(1<<m)-1;
	rep(i,1,n) rep(j,1,m-1) l[i][j]=!inn();
	rep(i,1,n-1) rep(j,0,m-1) d[i][j]=!inn();
	dp[1][0][all]=1;
	rep(i,1,n)
	{
		rep(j,0,m-1)
		{
			lint *now=dp[i&1][j&1],*nxt=dp[i&1][(j+1)&1];
			memset(nxt,0,sizeof(lint)*(all+1));
			rep(s,0,all) if(now[s])
			{
				int x=(j>0?((s>>(j-1))&1):1),y=(s>>j)&1,z=(s>>(j+1))&1;lint val=now[s];
				if(j<=m-2&&!y&&!z&&!d[i-1][j]&&!l[i-1][j+1]) upd(nxt[s|(1<<j)|(1<<(j+1))],val);
				if(j>0&&!x&&!y&&!l[i][j]&&!d[i-1][j]) upd(nxt[s|(1<<(j-1))|(1<<j)],val);
				if(!y&&!d[i-1][j]) upd(nxt[s|(1<<j)],val);
				if(j>0&&!x&&y&&!l[i][j]) upd(nxt[s|(1<<(j-1))|(1<<j)],val);
				if(y) upd(nxt[s|(1<<j)],val);if(y) upd(nxt[s^(1<<j)],val);
			}
		}
		rep(s,0,all) dp[i&1][m&1][s]%=mod;
		if(i<n)
		{
			lint *now=dp[i&1][m&1],*nxt=dp[(i+1)&1][0];
			memcpy(nxt,now,sizeof(lint)*(all+1));
		}
	}
	return !printf("%lld\n",dp[n&1][m&1][all]);
}
