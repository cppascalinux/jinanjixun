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
using namespace std;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
struct node{
	int to,next;
}e[1010100];
int n,m,q,tot,h[1010100],fa[100010][20],dep[100200],x[101010],y[101010];
int Sum1[1010],Sum2[1010];
inline void add(int from,int to){e[++tot].next=h[from];h[from]=tot;e[tot].to=to;}
inline void Pre(int now,int ffa){
	fa[now][0]=ffa;dep[now]=dep[ffa]+1;
//	debug(fa[now][0]);
	for(rint i=h[now];i;i=e[i].next) {
		int to=e[i].to;if(to==ffa) continue;
		Pre(to,now);
	}
}
inline int Lca(int u,int v) {
	if(dep[u]<dep[v]) swap(u,v);for(rint i=19;i>=0;--i) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;for(rint i=19;i>=0;--i) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];return fa[u][0];
}int tot1=0,tot2=0;
inline void DFS(int now,int ffa){
	for(rint i=h[now];i;i=e[i].next){
		int to=e[i].to;if(to==ffa) continue;
		DFS(to,now);Sum1[now]+=Sum1[to];Sum2[now]+=Sum2[to];
	}
	if(Sum1[now]) tot1++;
	if(Sum2[now]) tot2++;
}
vector<pa> vec[100010];
int Ans[1010100],f[101000],vis[100101];
inline int find(int x) {if(x==f[x]) {return x;}return f[x]=find(f[x]);}
inline void Gao(int x,int top,int p){
	//debug(x);debug(top);
//	for(rint i=1;i<=n;++i) debug(f[i]);
//	debug(f[x]);
	while(1){
		x=find(x);//debug(x);
		int o=fa[x][0];
		if(!vis[x]) Ans[p]++,vis[x]=1; 
		if(!o) break;
		
		if(dep[o]<dep[top]) return ;
		f[x]=find(o);
		x=o;Ans[p]--;
	}
}
int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read(),m=read(),q=read();
	for(rint i=1;i<n;++i) {
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	for(rint i=1;i<=m;++i) {
		x[i]=read(),y[i]=read();
	}
	Pre(1,0);
	for(rint i=1;i<=19;++i) {
		for(rint j=1;j<=n;++j) {
			fa[j][i]=fa[fa[j][i-1]][i-1];
		}
	}
	if(n<=1000&&m<=1000&&q<=1000) {
		for(rint i=1;i<=q;++i) {
			int L=read(),R=read();
			tot1=0,tot2=0;
			memset(Sum1,0,sizeof(Sum1));
			memset(Sum2,0,sizeof(Sum2));
			for(rint j=L;j<=R;++j) {
				int lca=Lca(y[j],x[j]);
//				debug(lca);
				Sum1[x[j]]++;
				Sum1[y[j]]++;
				Sum1[fa[lca][0]]-=2;
				Sum2[x[j]]++;
				Sum2[y[j]]++;
				Sum2[lca]-=2;
			}
			DFS(1,0);
			cout<<tot1-tot2<<"\n";
		}
	}
	else 
	{
		for(rint i=1;i<=n;++i) {
			f[i]=i;
		}
		for(rint i=1;i<=m;++i) {
			int lca=Lca(y[i],x[i]);
			Gao(x[i],lca,i);
			Gao(y[i],lca,i);
		}
		for(rint i=1;i<=m;++i) Ans[i]+=Ans[i-1];
		for(rint i=1;i<=q;++i) {
			int L=read(),R=read();
			cout<<Ans[R]<<"\n";
		}
	}
	return 0;
}	
