#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
const int maxn = 100005;
const int maxno = maxn << 2;
int sumv[maxno], setv[maxno];
int s2[maxno], tag2[maxno];
void maintain(int o) {
  sumv[o] = sumv[o << 1] + sumv[o << 1 | 1];
  s2[o] = s2[o << 1] + s2[o << 1 | 1];
}
void paint(int o, int L, int R, int v) {
  setv[o] = v;
  sumv[o] = (R - L + 1) * v;
}
void paint_2(int o, int L, int R, int v) {
  tag2[o] = v;
  s2[o] = (R - L + 1) * v;
}
void pushdown(int o, int L, int R) {
  if(setv[o] != -1) {
    int M = (L + R) / 2;
    paint(o << 1, L, M, setv[o]);
    paint(o << 1 | 1, M + 1, R, setv[o]);
    setv[o] = -1;
  }
  if(tag2[o] != -1) {
    int M = (L + R) / 2;
    paint_2(o << 1, L, M, tag2[o]);
    paint_2(o << 1 | 1, M + 1, R, tag2[o]);
    tag2[o] = -1;
  }
}

void modify(int o, int L, int R, int ql, int qr, int v) {
  if(ql <= L && R <= qr) {
    paint(o, L, R, v);
  } else {
    pushdown(o, L, R);
    int M = (L + R) / 2;
    if(ql <= M) modify(o << 1, L, M, ql, qr, v);
    if(qr > M) modify(o << 1 | 1, M + 1, R, ql, qr, v);
    maintain(o);
  }
}
void modify_2(int o, int L, int R, int ql, int qr, int v) {
  if(ql <= L && R <= qr) {
    paint_2(o, L, R, v);
  } else {
    pushdown(o, L, R);
    int M = (L + R) / 2;
    if(ql <= M) modify_2(o << 1, L, M, ql, qr, v);
    if(qr > M) modify_2(o << 1 | 1, M + 1, R, ql, qr, v);
    maintain(o);
  }
}
/*
int query(int o, int L, int R, int ql, int qr) {
  if(ql <= L && R <= qr) {
    return sumv[o];
  } else {
    pushdown(o, L, R);
    int M = (L + R) / 2;
    int ans = 0;
    if(ql <= M) ans += query(o << 1, L, M, ql, qr);
    if(qr > M) ans += query(o << 1 | 1, M + 1, R, ql, qr);
    return ans;
  }
}
int query_2(int o, int L, int R, int ql, int qr) {
  if(ql <= L && R <= qr) {
    return s2[o];
  } else {
    pushdown(o, L, R);
    int M = (L + R) / 2;
    int ans = 0;
    if(ql <= M) ans += query(o << 1, L, M, ql, qr);
    if(qr > M) ans += query(o << 1 | 1, M + 1, R, ql, qr);
    return ans;
  }
}
*/

std::vector<int> G[maxn];
void ins_edge(int u, int v) {
  G[u].push_back(v);
  G[v].push_back(u);
}

int n, m, q;
int siz[maxn], hson[maxn], fa[maxn], dep[maxn];
void dfs_1(int x, int father = 0, int depth = 1) {
  siz[x] = 1; fa[x] = father; dep[x] = depth;
  int max_siz = 0;
  for(int i = 0; i < G[x].size(); i ++) {
    int v = G[x][i];
    if(v != father) {
      dfs_1(v, x, depth + 1);
      siz[x] += siz[v];
      if(siz[v] > max_siz) {
        max_siz = siz[v];
        hson[x] = v;
      }
    }
  }
}
int dfn[maxn], tid[maxn], top[maxn];
void dfs_2(int x, int f, int a) {
  static int cnt = 0;
  dfn[x] = ++ cnt; tid[cnt] = x;
  top[x] = a;
  if(hson[x]) {
    dfs_2(hson[x], x, a);
  } else {
    return;
  }
  for(int i = 0; i < G[x].size(); i ++) {
    int v = G[x][i];
    if(v != f && v != hson[x]) {
      dfs_2(v, x, v);
    }
  }
}

struct Rec {
  int s, b;
  Rec(int x = 0, int y = 0) {
    s = x; b = y;
  }
};
Rec operator +(const Rec &a, const Rec &b) {
  return Rec(a.s + b.s, a.b + b.b);
}

void modify(int x, int y) {
  if(top[x] == top[y]) {
    if(dfn[x] > dfn[y]) std::swap(x, y);
    const int l = dfn[x], r = dfn[y];
    modify(1, 1, n, l, r, 1);
    if(l < r) modify_2(1, 1, n, l + 1, r, 1);
    return;
  }
  if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
  const int l = dfn[top[x]], r = dfn[x];
  modify(1, 1, n, l, r, 1);
  modify_2(1, 1, n, l, r, 1);
  modify(fa[top[x]], y);
}

int E[maxn][2], Q[maxn][2];
namespace BF_1 {
  void solve() {
    memset(setv, -1, sizeof(setv));
    memset(tag2, -1, sizeof(tag2));
    dfs_1(1); dfs_2(1, 0, 1);
    for(int i = 1; i <= q; i ++) {
      paint(1, 1, n, 0);
      paint_2(1, 1, n, 0);
      int l = Q[i][0], r = Q[i][1];
      for(int i = l; i <= r; i ++) {
        modify(E[i][0], E[i][1]);
      }
      printf("%d\n", sumv[1] - s2[1]);;
    }
  }
};

namespace Case_1 {
  std::vector<int> V[maxn];
  int ans[maxn];
  void solve() {
    memset(setv, -1, sizeof(setv));
    memset(tag2, -1, sizeof(tag2));
    dfs_1(1); dfs_2(1, 0, 1);
    for(int i = 1; i <= q; i ++) {
      V[Q[i][1]].push_back(i);
    }
    for(int i = 1; i <= n; i ++) {
      modify(E[i][0], E[i][1]);
      for(int j = 0; j < V[i].size(); j ++) {
        int id = V[i][j];
        ans[id] = sumv[1] - s2[1];
      }
    }
    for(int i = 1; i <= q; i ++) {
      printf("%d\n", ans[i]);
    }
  }
};

int main() {
#ifndef LOCAL
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
#endif
  scanf("%d%d%d", &n, &m, &q);
  bool is_chain = true;
  for(int i = 1; i <= n - 1; i ++) {
    int u, v; scanf("%d%d", &u, &v);
    if(u > v) std::swap(u, v);
    ins_edge(u, v);
    is_chain = is_chain && (u + 1 == v);
  }
  for(int i = 1; i <= m; i ++) {
    scanf("%d%d", &E[i][0], &E[i][1]);
  }
  bool case_1 = true;
  for(int i = 1; i <= q; i ++) {
    scanf("%d%d", &Q[i][0], &Q[i][1]);
    case_1 = case_1 && (Q[i][0] == 1);
  }
  if(n <= 1000 && m <= 1000 && q <= 1000) {
    BF_1::solve();
  } else if(case_1) {
    Case_1::solve();
  }
  return 0;
}
