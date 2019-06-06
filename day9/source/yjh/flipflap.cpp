#include <cstdio>
#include <cctype>
#define maxn 400005
inline int read() {
	int f=1,d=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-'){f=0;}ch=getchar();}
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return f?d:-d;
}

int n, m, sum;
int c[maxn];

inline void pushup(int x) {
	c[x] = c[x<<1] + c[x<<1|1];
}

void modify(int x, int l, int r, int tl, int tr, int v) {
	if(l == r) {c[x] += v; return;}
	int mid = (l+r)>>1;
	if(mid >= tl) modify(x<<1, l, mid, tl, tr, v);
	if(mid < tr) modify(x<<1|1, mid+1, r, tl, tr, v);
	pushup(x);
}

void dfs(int x, int l, int r, int tl, int tr, int v) {
	if(l >= tl && r <= tr && c[x] <= v) ++sum;
	if(l == r) return;
	int mid = (l+r)>>1;
	if(mid >= tl) dfs(x<<1, l, mid, tl, tr, v);
	if(mid < tr) dfs(x<<1|1, mid+1, r, tl, tr, v);
}

int main() {
	freopen("flipflap.in", "r", stdin);
	freopen("flipflap.out", "w", stdout);
	n = read(), m = read();
	while(m--) {
		int op = read(), l = read(), r = read(), a = read();
		if(op == 1) modify(1, 1, n, l, r, a);
		else {
			sum = 0;
			dfs(1, 1, n, l, r, a);
			printf("%d\n", sum);
		}
	}
	return 0;
}
