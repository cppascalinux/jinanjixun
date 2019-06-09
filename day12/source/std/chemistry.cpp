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

int n,k,fg,sp;
vector<PII> ret,v;
int T(int p) {
	if (p==sp) return 1; else if (p==1) return sp; return p;
}
int main() {
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);

	scanf("%d%d",&n,&k);
	if ((k&(-k))==k) {
		printf("%d\n",k-1);
		for (int x=2;x<=k;x<<=1) for (int i=x;i<=k;i+=x) printf("%d %d\n",k-(i-x/2)+1,k-i+1);
		return 0;
	}
	if (n==k||(n%2==0&&k==n-1)) { puts("-1"); return 0; }
	if (k%2!=0) ++k,fg=1;
	n=k+1;
	for (int x=2;x<=n;x<<=1) {
		for (int i=x;i<=n;i+=x) ret.pb(mp(i-x/2,i));
	}
	for (int x=n;x;x-=x&-x) {
		v.pb(mp(x,x&-x));
	}
	reverse(all(v));
	int c=v[0].se; sp=v[0].fi;
	rep(i,2,SZ(v)) {
		int s=v[i-1].se,t=v[i].se;
		int p=v[i-1].se,q=v[i].se;
		while (q!=s) {
			ret.pb(mp(sp,v[i].fi));
			c-=q; q*=2;
		}
		ret.pb(mp(v[i-1].fi,v[i].fi));
		q*=2;
		while (q!=t) {
			if (c>q) ret.pb(mp(sp,v[i].fi)),c-=q,q*=2;
			else ret.pb(mp(v[i].fi,sp)),q-=c,c*=2;
		}
	}
	if (fg) ret.pb(mp(sp,n));
	printf("%d\n",SZ(ret));
	k-=fg;
	for (auto p:ret) printf("%d %d\n",T(p.fi),T(p.se));
}
