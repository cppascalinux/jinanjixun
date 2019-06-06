#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, a[maxn];

int main(int argc, char const *argv[])
{
  freopen("sample1.in", "r", stdin), freopen("plasticmem.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) scanf("%d", a + i);
  for(int opt, l, r, t = 1; t <= m; ++t) {
    scanf("%d%d%d", &opt, &l, &r);
    if( opt < 7 ) switch( opt ) {
      case 1 : for(int i = l; i <= r; ++i) a[i] = 0; break;
      case 2 : for(int i = r; i >= l; --i) a[i] = 1; break;
      case 3 : for(int i = l; i < r; ++i) a[i] = a[i] | a[i + 1]; break;
      case 4 : for(int i = r; i > l; --i) a[i] = a[i] | a[i - 1]; break;
      case 5 : for(int i = l; i < r; ++i) a[i] = a[i] & a[i + 1]; break;
      case 6 : for(int i = r; i > l; --i) a[i] = a[i] & a[i - 1]; break;
    } else {
      long long ans = 0;
      for(int i = l; i <= r; ++i) ans = ans + a[i];
      printf("%lld\n", ans);
    }
  }

  return 0;
}