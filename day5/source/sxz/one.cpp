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
const int Maxn=210;
const int inf=0x3f3f3f3f;
const ll mod=1000000007;

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

int ma[110000],a[Maxn],b[Maxn],n,cnt;
ll mp[Maxn][Maxn],c[Maxn],sxz;

void dfs(int now,int cur) {
	if(now>n) {
		ma[cur]=++cnt;
		a[cnt]=cur;
		return ;
	}
	for(int i=1;i<=n;i++)
		if(!b[i]) {
			b[i]=1;
			dfs(now+1,cur*10+i);
			b[i]=0;
		}
}

void gauss(int n) {
	for(int i=1;i<=n;i++) {
		int temp;
		for(int j=i;j<=n;j++)
			if(mp[j][i]) {
				temp=j;
				break;
			}
		if(temp!=i) for(int k=i;k<=n;k++) swap(mp[i][k],mp[temp][k]),swap(c[i],c[temp]);
		ll inv=powp(mp[i][i],mod-2);
		for(int j=i;j<=n;j++) mp[i][j]=mp[i][j]*inv%mod;
		c[i]=c[i]*inv%mod;
		for(int j=1;j<=n;j++) if(i!=j) {
			ll temp=mp[j][i];
			for(int k=i;k<=n;k++) mp[j][k]=modd(mp[j][k]-mp[i][k]*temp%mod);
			c[j]=modd(c[j]-c[i]*temp%mod);
		}
	}
}

int main() {
	freopen("one.in","r",stdin);
	freopen("one.out","w",stdout);
	read(n);
	sxz=powp(n*(n-1)/2,mod-2);
	dfs(1,0);
	mp[1][1]=1;
	for(int i=2;i<=cnt;i++) {
		mp[i][i]=1;
		int temp=a[i];
		for(int j=1;j<=n;j++) {
			b[j]=temp%10;
			temp/=10;
		}
		for(int j=1;j<n;j++)
			for(int k=j+1;k<=n;k++) {
				swap(b[j],b[k]);
				temp=0;
				for(int l=n;l;l--)
					temp=temp*10+b[l];
				mp[i][ma[temp]]=modd(-sxz);
				swap(b[j],b[k]);
			}
		c[i]=1;
	}
	memset(b,0,sizeof(b));
	gauss(cnt);
	int temp=0;
	for(int i=1;i<=cnt;i++) printf("%d : %d\n",a[i],c[i]);
	for(int i=1;i<=n;i++) read(sxz),temp=temp*10+sxz;
	printf("%lld\n",c[ma[temp]]);
	return 0;
}

