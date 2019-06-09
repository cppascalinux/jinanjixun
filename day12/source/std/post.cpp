#include <bits/stdc++.h>
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
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=200010;
int n,c,segl[N];
ll l,a[N*2],sa[N*2],ans;
vector<int> prv[N],ansr;
vector<ll> vdp[N];


ll weight(int x,int y) { // x...y
	if (x>y) return 0;
	int md=(x+y)/2;
	return (sa[y]-sa[md-1])-(y-md+1)*a[md]+a[md]*(md-x)-(sa[md-1]-sa[x-1]);
}

//dp: for i = 1 to n : f[i]= min_{0<=j<i} {f[j]+w(j,i)}   
ll f[N];
int opt[N];
ll val(int j,int i); //let val(j,i) = f[j]+w(j,i)
int solve(ll c,int ty=0){
	static int vo[N],po[N];
	int p=1,q=0;
	f[0]=0;
	auto val=[&](int j,int i) {
		return f[j]+weight(j+1,i)+c;
	};
	auto check=[&](int p,int q,int r) {
		return (ty==0)?val(p,r)<=val(q,r):val(p,r)<val(q,r);
	};
	rep(i,0,n){
		while(p<=q && check(i,vo[q],po[q]))q--;//
		if(p>q)po[++q]=i+1,vo[q]=i;
		else{
			int l=po[q],r=n;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check(i,vo[q],mid))r=mid-1;//
				else l=mid+1;
			}
			if(l<=n) po[++q]=l,vo[q]=i;
		}
		while(p<q && i+1>=po[p+1])p++;
		f[i+1]=val(vo[p],i+1);
		opt[i+1]=vo[p];
	}
	int x=n,cnt=0;;
	while (x!=0) x=opt[x],cnt++;
	return cnt;
}
VI getway() {
	VI p;
	int x=n;
	while (x!=0) x=opt[x],p.pb(x);
	reverse(all(p)); p.pb(n);
	return p;
}

void gao(int id,int fl,int fr,int l,int r) {
	if (l>r) return;
	int md=(l+r)>>1;
	ll minv=1ll<<60; int minp=-1;
	for (int i=fl;i<=fr;i++) {
		ll v=vdp[id-1][i-segl[id-1]]+weight(i+1,md);
		if (v<minv) {
			minv=v;
			minp=i;
		}
	}
	vdp[id][md-segl[id]]=minv;
	prv[id][md-segl[id]]=minp;
	if (l<md) gao(id,fl,minp,l,md-1);
	if (md<r) gao(id,minp,fr,md+1,r);
}

void solve(VI &p,VI &q) {
	if (p[0]>q[0]) return;
	VI mid(c);
	mid[0]=(p[0]+q[0])/2;
//	printf("%d %d %d\n",p[0],q[0],mid[0]);
	ll ret=1ll<<60;
	if (c>1) {
		rep(i,p[1],q[1]+1) {
			prv[1][i-segl[1]]=mid[0];
			vdp[1][i-segl[1]]=weight(mid[0]+1,i);
		}
		rep(i,2,c) {
			gao(i,p[i-1],q[i-1],p[i],q[i]);
		}
		rep(i,p[c-1],q[c-1]+1) {
			ll v=vdp[c-1][i-segl[c-1]]+weight(i+1,mid[0]+n);
			if (v<ret) {
				ret=v;
				mid[c-1]=i;
			}
		}
		per(i,0,c-1) {
			mid[i]=prv[i+1][mid[i+1]-segl[i+1]];
		}
	} else {
		ret=weight(mid[0]+1,mid[0]+n);
	}
	if (ret<ans) {
		ans=ret;
		ansr=mid;
	}
	if (p[0]<mid[0]) {
		--mid[0];
		solve(p,mid);
		++mid[0];
	}
	if (mid[0]<q[0]) {
		++mid[0];
		solve(mid,q);
		--mid[0];
	}
}

int main() {
	freopen("post.in","r",stdin);
	freopen("post.out","w",stdout);

	scanf("%d%d%lld",&n,&c,&l);
	rep(i,1,n+1) scanf("%lld",a+i);
	rep(i,1,n+1) a[i+n]=a[i]+l;
	rep(i,1,2*n+1) sa[i]=sa[i-1]+a[i];

	ll pl=0,pr=l*n/c+1;
	ll pres=0;
	rep(i,1,c+1) pres+=weight((ll)(i-1)*n/c+1,(ll)i*n/c);
	pr=min(pr,pres+10);
	while (pl+1<pr) {
		ll md=(pl+pr)>>1;
		int w=solve(md,0);
		// dp[w]=f[n]-md*c
		if (w==c) {
			pl=md;
			break;
		}
		if (w>c) pl=md; else pr=md;
		ll dpw=f[n]-md*w;
		if (w>c) pl=max(pl,dpw/(n-w+1)-10);
//		fprintf(stderr,"%lld %lld %lld\n",pl,pr,md);
	}
	solve(pl,0);
	VI seg=getway();
	if (SZ(seg)-1>c) {
		solve(pl,1);
		VI s2=getway();
		bool suc=0;
		rep(i,0,SZ(s2)-1) {
			int j=SZ(seg)-(c-i)-1;
			if (j>=0&&j<SZ(seg)-1&&s2[i]<=seg[j]&&seg[j+1]<=s2[i+1]) {
				VI ss;
				rep(k,0,i+1) ss.pb(s2[k]);
				rep(k,j+1,SZ(seg)) ss.pb(seg[k]);
				assert(SZ(ss)==c+1);
				suc=1;
				seg=ss;
				break;
			}
		}
		assert(suc);
	}

	assert(SZ(seg)==c+1);
	int ming=n;
	rep(i,0,c) ming=min(ming,seg[i+1]-seg[i]);
	seg.resize(2*c+1);
	rep(i,1,c+1) seg[i+c]=seg[i]+n;
	VI fl(c,0),fr(c,0);
	rep(i,0,c) if (seg[i+1]-seg[i]==ming) {
		rep(j,0,c) {
			fl[j]=seg[i+j],fr[j]=seg[i+j+1];
			segl[j]=fl[j];
		}
		break;
	}

	rep(i,0,c) {
		prv[i]=VI(fr[i]-fl[i]+1,0);
		vdp[i]=vector<ll>(fr[i]-fl[i]+1,0);
	}
	ans=1ll<<60;
	solve(fl,fr);
	printf("%lld\n",ans);
	ansr.pb(ansr[0]+n);
	vector<ll> shop(c);
	rep(i,0,c) {
		shop[i]=a[(ansr[i]+ansr[i+1]+1)/2]%l;
	}
	sort(all(shop));
	rep(i,0,c) printf("%lld%c",shop[i]," \n"[i==c-1]);
}