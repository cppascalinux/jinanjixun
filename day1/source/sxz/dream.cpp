#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define pir pair<int,int>
#define fr first
#define sc second
#define mp(x,y) make_pair(x,y)
#define vic vector<int>
#define vit vic::iterator
#define rsort(x,y) sort(x,y),reverse(x,y)
using namespace std;

inline char gc() {
	return  getchar();
}

template<typename T1>
int read(T1 &a) {
	a=0;
	char ch=gc();
	T1 f=1;
	while(!isdigit(ch)) {
		if(ch==EOF) return 0;
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(isdigit(ch)) {
		a=a*10+ch-'0';
		ch=gc();
	}
	a=a*f;
	return 1;
}

template<typename T1,typename T2>
int read(T1 &a,T2 &b) {
	return read(a)+read(b);
}

template<typename T1,typename T2,typename T3>
int read(T1 &a,T2 &b,T3 &c) {
	return read(a,b)+read(c);
}

typedef long long ll;
const int Maxn=63;
const int inf=0x3f3f3f3f;
const ll mod=998244353;

inline ll modd(ll x) {
	return x<0?x+mod:x>=mod?x-mod:x;
}

ll powp(ll a,ll b) {
	ll ans=1;
	while(b) {
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int n,m,h,w,bj[Maxn][Maxn][Maxn],ans[Maxn][Maxn][Maxn],d[Maxn];
ll dat[Maxn][Maxn][Maxn],zhy,sxz,tot;

int main() {
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	read(n,m,h); read(w);
	tot=1ll*n*(n+1)*m*(m+1)*h*(h+1)/8%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++) {
				read(bj[i][j][k]);
				bj[i][j][k]^=1;
				bj[i][j][k]+=bj[i-1][j][k];
				bj[i][j][k]+=bj[i][j-1][k];
				bj[i][j][k]-=bj[i-1][j-1][k];
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
				read(dat[i][j][k]);
	d[h+1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int ii=i;ii<=n;ii++)
				for(int jj=j;jj<=m;jj++) {
					for(int k=1;k<=h;k++) d[k]=bj[ii][jj][k]-bj[i-1][jj][k]-bj[ii][j-1][k]+bj[i-1][j-1][k];
					int temp=1;
					for(int k=1;k<=h+1;k++)
						if(d[k]) {
							for(int l=temp;l<k;l++) {
								int zhy=(l-temp+1)*(k-l);
								ans[i][j][l]+=zhy;
								ans[i][jj+1][l]-=zhy;
								ans[ii+1][j][l]-=zhy;
								ans[ii+1][jj+1][l]+=zhy;
							}
							zhy+=(k-temp)*(k-temp+1)/2;
							temp=k+1;
						}
				}
	zhy%=mod;
	sxz=powp(tot,mod-2);
	sxz=sxz*zhy%mod;
	sxz=powp(sxz,w);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
				ans[i][j][k]+=ans[i-1][j][k]+ans[i][j-1][k]-ans[i-1][j-1][k];
	ll res=0,inv=powp(zhy,mod-2);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=h;k++)
				res=modd(res+sxz*dat[i][j][k]%mod*modd(1-powp(inv*modd(zhy-ans[i][j][k])%mod,w))%mod);
	printf("%lld\n",res);
	return 0;
}

