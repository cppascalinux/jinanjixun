#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define maxn 100010
#define cQ const Query
using namespace std;

int n, m, q;

int a[maxn], b[maxn];

struct Edge {
	int to, next; 	
} e[maxn * 2]; int c1, head[maxn];
inline void add_edge(int u, int v) {
	e[c1].to = v; e[c1].next = head[u]; head[u] = c1++; 		
}

int ans[maxn], blo; 
struct _ {
	
	int ou[maxn * 2], c2, in[maxn], f[maxn];
	void dfs(int u, int fa) {
		ou[++c2] = u; in[u] = c2;
		for (int i = head[u]; ~i; i = e[i].next) {
			int v = e[i].to; if (v == fa) continue ; 
			f[v] = u; dfs(v, u); ou[++c2] = u; 
		}
	}
	
	inline int st_min(int l, int r) { return in[l] < in[r] ? l : r; }
	
	int Log[maxn * 2], st[maxn * 2][21];  
	void init_lca() { Log[0] = -1; 
		for (int i = 1; i <= c2; ++i) Log[i] = Log[i >> 1] + 1, st[i][0] = ou[i];
		for (int j = 1; j <= 20; ++j) 
			for (int i = 1; i + (1 << j) - 1 <= c2; ++i) st[i][j] = st_min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]); 
	}
	
	inline int get_lca(int l, int r) {
		l = in[l]; r = in[r]; if (l > r) swap(l, r);  
		int k = Log[r - l + 1]; 
		return st_min(st[l][k], st[r - (1 << k) + 1][k]);  
	}


	struct Query {
		int l, r, id;	
		
		friend bool operator < (cQ &u, cQ &v) {
			if (u.l / blo == v.l / blo) return u.r < v.r; 
			return u.l < v.l; 
		}
	} Q[maxn];
	
	int cnt[maxn], s; bool F; 
	inline void add(int i) {
		int x = a[i], y = b[i], g = get_lca(x, y); 
		while (x != g) {
			if (++cnt[x] == 1) ++s; 
			x = f[x]; 	
		}
		
		while (y != g) {
			if (++cnt[y] == 1) ++s; 
			y = f[y]; 	
		}
		
		if (F) 
			if (++cnt[g] == 1) ++s; 
	}
	
	inline void del(int i) {
		int x = a[i], y = b[i], g = get_lca(x, y); 
		while (x != g) {
			if (--cnt[x] == 0) --s; 
			x = f[x]; 	
		}
		
		while (y != g) {
			if (--cnt[y] == 0) --s; 
			y = f[y]; 	
		}
		
		if (F) 
			if (--cnt[g] == 0) --s; 
	}
	
	int Main() {
		dfs(1, 0); blo = sqrt(n); init_lca();
		for (int i = 1; i <= m; ++i) scanf("%d%d", &a[i], &b[i]); 
		for (int i = 1; i <= q; ++i) scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].id = i;
		sort(Q + 1, Q + q + 1);
		int l = Q[1].l, r = l - 1; F = 1;  
		for (int i = 1; i <= q; ++i) {
			while (r < Q[i].r) add(++r); 
			while (l > Q[i].l) add(--l); 
			while (r > Q[i].r) del(r--);
			while (l < Q[i].l) del(l++); 		
			ans[Q[i].id] = s; 
		}
		l = Q[1].l; r = l - 1; F = 0; s = 0; memset(cnt, 0, sizeof cnt); 
		for (int i = 1; i <= q; ++i) {
			while (r < Q[i].r) add(++r); 
			while (l > Q[i].l) add(--l); 
			while (r > Q[i].r) del(r--);
			while (l < Q[i].l) del(l++); 		
			ans[Q[i].id] -= s;
		}
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]); 
	}
} _;

int f[maxn], dep[maxn], son[maxn], sz[maxn];
void dfs(int u, int fa) {
	int Max = 0; sz[u] = 1; 
	for (int i = head[u]; ~i; i = e[i].next) {
		int v = e[i].to; if (v == fa) continue ; 
		dep[v] = dep[u] + 1; f[v] = u; dfs(v, u); 	
		sz[u] += sz[v]; if (sz[v] > Max) Max = sz[v], son[u] = v;
	}
}

int top[maxn], id[maxn], c2;
void dfs(int u, int fa, int topf) {
	top[u] = topf; id[u] = ++c2;
	if (son[u]) dfs(son[u], u, topf); 
	for (int i = head[u]; ~i; i = e[i].next) {
		int v = e[i].to; if (v == fa || v == son[u]) continue ; 
		dfs(v, u, v); 
	}
}

#define lc i << 1
#define rc i << 1 | 1
struct seg {
	int v, mem; 	
} T[maxn * 4]; 
inline void maintain(int i) { T[i].v = T[lc].v + T[rc].v; }  

void build(int i, int l, int r) {
	T[i].v = T[i].mem = 0; 
	if (l == r) return ;
	int m = l + r >> 1; 
	build(lc, l, m); build(rc, m + 1, r); 	
}

inline void setm(int i, int l, int r) {
	if (!i) return ; 
	T[i].v = r - l + 1; T[i].mem = 1; 	
}

inline void push(int i, int l, int r) {
	int m = l + r >> 1; 
	if (T[i].mem) setm(lc, l, m), setm(rc, m + 1, r);
	T[i].mem = 0; 	
}

void update(int i, int l, int r, int L, int R) {
	if (l > R || r < L) return ; 
	if (L <= l && r <= R) return setm(i, l, r); 
	int m = l + r >> 1; push(i, l, r); 
	update(lc, l, m, L, R); update(rc, m + 1, r, L, R); 
	maintain(i);  	
}

int F;
void update(int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y); 
		update(1, 1, n, id[top[x]], id[x]); 
		x = f[top[x]]; 
	}
	if (dep[x] > dep[y]) swap(x, y); 
	update(1, 1, n, id[x] + F, id[y]); 
}

int main() { memset(head, -1, sizeof head); 
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	cin >> n >> m >> q;  
	for (int i = 1; i < n; ++i) {
		int x, y; scanf("%d%d", &x, &y); 
		add_edge(x, y); add_edge(y, x); 
	} 
	if (n <= 1000 && m <= 1000 && q <= 1000) return _.Main(); 
	for (int i = 1; i <= m; ++i) scanf("%d%d", &a[i], &b[i]); 
	dfs(1, 0); dfs(1, 0, 1);

	for (int i = 1; i <= m; ++i) {
		update(a[i], b[i]); 	
		ans[i] = T[1].v; 
	}
	
	build(1, 1, n); F = 1; 
	for (int i = 1; i <= m; ++i) {
		update(a[i], b[i]); 	
		ans[i] -= T[1].v; 
	}
	
	for (int i = 1; i <= q; ++i) {
		int x, y; scanf("%d%d", &x, &y); 
		printf("%d\n", ans[y]); 	
	}
	return 0; 	
}
