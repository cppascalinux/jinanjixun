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
#include <set>
const int maxn = 100005;
using ll = long long;
using pii = std::pair<int, ll>;
std::vector<pii> G[maxn];
inline void ins_edge(int u, int v, ll w) {
  G[u].push_back({v, w});
  G[v].push_back({u, w});
}

int n, m;
ll ew[maxn];
namespace BF_1 {
  
};

namespace CT_4 {
  void solve() {
    ll ans = 0;
    std::priority_queue<ll> Q;
    for(auto e : G[1]) {
      ans += e.second << 1;
      Q.push(e.second);
    }
    printf("%lld", ans);
    for(int i = 1; i <= m; i ++) {
      ll w = ew[i];
      if(w < Q.top()) {
        ans -= Q.top() << 1; Q.pop();
        ans += w << 1; Q.push(w);
      }
      printf(" %lld", ans);
    }
    puts("");
  }
};

int main() {
#ifndef LOCAL
  freopen("love.in", "r", stdin);
  freopen("love.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  bool is_1 = true;
  for(int i = 1; i <= n - 1; i ++) {
    int u, v, w; scanf("%d%d%d", &u, &v, &w);
    if(u > v) std::swap(u, v);
    is_1 &= (u == 1);
    ins_edge(u, v, w);
  }
  for(int i = 1; i <= m; i ++) {
    scanf("%lld", &ew[i]);
  }
  if(is_1) {
    CT_4::solve();
  }
  return 0;
}
