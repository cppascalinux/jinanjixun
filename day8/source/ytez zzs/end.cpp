#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
const int maxs = 1 << 7;
typedef long long ll;
const int ha = 1000000007LL;
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

typedef ll Mat[maxs][maxs];
void mat_mul(Mat A, Mat B, int n, int m, int p, Mat &res) {
  static Mat C; memset(C, 0, sizeof(C));
  for(int i = 0; i < n; i ++) {
    for(int j = 0; j < p; j ++) {
      for(int k = 0; k < m; k ++) {
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % ha;
      }
    }
  }
  memcpy(res, C, sizeof(C));
}
void mat_pow(Mat A, int n, int c, Mat &C) {
  static Mat ans, res;
  memcpy(res, A, sizeof(res));
  memset(ans, 0, sizeof(ans));
  for(int i = 0; i < n; i ++) ans[i][i] = 1;
  while(c) {
    if(1 & c) mat_mul(ans, res, n, n, n, ans);
    mat_mul(res, res, n, n, n, res); c >>= 1;
  }
  memcpy(C, ans, sizeof(ans));
}

int n, k, L;
Mat trans_0;
inline void gen_mat_0() {
  memset(trans_0, 0, sizeof(trans_0));
  for(int s = 0; s < (1 << n); s ++) {
    for(int t = 0; t < (1 << n); t ++) {
      int t_cnt = 0;
      for(int i = 0; i < n; i ++) if((1 << i) & t) t_cnt ++;
      if(1 & t_cnt) continue;
      int ns = s; bool ok = true;
      for(int i = 0; i < n; i ++) {
        if((1 << i) & s) {
          if((1 << i) & t) {
            ok = false; break;
          }
        }
      }
      if(ok) trans_0[ns][s] ++;
    }
  }
#ifdef LOCAL
  puts("Mat 0 :");
  for(int i = 0; i < (1 << n); i ++) {
    for(int j = 0; j < (1 << n); j ++) {
      printf("%lld ", trans_0[i][j]);
    }
    puts("");
  }
#endif
}

Mat trans_1;
inline void gen_mat_1() {
  memset(trans_1, 0, sizeof(trans_1));
  for(int s = 0; s < (1 << n); s ++) {
    for(int t = 0; t < (1 << n); t ++) {
      int t_cnt = 0;
      for(int i = 0; i < n; i ++) if((1 << i) & t) t_cnt ++;
      if(1 & t_cnt) continue;
      int ns = s;
      for(int i = 0; i < n; i ++) {
        if((1 << i) & s) {
          if(!((1 << i) & t)) {
            ns ^= (1 << i);
          }
        }
      }
      trans_1[ns][s] ++;
    }
  }
#ifdef LOCAL
  puts("Mat 1 :");
  for(int i = 0; i < (1 << n); i ++) {
    for(int j = 0; j < (1 << n); j ++) {
      printf("%lld ", trans_1[i][j]);
    }
    puts("");
  }
#endif
}

const int maxn = 100005;
char S[maxn];
namespace BF_1 {
  Mat tmp, vec;
  ll solve_r(int th) {
    n = th;
    memset(tmp, 0, sizeof(tmp));
    memset(vec, 0, sizeof(vec));
    const int s = (1 << n);
    gen_mat_0(); gen_mat_1();
    for(int i = 0; i < s; i ++) {
      tmp[i][i] = 1;
    }
    for(int i = 0; i < L; i ++) {
      if(S[i] == '1') {
        mat_mul(trans_1, tmp, s, s, s, tmp);
      } else {
        mat_mul(trans_0, tmp, s, s, s, tmp);
      }
    }
    mat_pow(tmp, s, k, tmp);
#ifdef LOCAL
    printf("Transform matrix %d :\n", th);
    for(int i = 0; i < s; i ++) {
      for(int j = 0; j < s; j ++) {
        printf("%lld ", tmp[i][j]);
      }
      puts("");
    }
#endif
    vec[s - 1][0] = 1;
    mat_mul(tmp, vec, s, s, 1, vec);
    ll ans = 0;
    return vec[0][0];
  }
  
  ll p_ans[15], n_pw;
  ll fac[15]; int bel[15];
  ll dfs(int p, int id) {
    if(p > n) {
      static int sz[15];
      memset(sz, 0, sizeof(sz));
      for(int i = 1; i <= n; i ++) sz[bel[i]] ++;
      ll xi = (1 & (n - id)) ? (ha - 1LL) : 1LL;
      int rcnt = 0;
      for(int i = 1; i <= id; i ++) {
        xi = xi * fac[sz[i] - 1] % ha;
        if(1 & sz[i]) {
          rcnt ++;
        } else {
          xi = xi * n_pw % ha;
        }
      }
      return xi * p_ans[rcnt] % ha;
    }
    ll ans = 0;
    for(int i = 1; i <= id + 1; i ++) {
      bel[p] = i;
      ans = (ans + dfs(p + 1, std::max(i, id))) % ha;
    }
    return ans;
  }
  void solve() {
    fac[0] = 1;
    for(int i = 1; i <= 10; i ++) fac[i] = fac[i - 1] * i % ha;
    ll n_rv = 0, sum_pw = 0;
    for(int i = 0; i < L; i ++) {
      n_rv = ((n_rv << 1) + (ll(S[i] - '0'))) % ha;
    }
    for(int i = 0; i < k; i ++) {
      sum_pw = (sum_pw + pow_mod(2, (ll)i * (ll)L)) % ha;
    }
    n_pw = n_rv * sum_pw % ha;
#ifdef LOCAL
    printf("n_pw : %lld\n", n_pw);
#endif
    const int pn = n;
    for(int i = pn; i > 0; i -= 2) {
      p_ans[i] = solve_r(i);
    }
    n = pn;
    printf("%d\n", int(dfs(1, 0) * inv(fac[n]) % ha));
  }
};

int main() {
#ifndef WOEE
  freopen("end.in", "r", stdin);
  freopen("end.out", "w", stdout);
#endif
  scanf("%d%d%s", &n, &k, S); L = strlen(S);
  if(L <= 50) {
    BF_1::solve();
  }
  return 0;
}
