#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n. m, a[maxn], cnt_0, cnt_1;

int main(int argc, char const *argv[])
{
  freopen("game.in", "r", stdin), freopen("game.out", "w", stdout);

  scanf("%d", &n);
  while( ~scanf("%d%d", &n, &m) ) {
    for(int i = 1; i <= n; ++i) scanf("%d", a + i), (a[i] = a[i] & 1) ? ++cnt_1 : ++cnt_0;
    if( cnt_1 > 2 * cnt_0 ) printf("B\n");
    else printf("A\n");
  }

  return 0;
}