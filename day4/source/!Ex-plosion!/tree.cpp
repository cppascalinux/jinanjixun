#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
namespace INPUT_SPACE{
	const int BS=(1<<24)+5;char S[BS],*h,*t;inline int gc() { if(h==t) t=(h=S)+fread(S,1,BS,stdin);return h==t?EOF:(*h++); }
	inline int inn() { int x,ch;while((ch=gc())<'0'||ch>'9');x=ch^'0';while((ch=gc())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^'0');return x; }
}using INPUT_SPACE::inn;
namespace OUTPUT_SPACE{
	char ss[100000*15],tt[20];int ssl,ttl;inline int Flush() { return fwrite(ss+1,1,ssl,stdout),ssl=0; }
	inline int print(int x) { if(!x) ss[++ssl]='0';for(ttl=0;x;x/=10) tt[++ttl]=char(x%10+'0');for(;ttl;ttl--) ss[++ssl]=tt[ttl];return ss[++ssl]='\n'; }
}using OUTPUT_SPACE::print;using OUTPUT_SPACE::Flush;
const int N=200010;
namespace T{ int fa[N]; }
struct edges{
	int to,pre;
}e[N<<1];int h[N],etop,val[N];
inline int add_edge(int u,int v) { return e[++etop].to=v,e[etop].pre=h[u],h[u]=etop; }
namespace GR{
	vector<int> g[N];int nc=0;
	inline int dfs(int x,int f=0)
	{
		val[x]=1;int y;
		Rep(i,g[x]) if((y=g[x][i])^f)
			val[++nc]=-1,T::fa[nc]=x,T::fa[y]=nc,
			add_edge(x,nc),add_edge(nc,y),dfs(y,x);
		return 0;
	}
	inline int solve(int n) { return nc=n,dfs(1),nc; }
}
namespace LCA_space{
	const int LOG=20;
	int up[N][LOG],Log[N],d[N];
	inline int dfs(int x)
	{
		up[x][0]=T::fa[x],d[x]=d[T::fa[x]]+1;
		rep(i,1,Log[d[x]]) up[x][i]=up[up[x][i-1]][i-1];
		for(int i=h[x];i;i=e[i].pre) dfs(e[i].to);return 0;
	}
	inline int prelude(int n) { rep(i,2,n) Log[i]=Log[i>>1]+1;return dfs(1); }
	inline int LCA(int x,int y)
	{
		if(d[x]<d[y]) swap(x,y);
		for(int i=Log[d[x]];i>=0;i--)
			if(d[up[x][i]]>=d[y]) x=up[x][i];
		if(x==y) return x;
		for(int i=Log[d[x]];i>=0;i--)
			if(up[x][i]^up[y][i]) x=up[x][i],y=up[y][i];
		return up[x][0];
	}
}using LCA_space::LCA;
namespace BIT{
	int b[N],n;
	inline int query(int p) { int ans=0;for(;p;p^=p&-p) ans+=b[p];return ans; }
	inline int update(int p,int v) { for(;p<=n;p+=p&-p) b[p]+=v;return 0; }
	inline int update(int s,int t,int v) { return s<=t?update(s,v),update(t+1,-v):0; }
}using BIT::update;using BIT::query;
namespace LCT{
	int fa[N],ch[N][2],s[N],pf[N],las[N],R,c;
	inline int gw(int x) { return ch[fa[x]][1]==x; }
	inline int push_up(int x) { return s[x]=s[ch[x][0]]+s[ch[x][1]]+val[x]; }
	inline int setc(int x,int y,int z) { if(!x) return fa[y]=0;ch[x][z]=y;if(y) fa[y]=x;return push_up(x); }
	inline int rotate(int x)
	{
		int y=fa[x],z=fa[y],a=gw(x),b=gw(y),c=ch[x][a^1];
		return swap(las[x],las[y]),swap(pf[x],pf[y]),setc(y,c,a),setc(x,y,a^1),setc(z,x,b);
	}
	inline int splay(int x) { for(;fa[x];rotate(x)) if(fa[fa[x]]) rotate(gw(x)==gw(fa[x])?fa[x]:x);return 0; }
	inline int expose(int x)
	{
		splay(x);int y=ch[x][1];
		if(y) ch[x][1]=fa[y]=0,pf[y]=x,las[y]=las[x],push_up(x);
		return update(las[x]+1,R,s[x]),las[x]=R;
	}
	inline int splice(int x)
	{
		splay(x);int z=x;while(ch[z][0]) z=ch[z][0];splay(z),splay(x);
		if(z==c) return 0;int y=pf[x];assert(y);
		return expose(y),splay(y),setc(y,x,1),pf[x]=0,las[x]=0,1;
	}
	inline int cut(int x)
	{
		splay(x);int y=ch[x][0];if(!y) return 0;
		ch[x][0]=fa[y]=0,las[y]=las[x],pf[y]=pf[x],push_up(x);
		while(ch[y][1]) y=ch[y][1];return splay(y),pf[x]=y;
	}
	inline int access(int x) { expose(x);while(splice(x));return 0; }
	inline int pt(int x,int y,int _R) { return R=_R,cut(c=LCA(x,y)),access(x),access(y); }
	inline int prelude(int n) { rep(i,1,n) pf[i]=T::fa[i],s[i]=val[i],las[i]=0;return 0; }
}using LCT::pt;
int s[N],t[N],ans[N];
struct Q{
	int l,r,id;inline bool operator<(const Q &q)const { return r<q.r; }
}q[N];
int main()
{
	freopen("tree.in","r",stdin),freopen("tree.out","w",stdout);
	int n=inn(),m=inn(),qc=inn(),x,y;
	rep(i,1,n-1) x=inn(),y=inn(),GR::g[x].pb(y),GR::g[y].pb(x);
	n=GR::solve(n),LCA_space::prelude(n),BIT::n=m,LCT::prelude(n);
	rep(i,1,m) s[i]=inn(),t[i]=inn();
	rep(i,1,qc) q[i].l=inn(),q[i].r=inn(),q[i].id=i;
	sort(q+1,q+qc+1);
	for(int i=1,j=1;i<=qc;i++)
	{
		while(j<=q[i].r) pt(s[j],t[j],j),j++;
		ans[q[i].id]=query(q[i].l);
	}
	rep(i,1,qc) print(ans[i]);return Flush(),0;
}
