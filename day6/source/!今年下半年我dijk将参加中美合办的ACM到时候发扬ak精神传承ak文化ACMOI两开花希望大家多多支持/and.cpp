#include <cstdio>
int f[512][512], g[512][512];
int n, m, a[15], b[15], c[15], as, d[15][35];
int jz, i, j, N1, N2, z;
const int mod = 1000000007;
inline int MOD(int x) {
	return x >= mod ? x - mod : x;
}
inline void dfs(int nw, int x, int y) {
	if(nw == n + 1) {
		g[x][y] = MOD(z + g[x][y]);
		return;
	}
	if(nw == 1) {
		b[nw] = d[nw][jz];
		c[nw] = 1;
		dfs(nw + 1, x, y);
		b[nw] = 0;
		c[nw] = d[nw][jz];
		dfs(nw + 1, x, y);
		return;
	}
	int xx = x, yy = y, bj = 1, k = 1 << (nw - 2);
	b[nw] = d[nw][jz];
	c[nw] = 1;
	if(!(x & k)) {
		if(b[nw] < b[nw - 1]) bj = 0;
		else if(b[nw] > b[nw - 1]) xx = xx | k;
	}
	if(!(y & k)) {
		if(c[nw] > c[nw - 1]) bj = 0;
		else if(c[nw] < c[nw - 1]) yy = yy | k;
	}
	if(bj) dfs(nw + 1, xx, yy);
	xx = x; yy = y;
	b[nw] = 0;
	c[nw] = d[nw][jz];
	if(!(x & k)) {
		if(b[nw] < b[nw - 1]) return;
		else if(b[nw] > b[nw - 1]) xx = xx | k;
	}
	if(!(y & k)) {
		if(c[nw] > c[nw - 1]) return;
		else if(c[nw] < c[nw - 1]) yy = yy | k;
	}
	dfs(nw + 1, xx, yy);
}
int main() {
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int o = 1; o <= n; ++o) scanf("%d", &a[o]);
	N1 = 1 << n; N2 = 1 << (n - 1);
	f[0][0] = 1;
	for(int o = m - 1; o >= 0; --o) for(int p = 1; p <= n; ++p) d[p][o] = (a[p] >> o) & 1;
	for(jz = m - 1; jz >= 0; --jz) {
		for(i = 0; i < N2; ++i) for(j = 0; j < N2; ++j) {
			if(f[i][j] == 0) continue;
			z = f[i][j];
			dfs(1, i, j);
		}
		for(i = 0; i < N2; ++i) for(j = 0; j < N2; ++j) f[i][j] = g[i][j], g[i][j] = 0;
	}
	for(i = 0; i < N2; ++i) for(j = 0; j < N2; ++j) as = MOD(as + f[i][j]);
	printf("%d\n", as);
	return 0;
}
