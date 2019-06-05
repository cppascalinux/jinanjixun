#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 200010
#define re register
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;

int n, m, c, r, t, x, y, z;
int sq, num;
int a[maxn], b[maxn], tag[maxn], lef[maxn], rig[maxn];
int ans, head[maxn], depth[maxn], maxx, minn;

struct hz {
	int next;
	int to;
}h[maxn];

void add(int from, int to) {
	h[++num].next = head[from];
	h[num].to = to;
	head[from] = num;
}

void dfs1(int x, int fa) {
	depth[x] = depth[fa] + 1;
	for(re int i = head[x]; i != 0; i = h[i].next) {
		if(h[i].to == fa)
		  continue;
		dfs1(h[i].to, x);
	}
}

void dfs2(int x, int nval, int wval, int fa) {
	a[x] = wval;
	for(re int i = head[x]; i != 0; i = h[i].next) {
		if(a[h[i].to] != nval || h[i].to == fa)
		  continue;
		dfs2(h[i].to, nval, wval, x);
	}
}

void dfs3(int x, int fa, int val) {
	maxx = max(maxx, depth[x]);
	minn = min(minn, depth[x]);
	++ans;
	for(re int i = head[x]; i != 0; i = h[i].next) {
		if(h[i].to == fa || a[h[i].to] != val)
		  continue;
		dfs3(h[i].to, x, val);
	}
}

int main() {
	freopen("su.in", "r", stdin);
	freopen("su.out", "w", stdout);
	scanf("%d", &n);
	FOR(i, 1, n) {
		scanf("%d", &x);
		if(x != 0)
		  add(x, i), add(i, x);
	}
	FOR(i, 1, n)
	  scanf("%d", &a[i]);
	depth[0] = -1;
	dfs1(1, 0);
	scanf("%d", &m);
	FOR(i, 1, m) {
		scanf("%d", &t);
		if(t == 1) {
			scanf("%d%d", &x, &y);
			a[x] = y;
		}
		if(t == 2) {
			scanf("%d%d", &x, &y);
			dfs2(x, a[x], y, 0);
		}
		if(t == 3) {
			scanf("%d", &x);
			printf("%d ", a[x]);
			maxx = -9999999, minn = 9999999, ans = 0;
			dfs3(x, 0, a[x]);
			printf("%d %d\n", ans, maxx-minn+1);
		}
	}
}
