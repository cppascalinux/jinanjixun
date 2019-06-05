#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 100005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m;
int a[maxn];

namespace solve1 {
	int c[maxn<<2], tag[maxn<<2];
	
	inline void pushup(int x) {
		c[x] = c[x<<1]^c[x<<1|1];
	}
	
	inline void col(int x, int l, int r, int v) {
		tag[x] ^= v;
		if((r-l+1)&1) c[x] ^= v;
	}
	
	inline void pushdown(int x, int l, int r) {
		if(tag[x]) {
			int mid = (l+r)>>1;
			col(x<<1, l, mid, tag[x]);
			col(x<<1|1, l, mid, tag[x]);
			tag[x] = 0;
		}
	}
	
	void build(int x, int l, int r) {
		if(l == r) {c[x] = a[l]; return;}
		int mid = (l+r)>>1;
		build(x<<1, l, mid);
		build(x<<1|1, mid+1, r);
		pushup(x);
	}
	
	void modify(int x, int l, int r, int tl, int tr, int v) {
		if(l >= tl && r <= tr) return col(x, l, r, v);
		pushdown(x, l, r);
		int mid = (l+r)>>1;
		if(mid >= tl) modify(x<<1, l, mid, tl, tr, v);
		if(mid < tr) modify(x<<1|1, mid+1, r, tl, tr, v);
		pushup(x);
	}
	
	int query(int x, int l, int r, int tl, int tr) {
		if(l >= tl && r <= tr) return c[x];
		pushdown(x, l, r);
		int sum = 0, mid = (l+r)>>1;
		if(mid >= tl) sum ^= query(x<<1, l, mid, tl, tr);
		if(mid < tr) sum ^= query(x<<1|1, mid+1, r, tl, tr);
		return sum;
	}
	
	int work() {
		build(1, 1, n);
		while(m--) {
			int op = read(), l = read(), r = read();
			if(op == 1) {
				int x = read();
				modify(1, 1, n, l, r, x);
			}
			else if(op == 3) printf("%d\n", query(1, 1, n, l, r));
		}
		return 0;
	}
}

int main() {
	freopen("save.in", "r", stdin);
	freopen("save.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	if(n*m > 100000000) return solve1::work();
	while(m--) {
		int op = read(), l = read(), r = read();
		if(op == 1) {
			int x = read();
			for(int i = l; i <= r; ++i) a[i] ^= x;
		}
		else if(op == 2) std::sort(a+l, a+r+1);
		else {
			int sum = 0;
			for(int i = l; i <= r; ++i) sum ^= a[i];
			printf("%d\n", sum);
		}
	}
	return 0;
}
