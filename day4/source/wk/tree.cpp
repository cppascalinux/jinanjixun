#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct E{int u,nxt;}e[N*2];
int a[N],b[N],p[N],fa[N],siz[N],son[N],ord[N],pre[N],nxt[N],dep[N],top[N],num,n;
inline void add(int x,int y){e[++num]=(E){y,p[x]},p[x]=num;}
void dfs1(int s){
	int sz=0;
	siz[s]=1;
	for(int i=p[s];i;i=e[i].nxt) if(fa[s]!=e[i].u){
		fa[e[i].u]=s,dep[e[i].u]=dep[s]+1,dfs1(e[i].u),siz[s]+=siz[e[i].u];
		if(siz[e[i].u]>sz) sz=siz[e[i].u],son[s]=e[i].u;
	}
}
void dfs2(int s){
	ord[s]=++num,top[s]=son[fa[s]]==s?top[fa[s]]:s;
	if(son[s]) dfs2(son[s]);
	for(int i=p[s];i;i=e[i].nxt) if(fa[s]!=e[i].u&&son[s]!=e[i].u) dfs2(e[i].u);
}
int lca(int x,int y){
	while(top[x]!=top[y]){if(dep[x]<dep[y]) swap(x,y);x=fa[top[x]];}
	return dep[x]<dep[y]?x:y;
}
struct SGT{
	int T[N*4],tag[N*4];
	inline void push(int r,int s,int t){
		if(!tag[r]) return;
		int mid=s+t>>1,r1=r<<1,r2=r1|1;
		T[r1]=tag[r]==2?mid-s+1:0,T[r2]=tag[r]==2?t-mid:0;
		tag[r1]=tag[r],tag[r2]=tag[r],tag[r]=0;
	}
	void UPD(int r,int ns,int nt,int s,int t,bool v){
		if(ns>t||nt<s) return;
		if(ns>=s&&nt<=t){T[r]=v*(nt-ns+1),tag[r]=v+1;return;}
		int mid=ns+nt>>1,r1=r<<1,r2=r1|1;
		push(r,ns,nt),UPD(r1,ns,mid,s,t,v),UPD(r2,mid+1,nt,s,t,v),T[r]=T[r1]+T[r2];
	}
	int QRY(int r,int ns,int nt,int s,int t){
		if(ns>t||nt<s) return 0;
		if(ns>=s&&nt<=t) return T[r];
		int mid=ns+nt>>1;
		push(r,ns,nt);
		return QRY(r<<1,ns,mid,s,t)+QRY(r<<1|1,mid+1,nt,s,t);
	}
	void upd(int x,int y,bool v){
		while(top[x]!=top[y]){
			if(dep[x]<dep[y]) swap(x,y);
			UPD(1,1,n,ord[top[x]],ord[x],v),x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		UPD(1,1,n,ord[x],ord[y],v);
	}
	int qry(int x,int y){
		int s=0;
		while(top[x]!=top[y]){
			if(dep[x]<dep[y]) swap(x,y);
			s+=QRY(1,1,n,ord[top[x]],ord[x]),x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		return s+QRY(1,1,n,ord[x],ord[y]);
	}
}nq,mq;
int main(){
	freopen("tree.in","r",stdin),freopen("tree.out","w",stdout);
	int m,q,X,Y,x,y,z,s1=0,s2=0,s;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	for(int i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]),nxt[i]=i+1,pre[i]=i-1;
	nxt[0]=1,dep[1]=1,num=0,dfs1(1),dfs2(1);
	while(q--){
		scanf("%d%d",&X,&Y);
		for(int i=nxt[pre[X]];i<=Y;i=nxt[i]){
			x=a[i],y=b[i],z=lca(x,y),s=mq.qry(z,z),m=dep[x]+dep[y]-2*dep[z]+1;
			s1-=nq.qry(x,y),s1+=m,nq.upd(x,y,1);
			s2-=mq.qry(x,y),s2+=m-!s,mq.upd(x,y,1),mq.upd(z,z,s);
			nxt[pre[i]]=nxt[i],pre[nxt[i]]=pre[i];
		}
		printf("%d\n",s1-s2);
	}
	return 0;
}
