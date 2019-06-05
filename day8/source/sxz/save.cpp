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
const int Maxn=110000;
const int inf=0x3f3f3f3f;

#define lch (root<<1)
#define rch (root<<1|1)

int tn[Maxn<<2],tl[Maxn<<2],tr[Maxn<<1],bj[Maxn<<2];
int a[Maxn],n,m,l,r,x,opt;

inline void update(int root) {
	tn[root]=tn[lch]^tn[rch];
}

void build(int root,int l,int r) {
	tl[root]=l,tr[root]=r;
	if(l==r) {
		tn[root]=a[l];
		return;
	}
	int mid=l+r>>1;
	build(lch,l,mid);
	build(rch,mid+1,r);
	update(root);
}

inline void abj(int root,int x) {
	if((tr[root]-tl[root]&1)==0) tn[root]^=x;
	bj[root]^=x;
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
	update(root);
}

int query(int root,int ql,int qr) {
	int l=tl[root],r=tr[root],mid=l+r>>1;
	if(ql<=l&&qr>=r) return tn[root];
	pushdown(root); int ans=0;
	if(ql<=mid) ans^=query(lch,ql,qr);
	if(qr> mid) ans^=query(rch,ql,qr);
	return ans; 
}

int main() {
	freopen("save.in","r",stdin);
	freopen("save.out","w",stdout);
	read(n,m);
	for(int i=1;i<=n;i++) read(a[i]);
	if(n<=10000&&m<=10000) {
		while(m--) {
			read(opt,l,r);
			if(opt==1) {
				read(x);
				for(int i=l;i<=r;i++) a[i]^=x;
			}
			if(opt==2) {
				sort(a+l,a+r+1);
			}
			if(opt==3) {
				int ans=0;
				for(int i=l;i<=r;i++) ans^=a[i];
				printf("%d\n",ans);
			}
		}
	}
	else {
		build(1,1,n);
		while(m--) {
			read(opt,l,r);
			if(opt==1) {
				read(x);
				chang(1,l,r,x);
			}
			else printf("%d\n",query(1,l,r));
		}
	}
	return 0;
}

