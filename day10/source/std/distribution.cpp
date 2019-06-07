#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
// head

int _,T;
double dp[110][110],x,prob[110],p,coef[110];
int main() {
	freopen("distribution.in","r",stdin);
	freopen("distribution.out","w",stdout);
	scanf("%d",&_);
	scanf("%lf",&p);
	dp[0][0]=1;
	rep(i,0,100) rep(j,0,i+1) dp[i+1][j+1]+=dp[i][j]*p,dp[i+1][j]+=dp[i][j]*(1-p);
	rep(i,1,101) rep(j,0,i+1) dp[i][j]=log(dp[i][j]);
	rep(n,1,101) coef[n]=0.5*log(n*p*(1-p));
	for (;_;_--) {
		scanf("%d",&T);
		rep(n,1,101) prob[n]=0;
		rep(i,0,T) {
			scanf("%lf",&x);
			rep(n,1,101) {
				int rr=floor(x*sqrt(n*p*(1-p))+n*p+0.5);
				if (rr<0||rr>n) prob[n]+=-1e9; else prob[n]+=dp[n][rr]+coef[n];
			}
		}
		printf("%d\n",max_element(prob+1,prob+101)-prob);
	}
}
