#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <functional>
#include <utility>
const int maxn = 200005;
using pii = std::pair<int, int>;
std::vector<pii> G[2][maxn];
inline void ins_edge(int id, int u, int v, int w) {
  G[id][u].push_back({v, w});
  G[id][v].push_back({u, w});
}

using ll = long long;
const int ha = 1000000007LL;
ll sumv[2][maxn]; int dep[2][maxn];
int cnt; int dfn[2][maxn];
void dfs_1(int id, int x, int fa, int depth, ll s, int *V) {
  sumv[id][x] = s; dep[id][x] = depth;
  V[++ cnt] = x; dfn[id][x] = cnt;
  for(pii e : G[id][x]) {
    int v = e.first, w = e.second;
    if(v != fa) {
      dfs_1(id, v, x, depth + 1, s + w, V);
      V[++ cnt] = x;
    }
  }
}

int n; int euler[2][maxn];
pii minv[2][18][maxn];
int lg2[2][maxn];
void process(int id) {
  cnt = 0; dfs_1(id, 1, 0, 0, 0, euler[id]);
  for(int i = 1; i <= cnt; i ++) {
    const int th = euler[id][i];
    minv[id][0][i] = pii(dep[id][th], th);
  }
  for(int j = 1; (1 << j) <= cnt; j ++) {
    pii *A = minv[id][j], *B = minv[id][j - 1];
    for(int i = 1; i + (1 << j) - 1 <= cnt; i ++) {
      A[i] = std::min(B[i], B[i + (1 << (j - 1))]);
    }
  }
  int *l_t = lg2[id];
  l_t[1] = 0;
  for(int i = 2; i <= cnt; i ++) {
    l_t[i] = l_t[i - 1];
    while((1 << (l_t[i] + 1)) <= i) l_t[i] ++;
  }
}
inline int lca(int id, int x, int y) {
  x = euler[id][x]; y = euler[id][y];
  if(x > y) std::swap(x, y);
  int lv = lg2[id][y - x + 1];
  return std::min(minv[id][lv][x], minv[id][lv][y - (1 << lv) + 1]).second;
}
inline ll dist(int id, int x, int y) {
  ll *s = sumv[id];
  return (s[x] + s[y] - 2LL * s[lca(id, x, y)]) % ha;
}

int main() {
#ifndef WOEE
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
#endif
  double bg_time = clock();
  scanf("%d", &n);
  for(int i = 1; i <= n - 1; i ++) {
    int u, v, w; scanf("%d%d%d", &u, &v, &w);
    ins_edge(0, u, v, w);
  }
  for(int i = 1; i <= n - 1; i ++) {
    int u, v, w; scanf("%d%d%d", &u, &v, &w);
    ins_edge(1, u, v, w);
  }
  process(0); process(1);
#ifdef LOCAL
  fprintf(stderr, "Time used now : %.5lf\n", (clock() - bg_time) / CLOCKS_PER_SEC);
#endif
  ll ans = 0;
  for(int i = 1; i < n; i ++) {
    for(int j = i + 1; j <= n; j ++) {
      ans = (ans + dist(0, i, j) * dist(1, i, j)) % ha;
    }
  }
  ans = (ans << 1) % ha;
  printf("%lld\n", ans);
  return 0;
}
