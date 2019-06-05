#include<bits/stdc++.h>
#define ll long long
#define mk make_pair
#define pb push_back
#define pa pair<int,int>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<"\n"
#define fir first
#define sec second
#define SZ(x) (x).size()
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
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
typedef tree<pa,null_type,less<pa >,rb_tree_tag,tree_order_statistics_node_update> rbt;
struct node{int to,next;} e[2010101];
rbt S[1010000];int n,m,val[1010010],h[1010010],tot,sz[1010100],hson[1010010],dfn[1010100],tim,Seq[1010000],top[1010100],fa[1010100][21],dep[1001000];
inline void add(int from,int to){e[++tot].next=h[from];h[from]=tot;e[tot].to=to;}
struct BIT{
	int Sum[1010010];
	inline int lowbit(int x) {return x&(-x);}
	inline void add(int pos,int d){while(pos<=n) {Sum[pos]+=d;pos+=(pos&(-pos));}}
	inline int Qry(int pos){int res=0;while(pos) res+=Sum[pos],pos-=(pos&(-pos));return res;}
	inline void Gao(int l,int r,int d){
		if(l>r) return ;
//		debug(l);debug(r);debug(d);
		add(l,d);add(r+1,-d);
	}
}fw;
inline void DFS1(int now,int ffa){
	sz[now]=1;dep[now]=dep[ffa]+1;
	for(rint i=h[now];i;i=e[i].next) {
		int to=e[i].to;if(to==ffa) continue;
		DFS1(to,now);sz[now]+=sz[to];
		if(sz[to]>sz[hson[now]]) hson[now]=to;
	}
}
inline void DFS2(int now,int ffa,int tp){
	top[now]=tp;dfn[now]=++tim;Seq[tim]=now;fa[now][0]=ffa;
	if(hson[now]) DFS2(hson[now],now,tp);
	for(rint i=h[now];i;i=e[i].next) {
		int to=e[i].to;if(to==ffa) continue;if(to==hson[now]) continue;
		DFS2(to,now,to); 
	}
}
inline int Lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);for(rint i=20;i>=0;--i) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;for(rint i=20;i>=0;--i) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i]; 
	return fa[u][0];
}
inline int Jump(int u,int v){
	for(rint i=20;i>=0;--i) if(dep[fa[u][i]]>dep[v]) u=fa[u][i];
	return u;
}
inline void DFS3(int now,int ffa) {
	for(rint i=h[now];i;i=e[i].next) {
		int to=e[i].to;if(to==ffa) continue;
		DFS3(to,now);
		if(hson[now]!=to) S[now].insert(mk(val[to],to));
	}
}
inline void Gao(int x,int y,int z){
	while(dep[top[x]]>dep[y]){
		int od=fw.Qry(dfn[top[x]]);
		fw.Gao(dfn[top[x]],dfn[x],z);
		int nw=fw.Qry(dfn[top[x]]);
		int tt=fa[top[x]][0];
		if(tt) {
			S[tt].erase(mk(od,top[x]));
			S[tt].insert(mk(nw,top[x]));
		}
		x=fa[top[x]][0];
	}
	int od=fw.Qry(dfn[top[x]]);
	fw.Gao(dfn[y],dfn[x],z);
	int nw=fw.Qry(dfn[top[x]]);
	int tt=fa[top[x]][0];
	if(top[x]==y) {
		if(tt) {
			S[tt].erase(mk(od,top[x]));
			S[tt].insert(mk(nw,top[x]));
		}
	}
}
inline int Qry(int x,int y){
//	debug(x);
//	debug(S[x].size());
	if(hson[x]) {
		S[x].insert(mk(fw.Qry(dfn[hson[x]]),hson[x]));
	}
	if(fa[x][0]) {
		S[x].insert(mk(fw.Qry(dfn[fa[x][0]]),fa[x][0]));
	}
	S[x].insert(mk(fw.Qry(dfn[x]),x));
//	S[x].erase();
//	for(auto xx:S[x]) debug(xx.sec);
	int t=(*S[x].find_by_order(y-1)).fir;
	if(hson[x]) {
		S[x].erase(mk(fw.Qry(dfn[hson[x]]),hson[x]));
	}
	if(fa[x][0]) {
		S[x].erase(mk(fw.Qry(dfn[fa[x][0]]),fa[x][0]));
	}
	S[x].erase(mk(fw.Qry(dfn[x]),x));
	return t;
}
char s[20101000];
int ttop=0;
inline void DFS(int x){
	if(!x) return ;
	DFS(x/10);
	s[++ttop]=x%10;
}
inline void Print(int x) {
	if(x==0) {
		s[++ttop]='0';
	}
	else {
		DFS(x);
	}
	s[++ttop]='\n';
}
int main(){
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	n=read(),m=read();
	for(rint i=1;i<=n;++i) val[i]=read();
	for(rint i=1;i<n;++i) {
		int x,y;x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	DFS1(1,0);DFS2(1,0,1);
	for(rint i=1;i<=20;++i) for(rint j=1;j<=n;++j) fa[j][i]=fa[fa[j][i-1]][i-1];
	DFS3(1,0);
	for(rint i=1;i<=n;++i) 
		fw.Gao(dfn[i],dfn[i],val[i]);
	for(rint i=1;i<=m;++i) {
		int opt;opt=read();
		if(opt==1) {
			int x,y,z;x=read(),y=read(),z=read();
			int lca=Lca(x,y);
			if(dep[x]<dep[y]) swap(x,y);
			if(y==lca) Gao(x,y,z);
			else {
				Gao(x,lca,z);
				Gao(y,Jump(y,lca),z);
			}
		}
		else {
			int x,y;x=read(),y=read();
			write(Qry(x,y));Putchar('\n');
		}
	}
	flush();
//	fwrite(s+1,1,ttop,stdout);
	return 0;
}

