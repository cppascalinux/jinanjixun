#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long LL;
typedef unsigned long long ULL;

const int N = 25;
const int P = 2000;
const int mod = 1000000007;

LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}

int n, to[P][N], ind[P], cnt = 1;
int B[N], A[P][N], m;

int &get(int l, const int *A) {
  int o = 0;
  for (int i = 0; i < l; ++i) {
    if (!to[o][A[i]]) to[o][A[i]] = ++cnt;
    o = to[o][A[i]];
  }
  return ind[o];
}

void dfs(int n, int i, int x) {
  if (n == 0)
    std::copy(B, B + i, A[get(i, B) = m++]);
  else
    for (B[i] = x; B[i] <= n; ++B[i])
      dfs(n - B[i], i + 1, B[i]);
}

int calc(const int *A) {
  static bool P[N];
  static int B[N];
  memset(P, 0, sizeof P);
  int l = 0;
  for (int i = 1; i <= n; ++i) if (!P[i]) {
    int t = 1;
    for (int j = A[i]; j != i; j = A[j])
      P[j] = true, ++t;
    B[l++] = t;
  }
  std::sort(B, B + l);
  return get(l, B);
}

int C[N];
LL F[P][P];

void dfs2(int t, int k, int x) {
  if (t == 0) {
    int x = get(k, B);
    F[x][x] = 1;
    if (k != n) {
      F[x][m] = k != n;
      int u = 1;
      for (int i = 0; i < k; ++i) {
        for (int j = 0; j < B[i]; ++j)
          C[u + j] = u + (j + 1) % B[i];
        u += B[i];
      }
      LL t = pow_mod(n * (n - 1) / 2, mod - 2);
      for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
          std::swap(C[i], C[j]); int y = calc(C);
          F[x][y] = (F[x][y] - t) % mod;
          std::swap(C[i], C[j]);
        }
    }
  } else
    for (B[k] = x; B[k] <= t; ++B[k])
      dfs2(t - B[k], k + 1, B[k]);
}

void Gauss() {
  for (int i = 0; i < m; ++i) {
    int j = i;
    while (!F[j][i]) ++j;
    for (int k = i; k <= m; ++k) std::swap(F[i][k], F[j][k]);
    LL v = pow_mod(F[i][i], mod - 2);
    for (int k = i; k <= m; ++k) F[i][k] = F[i][k] * v % mod;
    for (int j = i + 1; j < m; ++j)
      for (int k = m; k >= 1; --k)
        F[j][k] = (F[j][k] - F[i][k] * F[j][i]) % mod;
  }
  for (int i = m - 1; i; --i)
    for (int j = 0; j < i; ++j)
      F[j][m] = (F[j][m] - F[j][i] * F[i][m]) % mod;
}

int main() {
  freopen("one.in", "r", stdin);
  freopen("one.out", "w", stdout);
  scanf("%d", &n);
  dfs(n, 0, 1);
  dfs2(n, 0, 1);
  Gauss();
  for (int i = 1; i <= n; ++i) scanf("%d", &C[i]);
  printf("%lld\n", (F[calc(C)][m] + mod) % mod);
}