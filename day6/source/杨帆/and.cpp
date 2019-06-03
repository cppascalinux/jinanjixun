#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef long long LL;

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f = -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

const int N = 10;
const int M = 50;
const int mod = 1000000007;

int n, m, lim, B[M], f[M][1 << (N - 1)];

inline void upd(int &a, int b) { if ((a += b) >= mod) a -= mod; }

int Solve() {
  memset(f, 0, sizeof f);
  f[m][0] = 1;
  for (int i = m; i > 0; --i)
    for (int S = 0; S <= lim; ++S) if (f[i][S])
      for (int A = B[i - 1]; ; A = (A - 1) & B[i - 1]) {
        if (!(A & (~A >> 1) & ~S & lim))
          upd(f[i - 1][S | (~A & (A >> 1))], f[i][S]);
        if (!A) break;
      }
  int ans = 0;
  for (int i = 0; i <= lim; ++i) upd(ans, f[0][i]);
  return ans;
}

int main() {
  freopen("and.in", "r", stdin);
  freopen("and.out", "w", stdout);
  n = read(); m = read(); lim = (1 << (n - 1)) - 1;
  for (int i = 0; i < n; ++i) {
    int b = read();
    for (int j = 0; j < m; ++j)
      B[j] |= ((b >> j) & 1) << i;
  }
  int ans = Solve();
  for (int i = 0; i < m; ++i)
    B[i] = ((1 << n) - 1) ^ B[i];
  ans = (LL)ans * Solve() % mod;
  printf("%lld\n", ans);
  return 0;
}