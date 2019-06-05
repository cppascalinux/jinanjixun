#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp> 
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define debug(x) cerr<<#x<<" = "<<x
#define sp <<"  "
#define el <<endl
#define fgx cerr<<" -------------------------- "<<endl
#define LL long long
namespace IO{
	const int BS=(1<<24)+5; int Top=0;
	char Buffer[BS],OT[BS],*OS=OT,*HD,*TL,SS[20]; const char *fin=OT+BS-1;
	char Getchar(){if(HD==TL){TL=(HD=Buffer)+fread(Buffer,1,BS,stdin);} return (HD==TL)?EOF:*HD++;}
	void flush(){fwrite(OT,1,OS-OT,stdout),OS=OT;}
	void Putchar(char c){*OS++ =c;if(OS==fin)flush();}
	void write(int x){
		if(!x){Putchar('0');return;} if(x<0) x=-x,Putchar('-');
		while(x) SS[++Top]=x%10,x/=10;
		while(Top) Putchar(SS[Top]+'0'),--Top;
	}
	inline int read(){
		int nm=0; bool fh=true; char cw=Getchar();
		for(;!isdigit(cw);cw=Getchar()) fh^=(cw=='-');
		for(;isdigit(cw);cw=Getchar()) nm=nm*10+(cw-'0');
		return fh?nm:-nm;
	}
} using namespace IO;
#define M 1000020
#define pii pair<int,int>
#define mp make_pair
#define val first
tree<pii,null_type,less<pii >,rb_tree_tag,tree_order_statistics_node_update> t[M];
int n,m,fs[M],to[M<<1],nt[M<<1],tmp,vl[M],RT,pr[M];
int sz[M],mxs[M],tp[M],dep[M],fa[M],dfn[M],tk[M],cnt,c[M];
inline void link(int x,int y){nt[tmp]=fs[x],fs[x]=tmp,to[tmp++]=y;}
inline void add(int k,int dt){for(;k<=n;k+=(k&-k))c[k]+=dt;}
inline int calc(int &x,int res=0){
	if(!x) return 2147000000;
	for(int k=dfn[x]+sz[x]-1;k;k-=k&-k) res+=c[k];
	for(int k=dfn[x]-1;k;k-=k&-k) res-=c[k]; return res;
}
void dfs1(int x,int last){
	dep[x]=dep[fa[x]=last]+(sz[x]=1);
	for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]^last){
		dfs1(to[i],x),sz[x]+=sz[to[i]];
		if(sz[mxs[x]]<sz[to[i]]) mxs[x]=to[i];
	}
}
void dfs2(int x,int dtp){
	tp[x]=dtp,dfn[x]=++cnt,tk[cnt]=x; if(mxs[x]) dfs2(mxs[x],dtp);
	for(int i=fs[x];i!=-1;i=nt[i]) if(to[i]!=fa[x]&&to[i]!=mxs[x]) dfs2(to[i],to[i]),t[x].insert(mp(vl[to[i]],to[i]));
}
void mdf(int &x,int &y,int dt){
	int _x=x,_y=y;
	for(int pre;tp[x]!=tp[y];x=fa[x]){
		if(dep[tp[x]]<dep[tp[y]]) swap(x,y);
		pre=calc(x=tp[x]),t[fa[x]].erase(t[fa[x]].find(mp(pre,x)));
		t[fa[x]].insert(mp(pre+dt,x));
	}
	if(dep[x]>dep[y]) swap(x,y);
	if(x==tp[x]&&fa[x]>0){
		int pre=calc(x);t[fa[x]].erase(t[fa[x]].find(mp(pre,x)));
		t[fa[x]].insert(mp(pre+dt,x));
	}
	add(dfn[_x],dt),add(dfn[_y],dt),add(dfn[x],-dt);
	if(fa[x]>0) add(dfn[fa[x]],-dt);
}
inline int getans(int x,int y){
	if(mxs[x]) t[x].insert(mp(calc(mxs[x]),mxs[x]));
	if(fa[x]) t[x].insert(mp(calc(fa[x]),fa[x]));
	t[x].insert(mp(calc(x),x)); int res=(*t[x].find_by_order(y-1)).val;
	if(mxs[x]) t[x].erase(mp(calc(mxs[x]),mxs[x]));
	if(fa[x]) t[x].erase(mp(calc(fa[x]),fa[x]));
	t[x].erase(mp(calc(x),x));return res;
}
int main(){
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	n=read(),m=read(),memset(fs,-1,sizeof(fs));
	for(int i=1;i<=n;i++) vl[i]=read();
	for(int i=1,x,y;i<n;i++) x=read(),y=read(),link(x,y),link(y,x);
	dfs1(1,0),dfs2(1,1),mxs[0]=1,vl[0]=2140000000;
	for(int x=1;x<=n;x++){c[dfn[x]]+=vl[x];if(fa[x])c[dfn[fa[x]]]-=vl[x];}
	for(int i=1;i<=n;i++) c[i]+=c[i-1];
	for(int i=n;i>0;i--) c[i]-=c[i-(i&-i)];
//	for(int x=1;x<=n;x++) debug(x)sp,debug(fa[x])sp,debug(sz[x])sp,debug(tp[x])sp,debug(dfn[x])sp,debug(calc(x))el;
	for(int typ,x,y,v;m;--m){
		typ=read(),x=read(),y=read();
		if(typ==1) mdf(x,y,read());
		else write(getans(x,y)),Putchar('\n');
	} flush(); return 0;
}

/*

5 5
3 4 3 1 3
1 2
1 3
2 4
3 5
2 1 3
2 1 1
1 1 1 1
2 1 3
1 4 1 1

*/
