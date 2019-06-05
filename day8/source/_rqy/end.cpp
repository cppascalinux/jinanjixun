#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iterator>

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
const int M = 10050;
const int mod = 1000000007;

LL pow_mod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}

int C[N][N];

namespace Solve {
int n, k;
char s[M];
struct Mat {
  // Up Triangle
  LL A[N][N];
  Mat() { memset(A, 0, sizeof A); }
  friend Mat operator*(const Mat &x, const Mat &y) {
    Mat ans;
    for (int i = 0; i <= n; ++i)
      for (int j = i; j <= n; ++j)
        for (int k = j; k <= n; ++k)
          ans.A[i][k] = (ans.A[i][k] + x.A[i][j] * y.A[j][k]) % mod;
    return ans;
  }
} A0, A1, AS, res;

LL Solve(int _n) {
  n = _n;
  memset(A0.A, 0, sizeof A0.A);
  memset(A1.A, 0, sizeof A1.A);
  memset(AS.A, 0, sizeof AS.A);
  memset(res.A, 0, sizeof res.A);
  for (int i = 0; i <= n; ++i) {
    A0.A[i][i] = i ? 1 << (i - 1) : 1;
    AS.A[i][i] = res.A[i][i] = 1;
    for (int j = i; j <= n; ++j) {
      LL t = C[n - i][j - i];
      if (((n - j) & 1) && !i) t = 0;
      else t = t * (i ? 1 << (i - 1) : 1) % mod;
      A1.A[i][j] = t;
    }
  }
  for (int i = 0; s[i]; ++i)
    AS = AS * (s[i] == '0' ? A0 : A1);
  for (int t = k; t; t >>= 1, AS = AS * AS)
    if (t & 1) res = res * AS;
  return res.A[0][n];
}

LL get() {
  LL x = 0; int t = 0;
  for (; s[t]; ++t) x = (x * 2 + s[t] - '0') % mod;
  return x * pow_mod(pow_mod(2, t) - 1, mod - 2) % mod * (pow_mod(2, (LL)k * t) - 1) % mod;
}

};

int n, cnt, f[M], ans[N];
bool vis[M];
LL qwq;
typedef int Part[N];
Part P[M];

bool In(const Part x, const Part y) {
  static int T[N];
  for (int i = 1; i <= n; ++i) T[i] = 0;
  for (int i = 1; i <= n; ++i) {
    if (T[x[i]] && T[x[i]] != y[i]) return false;
    T[x[i]] = y[i];
  }
  return true;
}

Part u;

void dfs(int i, int x) {
  if (i == n + 1)
    memcpy(P[cnt++], u, sizeof u);
  else
    for (u[i] = 1; u[i] <= x + 1; ++u[i])
      dfs(i + 1, std::max(x, u[i]));
}

int get(const Part a, int &u) {
  static int T[N];
  u = 0;
  for (int i = 1; i <= n; ++i) T[i] = 0;
  for (int i = 1; i <= n; ++i) T[a[i]] ^= 1;
  int ans = 0;
  for (int i = 1; i <= n; ++i) ans += T[a[i]], T[a[i]] = false;
  for (int i = 1; i <= n; ++i) if (!T[a[i]]) ++u, T[a[i]] = true;
  u -= ans;
  return ans;
}

int dfs(int i) {
  if (vis[i]) return f[i];
  vis[i] = true;
  int u;
  f[i] = ans[get(P[i], u)];
  f[i] = f[i] * pow_mod(qwq, u) % mod;
  for (int j = 0; j < cnt; ++j)
    if (i != j && In(P[i], P[j]))
      f[i] = (f[i] - dfs(j)) % mod;
  return f[i];
}

int main() {
	freopen( "end.in" , "r" , stdin );
	freopen( "end.out" , "w" , stdout );
  n = read(); Solve::k = read();
  scanf("%s", Solve::s);
  for (int i = 0; i <= n; ++i)
    for (int j = C[i][0] = 1; j <= i; ++j)
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
  dfs(1, 0);
  qwq = Solve::get();
  for (int i = n; i >= 0; i -= 2)
    ans[i] = Solve::Solve(i);
  LL t = 1;
  for (int i = 1; i <= n; ++i) t = t * i % mod;
  printf("%lld\n", (dfs(cnt - 1) * pow_mod(t, mod - 2) % mod + mod) % mod);
}
