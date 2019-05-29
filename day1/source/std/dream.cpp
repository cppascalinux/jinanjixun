#include<bits/stdc++.h>
#define N 75
#define mod 998244353
using namespace std;
const int inf=1e9+7;
typedef long long ll;
int sta[N],n,m,K,W,a[N][N][N],val[N][N][N],h[N][N],mn[N];
ll dp[8][N][N][N],f[N];
int cal(int n){
	return n*(n+1)/2;
}
int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)ans=1ll*ans*a%mod;
	return ans;
}
ll cal(int x,int y,int z){
	return (dp[0][n][m][K]
			-dp[0][x-1][m][K]-dp[4][x+1][m][K]
			-dp[0][n][y-1][K]-dp[2][n][y+1][K]
			-dp[0][n][m][z-1]-dp[1][n][m][z+1]
			+dp[0][x-1][y-1][K]+dp[2][x-1][y+1][K]+dp[4][x+1][y-1][K]+dp[6][x+1][y+1][K]
			+dp[0][x-1][m][z-1]+dp[1][x-1][m][z+1]+dp[4][x+1][m][z-1]+dp[5][x+1][m][z+1]
			+dp[0][n][y-1][z-1]+dp[1][n][y-1][z+1]+dp[2][n][y+1][z-1]+dp[3][n][y+1][z+1]
			-dp[0][x-1][y-1][z-1]-dp[1][x-1][y-1][z+1]-dp[2][x-1][y+1][z-1]-dp[3][x-1][y+1][z+1]
			-dp[4][x+1][y-1][z-1]-dp[5][x+1][y-1][z+1]-dp[6][x+1][y+1][z-1]-dp[7][x+1][y+1][z+1])%mod;
}
void sol(){
	int tp=0;
	ll sum=0;
	sta[0]=0;
	for(int i=1;i<=K;++i){
		while(tp&&mn[sta[tp]]>mn[i])
			sum-=(sta[tp]-sta[tp-1])*mn[sta[tp]],tp--;
		sta[++tp]=i,sum+=(sta[tp]-sta[tp-1])*mn[i],f[i]=f[i-1]+sum;
	}
}
void revsol(){
	int tp=0;
	ll sum=0;
	sta[0]=K+1;
	for(int i=K;i>=1;--i){
		while(tp&&mn[sta[tp]]>mn[i])
			sum-=(sta[tp-1]-sta[tp])*mn[sta[tp]],tp--;
		sta[++tp]=i,sum+=(sta[tp-1]-sta[tp])*mn[i],f[i]=f[i+1]+sum;
	}
}
namespace Br{

	bool c[20][20][20][20][20][20];
	int all=0;
	void init(){
		for(int i=1;i<=n;++i)
			for(int i2=1;i2<=m;++i2)
				for(int i3=1;i3<=K;++i3)
					for(int i4=i;i4<=n;++i4)
						for(int i5=i2;i5<=m;++i5)
							for(int i6=i3;i6<=K;++i6){
								int flg=1;
								for(int x=i;x<=i4&&flg;++x)
									for(int y=i2;y<=i5&&flg;++y)
										for(int z=i3;z<=i6&&flg;++z)
											flg&=a[x][y][z];
								if(flg)all++;
								c[i][i2][i3][i4][i5][i6]=flg;
							}
								
	}
	int cal(int x,int y,int z){
		int ret=0;
		for(int i=1;i<=x;++i)
			for(int i2=1;i2<=y;++i2)
				for(int i3=1;i3<=z;++i3)
					for(int i4=x;i4<=n;++i4)
						for(int i5=y;i5<=m;++i5)
							for(int i6=z;i6<=K;++i6)
								if(c[i][i2][i3][i4][i5][i6])ret++;
		return ret;
	}
	void main(){
		init();
		int ans=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				for(int k=1;k<=K;++k)
					ans=(ans+1ll*val[i][j][k]*(qpow(all,W)-qpow(all-cal(i,j,k),W)+mod))%mod;
		ans=1ll*qpow(1ll*qpow(::cal(n),mod-2)*qpow(::cal(m),mod-2)%mod*qpow(::cal(K),mod-2)%mod,W)*ans%mod;
		printf("[%d]",ans);
	}
};
void solve(){
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				if(a[i][j][k])h[j][k]++;
				else h[j][k]=0;
		for(int j=1;j<=m;++j){
			for(int k=1;k<=K;++k)mn[k]=inf;
			for(int k=j;k<=m;++k){
				for(int l=1;l<=K;++l)
					mn[l]=min(mn[l],h[k][l]);
				sol();
				for(int l=1;l<=K;++l)
					dp[0][i][k][l]+=f[l];
				revsol();
				for(int l=K;l>=1;--l)
					dp[1][i][k][l]+=f[l];
			}
		}
		for(int j=m;j>=1;--j){
			for(int k=1;k<=K;++k)mn[k]=inf;
			for(int k=j;k>=1;--k){
				for(int l=1;l<=K;++l)
					mn[l]=min(mn[l],h[k][l]);
				sol();
				for(int l=1;l<=K;++l)
					dp[2][i][k][l]+=f[l];
				revsol();
				for(int l=K;l>=1;--l)
					dp[3][i][k][l]+=f[l];
			}
		}
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				dp[0][i][j][k]+=dp[0][i][j-1][k],
				dp[1][i][j][k]+=dp[1][i][j-1][k];
		for(int j=m;j>=1;--j)
			for(int k=1;k<=K;++k)
				dp[2][i][j][k]+=dp[2][i][j+1][k],
				dp[3][i][j][k]+=dp[3][i][j+1][k];
		for(int l=0;l<4;++l)
			for(int j=1;j<=m;++j)
				for(int k=1;k<=K;++k)
					dp[l][i][j][k]+=dp[l][i-1][j][k];
	}
}
int main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
//	freopen("a.out")
	scanf("%d%d%d%d",&n,&m,&K,&W);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				scanf("%d",&a[i][j][k]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				scanf("%d",&val[i][j][k]);
//	Br::main();
	for(int i=1;i<=n-i+1;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				swap(a[i][j][k],a[n-i+1][j][k]);
	solve();
	for(int i=0;i<4;++i)
		for(int j=1;j<=n;++j)
			for(int k=1;k<=m;++k)
				for(int l=1;l<=K;++l)
					dp[i+4][n-j+1][k][l]=dp[i][j][k][l],dp[i][j][k][l]=0;
	for(int i=1;i<=n-i+1;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				swap(a[i][j][k],a[n-i+1][j][k]);
	solve();
	int ans=0;
	int all=dp[0][n][m][K],Z=qpow(all,W);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=K;++k)
				ans=(ans+1ll*val[i][j][k]*(Z-qpow(all-cal(i,j,k),W)+mod))%mod;
	ans=(ans%mod+mod)%mod;
	ans=1ll*qpow(1ll*qpow(cal(n),mod-2)*qpow(cal(m),mod-2)%mod*qpow(cal(K),mod-2)%mod,W)*ans%mod;
	printf("%d\n",ans);
}
