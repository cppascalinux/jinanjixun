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
#define gc getchar()
#define debug(x) cerr<<#x<<"="<<x
#define sp <<" "
#define ln <<endl
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
inline int inn()
{
	int x,ch;while((ch=gc)<'0'||ch>'9');
	x=ch^'0';while((ch=gc)>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');return x;
}
const int N=200010,SIG=27,INF=INT_MAX/10,inf=INT_MIN/10;
namespace seg{
	const int T=400010;
	int n,rt,node_cnt,ch[T][2],fa[T],s[T];
	inline int clear() { return rt=0,node_cnt=0; }
	inline int new_node() { int x=++node_cnt;ch[x][0]=ch[x][1]=fa[x]=0,s[x]=0;return x; }
	inline int update(int &x,int l,int r,int p,int v)
	{
		if(!x) x=new_node();s[x]+=v;
		if(l==r) return 0;int mid=(l+r)>>1;
		if(p<=mid) update(ch[x][0],l,mid,p,v);
		else update(ch[x][1],mid+1,r,p,v);
		return 0;
	}
	inline int update(int p,int v) { return update(rt,1,n,p,v); }
	inline int query(int x,int l,int r,int k)
	{
		if(s[x]<=k) return r;if(l==r) return l-1;int mid=(l+r)>>1;
		if(k<s[ch[x][0]]) return query(ch[x][0],l,mid,k);
		return query(ch[x][1],mid+1,r,k-s[ch[x][0]]);
	}
	inline int query(int k,int s,int t)
	{
		int r=query(rt,1,n,k),l=query(rt,1,n,k-1)+1;
		return l=max(l,s),r=min(r,t),max(r-l+1,0);
	}
}
struct edges{
	int to,pre;
}e[N<<1];int h[N],etop;
inline int add_edge(int u,int v) { return e[++etop].to=v,e[etop].pre=h[u],h[u]=etop; }
struct SAM{
	int rt,las,node_cnt,fa[N],val[N],sz[N],ch[N][SIG],ans[N],in[N],out[N],r[N],son[N],tms[N],dfc;set<int> s;
	SAM() { node_cnt=0,rt=las=new_node(0); }
	inline int new_node(int v) { int x=++node_cnt;return val[x]=v,x; }
	inline int extend(int w,int _r)
	{
		int p=las,np=new_node(val[p]+1);
		while(p&&!ch[p][w]) ch[p][w]=np,p=fa[p];
		if(!p) fa[np]=rt;
		else{
			int q=ch[p][w],v=val[p]+1;
			if(val[q]==v) fa[np]=q;
			else{
				int nq=new_node(v);fa[nq]=fa[q];
				fa[q]=fa[np]=nq,memcpy(ch[nq],ch[q],sizeof ch[q]);
				while(p&&ch[p][w]==q) ch[p][w]=nq,p=fa[p];
			}
		}
		return sz[np]++,r[np]=_r,las=np;
	}
	inline int ins(int x)
	{
		sit nxt=s.lower_bound(x),las=nxt;las--;
		int l=*las,r=*nxt;
		if(l!=inf) seg::update(x-l,1);
		if(r!=INF) seg::update(r-x,1);
		if(l!=inf&&r!=INF) seg::update(r-l,-1);
		return s.insert(x),0;
	}
	inline int dfs(int x,int k)
	{
		for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^son[x])
			dfs(y,k),seg::clear(),set<int>().swap(s);
		if(son[x])
		{
			dfs(son[x],k),(r[x]?ins(r[x]):0);
			for(int i=h[x],y;i;i=e[i].pre) if((y=e[i].to)^son[x])
				rep(t,in[y],out[y]) ins(tms[t]);
		}
		else s.insert(inf),s.insert(INF),(r[x]?s.insert(r[x]),0:0);
		if(x!=rt&&sz[x]>=k) ans[x]=seg::query(sz[x]-k,val[fa[x]]+1,val[x]);
		return 0;
	}
	inline int fir_dfs(int x)
	{
		in[x]=dfc+1;if(r[x]) tms[++dfc]=r[x];
		for(int i=h[x],y;i;i=e[i].pre)
			sz[x]+=fir_dfs(y=e[i].to),(sz[y]>sz[son[x]]?son[x]=y:0);
		return out[x]=dfc,sz[x];
	}
	inline lint solve(int k)
	{
		rep(i,2,node_cnt) add_edge(fa[i],i);
		fir_dfs(rt),dfs(rt,k);lint res=0;
		rep(i,1,node_cnt) res+=ans[i];return res;
	}
}s;
char str[N];
int main()
{
	freopen("two.in","r",stdin),freopen("two.out","w",stdout);
	scanf("%s",str+1);int n=(int)strlen(str+1),k=inn();
	rep(i,1,n) s.extend(str[i]-'a',i);seg::n=n;
	return !printf("%lld\n",s.solve(k));
}
