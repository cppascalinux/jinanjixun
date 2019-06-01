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
namespace IO
{   const int __S=5e6;char __buf[__S],*__H,*__T;
    inline char getc()
    {   if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
        if(__H==__T) return -1;return *__H++;
    }
    template <class __I>inline void read(__I &__x)
    {   char __c=getc(); while(!isdigit(__c)) __c=getc();
        for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
    }
}using namespace IO;
int head[N],tot,sz[N],son[N],dfn[N],fa[N],dep[N],top[N],L[N],R[N],ans[N],la[N]; pii b[N];
struct Edge{int v,next;}edge[N];
inline void add(int x,int y){edge[++tot]=(Edge){y,head[x]};head[x]=tot;}
void dfs1(int x,int la=0)
{	for(rint i=head[x];i;i=edge[i].next)
	if(to!=la) dfs1(to,x),sz[x]+=sz[to],son[x]=sz[to]>sz[son[x]]?to:son[x];
}
void dfs2(int x,int la=0)
{	dfn[x]=++dfn[0]; fa[x]=la; dep[x]=dep[la]+1;
	if(son[x]) top[son[x]]=top[x],dfs2(son[x],x);
	for(rint i=head[x];i;i=edge[i].next) if(to!=la&&to!=son[x]) top[to]=to,dfs2(to,x);
}
inline int lca(int x,int y)
{	for(;top[x]!=top[y];x=fa[top[x]]) if(dep[top[x]]<dep[top[y]]) swap(x,y);
	return dep[x]<dep[y]?x:y;
}
struct node{int l,r,s;vector<int> v;}a[N];
void build(int l,int r,int o)
{	a[o].l=l; a[o].r=r; a[o].v.clear();
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,o+o); build(mid+1,r,o+o+1);
}
void ins(int x,int y,int o)
{	if(a[o].l==a[o].r){a[o].v.push_back(y);a[o].s=a[o].v.size();return;}
	int mid=(a[o].l+a[o].r)>>1;
	if(x<=mid) ins(x,y,o+o); else ins(x,y,o+o+1);
	a[o].s=a[o+o].s+a[o+o+1].s;
}
void gaol(int l,int r,int k,int o)
{	if(!a[o].s) return;
	if(a[o].l==a[o].r){while(!a[o].v.empty())L[a[o].v.back()]=k,a[o].v.pop_back();a[o].s=0;return;}
	int mid=(a[o].l+a[o].r)>>1;
	if(a[o].l==l&&a[o].r==r){gaol(l,mid,k,o+o),gaol(mid+1,r,k,o+o+1),a[o].s=a[o+o].s+a[o+o+1].s;return;}
	if(r<=mid) gaol(l,r,k,o+o);
	else if(l>mid) gaol(l,r,k,o+o+1);
	else gaol(l,mid,k,o+o),gaol(mid+1,r,k,o+o+1);
	a[o].s=a[o+o].s+a[o+o+1].s;
}
void gaor(int l,int r,int k,int o)
{	if(!a[o].s) return;
	if(a[o].l==a[o].r){while(!a[o].v.empty())R[a[o].v.back()]=k,a[o].v.pop_back();a[o].s=0;return;}
	int mid=(a[o].l+a[o].r)>>1;
	if(a[o].l==l&&a[o].r==r){gaor(l,mid,k,o+o),gaor(mid+1,r,k,o+o+1),a[o].s=a[o+o].s+a[o+o+1].s;return;}
	if(r<=mid) gaor(l,r,k,o+o);
	else if(l>mid) gaor(l,r,k,o+o+1);
	else gaor(l,mid,k,o+o),gaor(mid+1,r,k,o+o+1);
	a[o].s=a[o+o].s+a[o+o+1].s;
}
void gaol(int x,int y,int id)
{	for(;top[x]!=top[y];x=fa[top[x]])
	{	if(dep[top[x]]<dep[top[y]]) swap(x,y);
		gaol(dfn[top[x]],dfn[x],id,1);
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) gaol(dfn[x],dfn[y]-1,id,1);
}
void gaor(int x,int y,int id)
{	for(;top[x]!=top[y];x=fa[top[x]])
	{	if(dep[top[x]]<dep[top[y]]) swap(x,y);
		gaor(dfn[top[x]],dfn[x],id,1);
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x!=y) gaor(dfn[x],dfn[y]-1,id,1);
}
struct Q{int tp,x,l,r;}q[N];
inline bool operator <(Q x,Q y){return x.x==y.x?abs(x.tp)>abs(y.tp):x.x<y.x;}
namespace T
{	struct node{int l,r,s,tag;}a[N];
	void build(int l,int r,int o)
	{	a[o].l=l; a[o].r=r;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(l,mid,o+o); build(mid+1,r,o+o+1);
	}
	void down(int o)
	{a[o].s+=a[o].tag*(a[o].r-a[o].l+1);if(a[o].l!=a[o].r)a[o+o].tag+=a[o].tag,a[o+o+1].tag+=a[o].tag;a[o].tag=0;}
	void update(int o){if(a[o+o].tag)down(o+o);if(a[o+o+1].tag)down(o+o+1);a[o].s=a[o+o].s+a[o+o+1].s;}
	void add(int l,int r,int k,int o)
	{//	if(o==1) debug(l,r,k);
		if(a[o].tag) down(o);
		if(a[o].l==l&&r==a[o].r){a[o].tag+=k;down(o);return;}
		int mid=(a[o].l+a[o].r)>>1;
		if(r<=mid) add(l,r,k,o+o);
		else if(l>mid) add(l,r,k,o+o+1);
		else add(l,mid,k,o+o),add(mid+1,r,k,o+o+1);
		update(o);
	}
	int query(int x,int o)
	{	if(a[o].tag) down(o);
		if(a[o].l==a[o].r) return a[o].s;
		int mid=(a[o].l+a[o].r)>>1;
		if(x<=mid) return query(x,o+o); else return query(x,o+o+1);
	}
}
int main()
{	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m,fuck,x,y,t=0; cin>>n>>m>>fuck;
	for(rint i=1;i<n;i++) read(x),read(y),add(x,y),add(y,x);
	dfs1(1); top[1]=1; dfs2(1);
	for(rint i=1;i<=m;i++) read(x),read(y),b[i]=mp(x,y);
	build(1,n,1);
	for(rint i=1;i<=m;i++)
	{	int l=lca(b[i].first,b[i].second);
		gaor(b[i].first,l,i); gaor(b[i].second,l,i); ins(dfn[l],i,1);
	}
	for(rint i=1;i<=m;i++) if(!R[i]) R[i]=m+1;
	build(1,n,1);
	for(rint i=m;i>=1;i--)
	{	int l=lca(b[i].first,b[i].second);
		gaol(b[i].first,l,i); gaol(b[i].second,l,i); ins(dfn[l],i,1);
	}
	for(rint i=1;i<=m;i++) if(!L[i]) L[i]=0;
	for(rint i=1;i<=m;i++){int l=lca(b[i].first,b[i].second);L[i]=max(L[i],la[l]);la[l]=i;}
	for(rint i=1;i<=m;i++) q[++t]=(Q){1,L[i]+1,i,R[i]-1},q[++t]=(Q){-1,i+1,i,R[i]-1};
	for(rint i=1;i<=fuck;i++) read(x),read(y),q[++t]=(Q){0,x,y,i};
//	for(rint i=1;i<=m;i++) debug(L[i],R[i]);
	T::build(1,m,1); sort(q+1,q+t+1);
	for(rint i=1;i<=t;i++)
	if(!q[i].tp) ans[q[i].r]=T::query(q[i].l,1);
	else T::add(q[i].l,q[i].r,q[i].tp,1);
	for(rint i=1;i<=fuck;i++) cout<<ans[i]<<"\n";
	return 0;
}

