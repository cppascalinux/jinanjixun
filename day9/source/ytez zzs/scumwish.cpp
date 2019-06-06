#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
const int maxn = 14;
const int ha = 100000007;
int d[maxn][maxn][1 << 10]; int n, m;
int ban_1[maxn][maxn], ban_2[maxn][maxn];
int dp(int i, int j, int s) {
  if(i > n) {
    if(s == ((1 << m) - 1)) return 1;
    else return 0;
  }
  int &ans = d[i][j][s];
  if(ans != -1) return ans;
  ans = 0;
  int ni, nj;
  if(j < m) ni = i, nj = j + 1;
  else ni = i + 1, nj = 1;
  if((1 << (j - 1)) & s) {
    ans = (dp(ni, nj, s) + dp(ni, nj, s ^ (1 << (j - 1))));
    if(ans >= ha) ans -= ha;
    if(j > 1 && !((1 << (j - 2)) & s) && ban_1[i][j - 1]) {
      ans += dp(ni, nj, s | (1 << (j - 2)));
      if(ans >= ha) ans -= ha;
    }
  } else if(ban_2[i - 1][j]) {
    int bs = s | (1 << (j - 1));
    ans = dp(ni, nj, bs);
    if(j > 1 && !((1 << (j - 2)) & s) && ban_1[i][j - 1]) {
      ans += dp(ni, nj, bs | (1 << (j - 2)));
      if(ans >= ha) ans -= ha;
    }
    if(j < m && !((1 << j) & s) && ban_1[i - 1][j]) {
      ans += dp(ni, nj, bs | (1 << j));
      if(ans >= ha) ans -= ha;
    }
  }
#ifdef LOCAL
  printf("State (%d, %d, %d) : %d\n", i, j, s, ans);
#endif
  return ans;
}


int main() {
#ifndef WOEE
  freopen("scumwish.in", "r", stdin);
  freopen("scumwish.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  memset(d, 0xff, sizeof(d));
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j < m; j ++) {
      scanf("%d", &ban_1[i][j]);
    }
  }
  for(int i = 1; i < n; i ++) {
    for(int j = 1; j <= m; j ++) {
      scanf("%d", &ban_2[i][j]);
    }
  }
  printf("%d\n", dp(1, 1, (1 << m) - 1));
  return 0;
}
