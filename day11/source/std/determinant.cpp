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

const int N=101000;
int n,f[N],val[N],_;
PII p[N],q[N];
vector<PII> e[N];

void dfs(int u,int f) {
	rep(i,0,SZ(e[u])) {
		PII p=e[u][i];
		if (p.fi==f) continue;
		val[p.se]=p.fi;
		dfs(p.fi,u);
	}
}
int find(int x) { return f[x]==x?x:f[x]=find(f[x]); }
int solve(PII *p) {
	rep(i,0,n+1) f[i]=i,e[i].clear();
	rep(i,0,n) {
		int u=p[i].fi-1,v=p[i].se;
		if (find(u)==find(v)) return 0;
		f[find(u)]=find(v);
		e[u].pb(mp(v,i)); e[v].pb(mp(u,i));
	}
	dfs(n,-1);
	int cnt=n;
	rep(i,0,n) f[i]=i,cnt+=val[i]==p[i].se;
	rep(i,0,n) {
		if (find(val[i])==find(i)) --cnt;
		f[find(i)]=find(val[i]);
	}
	return cnt%2==0?1:-1;
}
int main() {
	freopen("determinant.in","r",stdin);
	freopen("determinant.out","w",stdout);
	for (scanf("%d",&_);_;_--) {
		ll s=1;
		scanf("%d",&n);
		rep(i,0,n) {
			scanf("%d%d",&p[i].fi,&p[i].se);
			scanf("%d%d",&q[i].fi,&q[i].se);
			s=s*(p[i].se-p[i].fi+1)%mod*(q[i].se-q[i].fi+1)%mod;
		}
		s=powmod(s,mod-2);
		s=s*solve(p)*solve(q)%mod;
		if (s<0) s+=mod;
		printf("%lld\n",s);
	}
}