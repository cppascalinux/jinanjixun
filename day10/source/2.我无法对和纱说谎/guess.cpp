#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 10;
int n, a[maxn], dp[maxn][maxn]; char str[maxn];

int main(int argc, char const *argv[])
{
  freopen("guess.in", "r", stdin), freopen("guess.out", "r", stdout);

  scanf("%s", str + 1), n = strlen(str + 1);
  memset(dp, 0x3f, sizeof dp);
  for(int i = 1; i <= n; ++i) dp[i][i] = (a[i] = (str[i] ^ 48));
  for(int c = 2; c <= n; ++c) for(int l = 1; l <= n; ++l) {
      int r = l + c - 1;
      for(int i = l; i < r; ++i) dp[l][r] = min(dp[l][r], max(dp[l][i], dp[i + 1][r]) + a[i]);
  }
  printf("%d\n", dp[1][n]);

  return 0;
}