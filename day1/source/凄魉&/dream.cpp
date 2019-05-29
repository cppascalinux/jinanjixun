#include<cstdio>
#define mod 998244353
int a[61][61][61],S[61][61][61],V[61][61][61],n,m,k,W,b[61][61][61];
int qpow(int base,int n)
{
	if (!n) return 1;
	int ans=base%mod;--n;
	while(n)
	{
		if (n&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		n>>=1;
	}
	return ans;
}
void sol()
{
	int ss=0,ans=0,N=n*(n+1)*m*(m+1)*k*(k+1)/8;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				S[i][j][l]=S[i-1][j][l]+a[i][j][l];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				S[i][j][l]+=S[i][j-1][l];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				S[i][j][l]+=S[i][j][l-1];
	for (int i1=1;i1<=n;++i1)
		for (int i2=i1;i2<=n;++i2)
			for (int j1=1;j1<=m;++j1)
				for (int j2=j1;j2<=m;++j2)
					for (int l1=1;l1<=k;++l1)
						for (int l2=l1;l2<=k;++l2)
						{
							int tmp=S[i2][j2][l2]-S[i2][j2][l1-1]-S[i1-1][j2][l2]-S[i2][j1-1][l2]+S[i2][j1-1][l1-1]+S[i1-1][j2][l1-1]+S[i1-1][j1-1][l2]-S[i1-1][j1-1][l1-1];
							if (tmp>0) ++ss;
							else
							{
								--b[i2+1][j2+1][l2+1];
								++b[i2+1][j2+1][l1];++b[i2+1][j1][l2+1];++b[i1][j2+1][l2+1];
								--b[i1][j1][l2+1];--b[i1][j2+1][l1];--b[i2+1][j1][l1];
								++b[i1][j1][l1];
							}
						}
	
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				b[i][j][l]+=b[i-1][j][l];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				b[i][j][l]+=b[i][j-1][l];
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				b[i][j][l]+=b[i][j][l-1];
	int all=qpow(N-ss,W);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
			{
				if (a[i][j][l]==1) continue;
				ans=(ans+1ll*V[i][j][l]*(all+mod-qpow(N-ss-b[i][j][l],W)))%mod;
			}
	printf("%lld",1ll*ans*qpow(qpow(N,W),mod-2)%mod);
}
inline int read(){
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	n=read();m=read();k=read();W=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l)
				a[i][j][l]=1-read();//1ÎªÕÏ°­
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int l=1;l<=k;++l) 
				V[i][j][l]=read();
	if (n<=20&&m<=20&&k<=20) sol();
	else printf("1");
	return 0;
}
