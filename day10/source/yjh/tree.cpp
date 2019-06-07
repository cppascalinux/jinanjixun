#include <cstdio>
#include <cctype>
#include <algorithm>
#define maxn 100005
#define maxm 200005
#define M 1000000007
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

int n, ans;

struct tree {
	int head[maxn], ver[maxm], edge[maxm], nxt[maxm], tot;
	
	inline void add(int u, int v, int w) {
		ver[++tot] = v, edge[tot] = w, nxt[tot] = head[u], head[u] = tot;
		ver[++tot] = u, edge[tot] = w, nxt[tot] = head[v], head[v] = tot;
	}
	
	int fa[maxn], dep[maxn], sz[maxn], wson[maxn], top[maxn];
	int dis[maxn];
	
	void dfs1(int u, int lst) {
		fa[u] = lst, dep[u] = dep[lst] + 1, sz[u] = 1;
		for(int p = head[u]; p; p = nxt[p]) {
			int v = ver[p];
			if(v != lst) {
				dis[v] = (dis[u]+edge[p])%M;
				dfs1(v, u);
				sz[u] += sz[v];
				if(sz[v] > sz[wson[u]]) wson[u] = v;
			}
		}
	}
	
	void dfs2(int u, int lst) {
		top[u] = lst;
		if(!wson[u]) return;
		dfs2(wson[u], lst);
		for(int p = head[u]; p; p = nxt[p]) {
			int v = ver[p];
			if(v != fa[u] && v != wson[u]) dfs2(v, v);
		}
	}
	
	int lca(int u, int v) {
		while(top[u] != top[v]) {
			if(dep[top[u]] < dep[top[v]]) std::swap(u, v);
			u = fa[u];
		} return dep[u] < dep[v] ? u : v;
	}
	
	inline int dist(int u, int v) {
		int l = lca(u, v);
		return ((dis[u]+dis[v])%M-2ll*dis[l]%M+M)%M;
	}
	
	void init() {
		int u, v, w;
		for(int i = 1; i < n; ++i) {
			u = read(), v = read(), w = read();
			add(u, v, w);
		}
		dfs1(1, 0), dfs2(1, 1);
	}
}T1, T2;

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = read();
	T1.init();
	T2.init();
	for(int u = 1; u <= n; ++u)
		for(int v = u + 1; v <= n; ++v)
			ans += 1ll*T1.dist(u, v)*T2.dist(u, v)%M;
	printf("%d", ans*2%M);
	return 0;
}
