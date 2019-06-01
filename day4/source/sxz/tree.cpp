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
//const int Maxn=;
const int inf=0x3f3f3f3f;

int n,m,q;

namespace sub1 {
	const int Maxn=2100;
	
	int to[Maxn],nxt[Maxn],first[Maxn],tot=1;
	int dat1[Maxn],dat2[Maxn],dep[Maxn];
	int x[Maxn],y[Maxn],l[Maxn],f[Maxn];
	int u,v;
	
	inline void add(int u,int v) {
		to[tot]=v;
		nxt[tot]=first[u];
		first[u]=tot++;
		to[tot]=u;
		nxt[tot]=first[v];
		first[v]=tot++;
	}
	
	void dfs(int root) {
		for(int i=first[root];i;i=nxt[i])
			if(to[i]!=f[root]) dep[to[i]]=dep[root]+1,f[to[i]]=root,dfs(to[i]);
	}
	
	int lca(int x,int y) {
		if(dep[x]<dep[y]) swap(x,y);
		while(dep[x]>dep[y]) x=f[x];
		while(x!=y) x=f[x],y=f[y];
		return x;
	}
	
	void work(int root) {
		for(int i=first[root];i;i=nxt[i])
			if(to[i]!=f[root]) work(to[i]),dat1[root]+=dat2[to[i]];
		dat2[root]+=dat1[root];
	}
	
	void work() {
		for(int i=1;i<n;i++) {
			read(u,v);
			add(u,v);
		}
		dfs(1);
		for(int i=1;i<=m;i++) {
			read(x[i],y[i]);
			l[i]=lca(x[i],y[i]);
		}
		while(q--) {
			for(int i=1;i<=n;i++) dat1[i]=dat2[i]=0;
			read(u,v);
			if(u>v) swap(u,v);
			for(int i=u;i<=v;i++) {
				dat1[x[i]]++;
				dat1[y[i]]++;
				dat2[l[i]]-=2;
			}
			work(1);
			int cnt=0;
			for(int i=1;i<=n;i++) if(dat1[i]&&!dat2[i]) cnt++;
			printf("%d\n",cnt);
		}
	}
}

namespace sub2 {
	const int Maxn=1100000;
	
	#define lch (root<<1)
	#define rch (root<<1|1)
	
	int tl[Maxn],tr[Maxn];
	int ans[Maxn],u,v;
	int las[Maxn];
	
	void build(int root,int l,int r) {
		tl[root]=l,tr[root]=r;
		int mid=l+r>>1;
		if(l==r) {
			return ;
		}
		build(lch,l,mid);
		build(rch,mid+1,r);
	}
	
	namespace segt1 {
		
		int tn[Maxn],bj[Maxn];
		
		inline void abj(int root,int x) {
			tn[root]=bj[root]=x;
		}
		
		void pushdown(int root) {
			if(bj[root]) {
				abj(lch,bj[root]);
				abj(rch,bj[root]);
				bj[root]=0;
			}
		}
		
		void chang(int root,int ql,int qr,int x) {
			int l=tl[root],r=tr[root],mid=l+r>>1;
			if(ql<=l&&qr>=r) {
				abj(root,x);
				return ;
			}
			pushdown(root);
			if(ql<=mid) chang(lch,ql,qr,x);
			if(qr> mid) chang(rch,ql,qr,x);
			tn[root]=x;
		}
		
		int query(int root,int ql,int qr) {
			int l=tl[root],r=tr[root],mid=l+r>>1;
			if(ql<=l&&qr>=r) {
				return tn[root];
			}
			pushdown(root);
			int ans=0;
			if(ql<=mid) qmax(ans,query(lch,ql,qr));
			if(qr> mid) qmax(ans,query(rch,ql,qr));
			return ans;
		}
		
	}
	
	namespace segt2 {
		
		int tn[Maxn];
		
		void chang(int root,int x) {
			if(x==0) return ;
			int l=tl[root],r=tr[root],mid=l+r>>1;
			tn[root]++;
			if(l==r) return ;
			if(x<=mid) chang(lch,x);
			else chang(rch,x);
		}
		
		int query(int root,int ql,int qr) {
			int l=tl[root],r=tr[root],mid=l+r>>1;
			if(ql<=l&&qr>=r) return tn[root];
			int ans=0;
			if(ql<=mid) ans+=query(lch,ql,qr);
			if(qr> mid) ans+=query(rch,ql,qr);
			return ans;
		}
		
	}
	
	struct querys {
		int l,r,id;
		
		bool operator < (const querys &a) {
			return r<a.r;
		}
	}a[Maxn];
	
	void work() {
		for(int i=1;i<n;i++) read(u,v);
		build(1,1,max(n,q));
		for(int i=1;i<=m;i++) {
			read(u,v);
			if(u>v) swap(u,v);
			las[i]=segt1::query(1,u,v);
			segt1::chang(1,u,v,i);
		}
		for(int i=1;i<=q;i++) read(a[i].l,a[i].r),a[i].id=i;
		for(int i=1;i<=q;i++) if(a[i].l>a[i].r) swap(a[i].l,a[i].r);
		sort(a+1,a+q+1);
		int temp=1,sxz=1;
		for(int i=1;i<=q;i=temp) {
			while(sxz<=a[temp].r) segt2::chang(1,las[sxz]),sxz++;
			while(a[i].r==a[temp].r) {
				ans[a[temp].id]=(a[temp].r-a[temp].l+1)-segt2::query(1,a[temp].l,a[temp].r);
				temp++;
			}
		}
		for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	}
}

int main() {
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	read(n,m,q);
	if(n<=1000&&m<=1000&&q<=1000) sub1::work();
	else sub2::work();
	return 0;
}

