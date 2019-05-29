#include<bits/stdc++.h>
#define ll long long
#define mk make_pair
#define pb push_back
#define pa pair<int,int>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<"\n"
#define fir first
#define sec second
#define SZ(x) (x).size()
using namespace std;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
const int mod=998244353;
int a[11][11][11],w[11][11][11],sum[11][11][11],sum2[11][11][11];
int n,m,l,i,j,k,x,y,z,ans=0,ca,summ;
inline ll ksm(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int calc1(int x,int y,int z,int xx,int yy,int zz) {
	int ans=0,s1,s2,tmp,i;
	for(i=x; i<=xx; i++) {
		s1=(sum[i][yy][zz]+sum[i][y-1][z-1])%mod;
		s2=(sum[i][yy][z-1]+sum[i][y-1][zz])%mod;
		tmp=(s1-s2+mod)%mod;
		ans=(ans+tmp)%mod;
	}
	return ans;
}
int calc2(int x,int y,int z,int xx,int yy,int zz) {
	int ans=0,s1,s2,tmp,i;
	for(i=x; i<=xx; i++) {
		s1=(sum2[i][yy][zz]+sum2[i][y-1][z-1])%mod;
		s2=(sum2[i][yy][z-1]+sum2[i][y-1][zz])%mod;
		tmp=(s1-s2+mod)%mod;
		ans=(ans+tmp)%mod;
	}
	return ans;
}
int main() {
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	n=read(),m=read(),l=read(),ca=read();
	if(ca==1) {
		for(i=1; i<=n; i++) {
			for(j=1; j<=m; j++)
				for(k=1; k<=l; k++) {
					scanf("%d",&a[i][j][k]);
					a[i][j][k]^=1;
				}
			for(j=1; j<=m; j++)
				for(k=1; k<=l; k++) {
					sum2[i][j][k]=(sum2[i][j-1][k]+sum2[i][j][k-1]);
					sum2[i][j][k]=(sum2[i][j][k]-sum2[i][j-1][k-1]);
					sum2[i][j][k]=(sum2[i][j][k]+a[i][j][k]);
				}
		}
		for(i=1; i<=n; i++) {
			for(j=1; j<=m; j++)
				for(k=1; k<=l; k++)
					scanf("%d",&w[i][j][k]);
			for(j=1; j<=m; j++)
				for(k=1; k<=l; k++) {
					sum[i][j][k]=(sum[i][j-1][k]+sum[i][j][k-1])%mod;
					sum[i][j][k]=(sum[i][j][k]-sum[i][j-1][k-1]+mod)%mod;
					sum[i][j][k]=(sum[i][j][k]+w[i][j][k])%mod;
				}
		}
		summ=0;
		for(i=1; i<=n; i++)
			for(x=i; x<=n; x++)
				for(j=1; j<=m; j++)
					for(y=j; y<=m; y++)
						for(k=1; k<=l; k++)
							for(z=k; z<=l; z++) {
								summ++;
								if(calc2(i,j,k,x,y,z)==0) {
									ans=(ans+calc1(i,j,k,x,y,z))%mod;
								}
							}
		ans=(long long)ans*ksm(summ,mod-2)%mod;
		printf("%d\n",ans);
	}
	return 0;
}

