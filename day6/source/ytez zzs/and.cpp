#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
typedef long long ll;
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

int b[10];
int n;
int d[2][11][2][(1 << 9) | 1][(1 << 9) | 1];
inline int get_val(int bi, int lt, int last, int s_1, int s_2) {
  if(bi < 0) return 1;
  bi &= 1;
  return d[bi][lt][last][s_1][s_2];
}
inline void do_dp(int bi, int lt, int last, int s_1, int s_2) {
  const int now = bi & 1;
  const int lp = now ^ 1;
  int &ans = d[now][lt][last][s_1][s_2];
  ans = 0;
  const int th_b = 1 << bi;
  for(int x = 0; x < 2; x ++) {
    if(lt == 1) {
      ans += d[now][lt + 1][x][s_1][s_2];
      if(ans >= ha) ans -= ha;
      continue;
    }
    int ns_1 = s_1, ns_2 = s_2;
    int th = (x) ? (th_b & b[lt]) : 0;
    int las = (last) ? (th_b & b[lt - 1]) : 0;
    if(!((1 << (lt - 2)) & s_1)) {
      if(th < las) {
        continue;
      } else if(th > las) {
        ns_1 |= (1 << (lt - 2));
      }
    }
    th = (x) ? th_b : (th_b & b[lt]);
    las = (last) ? th_b : (th_b & b[lt - 1]);
    if(!((1 << (lt - 2)) & s_2)) {
      if(th > las) {
        continue;
      } else if(th < las) {
        ns_2 |= (1 << (lt - 2));
      }
    }
    if(lt == n) ans += d[lp][1][x][ns_1][ns_2];
    else ans += d[now][lt + 1][x][ns_1][ns_2];
    if(ans >= ha) ans -= ha;
  }
}
int m;
inline int solve() {
  for(int bi = 1; bi < 2; bi ++) {
    for(int i = n; i >= 1; i --) {
      for(int last = 0; last < 2; last ++) {
        for(int s_1 = 0; s_1 < (1 << (n - 1)); s_1 ++) {
          for(int s_2 = 0; s_2 < (1 << (n - 1)); s_2 ++) {
            d[bi][i][last][s_1][s_2] = 1;
          }
        }
      }
    }
  }
  for(int bi = 0; bi < m; bi ++) {
    for(int i = n; i >= 1; i --) {
      for(int last = 0; last < 2; last ++) {
        for(int s_1 = 0; s_1 < (1 << (n - 1)); s_1 ++) {
          for(int s_2 = 0; s_2 < (1 << (n - 1)); s_2 ++) {
            do_dp(bi, i, last, s_1, s_2);
          }
        }
      }
    }
  }
  return d[(m - 1) & 1][1][0][0][0];
}

int main() {
#ifndef LOCAL
  freopen("and.in", "r", stdin);
  freopen("and.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) scanf("%d", &b[i]);
  printf("%d\n", solve());
  return 0;
}
