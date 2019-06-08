#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<queue>
#define qmin(x,y) (x=min(x,y))
#define qmax(x,y) (x=max(x,y))
#define pir pair<int,int>
#define fr first
#define sc second
#define mp(x,y) make_pair(x,y)
#define vic vector<int>
#define vit vic::iterator
#define rsort(x,y) sort(x,y),reverse(x,y)
using namespace std;

inline char gc() {
	return  getchar();
}

template<typename T1>
int read(T1 &a) {
	a=0;
	char ch=gc();
	T1 f=1;
	while(!isdigit(ch)) {
		if(ch==EOF) return 0;
		if(ch=='-') f=-1;
		ch=gc();
	}
	while(isdigit(ch)) {
		a=a*10+ch-'0';
		ch=gc();
	}
	a=a*f;
	return 1;
}

template<typename T1,typename T2>
int read(T1 &a,T2 &b) {
	return read(a)+read(b);
}

template<typename T1,typename T2,typename T3>
int read(T1 &a,T2 &b,T3 &c) {
	return read(a,b)+read(c);
}

typedef long long ll;
const int Maxn=31000;
const int inf=0x3f3f3f3f;
const int mod=1000000007;

inline int modd(int x) {
	return x>=mod?x-mod:x;
}

int dis[Maxn],dis2[Maxn],vis[Maxn],n,u,v,wi;
int q[Maxn],top;

struct tree {
	int to[Maxn<<1],nxt[Maxn<<1],first[Maxn],w[Maxn],tot;
	
	tree () {tot=1;}

	inline void add(int u,int v,int wi) {
		to[tot]=v;
		nxt[tot]=first[u];
		w[tot]=wi;
		first[u]=tot++;
		to[tot]=u;
		nxt[tot]=first[v];
		w[tot]=wi;
		first[v]=tot++;
	}

	inline void pre(int now) {
		q[top=1]=now;
		dis[now]=0; vis[now]=1;
		while(top) {
			now=q[top--];
			for(int i=first[now];i;i=nxt[i]) if(!vis[to[i]]) {
				dis[to[i]]=modd(dis[now]+w[i]);
				vis[to[i]]=1;
				q[++top]=to[i];
			}
		}
	}
	
	inline void work(int now) {
		q[top=1]=now;
		dis2[now]=0; vis[now]=0;
		while(top) {
			now=q[top--];
			for(int i=first[now];i;i=nxt[i]) if(vis[to[i]]) {
				dis2[to[i]]=modd(dis2[now]+w[i]);
				vis[to[i]]=0;
				q[++top]=to[i];
			}
		}
	}
}t[2];

int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	read(n);
	for(int i=1;i<n;i++) {
		read(u,v,wi);
		t[0].add(u,v,wi);
	}
	for(int i=1;i<n;i++) {
		read(u,v,wi);
		t[1].add(u,v,wi);
	}
	int ans=0;
	for(int i=1;i<=n;i++) {
		t[0].pre(i);
		t[1].work(i);
		for(int j=1;j<=n;j++) ans=modd(ans+1ll*dis[j]*dis2[j]%mod);
	}
	printf("%d\n",ans);
	return 0;
}

