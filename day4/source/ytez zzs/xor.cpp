#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <set>
int m, q;

namespace BF_1 {
  int B[31], r;
  void insert(int x) {
    for(int i = m - 1; i >= 0; i --) {
      if(B[i]) {
        x ^= B[i];
      } else {
        B[i] = x; r ++;
        return;
      }
    }
  }
  void solve() {
    std::set<int> S; r = 0;
    while(q --) {
      int op, x; scanf("%d%d", &op, &x);
      if(op == 1) {
        S.insert(x);
        insert(x);
      } else {
        S.erase(x);
        memset(B, 0, sizeof(B)); r = 0;
        for(std::set<int>::iterator it = S.begin(); it != S.end(); ++ it) {
          insert(*it);
        }
      }
      printf("%d\n", 1 << r);
    }
  }
};

int main() {
#ifndef LOCAL
  freopen("xor.in", "r", stdin);
  freopen("xor.out", "w", stdout);
#endif
  scanf("%d%d", &m, &q);
  BF_1::solve();
  return 0;
}
