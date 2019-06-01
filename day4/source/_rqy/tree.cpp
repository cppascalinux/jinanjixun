#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long LL;

const int N = 100050;

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f = -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

int n, m, q;
int siz[N], fa[N], dep[N], pos[N], top[N], son[N], node[N];
int pre[N], to[N * 2], nxt[N * 2], cnt;

int setv[N << 2];

void Modify(int o, int l, int r, int L, int R, int v) {
  if (r < L || R < l) return;
  if (L <= l && r <= R) return void(setv[o] = v);
  int mid = (l + r) / 2;
  if (setv[o])
    setv[o << 1] = setv[o << 1 | 1] = setv[o], setv[o] = 0;
  Modify(o << 1, l, mid, L, R, v);
  Modify(o << 1 | 1, mid + 1, r, L, R, v);
}

int Query(int o, int l, int r, int x) {
  if (l == r || setv[o]) return setv[o];
  int mid = (l + r) / 2;
  if (x <= mid) return Query(o << 1, l, mid, x);
  else return Query(o << 1 | 1, mid + 1, r, x);
}

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

int dfs0(int x, int f) {
  dep[x] = dep[fa[x] = f] + 1;
  son[x] = 0;
  siz[x] = 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f) {
      siz[x] += dfs0(to[i], x);
      //if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
    }
  return siz[x];
}

void dfs1(int x, int tp) {
  static int cnt = 0;
  node[pos[x] = ++cnt] = x;
  top[x] = tp;
  if (son[x] != 0) dfs1(son[x], tp);
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != fa[x] && to[i] != son[x])
      dfs1(to[i], to[i]);
}

struct Event {
  int tp, tim, x, y;
  Event() {}
  Event(int tp, int tim, int x, int y) : tp(tp), tim(tim), x(x), y(y) {}
  bool operator<(const Event &r) const {
    if (tim != r.tim) return tim < r.tim;
    else return tp > r.tp;
  }
} e[N << 1];

int ans[N];

int Set(int x, int y, int v, bool lca) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    Modify(1, 1, n, pos[top[x]], pos[x], v);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  Modify(1, 1, n, pos[x] + !lca, pos[y], v);
  return x;
}

int L[N], R[N], x[N], y[N], lca[N];
int S[N];

void add(int x, int v) {
  for (; x <= n; x += x & -x) S[x] += v;
}

int query(int x) {
  int v = 0;
  for (; x; x &= x - 1) v += S[x];
  return v;
}

int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  n = read(); m = read(); q = read();

  memset(pre, -1, sizeof pre);
  for (int i = 1; i < n; ++i) 
    addEdge(read(), read());

  dfs0(1, 0);
  dfs1(1, 1);

  memset(setv, 0, sizeof setv);
  for (int i = 1; i <= m; ++i) {
    x[i] = read(); y[i] = read();
    lca[i] = Set(x[i], y[i], i, false);
    L[i] = Query(1, 1, n, pos[lca[i]]) + 1;
  }

  memset(setv, 0, sizeof setv);
  for (int i = m; i >= 1; --i) {
    R[i] = Query(1, 1, n, pos[lca[i]]) - 1;
    if (R[i] == -1) R[i] = m;
    Set(x[i], y[i], i, true);
  }

  int u = 0;
  for (int i = 1; i <= m; ++i) {
    // add [l, i] [i, r]
    int l = L[i], r = R[i];
    e[u++] = Event(1, l, i, r);
    e[u++] = Event(-1, i, i, r);
  }
  for (int i = 0; i < q; ++i) {
    int l = read(), r = read();
    e[u++] = Event(0, l, r, i);
  }

  std::sort(e, e + u);
  for (int i = 0; i < u; ++i)
    if (e[i].tp) {
      add(e[i].x, e[i].tp);
      add(e[i].y + 1, -e[i].tp);
    } else
      ans[e[i].y] = query(e[i].x);

  for (int i = 0; i < q; ++i)
    printf("%d\n", ans[i]);
}
