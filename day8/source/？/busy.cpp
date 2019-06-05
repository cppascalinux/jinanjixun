#include <cmath>
#include <queue>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, a[maxn], p_1, p_2, ans;

int main(int argc, char const *argv[])
{
  freopen("busy.in", "r", stdin), freopen("busy.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) scanf("%d", a + i);
  for(int opt, x, y, k = 1; k <= m; ++k) {
    scanf("%d%d%d", &opt, &x, &y), x = x ^ ans, y = y ^ ans;
    if( opt & 1 ) { for(int i = 1; i <= m; ++i) if( a[i] == x ) a[i] = y; continue; }
    p_1 = 0, p_2 = 0, ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; ++i) {
      if( a[i] == x ) p_1 = i;
      if( a[i] == y ) p_2 = i;
      if( p_1 && p_2 ) ans = min(ans, abs(p_1 - p_2));
    }
    ans == 0x3f3f3f3f ? ans = 0, printf("Chtholly\n") : printf("%d\n", ans);
  }

  return 0;
}