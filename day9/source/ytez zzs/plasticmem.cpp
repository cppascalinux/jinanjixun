#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
const int maxn = 100005;
int n, m, A[maxn];
namespace BF {
  void solve() {
    while(m --) {
      int op, l, r; scanf("%d%d%d", &op, &l, &r);
      if(op == 1) {
        std::fill(A + l, A + r + 1, 0);
      } else if(op == 2) {
        std::fill(A + l, A + r + 1, 1);
      } else if(op == 3) {
        for(int i = l; i < r; i ++) A[i] |= A[i + 1];
      } else if(op == 4) {
        for(int i = r; i > l; i --) A[i] |= A[i - 1];
      } else if(op == 5) {
        for(int i = l; i < r; i ++) A[i] &= A[i + 1];
      } else if(op == 6) {
        for(int i = r; i > l; i --) A[i] &= A[i - 1];
      } else {
        int ans = 0;
        for(int i = l; i <= r; i ++) ans += A[i];
        printf("%d\n", ans);
      }
    }
  }
};

int main() {
#ifndef WOEE
  freopen("plasticmem.in", "r", stdin);
  freopen("plasticmem.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) scanf("%d", &A[i]);
  if(n <= 1000 && m <= 1000) {
    BF::solve();
  }
  return 0;
}
