#include<bits/stdc++.h>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1000000
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
struct B
{	vector<pii> v; vector<ll> a; vector<int> bl; int B;
	struct info{vector<pair<ll,int>> s;ll tag;};vector<info> b;
	inline void init()
	{	a.resize(v.size()); bl.resize(v.size()); B=max(db(1),sqrtl(v.size()*log2(v.size())/10)); for(rint i=0;i<v.size();i++) bl[i]=i/B;
		b.resize(bl[v.size()-1]+1); for(rint i=0;i<v.size();i++) b[bl[i]].s.push_back(mp(0,i));
	}
	inline void fuck(int l,int r,int _)
	{	vector<pair<ll,int>> X,Y;
		for(auto gg:b[_].s) if(l<=gg.second&&gg.second<=r) X.push_back(mp(a[gg.second],gg.second));
		for(auto gg:b[_].s) if(gg.second<l||gg.second>r) Y.push_back(gg);
		merge(X.begin(),X.end(),Y.begin(),Y.end(),b[_].s.begin());
	}
	inline void addb(int l,int r,ll k,int _){for(rint i=l;i<=r;i++)a[i]+=k;fuck(l,r,_);}
	inline void add(int L,int R,ll k)
	{	int l=lower_bound(v.begin(),v.end(),mp(L,0))-v.begin(),r=upper_bound(v.begin(),v.end(),mp(R+1,0))-v.begin()-1;
		if(r>=0&&v[r].second>R) r--;// debug(l,r);
		if(l>r)
		{//	debug(L,R,l,r,v[l-1].first,v[l-1].second);
			if(l-1==r+1&&0<=l-1&&l-1<v.size()&&v[l-1].first<=L&&R<=v[l-1].second)
			a[l-1]+=k/(v[l-1].second-v[l-1].first+1)*(R-L+1),fuck(l-1,l-1,bl[l-1]);
		//	debug(v[l].first,v[l].second,k/(v[l].second-v[l].first+1)*(R-v[l].first+1));
			if(0<=l&&l<v.size()&&v[l].first<=R) a[l]+=k/(v[l].second-v[l].first+1)*(R-v[l].first+1),fuck(l,l,bl[l]);
			if(0<=r&&r<v.size()&&L<=v[r].second) a[r]+=k/(v[r].second-v[r].first+1)*(v[r].second-L+1),fuck(r,r,bl[r]);
			return;
		}
		if(0<=l-1&&l-1<v.size()&&L<=v[l-1].second) a[l-1]+=k/(v[l-1].second-v[l-1].first+1)*(v[l-1].second-L+1),fuck(l-1,l-1,bl[l-1]);
		if(0<=r+1&&r+1<v.size()&&v[r+1].first<=R) a[r+1]+=k/(v[r+1].second-v[r+1].first+1)*(R-v[r+1].first+1),fuck(r+1,r+1,bl[r+1]);
	//	debug(L,R,l,r,bl[l],bl[r]);
		if(bl[l]==bl[r]){addb(l,r,k,bl[l]);return;}
		addb(l,(bl[l]+1)*B-1,k,bl[l]),addb(bl[r]*B,r,k,bl[r]);
//		debug(l,(bl[l]+1)*B-1,bl[r]*B,r);
		for(rint i=bl[l]+1;i<bl[r];i++) b[i].tag+=k;
	}
	inline int queryb(int l,int r,ll k){int ans=0;for(rint i=l;i<=r;i++)ans+=a[i]<=k;return ans;}
	inline int query(int L,int R,int k)
	{//	for(auto _:v) debug(_.first,_.second);fgx;
		int l=lower_bound(v.begin(),v.end(),mp(L,0))-v.begin(),r=upper_bound(v.begin(),v.end(),mp(R+1,0))-v.begin()-1;
		if(r>=0&&v[r].second>R) r--;// debug(l,r,L,R,bl[l],bl[r]);
		if(l>r) return 0; if(bl[l]==bl[r]){return queryb(l,r,k-b[bl[l]].tag);}
		int ans=queryb(l,(bl[l]+1)*B-1,k-b[bl[l]].tag)+queryb(bl[r]*B,r,k-b[bl[r]].tag);
	//	debug(l,(bl[l]+1)*B-1,bl[r]*B,r,ans);
		for(rint i=bl[l]+1;i<bl[r];i++) ans+=upper_bound(b[i].s.begin(),b[i].s.end(),mp(k-b[i].tag+1,0))-b[i].s.begin();
		return ans;
	}
}a[N]; vector<int> len;
void build(int l,int r)
{	a[r-l+1].v.push_back(mp(l,r)); len.push_back(r-l+1);
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid); build(mid+1,r);
}
int main()
{	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	int n,m,tp,x,y,z; cin>>n>>m;
	build(1,n); sort(len.begin(),len.end()); len.erase(unique(len.begin(),len.end()),len.end());
	for(auto _:len) a[_].init();
	while(m--)
	{	int ans=0; scanf("%d%d%d%d",&tp,&x,&y,&z);
		if(tp==1) for(auto _:len)// cerr<<_<<":::::\n",
		a[_].add(x,y,(ll)z*_);
		else{for(auto _:len){//cerr<<_<<":::::\n",
		ans+=a[_].query(x,y,z);}cout<<ans<<"\n";}
	//	exit(0);
	}
	return 0;
}

