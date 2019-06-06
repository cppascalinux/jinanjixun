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
const int Maxn=410000;
const int inf=0x3f3f3f3f;

int siz[Maxn],tl[Maxn],tr[Maxn];
ll *v[Maxn],tn[Maxn],bj[Maxn];
int n,m,opt,x,y,a;

#define lch (root<<1)
#define rch (root<<1|1)
#define orz 100

inline void update(int root) {
	tn[root]=tn[lch]+tn[rch];
	if(siz[root]<=orz) {
		int ls=siz[lch],rs=siz[rch];
		int ln=0,rn=0,now=0,flag=0;
		while(ln!=ls&&rn!=rs) {
			if(v[lch][ln]<v[rch][rn]) {
				if(!flag&&tn[root]<v[lch][ln]) {
					v[root][now++]=tn[root];
					flag=1;
				}
				else v[root][now++]=v[lch][ln++];
			}
			else {
				if(!flag&&tn[root]<v[rch][rn]) {
					v[root][now++]=tn[root];
					flag=1;
				}
				else v[root][now++]=v[rch][rn++];
			}
		}
		while(ln!=ls) {
			if(!flag&&tn[root]<v[lch][ln]) {
				v[root][now++]=tn[root];
				flag=1;
			}
			else v[root][now++]=v[lch][ln++];
		}
		while(rn!=rs) {
			if(!flag&&tn[root]<v[rch][rn]) {
				v[root][now++]=tn[root];
				flag=1;
			}
			else v[root][now++]=v[rch][rn++];
		}
		if(!flag) v[root][now++]=tn[root];
	}
}

void build(int root,int l,int r) {
	tl[root]=l,tr[root]=r;
	siz[root]=1;
	if(l==r) {
		v[root]=new long long [1];
		v[root][0]=0;
		return ;
	}
	int mid=l+r>>1;
	build(lch,l,mid);
	build(rch,mid+1,r);
	siz[root]+=siz[lch]+siz[rch];
	if(siz[root]<=orz) v[root]=new long long [siz[root]];
	update(root);
}

void dfs(int root,int x) {
	if(tl[root]==tr[root]) {
		tn[root]+=x;
		v[root][0]+=x;
	}
	else {
		dfs(lch,x),dfs(rch,x);
		update(root);
	}
}

void abj(int root,int x) {
	if(siz[root]<=orz) {
		dfs(root,x);
	}
	else {
		tn[root]+=1ll*(tr[root]-tl[root]+1)*x;
		bj[root]+=x;
	}
}

void pushdown(int root) {
	if(bj[root]) {
		abj(lch,bj[root]);
		abj(rch,bj[root]);
		bj[root]=0;
	}
}

void chang(int root,int ql,int qr,ll x) {
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

int ask(int root,int x) {
	if(v[root][siz[root]-1]<=x) return siz[root];
	int l=0,r=siz[root]-1,mid=l+r>>1,ans;
	while(l<=r) {
		if(v[root][mid]>x) {
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
		mid=l+r>>1;
	}
	return ans;
}

int query(int root,int ql,int qr,ll x) {
	int l=tl[root],r=tr[root],mid=l+r>>1;
	pushdown(root); 
	if(ql<=l&&qr>=r) {
		if(siz[root]<=orz) return ask(root,x);
		else return query(lch,ql,qr,x)+query(rch,ql,qr,x)+(tn[root]<=x);
	}
	pushdown(root); int ans=0;
	if(ql<=mid) ans+=query(lch,ql,qr,x);
	if(qr> mid) ans+=query(rch,ql,qr,x);
	return ans;
}

int baoli(int root,int ql,int qr,int x) {
	int l=tl[root],r=tr[root],mid=l+r>>1;
	if(l==r) return tn[root]<=x;
	pushdown(root); int ans=(ql<=l&&qr>=r)&(tn[root]<=x);
	if(ql<=mid) ans+=query(lch,ql,qr,x);
	if(qr> mid) ans+=query(rch,ql,qr,x);
	return ans;
}

int main() {
	freopen("flipflap.in","r",stdin);
	freopen("flipflap.out","w",stdout);
	read(n,m);
	build(1,1,n);
	while(m--) {
		read(opt); read(x,y,a);
		if(opt==1) chang(1,x,y,a);
		else printf("%d\n",query(1,x,y,a));
	}
	return 0;
}

