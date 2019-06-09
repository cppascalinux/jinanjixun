#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;
const int N = 105;

int n, p;
LL _f[2][N][N * N], C[N][N], (*f)[N * N] = _f[0], (*g)[N * N] = _f[1], inv[N * N];

inline int sqr(int x) { return x * x; }
inline int minSS(int i, int j) { return sqr(j - i + 1) + i - 1; }
inline int maxSS(int i, int j) { return i ? sqr(j / i) * (i - j % i) + sqr(j / i + 1) * (j % i) : n; }

int main() {
  freopen("random.in", "r", stdin);
  freopen("random.out", "w", stdout);
  scanf("%d%d", &n, &p);
  f[0][0] = 1;
  LL fac = 1;
  inv[1] = 1;
  for (int i = 2; i <= n * n; ++i) inv[i] = -(p / i) * inv[p % i] % p;
  for (int i = 0; i <= n; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= n; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
  }
  LL ans = 0;
  for (int i = 0; i < n; fac = fac * (++i) % p, std::swap(f, g)) {
    memset(g, 0, sizeof _f[0]);
    for (int j = i; j < n; ++j)
      for (int k = minSS(i, j), __k = maxSS(i, j); k <= __k; ++k)
        if (f[j][k])
          for (int t = 1; t + j <= n; ++t)
            (g[j + t][k + sqr(t)] += f[j][k] * C[n - j - 1][t - 1]) %= p;
    LL anst = 0;
    for (int k = 1, __k = sqr(n); k <= __k; ++k)
      anst = (anst + g[n][k] * n * n % p * inv[n * n - k]) % p;
    anst = anst * fac % p;
    if (i & 1) ans += anst;
    else ans -= anst;
  }
  ans = (ans % p + p) % p;
  printf("%lld\n", ans);
}