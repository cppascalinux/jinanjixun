#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, q, t, head[maxn], u[maxn], v[maxn], s[maxn], e[maxn], l[maxn], r[maxn], edge_num;

struct Edge { int v, nxt; } edge[maxn << 1];

class Subtask_1 {
private:
  static const int maxx = 1000 + 10;
  int f[maxx], deef[maxx], pre[maxx], col[maxx], cnt[maxx], path[maxx][maxx];

  std::vector<int> vis[maxx];

public:
  inline int Find(int x) { return x == f[x] ? x : f[x] = Find(f[x]); }
  inline void Unio(int x, int y) { f[Find(x)] = Find(y); }

  inline void Deep_fs(int x, int p) {
    deef[x] = deef[p] + 1, pre[x] = p;
    for(int i = head[x]; i; i = edge[i].nxt) if( edge[i].v != p ) Deep_fs(edge[i].v, x);
  }

  inline void Get_path(int x, int y, int id) {
    while( x != y ) deef[x] > deef[y] ? (path[id][++path[id][0]] = x, x = pre[x]) : (path[id][++path[id][0]] = y, y = pre[y]);
    path[id][++path[id][0]] = x;
  }

  inline void Main() {
    Deep_fs(1, 0);
    for(int i = 1; i <= m; ++i) Get_path(s[i], e[i], i);
    for(int i = 1; i <= q; ++i) {
      for(int j = 1; j <= n; ++j) col[j] = 0, cnt[j] = 0, f[j] = j;
      for(int j = l[i]; j <= r[i]; ++j) {
        for(int k = 1; k <= path[j][0]; ++k) col[path[j][k]] = 1;
        for(int k = 2; k <= path[j][0]; ++k) Unio(path[j][k - 1], path[j][k]);
      }
      for(int j = 1; j <= n; ++j) if( col[j] ) cnt[Find(j)] = 1;
      int ans = 0;
      for(int j = 1; j <= n; ++j) ans = ans + cnt[j];
      printf("%d\n", ans);
    }
  }
} subtask_1;

inline void Add_edge(int u, int v) { edge[++edge_num].v = v, edge[edge_num].nxt = head[u], head[u] = edge_num; }

int main(int argc, char const *argv[])
{
  freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);

  scanf("%d%d%d", &n, &m, &q);
  for(int i = 1; i < n; ++i) scanf("%d%d", u + i, v + i), Add_edge(u[i], v[i]), Add_edge(v[i], u[i]);
  for(int i = 1; i < n; ++i) if( u[i] != v[i] - 1 && u[i] != v[i] + 1 ) t = 1;
  for(int i = 1; i <= m; ++i) scanf("%d%d", s + i, e + i);
  for(int i = 1; i <= q; ++i) scanf("%d%d", l + i, r + i);
  subtask_1.Main();

  return 0;
}