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
const int N=1000010;
namespace BST_space{
	const int T=4000010;
	struct RND{
		ull x;inline ull operator()() { return x=((((x>>7)^((x+12321)<<3))^998244353)+1000000007)^19260817; }
	}rnd;int stk[T],top;
	int cnt[T],sz[T],val[T],ch[T][2];ull key[T];
	inline int push_up(int x) { return sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x]; }
	inline int setc(int x,int y,int z) { if(!x) return 0;ch[x][z]=y;return push_up(x); }
	inline int _init() { for(int i=T-1;i;i--) stk[++top]=i;return 0; }
	inline int new_node(int w)
	{
		int x=stk[top--];cnt[x]=sz[x]=1,val[x]=w,key[x]=rnd();return x;
	}
	inline int _merge(int x,int y)
	{
		if(!x||!y) return x+y;
		if(key[x]<key[y]) return setc(x,_merge(ch[x][1],y),1),x;
		return setc(y,_merge(x,ch[y][0]),0),y;
	}
	inline pii splitv(int x,int v)
	{
		if(!x) return mp(0,0);pii t;
		if(v<val[x]) return t=splitv(ch[x][0],v),setc(x,t.sec,0),mp(t.fir,x);
		return t=splitv(ch[x][1],v),setc(x,t.fir,1),mp(x,t.sec);
	}
	inline pii splitk(int x,int k)
	{
		if(!x||sz[x]<=k) return mp(x,0);if(!k) return mp(0,x);pii t;
		if(k<=sz[ch[x][0]]) return t=splitk(ch[x][0],k),setc(x,t.sec,0),mp(t.fir,x);
		return t=splitk(ch[x][1],max(k-sz[ch[x][0]]-cnt[x],0)),setc(x,t.fir,1),mp(x,t.sec);
	}
	struct BST{
		int rt;BST() { rt=0; }
		inline int ins(int w)
		{
			pii a=splitv(rt,w),b=splitv(a.fir,w-1);
			if(b.sec) cnt[b.sec]++,sz[b.sec]++;
			else b.sec=new_node(w);
			rt=_merge(_merge(b.fir,b.sec),a.sec);
			return 0;
		}
		inline int del(int w)
		{
			pii a=splitv(rt,w),b=splitv(a.fir,w-1);
			assert(b.sec),cnt[b.sec]--,sz[b.sec]--;
			if(cnt[b.sec]) b.fir=_merge(b.fir,b.sec);
			else stk[++top]=b.sec;
			return rt=_merge(b.fir,a.sec);
		}
		inline int query(int k)
		{
			pii t=splitk(rt,k);int x=t.fir,ans=0;
			while(ch[x][1]) x=ch[x][1];ans=val[x];
			return rt=_merge(t.fir,t.sec),ans;
		}
	}s[N];
}using BST_space::s;
struct BIT{
	lint b[N];int n;
	inline int build(int _n) { for(int i=n=_n;i;i--) b[i]-=b[i^(i&-i)];return 0; }
	inline int update(int p,int v) { for(;p<=n;p+=p&-p) b[p]+=v;return 0; }
	inline int update(int s,int t,int v) { return (s<=t?update(s,v),update(t+1,-v):0); }
	inline int query(int p) { lint ans=0;for(;p;p^=p&-p) ans+=b[p];return int(ans); }
}b;
struct edges{
	int to,pre;
}e[N<<1];int h[N],etop,d[N],fa[N],sz[N],son[N],top[N],in[N],bot[N],dfc,val[N];
inline int add_edge(int u,int v) { return e[++etop].to=v,e[etop].pre=h[u],h[u]=etop; }
inline int fir_dfs(int x,int f=0)
{
	d[x]=d[fa[x]=f]+1,sz[x]=1;
	for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^f)
		sz[x]+=fir_dfs(y,x),(sz[y]>sz[son[x]]?son[x]=y:0);
	return sz[x];
}
map<int,int> vis[N];
inline int sec_dfs(int x)
{
	in[x]=++dfc;
	if(son[x]) son[x][top]=top[x],sec_dfs(son[x]),bot[x]=bot[son[x]];
	else bot[x]=x;
	for(int i=h[x],y;i;i=e[i].pre)
		if((y=e[i].to)!=fa[x]&&e[i].to!=son[x])
			top[y]=y,sec_dfs(y),s[x].ins(val[y]),vis[x][val[y]]++;
	return b.b[in[x]]=val[x],0;
}
inline int getv(int x) { return b.query(in[x]); }
inline int update(int x,int y,int w)
{
	for(;top[x]^top[y];x=top[x][fa])
	{
		if(top[x][d]<top[y][d]) swap(x,y);int z=top[x];
		s[fa[z]].del(val[z]),s[fa[z]].ins(val[z]+=w);
		b.update(in[z],in[x],w);
	}
	if(in[x]>in[y]) swap(x,y);
	if(x==top[x]&&fa[x]) s[fa[x]].del(val[x]),s[fa[x]].ins(val[x]+=w);
	return b.update(in[x],in[y],w);
}
inline int query(int x,int k)
{
	int vs=0,vf=0,vx=0;s[x].ins(vx=getv(x));
	if(son[x]) s[x].ins(vs=getv(son[x]));
	if(fa[x]) s[x].ins(vf=getv(fa[x]));
	int ans=s[x].query(k);s[x].del(vx);
	if(son[x]) s[x].del(vs);if(fa[x]) s[x].del(vf);
	return ans;
}
char ss[1000010*20],tt[20];int ssl,ttl;
inline int print(int x)
{
	if(!x) ss[++ssl]='0';for(ttl=0;x;x/=10) tt[++ttl]=char(x%10+'0');
	for(;ttl;ttl--) ss[++ssl]=tt[ttl];return ss[++ssl]='\n';
}
int main()
{
	freopen("yuki.in","r",stdin),
	freopen("yuki.out","w",stdout);
	int n=inn(),m=inn(),x,y;rep(i,1,n) val[i]=inn();
	rep(i,1,n-1) x=inn(),y=inn(),add_edge(x,y),add_edge(y,x);
	BST_space::_init(),fir_dfs(1),top[1]=1,sec_dfs(1),b.build(n);
	while(m--)
	{
		int tp=inn(),x,y,w;
		if(tp==1) x=inn(),y=inn(),w=inn(),update(x,y,w);
		else x=inn(),y=inn(),print(query(x,y));
	}
	return fwrite(ss+1,1,ssl,stdout),0;
}
