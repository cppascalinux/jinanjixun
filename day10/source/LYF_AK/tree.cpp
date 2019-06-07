#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" --------------------------------- "<<endl
inline int read(){
	int nm=0; bool fh=true; char cw=getchar();
	for(;!isdigit(cw);cw=getchar()) fh^=(cw=='-');
	for(;isdigit(cw);cw=getchar()) nm=nm*10+(cw-'0');
	return fh?nm:-nm;
}
#define M 100020
#define mod 1000000007
#define LL long long
inline int add(int x,int y){x+=y;return (x>=mod)?(x-mod):x;}
inline int mns(int x,int y){x-=y;return (x<0)?(x+mod):x;}
inline int mul(int x,int y){return (LL)x*(LL)y%mod;}
inline void upd(int &x,int y){x+=y;(x>=mod)?(x-=mod):0;}
inline void dec(int &x,int y){x-=y;(x<0)?(x+=mod):0;}
int n,m,fa[M],dep[M],tp[M],sz[M],mxs[M],ans,DX,ct[M],cnt,dfn[M];
int S[M],top,tot,cur,F[M],G[M],H[M],T[M],node[M],vl[M]; bool vis[M],vs[M];
struct TREE{
	int fs[M],nt[M<<1],to[M<<1],tmp,cnt,len[M<<1],dis[M];
	inline void link(int x,int y,int ww=0){nt[tmp]=fs[x],fs[x]=tmp,to[tmp]=y,len[tmp++]=ww;}
	inline void ad(int x,int y,int ww){link(x,y,ww),link(y,x,ww);}
	void init(){memset(fs,-1,sizeof(fs)),tmp=cnt=0;}
	inline void edges(){init(); for(int x,y,d,i=1;i<n;i++) x=read(),y=read(),d=read(),ad(x,y,d);}
	void dfs1(int x,int last){
		sz[x]=1,fa[x]=last,dep[x]=dep[last]+1;
		for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]^last){
			dis[to[i]]=add(dis[x],len[i]),dfs1(to[i],x),sz[x]+=sz[to[i]];
			((sz[to[i]]>sz[mxs[x]])?(mxs[x]=to[i]):0);
		}
	}
	void dfs2(int x,int dtp){
		dfn[x]=++cnt; if(mxs[x]>0) dfs2(mxs[x],dtp); tp[x]=dtp;
		for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]^fa[x]&&to[i]^mxs[x]) dfs2(to[i],to[i]);
	}
	inline int lca(int x,int y){
		while(tp[x]!=tp[y]){dep[tp[x]]>dep[tp[y]]?x=fa[tp[x]]:y=fa[tp[y]];}
		return dep[x]>dep[y]?y:x;
	}
	#define rep for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]!=last&&!vis[to[i]])
	inline void init_lca(){dfs1(1,0),dfs2(1,1);}
	void fdrt(int x,int last,int all,int &rt){
		sz[x]=1,mxs[x]=0;
		rep fdrt(to[i],x,all,rt),sz[x]+=sz[to[i]],mxs[x]=max(mxs[x],sz[to[i]]);
		mxs[x]=max(mxs[x],all-sz[x]); if(rt==0||mxs[rt]>mxs[x]) rt=x;
	}
	void build(int x,int last){sz[x]=1;rep dis[to[i]]=add(dis[x],len[i]),build(to[i],x),sz[x]+=sz[to[i]];}
	void fd(int x,int last){vs[node[++cur]=x]=true,vl[x]=dis[x],upd(DX,dis[x]);rep fd(to[i],x);}
	void DP1(int x,int last){
		if(vs[x]) ct[x]=1; else ct[x]=vl[x]=0; G[x]=F[x]=H[x]=T[x]=0;
		for(int i=fs[x];i!=-1;i=nt[i]){
			len[i]=mns(dis[to[i]],dis[x]),DP1(to[i],x),ct[x]+=ct[to[i]],upd(vl[x],vl[to[i]]);
			upd(F[x],F[to[i]]),upd(F[x],mul(ct[to[i]],len[i]));
			upd(H[x],H[to[i]]),upd(H[x],mul(vl[to[i]],len[i]));
		}
	}
	void DP2(int x,int last){
		if(last){
			int tar=add(F[last],G[last]); dec(tar,mul(ct[x],mns(dis[x],dis[last]))); dec(tar,F[x]);
			G[x]=add(tar,mul(mns(dis[x],dis[last]),tot-ct[x]));
			tar=add(H[last],T[last]); dec(tar,mul(vl[x],mns(dis[x],dis[last]))); dec(tar,H[x]);
			T[x]=add(tar,mul(mns(dis[x],dis[last]),mns(DX,vl[x])));
		} for(int i=fs[x];i!=-1;i=nt[i]) DP2(to[i],x);
	}
} fic,X,Y;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
inline int calc(int x,int last){
	while(cur) vl[node[cur]]=0,fic.fs[node[cur]]=-1,vs[node[cur]]=false,--cur; DX=fic.tmp=0;
	X.fd(x,last),sort(node+1,node+cur+1,cmp),S[top=1]=node[1],tot=cur;
	for(int i=2,TP=cur;i<=TP;i++){
		int k=Y.lca(node[i],S[top]); 
		while(top>1&&dfn[S[top-1]]>dfn[k]) fic.link(S[top-1],S[top]),top--;
		if(!top) S[++top]=k,node[++cur]=k;
		else if(S[top-1]!=k&&S[top]!=k) fic.link(k,S[top]),S[top]=k,node[++cur]=k;
		else if(top>1&&S[top-1]==k) fic.link(k,S[top]),top--; S[++top]=node[i];
	}
	while(top>1) fic.link(S[top-1],S[top]),--top; fic.DP1(S[1],0),fic.DP2(S[1],0); int res=0;
	for(int i=1;i<=tot;i++){int x=node[i];upd(res,add(add(H[x],T[x]),mul(X.dis[x],add(F[x],G[x]))));} return res;
}
void solve(int x,int all){
	if(all==1) return; int RT=0;
	X.fdrt(x,0,all,RT),X.dis[x=RT]=0,vis[x]=true;
	X.build(x,0),upd(ans,calc(x,0));
	for(int i=X.fs[x];i!=-1;i=X.nt[i]) if(!vis[X.to[i]])
		dec(ans,calc(X.to[i],x)),solve(X.to[i],sz[X.to[i]]);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(),X.edges(),Y.edges(),Y.dfs1(1,0),Y.dfs2(1,1),fic.init();
	for(int i=1;i<=n;i++) fic.dis[i]=Y.dis[i];
	solve(1,n); printf("%d\n",ans); return 0;
}
