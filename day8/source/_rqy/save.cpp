#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iterator>

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f = -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

int revv[1 << 15];

inline int rev(int x) {
  return revv[x & ((1 << 15) - 1)] << 15 | revv[x >> 15];
}

const int N = 100050;
const int NN = N * 3;
const int L = 30;

namespace CT { // Compressed Trie

int lc[NN], rc[NN], seta[NN], setb[NN], getv[NN], sizv[NN], h[NN], pre[NN];
int pool[NN], cnt;
bool sortv[NN];

void Init() {
  for (int i = NN - 1; i; --i) pool[cnt++] = i;
}

inline int newNode() {
  int o = pool[--cnt];
  lc[o] = rc[o] = seta[o] = setb[o] = getv[o] = sizv[o] = h[o] = pre[o] = sortv[o] = 0;
  return o;
}

inline int newNode(int v) {
  int o = pool[--cnt];
  lc[o] = rc[o] = seta[o] = setb[o] = sortv[o] = 0; pre[o] = getv[o] = v; sizv[o] = 1; h[o] = L;
  return o;
}

inline void delNode(int o) { pool[cnt++] = o; }

inline void upd(int o) {
  if (h[o] < L) {
    getv[o] = getv[lc[o]] ^ getv[rc[o]];
    sizv[o] = sizv[lc[o]] + sizv[rc[o]];
    if (sizv[o] & 1) getv[o] ^= seta[o] ^ setb[o];
  }
}

inline void set(int o, int v) {
  pre[o] ^= v;
  setb[o] ^= v;
  if (sizv[o] & 1) getv[o] ^= v;
}

inline void sort(int o) { seta[o] ^= setb[o]; sortv[o] = true; setb[o] = 0; }

void pushd(int o) {
  set(lc[o], seta[o]); set(rc[o], seta[o]); seta[o] = 0;
  if (sortv[o]) {
    if (rev(pre[lc[o]]) > rev(pre[rc[o]])) std::swap(lc[o], rc[o]);
    sort(lc[o]); sort(rc[o]); sortv[o] = false;
  }
  set(lc[o], setb[o]); set(rc[o], setb[o]); setb[o] = 0;
}

void merge(int &x, int y) {
  if (!x || !y) return void(x |= y);
  if (h[x] > h[y]) std::swap(x, y);
  pushd(x); pushd(y);
  int t = __builtin_ctz(pre[x] ^ pre[y]);
  if (t < h[x]) {
    int o = newNode(); pre[o] = pre[x]; h[o] = t;
    if ((pre[y] >> t) & 1) lc[o] = x, rc[o] = y;
    else lc[o] = y, rc[o] = x;
    upd(x = o);
  } else if (h[x] == h[y]) {
    sizv[x] += sizv[y];
    getv[x] ^= getv[y];
    merge(lc[x], lc[y]);
    merge(rc[x], rc[y]);
    delNode(y);
    upd(x);
  } else {
    if ((pre[y] >> h[x]) & 1) merge(rc[x], y);
    else merge(lc[x], y);
    upd(x);
  }
}

void split(int &x, int &y, int k) {
  if (!k) { y = x; x = 0; return; }
  if (k >= sizv[x]) { y = 0; return; }
  pushd(x);
  if (h[x] == L) {
    y = newNode();
    h[y] = h[x]; pre[y] = pre[x]; sizv[y] = sizv[x] - k;
    seta[y] = seta[x]; setb[y] = setb[x]; sortv[y] = sortv[x];
    sizv[x] = k;
    getv[y] = sizv[y] & 1 ? pre[y] : 0;
    getv[x] = sizv[x] & 1 ? pre[x] : 0;
    return;
  }
  if (sizv[lc[x]] >= k)
    y = x, split(x = lc[x], lc[y], k);
  else
    split(rc[x], y, k - sizv[lc[x]]);
  if (h[x] < L) {
    if (!lc[x] || !rc[x]) {
      delNode(x); x = lc[x] | rc[x];
    } else upd(x);
  }
  if (h[y] < L) {
    if (!lc[y] || !rc[y]) {
      delNode(y); y = lc[y] | rc[y];
    } else upd(y);
  }
}

};

