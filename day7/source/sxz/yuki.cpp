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
const int Maxn=2100000;
const int inf=0x3f3f3f3f;

namespace output {
	int s[11],top,ocnt;
	char out[11000000];

	void print(int x) {
		while(x) {
			s[++top]=x%10;
			x/=10;
		}
		while(top) out[ocnt++]='0'+s[top--];
		out[ocnt++]='\n';
		if(ocnt>=10000000) {
			out[ocnt]='\0';
			printf("%s",out);
			ocnt=0;
		}
	}
	
	void flush() {
		if(ocnt) {
			out[ocnt]='\0';
			printf("%s",out);
		}
	}
}

using output::print;

int to[Maxn],nxt[Maxn],first[Maxn],tot=1;
int n,m,u,v,dat[Maxn],opt,x,y,z;

inline void add(int u,int v) {
	to[tot]=v;
	nxt[tot]=first[u];
	first[u]=tot++;
	to[tot]=u;
	nxt[tot]=first[v];
	first[v]=tot++;
}

bool check() {
	int cnt=0;
	for(int i=1;i<=n;i++) if(!nxt[first[i]]) cnt++;
	return cnt==2;
}

namespace sub1 {
	int dep[Maxn],fa[Maxn],a[Maxn],tot;
	
	void dfs(int root) {
		for(int i=first[root];i;i=nxt[i])
			if(!dep[to[i]]) fa[to[i]]=root,dep[to[i]]=dep[root]+1,dfs(to[i]);
	}
	
	void work() {
		dep[1]=1;
		dfs(1);
		for(int i=1;i<=m;i++) {
			read(opt);
			if(opt==1) {
				read(x,y,z);
				while(dep[x]>dep[y]) dat[x]+=z,x=fa[x];
				while(dep[y]>dep[x]) dat[y]+=z,y=fa[y];
				while(x!=y) dat[x]+=z,dat[y]+=z,x=fa[x],y=fa[y];
				dat[x]+=z;
			}
			else {
				read(x,y);
				a[tot=1]=dat[x];
				for(int i=first[x];i;i=nxt[i])
					a[++tot]=dat[to[i]];
				sort(a+1,a+tot+1);
				printf("%d\n",a[y]);
			}
		}
	}
}

namespace sub2 {
	int p[Maxn],a[Maxn],tot,cnt,tn[Maxn<<1],tl[Maxn<<1],tr[Maxn<<1];
	
	#define lch (root<<1)
	#define rch (root<<1|1)
	
	void dfs(int root) {
		p[root]=++cnt;
		for(int i=first[root];i;i=nxt[i])
			if(!p[to[i]]) dfs(to[i]);
	}
	
	void build(int root,int l,int r) {
		int mid=l+r>>1;
		tl[root]=l,tr[root]=r;
		if(l==r) {
			tn[root]=dat[l];
			return ;
		}
		build(lch,l,mid);
		build(rch,mid+1,r);
	}
	
	void add(int root,int ql,int qr,int z) {
		int l=tl[root],r=tr[root],mid=l+r>>1;
		if(ql<=l&&qr>=r) {
			tn[root]+=z;
			return ;
		}
		if(ql<=mid) add(lch,ql,qr,z);
		if(qr>mid) add(rch,ql,qr,z);
	}
	
	int query(int root,int x) {
		int l=tl[root],r=tr[root],mid=l+r>>1,ans=tn[root];
		if(l==r) return ans;
		if(x<=mid) ans+=query(lch,x);
		else ans+=query(rch,x);
		return ans;
	}
	
	void work() {
		for(int i=1;i<=n;i++) if(!nxt[first[i]]) {
			dfs(i);
			break;
		}
		build(1,1,n);
		for(int i=1;i<=m;i++) {
			read(opt);
			if(opt==1) {
				read(x,y,z);
				x=p[x],y=p[y];
				if(x>y) swap(x,y);
				add(1,x,y,z);
			}
			else {
				read(x,y);
				x=p[x];
				a[tot=1]=query(1,x);
				if(x!=1) a[++tot]=query(1,x-1);
				if(x!=n) a[++tot]=query(1,x+1);
				sort(a+1,a+tot+1);
				print(a[y]);
//				printf("%d\n",a[y]);
			}
		}
		output::flush();
	}
}

int main() {
	freopen("yuki.in","r",stdin);
	freopen("yuki.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(dat[i]);
	for(int i=1;i<n;i++) {
		read(u,v);
		add(u,v);
	}
	if(n<=1000&&m<=1000) sub1::work();
	else if(check()) sub2::work();
//	else sub3::work();
	return 0;
}

