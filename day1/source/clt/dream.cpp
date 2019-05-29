#include<cstdio>
#define re register
#define maxn 60
#define mod 998244353
#define sum(x1,y1,z1,x2,y2,z2) (a[x2][y2][z2]-a[x1-1][y2][z2]-a[x2][y1-1][z2]-a[x2][y2][z1-1]+a[x1-1][y1-1][z2]+a[x1-1][y2][z1-1]+a[x2][y1-1][z1-1]-a[x1-1][y1-1][z1-1])
#define min(a,b) ((a)<=(b)?(a):(b))

int n,m,c,t,size,tot,ans;
int a[maxn+1][maxn+1][maxn+1],w[maxn+1][maxn+1][maxn+1];
int x[maxn+1][maxn+1],y[maxn+2],p[maxn+1],q[maxn+1],r[maxn+1];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;x=1LL*x*x%mod,y>>=1)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

int main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&c,&t);
	size=1LL*n*(n+1)*m*(m+1)*c*(c+1)/8%mod;
	t%=mod-1;
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k)
				scanf("%d",&a[i][j][k]);
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k)
				x[j][k]=a[i][j][k]*(x[j][k]+1);
		for(re int j1=1;j1<=m;++j1){
			for(re int k=1;k<=c;++k)
				y[k]=mod;
			for(re int j2=j1;j2<=m;++j2){
				for(re int k=1;k<=c;++k)
					y[k]=min(y[k],x[j2][k]);
				for(re int top=0,k=1;k<=c+1;++k){
					re int tmp=0;
					for(;top&&p[top]>=y[k];--top)
						tmp+=q[top],tot=(tot+1LL*p[top]*q[top]*(k-r[top])%mod)%mod;
					p[++top]=y[k];
					q[top]=tmp+1;
					r[top]=k;
				}
			}
		}
	}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k)
				a[i][j][k]+=a[i][j][k-1];
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k)
				a[i][j][k]+=a[i][j-1][k];
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k)
				a[i][j][k]+=a[i-1][j][k];
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			for(re int k=1;k<=c;++k){
				scanf("%d",&w[i][j][k]);
				w[i][j][k]%=mod;
				re int cnt=0;
				for(re int i1=i;i1>=1&&sum(i1,j,k,i,j,k)==(i-i1+1)*(j-j+1)*(k-k+1);--i1)
				for(re int j1=j;j1>=1&&sum(i1,j1,k,i,j,k)==(i-i1+1)*(j-j1+1)*(k-k+1);--j1)
				for(re int k1=k;k1>=1&&sum(i1,j1,k1,i,j,k)==(i-i1+1)*(j-j1+1)*(k-k1+1);--k1)
				for(re int i2=i;i2<=n&&sum(i1,j1,k1,i2,j,k)==(i2-i1+1)*(j-j1+1)*(k-k1+1);++i2)
				for(re int j2=j;j2<=m&&sum(i1,j1,k1,i2,j2,k)==(i2-i1+1)*(j2-j1+1)*(k-k1+1);++j2)
				for(re int k2=k;k2<=c&&sum(i1,j1,k1,i2,j2,k2)==(i2-i1+1)*(j2-j1+1)*(k2-k1+1);++k2)
					cnt=(cnt+1)%mod;
				cnt=(cltpow(tot,t)-cltpow(tot-cnt+mod,t)+mod)%mod;
				ans=(ans+1LL*cnt*w[i][j][k]%mod)%mod;
			}
	printf("%lld",1LL*cltpow(size,mod-t-1)*ans%mod);
	return 0;
}

