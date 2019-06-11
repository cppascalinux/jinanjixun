#include <algorithm>
#include <cstdio>
#include <cstring>

inline bool check(int n, int k) {
  if ((k & (k - 1)) == 0) return n >= k;
  else if (k & 1) return n >= k + 2;
  else return n >= k + 1;
}

const int N = 300050;

int m, x[N], y[N];

int Solve(int k, int off) {
#define put(i, j) x[m] = off + (i), y[m++] = off + (j);
#define solve(k, off2) Solve((k), off + (off2))
  if (k == 1) {
    // do nothing
  } else if (k & 1) { // n >= k + 2
    solve(k + 1, 0);
    put(0, k + 1);
  } else if ((k & (k - 1)) == 0) { // n >= k
    solve(k / 2, 0); solve(k / 2, k / 2);
    put(k / 2, 0);
  } else { // n >= k + 1
    int t = 1; while ((t << 1) < k) t <<= 1;
    int u = k - t + 1;
    solve(t, u); // t
    for (int i = 1, j; i < t; i <<= 1) {
      for (j = 0; j + i < u; j += 2 * i)
        put(j + i, j); // k - t - 1
      if (j < u) put(u, j); // log k
    }
    int a = k + 1 - t, b = t;
    while (b != 1)
      if (a > b) {
        put(u, 0); a -= b; b *= 2;
      } else {
        put(0, u); b -= a; a *= 2;
      }
  }
}

int main() {
  freopen("chemistry.in", "r", stdin);
  freopen("chemistry.out", "w", stdout);
  int n, k;
  scanf("%d%d", &n, &k);
  if (!check(n, k)) return puts("-1") & 0;
  Solve(k, 1);
  printf("%d\n", m);
  for (int i = 0; i < m; ++i) printf("%d %d\n", x[i], y[i]);
  return 0;
}