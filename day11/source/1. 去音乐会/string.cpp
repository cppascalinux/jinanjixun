#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = (1 << 23) + 10;
int n, m, q, str[maxn], cnt[maxn], key[maxn], tmp[maxn], sa[maxn];

inline void Suffix_array() {
  for(int i = 1; i <= m; ++i) cnt[i] = 0;
  for(int i = 1; i <= n; ++i) ++cnt[key[i] = str[i]];
  for(int i = 2; i <= m; ++i) cnt[i] = cnt[i] + cnt[i - 1];
  for(int i = n; i >= 1; --i) sa[cnt[key[i]]--] = i;
  for(int num = 0, k = 1; k <= n; k = k << 1) {
    for(int i = n - k + 1; i <= n; ++i) tmp[++num] = i;
    for(int i = 1; i <= n; ++i) if( sa[i] > k ) tmp[++num] = sa[i] - k;
    for(int i = 1; i <= m; ++i) cnt[i] = 0;
    for(int i = 1; i <= n; ++i) ++cnt[key[i]];
    for(int i = 2; i <= m; ++i) cnt[i] = cnt[i] + cnt[i - 1];
    for(int i = n; i >= 1; --i) sa[cnt[key[tmp[i]]]--] = tmp[i], tmp[i] = 0;
    swap(key, tmp), num = 1, key[sa[1]] = 1;
    for(int i = 2; i <= n; ++i)
      key[sa[i]] = (num = num + (tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + k] != tmp[sa[i - 1] + k]));
    if( num == n ) break;
    m = num, num = 0;
  }
}

int main(int argc, char const *argv[])
{
  freopen("string.in", "r", stdin), freopen("string.out", "w", stdout);

  scanf("%d%d", &n, &q), m = 3;
  for(int i = 0; i < (1 << n); ++i) str[i] = str[i >> 1] ^ (i & 1);
  for(int i = (1 << n); i; --i) str[i] = str[i - 1] + 1;
  n = (1 << n), Suffix_array();
  for(int x, i = 1; i <= q; ++i) scanf("%d", &x), printf("%d ", sa[x] - 1);

  return 0;
}