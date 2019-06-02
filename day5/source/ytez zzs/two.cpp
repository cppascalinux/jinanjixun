#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <set>
const int maxn = 100005;
int n, k;
namespace ValSeg {
  const int maxno = maxn << 3;
  int sumv[maxno], cntv[maxno];
  bool empty_v[maxno];
  inline void maintain(int o) {
    const int lc = o << 1, rc = o << 1 | 1;
    sumv[o] = sumv[lc] + sumv[rc];
  }
  inline void paint(int o) {
    empty_v[o] = true;
    sumv[o] = 0;
  }
  inline void pushdown(int o) {
    if(empty_v[o]) {
      paint(o << 1);
      paint(o << 1 | 1);
      empty_v[o] = false;
    }
  }
  void modify(int o, int L, int R, int p, int v) {
    if(L == R) {
      empty_v[o] = false;
      sumv[o] += v;
    } else {
      pushdown(o);
      int M = (L + R) / 2;
      if(p <= M) modify(o << 1, L, M, p, v);
      else modify(o << 1 | 1, M + 1, R, p, v);
      maintain(o);
    }
  }
  void modify(int p, int v) {
    modify(1, 1, n, p, v);
  }
  int kth(int o, int L, int R, int s) {
    if(L == R) {
      if(sumv[o] == s) return L;
      else return -1;
    } else {
      pushdown(o);
      const int M = (L + R) / 2;
      const int lc = o << 1, rc = o << 1 | 1;
      if(sumv[lc] >= s) {
        return kth(lc, L, M, s);
      } else {
        return kth(rc, M + 1, R, s - sumv[lc]);
      }
    }
  }
  int kth(int s) {
#ifdef LOCAL
    printf("Querying %d-th (al_siz : %d)\n", s, sumv[1]);
#endif
    if(s == 0) return 1;
    if(sumv[1] < s || s < 0) return -1;
    else return kth(1, 1, n, s);
  }
  
  int kth_s(int o, int L, int R, int s) {
    if(L == R) {
      return L;
    } else {
      pushdown(o);
      const int M = (L + R) / 2;
      const int lc = o << 1, rc = o << 1 | 1;
      if(sumv[lc] >= s) {
        return kth_s(lc, L, M, s);
      } else {
        return kth_s(rc, M + 1, R, s - sumv[lc]);
      }
    }
  }
  int kth_s(int s) {
    if(s == 0) return 1;
    if(sumv[1] < s || s < 0) return -1;
    else return kth_s(1, 1, n, s);
  }
};

typedef std::set<int>::iterator iter_t;
std::set<int> *merge(std::set<int> *A, std::set<int> *B) {
  using namespace ValSeg;
  if(A -> size() < B -> size()) std::swap(A, B);
  for(iter_t it = B -> begin(); it != B -> end(); ++ it) {
    const int val = *it;
    iter_t ri = A -> lower_bound(val);
    if(ri == A -> end()) {
      -- ri;
      int l = *ri;
      modify(val - l, 1);
    } else if(ri == A -> begin()) {
      modify(*ri - val, 1);
    } else {
      const int r = *ri;
      -- ri; const int l = *ri;
      modify(r - l, -1);
      modify(val - l, 1);
      modify(r - val, 1);
    }
    A -> insert(val);
  }
  delete B;
  return A;
}

const int maxno = maxn << 1;
std::vector<int> son[maxno];
int fa[maxno], len[maxno];
int go[maxno][26], end_p[maxno];
int cnt = 0, las, rt;
inline void init_sam() {
  ++ cnt;
  las = rt = cnt;
  fa[rt] = 0; len[rt] = 0;
}
inline void insert(int id, char ch) {
  int c = ch - 'a';
  int np = ++ cnt;
  end_p[np] = id;
  len[np] = len[las] + 1;
  int p = las;
  while(p && go[p][c] == 0) {
    go[p][c] = np;
    p = fa[p];
  }
  if(!p) {
    fa[np] = rt;
  } else {
    int q = go[p][c];
    if(len[p] + 1 == len[q]) {
      fa[np] = q;
    } else {
      int nq = ++ cnt;
      fa[nq] = fa[q]; len[nq] = len[p] + 1;
      memcpy(go[nq], go[q], sizeof(go[q]));
      fa[q] = fa[np] = nq;
      while(p && go[p][c] == q) {
        go[p][c] = nq;
        p = fa[p];
      }
    }
  }
  las = np;
}

int siz[maxno], nod[maxno], hson[maxno];
void dfs_1(int x) {
  siz[x] = 1;
  if(end_p[x]) nod[x] = 1;
  int max_siz = 0;
  for(int i = 0; i < son[x].size(); i ++) {
    int v = son[x][i];
    dfs_1(v); siz[x] += siz[v];
    nod[x] += nod[v];
    if(siz[v] > max_siz) {
      max_siz = siz[v];
      hson[x] = v;
    }
  }
}

typedef long long ll;
ll ans = 0;
std::set<int> *dfs(int x) {
  std::set<int> *S = new std::set<int>();
  if(end_p[x]) {
    S -> insert(end_p[x]);
  }
  std::vector<std::set<int>*> V;
  for(int i = 0; i < son[x].size(); i ++) {
    int v = son[x][i];
    if(v != hson[x]) {
      ValSeg::paint(1);
      V.push_back(dfs(v));
    }
  }
  if(!hson[x]) {
    if(k == 1) ans += len[x] - len[fa[x]];
    ValSeg::paint(1); return S;
  }
  S = merge(dfs(hson[x]), S);
#ifdef LOCAL
  printf("Node (%d, %d)\n", x, len[x]);
#endif
  for(int i = 0; i < V.size(); i ++) {
    S = merge(S, V[i]);
  }
  // assert(ValSeg::sumv[1] + 1 == nod[x]);
  if(x == 1) return S;
  int minl = ValSeg::kth(S -> size() - k);
#ifdef LOCAL
  printf("minl : %d\n", minl);
#endif
  if(minl == -1 || minl > len[x]) {
    ;
  } else {
    int rp = ValSeg::kth_s(S -> size() - k + 1);
    if(rp == -1) rp = len[x] + 1;
    rp = std::min(rp, len[x] + 1);
    ans += std::max(0, rp - std::max(minl, len[fa[x]] + 1));
  }
  return S;
}

char S[maxn];
void solve() {
  init_sam();
  for(int i = 1; i <= n; i ++) insert(i, S[i]);
#ifdef LOCAL
  printf("cnt : %d\n", cnt);
#endif
  for(int i = 2; i <= cnt; i ++) son[fa[i]].push_back(i);
  dfs_1(1);
  delete (dfs(1));
  printf("%lld\n", ans);
}

int main() {
#ifndef LOCAL
  freopen("two.in", "r", stdin);
  freopen("two.out", "w", stdout);
#endif
  scanf("%s%d", S + 1, &k);
  n = strlen(S + 1);
  solve();
  return 0;
}
