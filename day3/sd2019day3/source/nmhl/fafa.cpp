#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, a[maxn], dp[maxn][2], vis[maxn], shit[maxn], ans;

class Subtask_1 {
public:
  inline int Check() {
    int length = 0;
    for(int i = 1; i <= n; ++i) dp[i][0] = dp[i][1] = 1;
    for(int i = 1; i <= n; ++i) for(int j = i + 1; j <= n; ++j) {
      if( a[j] < a[i] ) dp[j][0] = max(dp[j][0], dp[i][1] + 1);
      if( a[j] > a[i] ) dp[j][1] = max(dp[j][1], dp[i][0] + 1);
    }
    for(int i = 1; i <= n; ++i) length = max(length, dp[i][0]);
    return length == m;
  }

  inline void Deep_fs(int step) {
    if( step == n + 1 ) { ans = ans + Check(); return ; }
    for(int i = 1; i <= n; ++i) if( !vis[i] ) vis[i] = 1, a[step] = i, Deep_fs(step + 1), vis[i] = 0;
  }

  inline void Main() { Deep_fs(1), printf("%d\n", ans); }
} subtask_1;

int main(int argc, char const *argv[])
{
  freopen("fafa.in", "r", stdin), freopen("fafa.out", "w", stdout);

  scanf("%d%d", &n, &m), subtask_1.Main();

  return 0;
}