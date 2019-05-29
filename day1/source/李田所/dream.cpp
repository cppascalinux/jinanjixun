#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int N = 65, mod = 998244353;

int n, m, k, w, cube[N][N][N], val[N][N][N], tab[N][N], up[N][N], stck[N], top, sum[N], tot, f[N][N], g[N][N][N];

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

inline int addMod(int a, int b) {
	return (a += b) >= mod ? a - mod : a;
}

inline ll quickpow(ll base, ll pw) {
	ll ret = 1;
	while (pw) {
		if (pw & 1) ret = ret * base % mod;
		base = base * base % mod, pw >>= 1;
	}
	return ret;
}

int main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	read(n), read(m), read(k), read(w);
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			for (R int l = 1; l <= k; ++l)
				read(cube[i][j][l]);
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			for (R int l = 1; l <= k; ++l)
				read(val[i][j][l]);
	for (R int i = 1; i <= n; ++i) {
		for (R int u = 1; u <= m; ++u)
			for (R int v = 1; v <= k; ++v)
				tab[u][v] = 1;
		for (R int j = i; j <= n; ++j) {
			for (R int u = 0; u <= m; ++u)
				for (R int v = 0; v <= k; ++v)
					f[u][v] = 0;
			for (R int u = 1; u <= m; ++u) {
				top = 0;
				for (R int v = 1; v <= k; ++v) {
					tab[u][v] &= cube[j][u][v];
					up[u][v] = tab[u][v] ? up[u - 1][v] + 1 : 0;
					while (top && up[u][stck[top]] >= up[u][v]) --top;
					sum[v] = sum[stck[top]] + (v - stck[top]) * up[u][v];
					tot = addMod(sum[v], tot), stck[++top] = v;
					if (!up[u][v]) continue;
					for (R int l = 1; l <= top; ++l) {
						int a = up[u][stck[l]] - up[u][stck[l - 1]], b = stck[l] - stck[l - 1], c = a * b;
						if (!c) continue;
						int y[4] = {u - up[u][v] + 1, u - up[u][stck[l - 1]] + 1, u + 1, u + 2},
						x[3] = {stck[l - 1] + 1, v + 1, v + 2};
						++f[y[0]][x[0]], f[y[0]][x[1]] -= b + 1, f[y[0]][x[2]] += b;
						--f[y[1]][x[0]], f[y[1]][x[1]] += b + 1, f[y[1]][x[2]] -= b;
						f[y[2]][x[0]] -= a, f[y[2]][x[1]] += c + a, f[y[2]][x[2]] -= c;
						f[y[3]][x[0]] += a, f[y[3]][x[1]] -= c + a, f[y[3]][x[2]] += c;
					}
				}
			}
			for (R int u = 1; u <= m; ++u)
				for (R int v = 1; v <= k; ++v)
					f[u][v] = addMod(addMod(f[u][v - 1], f[u - 1][v]), addMod(f[u][v], mod - f[u - 1][v - 1]));
			for (R int u = 1; u <= m; ++u)
				for (R int v = 1; v <= k; ++v)
					f[u][v] = addMod(addMod(f[u][v - 1], f[u - 1][v]), addMod(f[u][v], mod - f[u - 1][v - 1]));
			for (R int u = 1; u <= m; ++u)
				for (R int v = 1; v <= k; ++v)
					for (R int l = i; l <= j; ++l)
						g[l][u][v] = addMod(g[l][u][v], f[u][v]);
		}
	}
	ll all = quickpow(tot * quickpow(quickpow(8, mod - 2) * n * (n + 1) * m * (m + 1) * k * (k + 1) % mod, mod - 2) % mod, w), valid = quickpow(tot, mod - 2), ans = 0;
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			for (R int l = 1; l <= k; ++l)
				ans = (ans + val[i][j][l] * (mod + 1 - quickpow(mod + 1 - g[i][j][l] * valid % mod, w))) % mod;
	cout << ans * all % mod;
	return 0;
}
