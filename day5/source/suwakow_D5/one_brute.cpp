#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int mod = 1e9 + 7;

int n, vis[30], fac[30], a[30], b[30], mat[730][730], inv, ans[730];

inline int cantor(int *a) {
	int ret = 0;
	for (R int i = 1; i <= n; ++i)
		vis[i] = 0;
	for (R int i = 1; i <= n; ++i) {
		int t = 0;
		for (R int j = 1; j < a[i]; ++j)
			t += !vis[j];
		vis[a[i]] = 1, ret += fac[n - i] * t;
	}
	return ret;
}

inline void decantor(int x, int *a) {
	for (R int i = 1; i <= n; ++i)
		vis[i] = 0;
	for (R int i = 1; i <= n; ++i) {
		int t = x / fac[n - i], j;
		x -= t * fac[n - i];
		for (j = 1; ~t && j <= n; ++j)
			t -= !vis[j];
		vis[j - 1] = 1, a[i] = j - 1;
	}
	return;
}

inline ll quickpow(ll base, ll pw) {
	ll ret = 1;
	while (pw) {
		if (pw & 1) ret = ret * base % mod;
		base = base * base % mod, pw >>= 1;
	}
	return ret;
}

inline int addMod(int a, int b) {
	return (a += b) >= mod ? a - mod : a;
}

inline void gauss(int n) {
	for (R int i = 0; i < n; ++i) {
		if (!mat[i][i]) {
			for (R int j = i + 1; !mat[i][i] && j < n; ++j)
				if (mat[j][i])
					for (int k = i; k <= n; ++k)
						swap(mat[i][k], mat[j][k]);
			if (!mat[i][i]) continue;
		}
		int inv = quickpow(mat[i][i], mod - 2);
		for (R int j = i + 1; j < n; ++j) {
			if (!mat[j][i]) continue;
			for (R int k = i, w = (ll) mat[j][i] * inv % mod; k <= n; ++k)
				mat[j][k] = addMod(mat[j][k], mod - (ll) mat[i][k] * w % mod);
		}
	}
	for (R int i = n - 1; ~i; --i) {
		for (R int j = i + 1; j < n; ++j)
			mat[i][n] = addMod(mat[i][n], mod - (ll) mat[i][j] * ans[j] % mod);
		ans[i] = mat[i][n] * quickpow(mat[i][i], mod - 2) % mod;
	}
	return;
}

int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	cin >> n;
	fac[0] = 1, mat[0][0] = mod - 1;
	inv = quickpow(n * (n - 1) / 2, mod - 2);
	for (R int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i;
	for (R int i = 1; i <= n; ++i)
		cin >> a[i];
	for (R int i = 1; i < fac[n]; ++i) {
		decantor(i, b);
		mat[i][i] = mat[i][fac[n]] = mod - 1;
		for (R int j = 1; j <= n; ++j)
			for (R int k = j + 1; k <= n; ++k) {
				swap(b[j], b[k]);
				mat[i][cantor(b)] = inv;
				swap(b[j], b[k]);
			}
	}
	gauss(fac[n]);
	printf("%d", ans[cantor(a)]);
	return 0;
}
