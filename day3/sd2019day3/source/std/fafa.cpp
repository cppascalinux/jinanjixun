#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,maxn=1e6+10;
int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)ans=1ll*ans*a%mod;
	return ans;
}
long long n;
int K,f[maxn],pw2[maxn],inv[maxn],cns[maxn];
int cal(int K){
	int ans=0;
	if(K<=0)return 0;
	for(int i=1;i<=K;++i){
		f[i]=0;
		if(i==1){
			for(int s=0;s<=K;++s)
				f[i]=(f[i]+1ll*pw2[s]*cns[s]%mod*(K-s))%mod;
		} else if(i==2){
			for(int s=0;s<=K;++s)
				f[i]=(f[i]+1ll*pw2[s]*cns[s]%mod*(1ll*(K-s)*(K-s-1)/2%mod))%mod;
		} else {
			f[i]=(1ll*(2*n-K+mod)%mod*f[i-1]+1ll*(-i+2+K)*f[i-2])%mod*inv[i]%mod;
			f[i]=(mod-f[i])%mod;
		}
	}
	for(int r=1;r<=K;++r)if((K+r)%2==0)
		ans=(ans+1ll*qpow(r,n%(mod-1))*f[(K+r)/2])%mod;
	ans=1ll*ans*qpow((mod+1)/2,K-1)%mod;
	return ans;
}
int main(){
	freopen("fafa.in","r",stdin);
	freopen("fafa.out","w",stdout);
	scanf("%lld%d",&n,&K);
	int ans=0;
	cns[0]=inv[0]=pw2[0]=1;
	for(int i=1;i<=K;++i)pw2[i]=1ll*(mod-2)*pw2[i-1]%mod;
	for(int i=1;i<=K;++i)inv[i]=(i==1?1:1ll*(mod-mod/i)*inv[mod%i]%mod);
	for(int i=1;i<=K;++i)cns[i]=1ll*(n-i+1)%mod*cns[i-1]%mod*inv[i]%mod;
	printf("%d",(cal(K)-cal(K-1)+mod)%mod);
}
