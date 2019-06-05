#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
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
const int Maxn=11000;
const int inf=0x3f3f3f3f;

int to[Maxn],nxt[Maxn],first[Maxn],tot=1;
int dat[Maxn],sxz,zhy,cnt,n,m,dep[Maxn],opt,x,y;

inline void add(int u,int v) {
	to[tot]=v;
	nxt[tot]=first[u];
	first[u]=tot++;
	to[tot]=u;
	nxt[tot]=first[v];
	first[v]=tot++;
}

void chang(int root,int x,int y) {
	dat[root]=x;
	for(int i=first[root];i;i=nxt[i])
		if(dat[to[i]]==y) chang(to[i],x,y);
}

void dfs(int root) {
	for(int i=first[root];i;i=nxt[i])
		if(!dep[to[i]]) dep[to[i]]=dep[root]+1,dfs(to[i]);
}

void query(int root,int fa,int x) {
	cnt++; qmin(sxz,dep[root]),qmax(zhy,dep[root]);
	for(int i=first[root];i;i=nxt[i])
		if(to[i]!=fa&&dat[to[i]]==x) query(to[i],root,x);
}

int main() {
	freopen("su.in","r",stdin);
	freopen("su.out","w",stdout);
	read(n,m);
	for(int i=2;i<=n;i++) {
		read(m);
		add(m,i);
	}
	dep[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++) read(dat[i]);
	read(m);
	while(m--) {
		read(opt);
		if(opt==1) {
			read(x,y);
			dat[x]=y;
		}
		else if(opt==2) {
			read(x,y);
			if(dat[x]==y) continue;
			chang(x,y,dat[x]);
		}
		else {
			cnt=0,zhy=0,sxz=inf;
			read(x);
			query(x,x,dat[x]);
			printf("%d %d %d\n",dat[x],cnt,zhy-sxz+1);
		}
	}
	return 0;
}

