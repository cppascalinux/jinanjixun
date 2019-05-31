#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <functional>

typedef long long LL;

LL read() {
  LL ans = 0; int c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

const int N = 100;

LL m, n;
namespace Solver {

int t;
LL b, bE[N], X[N], XE[N];

void calc() {
  t = 0;
  bE[t] = b; X[t] = 1; XE[t++] = 1;
  X[t++] = (m + b - 1) / b;
  while (true) {
    LL x = X[t - 1], y = XE[t - 2], bx = b * x % m, by = b * y % m;
    LL x1 = XE[t - 1] = y + (x - y) * (by / (by - bx)), x2 = x1 - (x - y);
    LL bx1 = bE[t - 1] = b * x1 % m, bx2 = b * x2 % m;
    if (!bx1) return;
    X[t++] = x1 * ((bx2 + bx1 - 1) / bx1) - x2;
  }
}

LL minX(LL a) {
  // min positive x such that bx mod m <= a
  if (a >= b) return 1;
  int i = std::lower_bound(bE, bE + t, a, std::greater<LL>()) - bE;
  LL x = X[i], y = XE[i - 1], bx = b * x % m, by = b * y % m;
  return y + (x - y) * ((by - a + by - bx - 1) / (by - bx));
}

LL minX(LL d, LL u) {
  if (d > u || (!d && !u)) return 0;
  LL x = minX(u), bx = b * x % m;
  LL td = (d + bx - 1) / bx, tu = u / bx;
  if (td <= tu) return td * x;
  return minX(d - tu * bx, u - tu * bx) + tu * x;
}

LL Solve(LL a, LL _b) {
  b = _b;
  calc();
  LL p = (a + (n - 1) % m * b) % m;
  a = (a + b * minX(m - a, (p - a + m) % m)) % m;
  LL ans = 0;
  while (a != p) {
    LL bx = minX(p - a) * b % m;
    ans += (p - a) / bx;
    a += (p - a) / bx * bx;
  }
  return ans;
}

LL Solve2(LL a, LL _b) {
  b = _b;
  calc();
  LL p = (a + (n - 1) % m * b) % m, tn = 1, _tmp;
  if (p < std::__gcd(m, b)) return 0;
#define go(x) (_tmp = (x), tn += _tmp, a = (a + _tmp * b) % m)
  go(minX(m - a, (p - a - 1 + m) % m));
  if (tn > n) return 0;
  LL ans = 1;
  while (true) {
    LL x = minX(p - a - 1), bx = x * b % m;
    if (!bx) break;
    LL u = std::min((n - tn) / x, (p - a - 1) / bx);
    if (!u) break;
    ans += u;
    go(u * x);
  }
  return ans;
}

};

int t;
LL X[N], XE[N], bE[N];

int main() {
  freopen("fuwafuwa.in", "r", stdin);
  freopen("fuwafuwa.out", "w", stdout);
  int T = read();
  while (T--) {
    LL a = read(); LL b = read(); m = read(); n = read();
    a = (a + b) % m; b %= m;
    if (b == 0) {
      printf("%lld\n", n - 1);
      continue;
    }
    LL m1 = m / std::__gcd(m, b);
    printf("%lld\n", (n + m1 - 1) / m1 + Solver::Solve(a, b) + Solver::Solve2(m - a - 1, m - b) - 1);
  }
}
