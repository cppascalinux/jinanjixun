#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
const int maxn = 100005;
int n, m;
int A[maxn], que[maxn][4];
namespace BF_1 {
  void solve() {
    for(int i = 1; i <= m; i ++) {
      const int op = que[i][0], l = que[i][1], r = que[i][2];
      if(op == 1) {
        const int x = que[i][3];
        for(int i = l; i <= r; i ++) A[i] ^= x;
      } else if(op == 2) {
        std::sort(A + l, A + r + 1);
      } else {
        int ans = 0;
        for(int i = l; i <= r; i ++) ans ^= A[i];
        printf("%d\n", ans);
      }
    }
  }
};

namespace CT_3 {
  int C[2][maxn];
  inline int lowbit(int x) {
    return x & (-x);
  }
  void add(int p, int v) {
    int *V = C[p & 1];
    while(p <= n) {
      V[p] ^= v;
      p += lowbit(p);
    }
  }
  int sum(int p) {
    int *V = C[p & 1];
    int ans = 0;
    while(p > 0) {
      ans ^= V[p];
      p -= lowbit(p);
    }
    return ans;
  }
  int query(int l, int r) {
    return sum(r) ^ sum(l - 1);
  }
  
  void solve() {
    for(int i = 1; i <= n; i ++) {
      add(i, A[i]); add(i + 1, A[i]);
    }
    for(int i = 1; i <= m; i ++) {
      const int op = que[i][0], l = que[i][1], r = que[i][2];
      if(op == 1) {
        const int x = que[i][3];
        add(l, x); add(r + 1, x);
      } else {
        printf("%d\n", query(l, r));
      }
    }
  }
};

int main() {
#ifndef WOEE
  freopen("save.in", "r", stdin);
  freopen("save.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) scanf("%d", &A[i]);
  bool case_3 = true;
  for(int i = 1; i <= m; i ++) {
    int *th = que[i];
    scanf("%d%d%d", &th[0], &th[1], &th[2]);
    if(th[0] == 1) scanf("%d", &th[3]);
    if(th[0] == 2) case_3 = false;
  }
  if(case_3) {
    CT_3::solve();
  } else {
    BF_1::solve();
  }
  return 0;
}
