#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

#define mp std::make_pair
typedef std::pair<int, int> PI;
const int N = 200050;

int ch[N][26], fa[N], len[N], last, cnt;
bool vis[N];

int n, k;
long long ans;
char s[N];

inline void Init() {
  cnt = 1; last = 0;
  fa[0] = -1;
}

void ins(int c) {
  int nw = cnt++, p = last;
  vis[nw] = true;
  len[nw] = len[last] + 1;
  last = nw;
  for (; ~p && !ch[p][c]; p = fa[p]) ch[p][c] = nw;
  if (p == -1) {
    fa[nw] = 0;
    return;
  } else {
    int np = ch[p][c];
    if (len[np] == len[p] + 1) {
      fa[nw] = np;
      return;
    } else {
      int nq = cnt++;
      len[nq] = len[p] + 1; fa[nq] = fa[np];
      memcpy(ch[nq], ch[np], sizeof ch[np]);
      fa[np] = fa[nw] = nq;
      for (; ~p && ch[p][c] == np; p = fa[p])
        ch[p][c] = nq;
    }
  }
}

std::set<int> S;

int sizv[N << 2];
void Modify(int o, int l, int r, int x, int v) {
  sizv[o] += v;
  if (l == r) return;
  int mid = (l + r) / 2;
  if (x <= mid) Modify(o << 1, l, mid, x, v);
  else Modify(o << 1 | 1, mid + 1, r, x, v);
}

void Clear(int o, int l, int r) {
  if (!sizv[o]) return;
  sizv[o] = 0;
  if (l == r) return;
  int mid = (l + r) / 2;
  Clear(o << 1, l, mid);
  Clear(o << 1 | 1, mid + 1, r);
}

int kth(int o, int l, int r, int k) {
  if (!k) return 0x3f3f3f3f;
  if (k > sizv[o]) return -0x3f3f3f3f;
  if (l == r) return l;
  int mid = (l + r) / 2;
  if (sizv[o << 1 | 1] >= k) return kth(o << 1 | 1, mid + 1, r, k);
  else return kth(o << 1, l, mid, k - sizv[o << 1 | 1]);
}

void Ins(int x) {
  std::set<int>::iterator it = S.lower_bound(x);
  if (it != S.end() && it != S.begin()) {
    std::set<int>::iterator t = it;
    --t;
    Modify(1, 1, n, *it - *t, -1);
  }
  if (it != S.end())
    Modify(1, 1, n, *it - x, 1);
  if (it != S.begin())
    Modify(1, 1, n, x - *(--it), 1);
  S.insert(x);
}

int ls[N], rb[N], siz[N], son[N];

inline void addEdge(int f, int x) {
  rb[x] = ls[f]; ls[f] = x;
}

int dfs0(int x) {
  son[x] = -1;
  siz[x] = 1;
  for (int y = ls[x]; y; y = rb[y]) {
    siz[x] += dfs0(y);
    if (son[x] == -1 || siz[y] > siz[son[x]]) son[x] = y;
  }
  return siz[x];
}

void dfs_ins(int x) {
  if (vis[x]) Ins(len[x]);
  for (int y = ls[x]; y; y = rb[y])
    dfs_ins(y);
}

void printS() {
  printf("{ ");
  for (std::set<int>::iterator it = S.begin(); it != S.end(); ++it)
    printf("%d, ", *it);
  printf("}");
}

void dfs1(int x, int lenf) {
  for (int y = ls[x]; y; y = rb[y])
    if (y != son[x]) dfs1(y, len[x]);
  Clear(1, 1, n); S.clear();
  if (son[x] > 0) dfs1(son[x], len[x]);
  if (vis[x]) Ins(len[x]);
  for (int y = ls[x]; y; y = rb[y])
    if (y != son[x]) dfs_ins(y);
  // printS(); printf(" %d\n", len[x]);
  if (x > 0 && sizv[1] >= k - 1) {
    int l1 = lenf + 1, r1 = len[x];
    int l2 = kth(1, 1, n, k), r2 = kth(1, 1, n, k - 1) - 1;
    int l = std::max(l1, l2), r = std::min(r1, r2);
    ans += std::max(r - l + 1, 0);
  }
}

int main() {
  freopen("two.in", "r", stdin);
  freopen("two.out", "w", stdout);
  scanf("%s%d", s, &k);
  n = strlen(s); Init();
  for (int i = 0; i < n; ++i) ins(s[i] - 'a');
  for (int i = 1; i < cnt; ++i)
    addEdge(fa[i], i);
  dfs0(0);
  dfs1(0, 0);
  printf("%lld\n", ans);
}