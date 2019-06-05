#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define to edge[i].v
#define mp make_pair
#define rint register int
#define fgx cerr<<"-------------"<<endl
#define N 1000010
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
void dbg(){cerr<<endl;}
template<typename A,typename... B>void dbg(A x,B... y){cerr<<x<<" ";dbg(y...);}
#define debug(...) cerr<<#__VA_ARGS__<<"=",dbg(__VA_ARGS__)
namespace IO
{	const int __S=1e7; char __buf[__S],*__H,*__T;
	inline char getc()
	{	if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
		if(__H==__T) return -1;return *__H++;
	}
	template <class __I>inline void read(__I &__x)
	{	char __c=getc(); while(!isdigit(__c)) __c=getc();
		for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
	}
	char __obuf[__S],*__oS=__obuf,*__oT=__oS+__S-1,__c,__qu[55];int __qr;
	inline void flush(){fwrite(__obuf,1,__oS-__obuf,stdout);__oS=__obuf;}
	inline void putc(char __x){*__oS++ =__x;if(__oS==__oT) flush();}
	template <class __I>inline void print(__I __x)
	{	if(!__x) putc('0');
		while(__x) __qu[++__qr]=__x%10^'0',__x/=10;
		while(__qr) putc(__qu[__qr--]);
	}
	inline void el(){putc('\n');}inline void sp(){putc(' ');}
}using namespace IO;
tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> t[N];
int head[N],tot,sz[N],son[N],top[N],fa[N],dep[N],b[N],dfn[N],p[N],a[N];
inline int query(int x){int ans=0;for(;x;x-=x&-x)ans+=a[x];return ans;}
#define add(A,B,C) ADD(A,C),ADD(B+1,-C)
inline void ADD(int x,int y){for(;x<=dfn[0];x+=x&-x)a[x]+=y;}
struct Edge{int v,next;}edge[N*2];
inline void adde(int x,int y){edge[++tot]=(Edge){y,head[x]};head[x]=tot;}
void dfs1(int x,int la=0)
{	sz[x]=1; fa[x]=la; dep[x]=dep[la]+1;
	for(rint i=head[x];i;i=edge[i].next)
	if(to!=la) dfs1(to,x),sz[x]+=sz[to],son[x]=sz[to]>sz[son[x]]?to:son[x];
}
void dfs2(int x,int la=0)
{	p[dfn[x]=++dfn[0]]=x;
	if(son[x]) top[son[x]]=top[x],dfs2(son[x],x);
	for(rint i=head[x];i;i=edge[i].next)
	if(to!=la&&to!=son[x]) top[to]=to,t[x].insert(mp(b[to],to)),dfs2(to,x);
}
inline void mdf(int x,int y,int z)
{	for(;top[x]!=top[y];x=fa[top[x]])
	{	if(dep[top[x]]<dep[top[y]]) swap(x,y);
		int _=fa[top[x]],fuck=query(dfn[top[x]]); if(_) t[_].erase(mp(fuck,top[x])),t[_].insert(mp(fuck+z,top[x]));
		add(dfn[top[x]],dfn[x],z);
	}
	if(dep[x]>dep[y]) swap(x,y);
	int _=fa[x],fuck=query(dfn[x]); if(_&&son[_]!=x) t[_].erase(mp(fuck,x)),t[_].insert(mp(fuck+z,x));
	add(dfn[x],dfn[y],z);
}
int main()
{	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	int n,m,tp,x,y,z; cin>>n>>m;
	for(rint i=1;i<=n;i++) read(b[i]);
	for(rint i=1;i<n;i++) read(x),read(y),adde(x,y),adde(y,x);
	dfs1(1); top[1]=1; dfs2(1);
	for(rint i=1;i<=n;i++) a[i]=b[p[i]]-b[p[i-(i&-i)]];
	while(m--)
	{	read(tp),read(x),read(y);
		if(tp==1) read(z),mdf(x,y,z);
		else
		{	int X=query(dfn[x]),Y,Z;
			t[x].insert(mp(X,x));
			if(fa[x]) Y=query(dfn[fa[x]]),t[x].insert(mp(Y,fa[x]));
			if(son[x]) Z=query(dfn[son[x]]),t[x].insert(mp(Z,son[x]));
			print((*t[x].find_by_order(y-1)).first),el();
			t[x].erase(mp(X,x));
			if(fa[x]) t[x].erase(mp(Y,fa[x]));
			if(son[x]) t[x].erase(mp(Z,son[x]));
		}
	}
	return flush(),0;
}

