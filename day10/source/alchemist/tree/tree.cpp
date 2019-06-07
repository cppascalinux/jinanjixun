#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5;
const int md=1e9+7;
typedef long long ll;

int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}

struct Edge{
	int to,next,val;
	Edge(int a=0,int b=0,int c=0){
		to=a,next=b,val=c;
	}
};

struct Tree{
	Edge l[maxn<<2];
	
	ll dis[maxn];
	int head[maxn],cnt;
	
	inline void Add(int u,int v,int w){
		l[++cnt]=Edge(v,head[u],w);head[u]=cnt;
		l[++cnt]=Edge(u,head[v],w);head[v]=cnt;
	}
	
	inline void Dfs(int u,int f){
		for (register int i=head[u];i;i=l[i].next){
			int v=l[i].to;if (v==f) continue;
			dis[v]=(dis[u]+l[i].val)%md,
			Dfs(v,u);
		}
	}
	
	inline void Read(int n){
		for (register int i=2;i<=n;++i){
			int u=read(),v=read(),w=read();
			Add(u,v,w);
		}
	}
}T1,T2;

int n;
ll ans;

int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	n=read();
	T1.Read(n);T2.Read(n);
	for (register int i=1;i<=n;++i){
		T1.dis[i]=T2.dis[i]=0;
		T1.Dfs(i,0);T2.Dfs(i,0);
		for (register int j=i;j<=n;++j)
		(ans+=T1.dis[j]*T2.dis[j]%md)%=md;
	}
	printf("%lld\n",2ll*ans%md);
}
