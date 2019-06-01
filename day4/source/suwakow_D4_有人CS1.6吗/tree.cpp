#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int N = 110000, M = N << 1;

struct node {
	int x, y, ind;
}que[N];
int n, m, q, x[N], y[N], lca[N], hd[N], nxt[M], to[M], dgr[N], maxDgr, ans[N], fa[N], son[N], size[N], top[N], root[N], vis[N], noedg = 1, dep[N];

inline void read(int &x) {
	x = 0;
	char ch = getchar(), w = 0;
	while (!isdigit(ch))
		w = (ch == '-'), ch = getchar();
	while (isdigit(ch))
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	x = w ? -x : x;
	return;
}

inline void addEdg(int x, int y) {
	nxt[++noedg] = hd[x], hd[x] = noedg, to[noedg] = y, maxDgr = max(maxDgr, ++dgr[y]);
	nxt[++noedg] = hd[y], hd[y] = noedg, to[noedg] = x, maxDgr = max(maxDgr, ++dgr[x]);
	return;
}

inline void work1() {
	
}

inline bool cmp2(const node &a, const node &b) {
	if (a.y == b.y)
		return a.x > b.x;
	return a.y < b.y;
} 

int find(int x) {
	return root[x] == x ? x : (root[x] = find(root[x]));
}

inline bool unite(int x, int y) {
	x = find(x), y = find(y);
	if (dep[x] < dep[y]) swap(x, y);cout << x << " QAQ " << y << endl;
	return x == y ? 0 : (root[x] = y, -1);
}

inline int insrt(int x, int y, int lca) {
	int ret = 0;
	for (R int i = x, tmp; dep[i] > dep[lca]; i = tmp)
		tmp = fa[find(i)], ret += !vis[i] + unite(i, lca), vis[i] = 1, cout << i << ' ' << find(i) << ' ' << fa[find(i)] << ' ' << lca << ' ' << find(lca) << endl;;
	cout << "emm " << ret << endl;
	for (R int i = y, tmp; dep[i] > dep[lca]; i = tmp)
		tmp = fa[find(i)], ret += !vis[i] + unite(i, lca), vis[i] = 1;
	ret += !vis[lca], vis[lca] = 1;cout << x << ' ' << y << ' ' << lca << " qwq " << ret << endl;
	return ret;
}

inline void work2() {/*
	sort(que + 1, que + 1 + q, cmp2);
	int hd = 0, tl = 0, sum = 0;
	for (R int i = 1; i <= q; ++i) {
		if (que[i].x > hd) {
			hd = que[i].x, tl = que[i].y, sum = 0;
			for (R int j = 1; j <= n; ++j)
				root[j] = j, vis[j] = 0;
			for (R int j = hd; j <= tl; ++j)
				sum += insrt(x[j], y[j], lca[j]);
		}
		else {
			for (R int j = que[i].x; j < hd; ++j)
				sum += insrt(x[j], y[j], lca[j]);
			for (R int j = tl + 1; j <= que[i].y; ++j)
				sum += insrt(x[j], y[j], lca[j]);
			hd = que[i].x, tl = que[i].y;
		}
		ans[que[i].ind] = sum;
	}
	for (R int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return;*/
	for (R int i = 2; i <= 2; ++i)  {
		for (R int j = 1; j <= n; ++j)
			root[j] = j, vis[j] = 0;
		cout << insrt(x[i], y[i], lca[i]) << endl;;
	}
}

void dfs1(int now) {
	size[now] = 1, dep[now] = dep[fa[now]] + 1;
	for (R int i = hd[now], v; i; i = nxt[i]) {
		if ((v = to[i]) == fa[now])
			continue;
		fa[v] = now, dfs1(v), size[now] += size[v];
		son[now] = size[son[now]] >= size[v] ? son[now] : v;
	}
	return;
}

void dfs2(int now) {
	if (son[now])
		top[son[now]] = top[now], dfs2(son[now]);
	for (R int i = hd[now], v; i; i = nxt[i]) {
		if ((v = to[i]) == fa[now] || v == son[now])
			continue;
		top[v] = v, dfs2(v);
	}
	return;
}

inline int getLca(int x, int y) {
	while (top[x] != top[y])
		dep[top[x]] <= dep[top[y]] ? (y = fa[top[y]]) : (x = fa[top[x]]);
	return dep[x] <= dep[y] ? x : y;
}

int main() {
	int u, v;
//	freopen("tree.in", "r", stdin);
//	freopen("tree.out", "w", stdout);
	read(n), read(m), read(q);
	for (R int i = 1; i < n; ++i)
		read(u), read(v), addEdg(u, v);
	dfs1(1), dfs2(1);
	for (R int i = 1; i <= m; ++i)
		read(x[i]), read(y[i]), lca[i] = getLca(x[i], y[i]);
	for (R int i = 1; i <= q; ++i)
		read(que[i].x), read(que[i].y), que[i].ind = i;
//	if (maxDgr <= 2)
//		work1();
//	else
		work2();
	return 0;
}
