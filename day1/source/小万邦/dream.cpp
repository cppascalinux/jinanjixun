#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
typedef long long ll;
const ll ha = 998244353;
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

bool is_ban[62][62][62];
ll A[62][62][62], w;

int n, m, h;
namespace BF {
  const int maxn = 22;
  int BS[maxn][maxn][maxn];
  inline int query(int i, int j, int k, int a, int b, int c) {
    int r = BS[i][j][k];
    r -= BS[i][j][c - 1] + BS[i][b - 1][k] + BS[a - 1][j][k];
    r += BS[i][b - 1][c - 1] + BS[a - 1][j][c - 1] + BS[a - 1][b - 1][k];
    r -= BS[a - 1][b - 1][c - 1];
#ifdef LOCAL
    // printf("Rec (%d, %d, %d, %d, %d, %d) : %d\n", i, j, k, a, b, c, r);
#endif
    return r;
  }
  int S[maxn][maxn][maxn];
  inline void add(int x, int y, int z, int val) {
    S[x][y][z] += val;
  }
  inline void add(int i, int j, int k, int a, int b, int c) {
    add(a, b, c, 1);
    add(i + 1, b, c, -1); add(a, j + 1, c, -1); add(a, b, k + 1, -1);
    add(i + 1, j + 1, c, 1); add(i + 1, b, k + 1, 1); add(a, j + 1, k + 1, 1);
    add(i + 1, j + 1, k + 1, -1);
  }
  
  int S_2D[maxn][maxn];
  void solve() {
    for(int i = 1; i <= n; i ++) {
      memset(S_2D, 0, sizeof(S_2D));
      for(int j = 1; j <= m; j ++) {
        for(int k = 1; k <= h; k ++) {
          S_2D[j][k] = S_2D[j - 1][k] + S_2D[j][k - 1] - S_2D[j - 1][k - 1];
          S_2D[j][k] += is_ban[i][j][k];
          BS[i][j][k] = BS[i - 1][j][k] + S_2D[j][k];
        }
      }
    }
    int al_cnt = 0;
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        for(int k = 1; k <= h; k ++) {
          for(int a = 1; a <= i; a ++) {
            for(int b = 1; b <= j; b ++) {
              for(int c = 1; c <= k; c ++) {
                if(query(i, j, k, a, b, c) == 0) {
                  al_cnt ++;
                  add(i, j, k, a, b, c);
                }
              }
            }
          }
        }
      }
    }
    for(int i = 1; i <= n; i ++) {
      memset(S_2D, 0, sizeof(S_2D));
      for(int j = 1; j <= m; j ++) {
        for(int k = 1; k <= h; k ++) {
          int &t_2 = S_2D[j][k];
          t_2 = S_2D[j - 1][k] + S_2D[j][k - 1] - S_2D[j - 1][k - 1];
          t_2 += S[i][j][k];
          S[i][j][k] = t_2 + S[i - 1][j][k];
#ifdef LOCAL
          // printf("Rec num (%d, %d, %d) : %d\n", i, j, k, S[i][j][k]);
#endif
        }
      }
    }
    ll num = n * (n + 1) * m * (m + 1) * h * (h + 1) / 8;
    ll good_prob = pow_mod((ll)al_cnt * inv(num) % ha, w);
    ll ans = 0, al_inv = inv(num);
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        for(int k = 1; k <= h; k ++) {
          ll f_prob = (ll(al_cnt - S[i][j][k])) * al_inv % ha;
          ll prob = (good_prob - pow_mod(f_prob, w) + ha) % ha;
          ans = (ans + prob * A[i][j][k]) % ha;
        }
      }
    }
    printf("%lld\n", ans);
  }
};

