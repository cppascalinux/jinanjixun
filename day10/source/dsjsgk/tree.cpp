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
//#define int long long 
using namespace std;
const int mod = 1e9+7;
inline int read(){int w=1,s=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();} while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();} return w*s;}
inline int pls(int a,int b){a+=b;return a>=mod?a-mod:a;}
inline int mns(int a,int b){a-=b;return a<0?a+mod:a;}
struct node{
	int to,next,w;
};
struct Tree{
	node e[401010];int h[201010],tot;
	inline void add(int from,int to,int w){e[++tot].next=h[from];h[from]=tot;e[tot].to=to;e[tot].w=w;}
}T1,T2,T3,Vt;
int n,cnt;
inline void Build(int now,int ffa) {
	int las=-1;
	for(rint i=T1.h[now];i;i=T1.e[i].next) {
		int to=T1.e[i].to;if(to==ffa) continue;
		Build(to,now);
		if(las==-1) las=now,T3.add(now,to,T1.e[i].w),T3.add(to,now,T1.e[i].w);
		else {
			++cnt;
			T3.add(las,cnt,0);T3.add(cnt,las,0);
			T3.add(cnt,to,T1.e[i].w);T3.add(to,cnt,T1.e[i].w);
			las=cnt;
		}
	}
}
int dis[401010],sz[401100],dep[410100],fa[101010][19],vis[1010010],dfn[401000],tim,out[401010];
int cur,Min,Num;
inline void Pre(int now,int ffa) {
	dep[now]=dep[ffa]+1;fa[now][0]=ffa;dfn[now]=++tim;
	for(rint i=T2.h[now];i;i=T2.e[i].next) {
		int to=T2.e[i].to;if(to==ffa) continue;
		dis[to]=pls(dis[now],T2.e[i].w);
		Pre(to,now);
	}out[now]=tim;
}
inline int Lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);for(rint i=18;~i;--i) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;for(rint i=18;~i;--i) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];return fa[u][0];
}
inline bool isfa(int a,int b) {
	if(dfn[b]<dfn[a]||dfn[b]>out[a]) return 0;
	return 1;
}
inline void get_Bian(int now,int ffa){
	sz[now]=1;int Max;
	for(rint i=T3.h[now];i;i=T3.e[i].next) {
		int to=T3.e[i].to;if(to==ffa) continue;if(vis[i]) continue;
		get_Bian(to,now);sz[now]+=sz[to];
		Max=max(sz[to],Num-sz[to]);
		if(Max<Min) Min=Max,cur=i;
	}
}
vector<int> vec[2];
int res=0,bl[401010],_d[401100];
inline void DFS1(int now,int ffa,int tp) {
	bl[now]=tp;if(now<=n) vec[tp].pb(now);sz[now]=1;
	for(rint i=T3.h[now];i;i=T3.e[i].next) {
		int to=T3.e[i].to;if(to==ffa) continue;if(vis[i]) continue;
		_d[to]=pls(_d[now],T3.e[i].w);
		DFS1(to,now,tp);sz[now]+=sz[to];
	}
}
int tmp[400100],Sta[400100];
inline bool cmp(int i,int j){return dfn[i]<dfn[j];}
int szz[2][401010],diss[2][401010],Ans[2][401010];
inline void dp1(int now,int ffa){
	szz[0][now]=szz[1][now]=diss[0][now]=diss[1][now]=0;
	if(bl[now]<2) szz[bl[now]][now]++;
	for(rint i=Vt.h[now];i;i=Vt.e[i].next) {
		int to=Vt.e[i].to;if(to==ffa) continue;
		dp1(to,now);
		szz[0][now]+=szz[0][to];szz[1][now]+=szz[1][to];
		diss[0][now]=pls(diss[0][now],diss[0][to]);
		diss[0][now]=pls(diss[0][now],1ll*szz[0][to]*Vt.e[i].w%mod);
		diss[1][now]=pls(diss[1][now],diss[1][to]);
		diss[1][now]=pls(diss[1][now],1ll*szz[1][to]*Vt.e[i].w%mod);
	}
}
inline void dp2(int now,int ffa) {
	for(rint i=Vt.h[now];i;i=Vt.e[i].next) {
		int to=Vt.e[i].to;if(to==ffa) continue;
		Ans[0][to]=Ans[0][now];Ans[1][to]=Ans[1][now];
		Ans[0][to]=pls(Ans[0][to],(1ll*Vt.e[i].w*(szz[0][1]-2*szz[0][to])%mod+mod)%mod);
		Ans[1][to]=pls(Ans[1][to],(1ll*Vt.e[i].w*(szz[1][1]-2*szz[1][to])%mod+mod)%mod);
		dp2(to,now);
	}
}
inline void Build_Virtual_Tree() {
	int o=0;
	for(rint i=0;i<SZ(vec[0]);++i) tmp[++o]=vec[0][i];
	for(rint i=0;i<SZ(vec[1]);++i) tmp[++o]=vec[1][i];
	sort(tmp+1,tmp+o+1,cmp);
	int tt=o;
	for(rint i=1;i<tt;++i) {
		int x=Lca(tmp[i],tmp[i+1]);
		if(bl[x]==-1) tmp[++o] = x , bl[x] = 2;
	}
	if(bl[1]==-1) tmp[++o]=1,bl[1]=2;
	sort(tmp+1,tmp+o+1,cmp);
	int top;
	Sta[top=1]=1;
	for(rint i=2;i<=o;++i) {
		while(!isfa(Sta[top],tmp[i])) top--;
		Vt.add(Sta[top],tmp[i],mns(dis[tmp[i]],dis[Sta[top]]));
		Vt.add(tmp[i],Sta[top],mns(dis[tmp[i]],dis[Sta[top]]));
		Sta[++top]=tmp[i]; 
	}
	dp1(1,0);
	Ans[0][1]=diss[0][1];
	Ans[1][1]=diss[1][1];
	dp2(1,0);
	Vt.tot=0;
	for(rint i=1;i<=o;++i) Vt.h[tmp[i]]=0,bl[tmp[i]]=-1;
}
inline void Solve(int now) {
	vis[now]=vis[now^1]=1;
	int u=T3.e[now].to,v=T3.e[now^1].to;
	vec[0].clear();vec[1].clear();
	_d[u]=0;_d[v]=0;
	DFS1(u,v,0);
	DFS1(v,u,1);
	Build_Virtual_Tree();
	int Sum=0;
	for(rint i=0;i<SZ(vec[0]);++i) res=pls(res,2ll*Ans[1][vec[0][i]]*_d[vec[0][i]]%mod),Sum=pls(Sum,Ans[1][vec[0][i]]);
	for(rint i=0;i<SZ(vec[1]);++i) res=pls(res,2ll*Ans[0][vec[1][i]]*_d[vec[1][i]]%mod),Sum=pls(Sum,Ans[0][vec[1][i]]);
	res=pls(res,1ll*T3.e[now].w*Sum%mod);
	cur=0,Min=1e9,Num=sz[u];
	get_Bian(u,0);
	if(cur) Solve(cur);
	cur=0,Min=1e9,Num=sz[v];
	get_Bian(v,0);
	if(cur) Solve(cur);
}
signed main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();cnt=n;
	memset(bl,-1,sizeof(bl));
	for(rint i=1;i<n;++i) {
		int u=read(),v=read(),w=read();
		T1.add(u,v,w);T1.add(v,u,w);
	}
	for(rint i=1;i<n;++i) {
		int u=read(),v=read(),w=read();
		T2.add(u,v,w);T2.add(v,u,w);
	}
	T3.tot=1;
	Build(1,0);
	Pre(1,0);
	for(rint i=1;i<=18;++i) for(rint j=1;j<=n;++j) fa[j][i]=fa[fa[j][i-1]][i-1];
	Num=cnt,Min=1e9;
	get_Bian(1,0);
	Solve(cur);
	cout<<(res%mod+mod)%mod<<"\n";
	return 0;
}	
