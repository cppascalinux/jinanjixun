#include <cstdio>
#define rep(i,a,n) for (int i=a;i<n;i++)
typedef long long ll;
int n,mod,_;
ll dp[110][10100],binom[110][110],inv[10100];
int main() {
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
	scanf("%d%d",&n,&mod);
	inv[1]=1;
	for (int i=2;i<=n*n;i++) inv[i]=(mod-inv[mod%i]*(mod/i))%mod;
	rep(i,0,n+1) {
		binom[i][0]=binom[i][i]=1;
		rep(j,1,i) binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%mod;
	}
	rep(i,1,n+1) rep(j,0,n*n+1) dp[i][j]=0;
	rep(i,2,n+1) rep(j,1,i) {
		ll p=binom[i-1][j-1];
		rep(k,0,j*j+1) dp[i][k+(i-j)*(i-j)]=(dp[i][k+(i-j)*(i-j)]-p*dp[j][k])%mod;
		dp[i][j*j+(i-j)*(i-j)]=(dp[i][j*j+(i-j)*(i-j)]+p)%mod;
	}
	ll ans=0;
	rep(j,1,n*n) ans=(ans+dp[n][j]*n*n%mod*inv[n*n-j])%mod;
	if (ans<0) ans+=mod;
	printf("%d\n",(int)ans);
}
