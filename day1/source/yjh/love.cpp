#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#define maxn 100005
#define maxm 200005
#define Inf 0x3f3f3f3f3f3f3f3fll
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}
typedef long long ll;

int n, m;
ll u, v, w;
ll sum;
int head[maxn], ver[maxm], nxt[maxm], tot;
ll edge[maxm];

namespace qwq {
	std::priority_queue<ll> q1, q2;
	
	ll getmx1() {
		if(q1.empty()) return -Inf;
		ll u = q1.top(); q1.pop();
		if(q1.empty()) return u;
		u += q1.top(), q1.pop();
		return u;
	}
	
	ll getmx2() {
		if(q2.empty()) return -Inf;
		ll u = q2.top(); q2.pop();
		return u;
	}
	
	int work() {
		for(int p = 1; p <= m; ++p) {
			u = getmx1(), v = getmx2(), w = read();
			if(u > v) std::swap(u, v);
			if(u != -Inf) q2.push(u);
			if(w < v) sum -= v-w, q2.push(w);
			else q2.push(v);
			printf("%lld ", sum);
		}
		return 0;
	}
}

inline void add(int u, int v, int w) {
	ver[++tot] = v, edge[tot] = w, nxt[tot] = head[u], head[u] = tot;
	ver[++tot] = u, edge[tot] = w, nxt[tot] = head[v], head[v] = tot;
}

int fa[maxn], dep[maxn];
ll dis[maxn];
std::priority_queue<ll> q;

void dfs(int u, int lst) {
	fa[u] = lst, dep[u] = dep[lst] + 1;
	for(int p = head[u]; p; p = nxt[p]) {
		int v = ver[p];
		if(v != lst) {
			dis[v] = dis[u] + edge[p];
			dfs(v, u);
		}
	}
}

int vis[maxn];

int lca(int x, int y) {
	if(dep[x] < dep[y]) std::swap(x, y);
	while(dep[x] > dep[y]) {
		if(vis[x]) return -1;
		x = fa[x];
	}
	while(x != y) {
		if(vis[x] || vis[y]) return -1;
		x = fa[x], y = fa[y];
	}
	return x;
}

void col(int x, int y) {
	if(dep[x] < dep[y]) std::swap(x, y);
	while(dep[x] > dep[y]) vis[x] = 1, x = fa[x];
	while(x != y) vis[x] = vis[y] = 1, x = fa[x], y = fa[y];
}

int main() {
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);
	n = read(), m = read();
	int fl4 = 1;
	for(int i = 1; i < n; ++i) {
		u = read(), v = read(), w = read();
		qwq::q1.push(w);
		add(u, v, w);
		if(u != 1 && v != 1) fl4 = 0;
		sum += 2ll*w;
	}
	printf("%lld ", sum);
	if(fl4) return qwq::work();
	dfs(1, 0);
	for(int i = 1; i <= m; ++i) {
		w = read();
		int mxj = 0, mxk = 0;
		ll mxdis = -1;
		for(int j = 1; j <= n; ++j)
			for(int k = j+1; k <= n; ++k) {
				int l = lca(j, k);
				if(l == -1) continue;
				ll dist = dis[j]+dis[k]-2*dis[l];
				if(dist > mxdis)
					mxdis = dist, mxj = j, mxk = k;
			}
		if(!q.empty() && q.top() > mxdis && q.top() > w) {
			sum -= q.top()-w; q.pop(), q.push(w);
		}
		else if(mxdis > w) {
			sum -= mxdis-w; q.push(w), col(mxj, mxk);
		}
		printf("%lld ", sum);
	}
	return 0;
}
