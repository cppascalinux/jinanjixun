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
std::vector<int> occur[maxn];

int main() {
#ifndef WOEE
  freopen("busy.in", "r", stdin);
  freopen("busy.out", "w", stdout);
#endif
  int n, m; scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) {
    int a; scanf("%d", &a);
    occur[a].push_back(i);
  }
  int lastans = 0;
  while(m --) {
    int op, x, y; scanf("%d%d%d", &op, &x, &y);
    x ^= lastans; y ^= lastans;
#ifdef LOCAL
    printf("True modify : %d, %d, %d\n", op, x, y);
#endif
    if(op == 1) {
      if(x != y) {
        for(int v : occur[x]) occur[y].push_back(v);
        occur[x].clear();
        std::sort(occur[y].begin(), occur[y].end());
      }
    } else {
      if(occur[x].empty() || occur[y].empty()) {
        puts("Chtholly");
        lastans = 0;
      } else {
        int ans = 200005;
        for(int v : occur[x]) {
          auto it = std::lower_bound(occur[y].begin(), occur[y].end(), v);
          if(it == occur[y].begin()) {
            ans = std::min(ans, *it - v);
          } else if(it == occur[y].end()) {
            -- it;
            ans = std::min(ans, v - *it);
          } else {
            ans = std::min(ans, *it - v);
            -- it;
            ans = std::min(ans, v - *it);
          }
        }
        printf("%d\n", lastans = ans);
      }
    }
  }
  return 0;
}
