#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,v) rep(i,0,(int)v.size()-1)
#define lint long long
#define mod 1000000007
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
const int N=200010,LOG=20;
inline int P(int x) { return x>=mod?x-mod:x; }
struct Tree{
	struct edges{
		int to,pre,w;
	}e[N<<1];int h[N],etop,n,nc,son[N],wf[N];vector<pair<pii,int> > es;
	inline int add_edge(int u,int v,int w) { return e[++etop].to=v,e[etop].w=w,e[etop].pre=h[u],h[u]=etop; }
	inline int input(int _n) { n=nc=_n;int x,y,w;rep(i,1,n-1) x=inn(),y=inn(),w=inn(),add_edge(x,y,w),add_edge(y,x,w);return 0; }
	inline int sdh(int x=1,int f=0)
	{
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^f) sdh(y,x);int cnt=0,y,z;
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^f) son[++cnt]=y,wf[cnt]=e[i].w;
		for(int c=cnt;(cnt=c)>2;cnt=c) rep(i,(c=0)+1,cnt) if(i&1)
		{
			if(i<cnt)
				y=++nc,z=son[i],es.pb(mp(mp(y,z),wf[i])),
				z=son[i+1],es.pb(mp(mp(y,z),wf[i+1])),
				son[++c]=y,wf[c]=0;
			else son[++c]=son[i],wf[c]=wf[i];
		}
		rep(i,1,cnt) y=son[i],es.pb(mp(mp(x,y),wf[i]));
		if(!f)
		{
			memset(h,0,sizeof(int)*(nc+1)),etop=0;
			Rep(i,es)
				x=es[i].fir.fir,y=es[i].fir.sec,z=es[i].sec,
				add_edge(x,y,z),add_edge(y,x,z);
			vector<pair<pii,int> >().swap(es);
		}
		return 0;
	}
	int dpt[N],d[N],up[N][LOG],Log[N],dfc,in[N];
	inline int dfsLCA(int x,int f=0)
	{
		dpt[x]=dpt[f]+1,up[x][0]=f,in[x]=++dfc;
		rep(i,1,Log[dpt[x]]) up[x][i]=up[up[x][i-1]][i-1];
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^f)
			d[y]=d[x]+e[i].w,(d[y]>=mod?d[y]-=mod:0),dfsLCA(y,x);
		return 0;
	}
	inline int getLCA(int x,int y)
	{
		if(dpt[x]<dpt[y]) swap(x,y);
		for(int i=Log[dpt[x]];i>=0;i--)
			if(up[x][i][dpt]>=dpt[y]) x=up[x][i];
		if(x==y) return x;
		for(int i=Log[dpt[x]];i>=0;i--)
			if(up[x][i]^up[y][i]) x=up[x][i],y=up[y][i];
		return up[x][0];
	}
	inline int preludeLCA() { rep(i,2,n) Log[i]=Log[i>>1]+1;return dfsLCA(1); }
	int sz[N],vis[N],esz,eid;
	inline int getsz(int x,int fa=0)
	{
		sz[x]=1;
		for(int i=h[x],y;i;i=e[i].pre)
			if((y=e[i].to)!=fa&&!vis[i]) sz[x]+=getsz(y,x);
		return sz[x];
	}
	inline int geteid(int x,int fa,int fsz)
	{
		for(int i=h[x],y;i;i=e[i].pre)
			if((y=e[i].to)!=fa&&!vis[i])
			{
				geteid(y,x,fsz);
				if(max(sz[y],fsz-sz[y])<esz)
					esz=max(sz[y],fsz-sz[y]),eid=i;
			}
		return 0;
	}
	int lst[N],lc,col[N],a[N],imp[N];pii lsttmp[N];vector<int> g[N];
	inline int getmsg(int x,int f,int c,int d,Tree &T)
	{
		if(d>=mod) d-=mod;
		if(x<=n) T.lst[++T.lc]=x,T.col[x]=c,T.a[x]=d;
		for(int i=h[x],y;i;i=e[i].pre)
			if((y=e[i].to)!=f&&!vis[i]) getmsg(y,x,c,d+e[i].w,T);
		return 0;
	}
	inline int bfz(Tree &T,int x=1)
	{
		getsz(x);if(sz[x]==1) return 0;
		eid=0,esz=nc+1,geteid(x,0,sz[x]);
		int u=e[eid].to,v=e[((eid-1)^1)+1].to;
		vis[eid]=vis[((eid-1)^1)+1]=1;T.lc=0;
		getmsg(u,v,0,0,T),getmsg(v,u,1,e[eid].w,T);
		int ans=T.solve();
		ans+=bfz(T,u),(ans>=mod?ans-=mod:0);
		ans+=bfz(T,v),(ans>=mod?ans-=mod:0);
		return ans;
	}
	int stc[N],Ans;
	struct MSG{
		int as,ds,ads,sz;
		MSG(int _as=0,int _ds=0,int _ads=0,int _sz=0) { as=_as,ds=_ds,ads=_ads,sz=_sz; }
		inline int clear() { return as=ds=ads=sz=0; }
		inline MSG operator+(const MSG &m)const { return MSG(P(as+m.as),P(ds+m.ds),P(ads+m.ads),P(sz+m.sz)); }
		inline MSG& operator+=(const MSG &m) { return (*this)=(*this)+m,*this; }
	}msg[N][2];
	inline int _init(int x,int c,int a,int d) { return msg[x][c].as=a,msg[x][c].ds=d,msg[x][c].ads=(lint)a*d%mod,msg[x][c].sz=1; }
	inline int _merge(MSG &x,MSG &y,int w)
	{
		int res=((lint)x.ads*y.sz+(lint)y.ads*x.sz+(lint)x.as*y.ds+(lint)x.ds*y.as-(lint)w*x.as%mod*y.sz-(lint)w*y.as%mod*x.sz)%mod;
		return res<0?res+mod:res;
	}
	inline int getAns(int x)
	{
		msg[x][0].clear(),msg[x][1].clear();
		if(imp[x]) _init(x,col[x],a[x],d[x]);int y;
		Rep(i,g[x])
			getAns(y=g[x][i]),
			Ans+=_merge(msg[x][0],msg[y][1],2*d[x]),(Ans>=mod?Ans-=mod:0),
			Ans+=_merge(msg[x][1],msg[y][0],2*d[x]),(Ans>=mod?Ans-=mod:0),
			msg[x][0]+=msg[y][0],msg[x][1]+=msg[y][1];
		return 0;
	}
	inline int solve()
	{
		rep(i,1,lc) lsttmp[i]=mp(in[lst[i]],lst[i]);sort(lsttmp+1,lsttmp+lc+1);
		rep(i,1,lc) lst[i]=lsttmp[i].sec,imp[lst[i]]=1;
		if(lst[1]^1) { lc++;for(int i=lc;i>1;i--) lst[i]=lst[i-1];lst[1]=1; }
		rep(i,1,lc) vector<int>().swap(g[lst[i]]);int t=1;stc[1]=1;
		rep(i,2,lc)
		{
			int x=lst[i],y=stc[t],z=stc[t-1],c;
			while(dpt[c=getLCA(x,y)]<=dpt[z]) g[z].pb(y),y=stc[--t],z=stc[t-1];
			if(c^y) vector<int>().swap(g[c]),g[c].pb(y),stc[t]=c;stc[++t]=x;
		}
		while(t>1) g[stc[t-1]].pb(stc[t]),t--;
		Ans=0,getAns(1);rep(i,1,lc) imp[lst[i]]=0;return Ans;
	}
}T1,T2;
int main()
{
	freopen("tree.in","r",stdin),freopen("tree.out","w",stdout);
	int n=inn();T1.input(n),T2.input(n),T1.sdh(),T2.preludeLCA();
	return !printf("%d\n",(T1.bfz(T2)<<1)%mod);
}
