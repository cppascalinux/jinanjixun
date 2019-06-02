#include <map>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
#define ull unsigned long long
using namespace std;
const int N = 700, base = 19260817, mod = 1e9 + 7;

int n, p[30], q[30], a[30], tot, mat[N][N], ans[N], vis[30];
struct node {
	int a[21], num;
	node () {
		num = 0, memset(a, 0, sizeof (a));
		return;
	}
	node (int *x, int num) {
		this->num = num;
		for (R int i = 0; i < num; ++i)
			a[i] = x[i + 1];
		return;
	}
	inline ull Hash() {
		ull ret = 0;
		for (R int i = 0; i < num; ++i)
			ret = ret * base + a[i];
		return ret;
	}
}d[N];
map<ull, int> table;

void dfs(int step, int rem) {
	if (!rem) {
		d[++tot] = node(a, step);
		table[d[tot].Hash()] = tot;
		return;
	}
	for (R int i = a[step]; i <= rem; ++i) {
		a[step + 1] = i;
		dfs(step + 1, rem - i);
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
	for (R int i = 1; i <= n; ++i)
		cin >> p[i];
	a[0] = 1, dfs(0, n);
	ll inv = quickpow(n * (n - 1), mod - 2);
	mat[0][0] = 1;
	for (R int i = 2; i <= tot; ++i) {
		mat[i - 1][i - 1] = mat[i - 1][tot] = mod - 1;
		for (R int j = 0; j < d[i].num; ++j) {
			for (R int k = j + 1, ind; k < d[i].num; ++k) {
				node tmp;
				for (R int t = 0; t < d[i].num; ++t)
					if (t != j && t != k)
						tmp.a[tmp.num++] = d[i].a[t];
				tmp.a[tmp.num++] = d[i].a[j] + d[i].a[k];
				sort(tmp.a, tmp.a + tmp.num), ind = table[tmp.Hash()] - 1;
				mat[i - 1][ind] = (mat[i - 1][ind] + d[i].a[j] * d[i].a[k] * inv * 2) % mod;
			}
			for (R int k = 1, ind; k < d[i].a[j]; ++k) {
				node tmp;
				for (R int t = 0; t < d[i].num; ++t)
					if (t != j)
						tmp.a[tmp.num++] = d[i].a[t];
				tmp.a[tmp.num++] = k, tmp.a[tmp.num++] = d[i].a[j] - k;
				sort(tmp.a, tmp.a + tmp.num), ind = table[tmp.Hash()] - 1;
				mat[i - 1][ind] = (mat[i - 1][ind] + d[i].a[j] * inv) % mod;
			}
		}
	}
	gauss(tot);
	node w;
	for (R int i = 1; i <= n; ++i)
		if (!vis[i]) {
			int k = 0, now = i;
			while (!vis[now])
				++k, vis[now] = 1, now = p[now];
			w.a[w.num++] = k;
		}
	sort(w.a, w.a + w.num);
	printf("%d", ans[table[w.Hash()] - 1]);
	return 0;
}
