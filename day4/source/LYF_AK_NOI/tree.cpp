#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define LL long long
#define fgx cerr<<" ---------------------------------------------- "<<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return nm*fh;
}
#define M 200020
int n,m,q,fs[M],val[M<<1],nt[M<<1],to[M<<1],tmp,x1[M],x2[M],ans[M],dep[M],tp[M],dfn[M],fa[M];
struct Q{int l,r,id,res;inline void gtin(int ID){l=read(),r=read(),id=ID;}}t[M]; int tt;
bool cmp(Q i,Q j){return i.r<j.r;}

namespace Ary{
	int con[M<<2];
	inline void init(){memset(con,0,sizeof(con));}
	inline void add(int l,int r,int k){
		r++;
		while(l<=m) con[l]+=k,l+=(l&-l);
		while(r<=m) con[r]-=k,r+=(r&-r);
	}
	inline int qry(int k,int res=0){while(k)res+=con[k],k-=(k&-k);return res;}
}
namespace Tree{
	int sz[M],mxs[M],cnt,sm[M<<2],tg[M<<2];
	inline void link(int x,int y){nt[tmp]=fs[x],fs[x]=tmp,to[tmp++]=y;}
	void dfs1(int x,int last){
		sz[x]=1,dep[x]=dep[fa[x]=last]+1;
		for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]^last){
			dfs1(to[i],x),sz[x]+=sz[to[i]];
			if(sz[to[i]]>sz[mxs[x]]) mxs[x]=to[i];
		}
	}
	void dfs2(int x,int dtp){
		tp[x]=dtp,val[dfn[x]=++cnt]=(x<=n?1:-1); if(mxs[x]) dfs2(mxs[x],dtp);
		for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]!=mxs[x]&&to[i]!=fa[x]) dfs2(to[i],to[i]);
	}
	inline void pushdown(int x){if(tg[x]>=0)tg[x<<1]=tg[x<<1|1]=tg[x],tg[x]=-1;}
	inline void pushup(int x){if(tg[x<<1]==tg[x<<1|1]) tg[x]=tg[x<<1]; else tg[x]=-1;}
	inline void build(int x,int l,int r){
		if(l==r){sm[x]=val[l];return;} int mid=((l+r)>>1);
		build(x<<1,l,mid),build(x<<1|1,mid+1,r),sm[x]=sm[x<<1]+sm[x<<1|1];
	}
	inline void cov(int x,int l,int r,int ls,int rs,int tim){
		if(ls<=l&&r<=rs&&tg[x]!=-1){Ary::add(tg[x]+1,tim,sm[x]),tg[x]=tim;return;}
		if(r<ls||rs<l) return; int mid=((l+r)>>1); pushdown(x);
		cov(x<<1,l,mid,ls,rs,tim),cov(x<<1|1,mid+1,r,ls,rs,tim),pushup(x);
	}
	inline void init(){
		for(int i=1,x,y;i<n;i++) x=read(),y=read(),link(x,i+n),link(i+n,x),link(y,i+n),link(i+n,y);
		dfs1(1,0),dfs2(1,1),build(1,1,tt);
	}
}
inline void calc(int x,int y,int tim){
	for(;tp[x]!=tp[y];Tree::cov(1,1,tt,dfn[tp[x]],dfn[x],tim),x=fa[tp[x]]) if(dep[tp[x]]<dep[tp[y]]) swap(x,y);
	if(dep[x]>dep[y]) swap(x,y); Tree::cov(1,1,tt,dfn[x],dfn[y],tim);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(),m=read(),q=read(),memset(fs,-1,sizeof(fs));
	tt=(n<<1)-1,Tree::init(),Ary::init();
	for(int i=1;i<=m;i++) x1[i]=read(),x2[i]=read();
	for(int i=1;i<=q;i++) t[i].gtin(i); sort(t+1,t+q+1,cmp);
	for(int i=1,nw=1;i<=m;i++){
		calc(x1[i],x2[i],i);
		while(nw<=q&&t[nw].r==i) ans[t[nw].id]=Ary::qry(t[nw].l),nw++;
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