int n, m, rt[N], setv[N << 2], sizv[N << 2], getv[N << 2];

inline void upd(int o, int l, int r) {
  if (l == r) {
    getv[o] = CT::getv[rt[l]];
    sizv[o] = CT::sizv[rt[l]];
  } else {
    getv[o] = getv[o << 1] ^ getv[o << 1 | 1];
    sizv[o] = sizv[o << 1] + sizv[o << 1 | 1];
  }
  if (sizv[o] & 1) getv[o] ^= setv[o];
}

inline void set(int o, int v) {
  setv[o] ^= v;
  if (sizv[o] & 1) getv[o] ^= v;
}

inline void pushd(int o, int l, int r) {
  if (l == r) {
    CT::set(rt[l], setv[o]);
  } else {
    set(o << 1, setv[o]); set(o << 1 | 1, setv[o]);
  }
  setv[o] = 0;
}

void Merge(int o, int l, int r, int L, int R, int &res) {
  if (r < L || R < l || !sizv[o]) return;
  pushd(o, l, r);
  if (l == r) CT::sort(rt[l]), CT::merge(res, rt[l]), rt[l] = 0;
  else {
    int mid = (l + r) / 2;
    Merge(o << 1, l, mid, L, R, res);
    Merge(o << 1 | 1, mid + 1, r, L, R, res);
  }
  upd(o, l, r);
}

void modifyRt(int o, int l, int r, int x) {
  if (l != r) pushd(o, l, r);
  else setv[o] = 0;
  if (l != r) {
    int mid = (l + r) / 2;
    if (x <= mid) modifyRt(o << 1, l, mid, x);
    else modifyRt(o << 1 | 1, mid + 1, r, x);
  }
  upd(o, l, r);
}

void Build(int o, int l, int r) {
  if (l < r) {
    int mid = (l + r) / 2;
    Build(o << 1, l, mid);
    Build(o << 1 | 1, mid + 1, r);
  }
  upd(o, l, r);
}

void Set(int o, int l, int r, int L, int R, int v) {
  if (r < L || R < l) return;
  if (L <= l && r <= R) return set(o, v);
  pushd(o, l, r);
  int mid = (l + r) / 2;
  Set(o << 1, l, mid, L, R, v);
  Set(o << 1 | 1, mid + 1, r, L, R, v);
  upd(o, l, r);
}

int FindIn(int o, int l, int r, int x) {
  if (!sizv[o]) return 0;
  pushd(o, l, r);
  if (l == r) return l;
  int ans, mid = (l + r) / 2;
  if (x <= mid || !(ans = FindIn(o << 1 | 1, mid + 1, r, x)))
    return FindIn(o << 1, l, mid, x);
  else
    return ans;
}

int Query(int o, int l, int r, int L, int R) {
  if (r < L || R < l) return 0;
  if (L <= l && r <= R) return getv[o];
  pushd(o, l, r);
  int mid = (l + r) / 2;
  return Query(o << 1, l, mid, L, R) ^ Query(o << 1 | 1, mid + 1, r, L, R);
}

inline void Split(int i) {
  if (i == n + 1) return;
  int l = FindIn(1, 1, n, i);
  if (i == l) return;
  CT::split(rt[l], rt[i], i - l);
  modifyRt(1, 1, n, l);
  modifyRt(1, 1, n, i);
}

int main() {
  freopen("save.in", "r", stdin);
  freopen("save.out", "w", stdout);
  for (int i = 1; i < (1 << 15); ++i)
    revv[i] = (i & 1) << 14 | revv[i >> 1] >> 1;
  n = read(); m = read();
  CT::Init();
  for (int i = 1; i <= n; ++i)
    rt[i] = CT::newNode(rev(read()));
  Build(1, 1, n);
  while (m--) {
    int op = read(), x = read(), y = read();
    Split(x); Split(y + 1);
    if (op == 1) {
      Set(1, 1, n, x, y, rev(read()));
    } else if (op == 2) {
      int t = 0;
      Merge(1, 1, n, x, y, t);
      CT::sort(rt[x] = t);
      modifyRt(1, 1, n, x);
    } else {
      printf("%d\n", rev(Query(1, 1, n, x, y)));
    }
  }
}