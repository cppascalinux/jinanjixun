#include<cstdio>
#include<vector>
#define re register
#define maxn 10
#define maxm 10
#define mod 1000000007

int n,m,M;
int a[maxn],f[maxn][1<<maxm];

int main(){
	freopen("and.in","r",stdin);
	freopen("and.out","w",stdout);
	scanf("%d%d",&n,&m);
	M=1<<m;
	for(re int i=0;i<n;++i)
		scanf("%d",&a[i]);
	for(re int i=0;i<M;++i)
		f[0][i]=1;
	for(re int i=1;i<n;++i)
		for(re int j=0;j<M;++j)
			for(re int k=0;k<M;++k)
				if((a[i-1]&j)<=(a[i]&k)&&(a[i-1]|j)>=a[i]|k)
					f[i][k]=(f[i][k]+f[i-1][j])%mod;
	re int ans=0;
	for(re int i=0;i<M;++i)
		ans=(ans+f[n-1][i])%mod;
	printf("%d",ans);
	return 0;
}

