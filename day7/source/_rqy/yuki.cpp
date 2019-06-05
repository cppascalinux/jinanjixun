#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

const int T = 10000000;
inline char getChar() {
  static char s[T], *end = s, *p = s;
  if (p == end) {
    if (feof(stdin)) return EOF;
    end = s + fread(p = s, 1, T, stdin);
  }
  return *(p++);
}

int read() {
  int ans = 0, c;
  while (!isdigit(c = getChar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getChar()));
  return ans;
}

char s[T], *p = s, *end = s + T;
inline void putChar(char c) {
  if (p == end) fwrite(p = s, 1, T, stdout);
  *(p++) = c;
}

void write(int x, char c) {
  if (x >= 10) write(x / 10, EOF);
  putChar(x % 10 + '0');
  if (c != EOF) putChar(c);
}

const int N = 1000050;

namespace Treap {
int pool[N], cnt;

void init() {
  for (int i = N - 1; i; --i) pool[cnt++] = i;
}

int root = 0, val[N], key[N], count[N], ch[N][2], siz[N];

void upd(int o) { siz[o] = siz[ch[o][0]] + siz[ch[o][1]] + count[o]; }

inline void rotate(int &o, int d) {
  int t = ch[o][d]; ch[o][d] = ch[t][d ^ 1];
  upd(ch[t][d ^ 1] = o); upd(o = t);
}

void erase(int &o, int v) {
  if (val[o] == v) {
    if (count[o] > 1) --count[o];
    else if (!ch[o][0] || !ch[o][1]) pool[cnt++] = o, o = ch[o][0] | ch[o][1];
    else {
      int d = key[ch[o][1]] > key[ch[o][0]];
      rotate(o, d);
      erase(ch[o][d ^ 1], v);
    }
  } else {
    int d = val[o] < v;
    erase(ch[o][d], v);
  }
  upd(o);
}

void insert(int &o, int t) {
  if (!o) {
    val[o = pool[--cnt]] = t;
    siz[o] = count[o] = 1;
    ch[o][0] = ch[o][1] = 0;
    key[o] = rand();
  } else if (val[o] == t) {
    ++count[o];
  } else {
    int d = val[o] < t;
    insert(ch[o][d], t);
    if (key[ch[o][d]] > key[o]) rotate(o, d);
  }
  upd(o);
}

int query(int o, int k, int A[3]) {
  if (!o) {
    std::sort(A, A + 3); return A[k - 1];
  }
  int tl = siz[ch[o][0]], to = count[o];
  for (int i = 0; i < 3; ++i)
    if (A[i] < val[o]) ++tl;
    else if (A[i] == val[o]) ++to;
  if (tl >= k) return query(ch[o][0], k, A);
  else if (tl + to >= k) return val[o];
  else {
    for (int i = 0; i < 3; ++i) if (A[i] <= val[o]) A[i] = 0x7f7f7f7f;
    return query(ch[o][1], k - tl - to, A);
  }
}
};

int n, m, pre[N], to[N * 2], nxt[N * 2], cnt;
int siz[N], fa[N], dep[N], left[N], right[N], top[N], son[N], cnt2;
int rt[N], V[N], S[N];

void add(int x, int v) { for (; x <= n; x += x & -x) S[x] += v; }
int get(int x) { int v = 0; for (; x; x &= x - 1) v += S[x]; return v; }
inline int val(int x) { return x == top[x] ? V[x] : V[x] + get(right[x]) - get(left[x] - 1); }

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

int dfs0(int x, int f) {
  dep[x] = dep[fa[x] = f] + 1;
  son[x] = 0; siz[x] = 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f) {
      siz[x] += dfs0(to[i], x);
      if (siz[to[i]] > siz[son[x]]) son[x] = to[i];
    }
  return siz[x];
}

void dfs1(int x, int tp) {
  left[x] = ++cnt2;
  top[x] = tp;
  if (son[x] != 0) dfs1(son[x], tp);
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != fa[x] && to[i] != son[x]) {
      dfs1(to[i], to[i]);
      Treap::insert(rt[x], V[to[i]]);
    }
  right[x] = cnt2;
}

inline void ModifyTop(int x, int v) {
  if (x != 1) {
    Treap::erase(rt[fa[x]], V[x]);
    Treap::insert(rt[fa[x]], V[x] += v);
  } else V[x] += v;
}

void Add(int x, int y, int v) {
  add(left[x], v); add(left[y], v);
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    ModifyTop(top[x], v);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  if (x == top[x]) ModifyTop(x, v);
  else V[x] += v;
  add(left[x], -2 * v);
}

inline int Query(int x, int k) {
  int A[3] = { val(x), val(fa[x]), val(son[x]) };
  return Treap::query(rt[x], k, A);
}

int main() {
  srand(time(NULL));
  freopen("yuki.in", "r", stdin);
  freopen("yuki.out", "w", stdout);
  V[0] = 0x7f7f7f7f;
  n = read(); m = read();
  memset(pre, -1, sizeof pre);
  for (int i = 1; i <= n; ++i)
    V[i] = read();
  for (int i = 1; i < n; ++i)
    addEdge(read(), read());

  Treap::init();
  dfs0(1, 0);
  dfs1(1, 1);

  while (m--) {
    int op = read(), x = read(), y = read();
    if (op == 1) Add(x, y, read());
    else write(Query(x, y), '\n');
  }
  fwrite(s, 1, p - s, stdout);
  fprintf(stderr, "%lu\n", clock());
  return 0;
}