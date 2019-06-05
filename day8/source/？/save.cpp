#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxb = 2000 + 10;
const int maxn = 200000 + 10;
int n, m, size, a[maxn], bel[maxn], tag[maxb], sum[maxb], s[maxb], e[maxb];

inline int read() {
  register int ch = 0; register int x = 0;
  for( ; !isdigit(ch); ch = getchar()) ; 
  for( ; isdigit(ch); x = (x * 10) + (ch ^ 48), ch = getchar()) ;
  return x;
}

int main(int argc, char const *argv[])
{
  freopen("save.in", "r", stdin), freopen("save.out", "w", stdout);

  scanf("%d%d", &n, &m), size = sqrt(n) + 1;
  for(int i = 1; i <= n; ++i) a[i] = read(), bel[i] = i / size + 1;
  for(int i = 1; i <= n; ++i) if( i % size == 0 ) s[bel[i]] = i, e[bel[i] - 1] = i - 1;
  s[bel[1]] = 1, e[bel[n]] = n;
  for(int i = 1; i <= n; ++i) sum[bel[i]] = sum[bel[i]] ^ a[i];
  for(register int opt = 0, x = 0, l = 0, r = 0, lef = 0, rig = 0, ans = 0, t = 1; t <= m; ++t) {
    opt = read(), l = read(), r = read();
    if( opt == 1 ) {
      x = read(), lef = bel[l] + 1, rig = bel[r] - 1;
      if( bel[l] == bel[r] ) {
        for(int i = l; i <= r; ++i) a[i] = a[i] ^ x;
        sum[bel[l]] ^ (((r - l + 1) & 1) * x);
        continue;
      }
      for(int i = lef; i <= rig; ++i) tag[i] = tag[i] ^ x, sum[i] = sum[i] ^ ((size & 1) * x);
      for(int i = l; i <= e[bel[l]]; ++i) a[i] = a[i] ^ x; sum[bel[l]] = sum[bel[l]] ^ (((e[bel[l]] - l + 1) & 1) * x);
      for(int i = s[bel[r]]; i <= r; ++i) a[i] = a[i] ^ x; sum[bel[r]] = sum[bel[r]] ^ (((r - s[bel[r]] + 1) & 1) * x);
    }
    if( opt == 3 ) {
      ans = 0, lef = bel[l] + 1, rig = bel[r] - 1;
      if( bel[l] == bel[r] ) {
        for(int i = l; i <= r; ++i) ans = ans ^ a[i];
        ans = ans ^ (((r - l + 1) & 1) * tag[bel[l]]), printf("%d\n", ans);
        continue;
      }
      for(int i = lef; i <= rig; ++i) ans = ans ^ sum[i];
      for(int i = l; i <= e[bel[l]]; ++i) ans = ans ^ a[i]; ans = ans ^ (((e[bel[l]] - l + 1) & 1) * tag[bel[l]]);
      for(int i = s[bel[r]]; i <= r; ++i) ans = ans ^ a[i]; ans = ans ^ (((r - s[bel[r]] + 1) & 1) * tag[bel[r]]);
      printf("%d\n", ans);
    }
    if( opt == 2 ) {
      lef = s[bel[l]], rig = e[bel[r]];
      for(int i = lef; i <= rig; ++i) a[i] = a[i] ^ tag[bel[i]];
      sort(a + l, a + r + 1);
      lef = bel[l], rig = bel[r];
      for(int i = lef; i <= rig; ++i) sum[i] = 0, tag[i] = 0;
      lef = s[bel[l]], rig = e[bel[r]];
      for(int i = lef; i <= rig; ++i) sum[bel[i]] = sum[bel[i]] ^ a[i];
    }
  }

  return 0;
}