namespace BF_2 {
  const int maxn = 62;
  int minv_n[maxn][maxn][maxn][maxn], minv_m[maxn][maxn][maxn][maxn];
  void process() {
    for(int t = 1; t <= h; t ++) {
      for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
          minv_n[t][i][j][j] = minv_n[t - 1][i][j][j];
          if(is_ban[i][j][t]) minv_n[t][i][j][j] = t;
        }
        for(int L = 2; L <= m; L ++) {
          for(int j = 1; j + L - 1 <= m; j ++) {
            const int k = j + L - 1;
            minv_n[t][i][j][k] = std::max(minv_n[t][i][j][k - 1], minv_n[t][i][k][k]);
          }
        }
      }
    }
    for(int t = 1; t <= h; t ++) {
      for(int i = 1; i <= m; i ++) {
        for(int j = 1; j <= n; j ++) {
          minv_m[t][i][j][j] = minv_m[t - 1][i][j][j];
          if(is_ban[j][i][t]) minv_m[t][i][j][j] = t;
        }
        for(int L = 2; L <= n; L ++) {
          for(int j = 1; j + L - 1 <= n; j ++) {
            const int k = j + L - 1;
            minv_m[t][i][j][k] = std::max(minv_m[t][i][j][k - 1], minv_m[t][i][k][k]);
          }
        }
      }
    }
  }
  ll GS[maxn][maxn][maxn];
  void do_mod(int t, int a, int b, int c, int d, int xi) {
    GS[t][b][d] += xi;
    GS[t][b][c - 1] -= xi;
    GS[t][a - 1][d] -= xi;
    GS[t][a - 1][c - 1] += xi;
  }
  void solve() {
    process();
    ll al_cnt = 0;
    for(int t = 1; t <= h; t ++) {
      for(int a = 1; a <= n; a ++) {
        for(int b = a; b <= n; b ++) {
          for(int c = 1; c <= m; c ++) {
            for(int d = c; d <= m; d ++) {
              int max_d = std::max(minv_n[t][a][c][d], minv_n[t][b][c][d]);
              max_d = std::max(max_d, std::max(minv_m[t][c][a][b], minv_m[t][d][a][b]));
#ifdef LOCAL
              printf("d (%d, %d, %d, %d, %d) : %d\n", t, a, b, c, d, max_d);
#endif
              do_mod(max_d + 1, a, b, c, d, 1);
              do_mod(t + 1, a, b, c, d, -1);
              al_cnt += t - max_d;
            }
          }
        }
      }
    }
    for(int t = 1; t <= h; t ++) {
      for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
          GS[t][i][j] += GS[t][i - 1][j] + GS[t][i][j - 1] - GS[t][i - 1][j - 1];
        }
      }
      for(int i = 1; i <= n; i ++) {
        for(int j = 1; j <= m; j ++) {
          GS[t][i][j] += GS[t - 1][i][j];
#ifdef LOCAL
          printf("num[%d][%d][%d] : %lld\n", i, j, t, GS[t][i][j]);
#endif
        }
      }
    }
    ll num = n * (n + 1) * m * (m + 1) * h * (h + 1) / 8;
    ll good_prob = pow_mod((ll)al_cnt * inv(num) % ha, w);
    ll ans = 0, al_inv = inv(num);
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        for(int k = 1; k <= h; k ++) {
          ll f_prob = (ll(al_cnt - GS[k][i][j])) * al_inv % ha;
          ll prob = (good_prob - pow_mod(f_prob, w) + ha) % ha;
          ans = (ans + prob * A[i][j][k]) % ha;
        }
      }
    }
    printf("%lld\n", ans);
  }
};

int main() {
#ifndef LOCAL
  freopen("dream.in", "r", stdin);
  freopen("dream.out", "w", stdout);
#endif
  // n = m = h = 60; BF::solve(); return 0;
  scanf("%d%d%d%lld", &n, &m, &h, &w);
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      for(int k = 1; k <= h; k ++) {
        int x; scanf("%d", &x);
        is_ban[i][j][k] = 1 - x;
      }
    }
  }
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      for(int k = 1; k <= h; k ++) {
        scanf("%lld", &A[i][j][k]);
      }
    }
  }
  // BF_2::solve(); return 0;
  if(n <= 20 && m <= 20 && h <= 20) BF::solve();
  else BF_2::solve();
  return 0;
}
