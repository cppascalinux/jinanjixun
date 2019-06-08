#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef long long LL;

const int N = 100050;
const int mod = 1000000007;

int read() {
  int ans = 0, cost, f = 1;
  while (!isdigit(cost = getchar()))
    if (cost == '-') f = -1;
  do ans = ans * 10 + cost - '0';
  while (isdigit(cost = getchar()));
  return ans * f;
}

LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}

int n;

struct Solve {
  int L[N], R[N], T[N];
  int rt[N], lc[N], rc[N], dis[N];

  int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (R[x] > R[y]) std::swap(x, y);
    if (dis[rc[x] = merge(rc[x], y)] > dis[lc[x]])
      std::swap(lc[x], rc[x]);
    dis[x] = dis[rc[x]] + 1;
    return x;
  }

  inline int pop(int &x) { int o = x; x = merge(lc[x], rc[x]); return o; }

  LL solve() {
    LL ans = 1;
    for (int i = 1; i <= n; ++i) rt[i] = 0;
    for (int i = 1; i <= n; ++i) {
      lc[i] = rc[i] = dis[i] = 0;
      rt[L[i]] = merge(rt[L[i]], i);
      ans = ans * (R[i] - L[i] + 1) % mod;
    }
    ans = pow_mod(ans, mod - 2);
    for (int i = 1; i <= n; ++i) {
      if (!rt[i]) return 0;
      int x = T[i] = pop(rt[i]), r = R[x];
      rt[r + 1] = merge(rt[r + 1], rt[i]);
    }
    for (int i = 1; i <= n; ++i)
      while (T[i] != i) std::swap(T[i], T[T[i]]), ans = -ans;
    return ans;
  }
} X, Y;

int main() {
  freopen("determinant.in", "r", stdin);
  freopen("determinant.out", "w", stdout);
  int T = read();
  while (T--) {
    n = read();
    for (int i = 1; i <= n; ++i) {
      X.L[i] = read(); X.R[i] = read();
      Y.L[i] = read(); Y.R[i] = read();
    }
    LL ans = X.solve() * Y.solve() % mod;
    printf("%lld\n", (ans + mod) % mod);
  }
}