#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 100005
#define maxm 200005
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, m, q;
int head[maxn], ver[maxm], nxt[maxm], tot;

inline void add(int u, int v) {
	ver[++tot] = v, nxt[tot]= head[u], head[u] = tot;
	ver[++tot] = u, nxt[tot]= head[v], head[v] = tot;
}

int stx[maxn], sty[maxn];
int fa[maxn], dep[maxn];

void dfs(int u, int lst) {
	fa[u] = lst, dep[u] = dep[lst] + 1;
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst) dfs(v, u);
	}
}

int sv[maxn], se[maxn];

void col(int x, int y) {
	if(dep[x] < dep[y]) std::swap(x, y);
	while(dep[x] > dep[y]) sv[x] = se[x] = 1, x = fa[x];
	while(x != y) sv[x] = se[x] = sv[y] = se[y] = 1, x = fa[x], y = fa[y];
	sv[x] = 1;
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = read(), m = read(), q = read();
	for(int i = 1; i < n; ++i) {
		int u = read(), v = read();
		add(u, v);
	}
	for(int i = 1; i <= m; ++i)
		stx[i] = read(), sty[i] = read();
	dfs(1, 0);
	while(q--) {
		int l = read(), r = read();
		for(int i = 1; i <= n; ++i) sv[i] = se[i] = 0;
		for(int i = l; i <= r; ++i) col(stx[i], sty[i]);
		int sum = 0;
		for(int i = 1; i <= n; ++i) if(sv[i] && !se[i]) ++sum;
		printf("%d\n", sum);
	}
	return 0;
}
