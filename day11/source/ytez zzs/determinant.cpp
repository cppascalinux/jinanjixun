#include <cstdio> 
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <ext/pb_ds/priority_queue.hpp>
using ll = long long;
const ll ha = 1000000007LL;
inline ll pow_mod(ll a, ll b) {
  ll ans = 1, res = a;
  while(b) {
    if(1LL & b) ans = ans * res % ha;
    res = res * res % ha; b >>= 1;
  }
  return ans;
}
inline ll inv(ll x) {
  return pow_mod(x, ha - 2LL);
}

const int maxn = 100005;
struct Rect {
  int x1, y1, x2, y2;
  Rect(int a = 0, int b = 0, int c = 0, int d = 0) {
    x1 = a; y1 = b; x2 = c; y2 = d;
  }
  bool operator <(const Rect &res) const {
    if(x1 == res.x1) {
      return x2 < res.x2;
    } else {
      return x1 < res.x1;
    }
  }
};
Rect rec[maxn]; int n;

namespace DET {
  struct N2 {
    int r, id;
    N2() {
      r = 0; id = 0;
    }
    N2(int x, int y) {
      r = x; id = y;
    }
    bool operator <(const N2 &res) const {
      if(r == res.r) {
        return id < res.id;
      } else {
        return r < res.r;
      }
    }
    bool operator >(const N2 &res) const {
      if(r == res.r) {
        return id > res.id;
      } else {
        return r > res.r;
      }
    }
    bool operator ==(const N2 &res) const {
      return (r == res.r) && (id == res.id);
    }
  };
   
  int par[maxn * 2];
  int get_fa(int x) {
    if(par[x] == x) return x;
    else return (par[x] = get_fa(par[x]));
  }
  void merge(int dir, int src) {
    dir = get_fa(dir); src = get_fa(src);
    if(dir == src) return;
    par[src] = dir;
  }
  bool is_same(int x, int y) {
    return (get_fa(x) == get_fa(y));
  }
   
  using Heap = __gnu_pbds::priority_queue<N2, std::greater<N2> >;
  Heap Q[maxn];
  int id[maxn], mp[maxn];
  int seg[maxn][2];
  void clear() {
    for(int i = 1; i <= n; i ++) {
      Q[i].clear();
    }
    for(int i = 1; i <= 2 * n; i ++) {
      par[i] = i;
    }
    for(int i = 1; i <= n; i ++) seg[i][0] = seg[i][1] = 0;
    for(int i = 1; i <= n; i ++) id[i] = mp[i] = i;
  }
  void insert(int L, int R, int id) {
    Q[L].push(N2(R, id));
    merge(L, n + id);
    seg[id][0] = L; seg[id][1] = R;
  }
  int det() {
    int flag = 1;
    for(int i = 1; i <= n; i ++) {
      if(Q[i].empty()) {
        return 0;
      }
      int p = id[i];
      if(!(get_fa(p + n) <= i && seg[p][1] == (Q[i].top()).r)) {
        flag *= -1;
        int np = (Q[i].top()).id;
        int nv = mp[np];
        std::swap(id[i], id[nv]);
        std::swap(mp[np], mp[p]);
      }
      p = id[i];
      Q[i].pop();
      int r = seg[p][1];
      if(Q[i].size() > 0 && (Q[i].top()).r == r) {
        return 0;
      }
      if(r < n) {
        Q[r + 1].join(Q[i]);
        merge(r + 1, i);
      }
    }
    return flag;
  }
  ll solve() {
    return (ha + det()) % ha;
  }
};

namespace Case_x {
  ll solve() {
    DET::clear();
    for(int i = 1; i <= n; i ++) {
      if(rec[i].x1 != i) {
        return 0;
      }
      DET::insert(rec[i].y1, rec[i].y2, i);
    }
    return DET::solve();
  }
};

namespace CT_1 {
  ll solve() {
    DET::clear();
    for(int i = 1; i <= n; i ++) {
      DET::insert(rec[i].x1, rec[i].x2, i);
    }
    ll ans = DET::solve();
    DET::clear();
    for(int i = 1; i <= n; i ++) {
      DET::insert(rec[i].y1, rec[i].y2, i);
    }
    ans = ans * DET::solve() % ha;
    return ans;
  }
};

int main() {
#ifndef WOEE
  freopen("determinant.in", "r", stdin);
  freopen("determinant.out", "w", stdout);
#endif
  int T; scanf("%d", &T);
  while(T --) {
    scanf("%d", &n);
    bool ct_x = true;
    ll dv = 1;
    for(int i = 1; i <= n; i ++) {
      Rect &p = rec[i];
      scanf("%d%d%d%d", &p.x1, &p.x2, &p.y1, &p.y2);
      dv = dv * inv((ll(p.x2 - p.x1 + 1)) * (ll(p.y2 - p.y1 + 1)) % ha);
      if(p.x1 != p.x2) ct_x = false;
    }
    std::sort(rec + 1, rec + 1 + n);
    ll ans;
    if(ct_x) {
      ans = Case_x::solve();
    } else {
      ans = CT_1::solve();
    }
    ans = ans * dv % ha;
    printf("%d\n", (int)ans);
  }
  return 0;
}
