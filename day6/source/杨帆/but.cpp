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

const int N = 55;
const LL inf = 0x7f7f7f7f7f7f7f7fLL;

struct Point {
  int x, y, id;
  LL val;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
  friend Point operator-(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
  }
  friend LL operator*(const Point &a, const Point &b) {
    return (LL)a.x * b.y - (LL)b.x * a.y;
  }
} P[N], p;

bool cmpArg(const Point &a, const Point &b) {
  return (a - p) * (b - p) > 0;
}

bool cmpXY(const Point &a, const Point &b) {
  if (a.y != b.y) return a.y < b.y;
  else return a.x < b.x;
}

int n;
LL val[N][N], f[N][N][N], ans[N];

int main() {
  freopen("but.in", "r", stdin);
  freopen("but.out", "w", stdout);
  n = read();
  for (int i = 0; i < n; ++i) {
    int x = read(), y = read(), w = read();
    P[i] = Point(x, y); P[i].val = w;
  }
  std::sort(P, P + n, cmpXY);
  for (int i = 0; i < n; ++i) {
    P[i].id = i;
    for (int j = i + 1; j < n; ++j)
      for (int k = i + 1; k <= j; ++k) {
        LL t = (P[j] - P[i]) * (P[k] - P[i]);
        if (t >= 0) val[i][j] += P[k].val;
        if (t > 0) val[j][i] -= P[k].val;
      }
  }
  memset(ans, 0x7f, sizeof ans);
#define V(u, v) val[P[(u)].id][P[(v)].id]
  for (int i = n - 3; i >= 0; --i) {
    p = P[i];
    std::sort(P + i + 1, P + n, cmpArg);
    memset(f, 0x7f, sizeof f);
    for (int v = i + 1; v < n; ++v) {
      f[i][v][1] = P[i].val + V(i, v);
      for (int u = i; u < v; ++u)
        for (int k = 2 - (u == i); f[u][v][k] < inf; ++k) {
          ans[k + 1] = std::min(ans[k + 1], f[u][v][k] + V(v, i));
          for (int w = v + 1; w < n; ++w)
            if ((P[v] - P[u]) * (P[w] - P[u]) >= 0)
              f[v][w][k + 1] = std::min(f[v][w][k + 1], f[u][v][k] + V(v, w));
        }
    }
  }
  for (int i = 3; i <= n; ++i)
    printf("%lld ", ans[i] < inf ? ans[i] : -1);
  return 0;
}