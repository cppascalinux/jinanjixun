#include <algorithm>
#include <cstdio>
#include <cctype>
#include <cstring>

typedef long long LL;
const int N = 100;

int n, q;
LL c1[N][2], c2[N][2][2], c3[N][2][2][2];

void Init() {
  c1[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    c1[i][0] = c1[i][1] = c1[i - 1][0] + c1[i - 1][1];
    c2[i][0][0] = c2[i - 1][1][0];
    c2[i][0][1] = c1[i - 1][0] + c2[i - 1][1][1];
    c2[i][1][0] = c1[i - 1][1] + c2[i - 1][0][0];
    c2[i][1][1] = c2[i - 1][0][1];
    for (int a = 0; a < 2; ++a)
      for (int b = 0; b < 2; ++b)
        for (int c = 0; c < 2; ++c)
          c3[i][a][b][c] = (a != b ? c2[i - 1][a][c] : 0) + (b != c ? c2[i - 1][!a][b] : 0);
  }
}

LL c4(int n, int a, int b, int c, int d) {
  return (a != b && c != d ? c2[n - 1][a][c] : 0) + (b != c ? c3[n - 1][!a][b][d] : 0); 
}

char ss[N][10], p[10];

LL kth(int n, LL k) {
  const char *s = ss[n];
  int l = strlen(s);
#define check(x) (strncmp(s, (x), l) == 0)
  if (n == 0) return 0;
  if (n == 1) {
    if (check("01") && !(--k)) return 0;
    else return 1;
  }
  int x = n & 1;
  for (int a = 0; a < 2; ++a) {
    p[0] = "01"[a];
    if (a == x && check(x ? "1" : "0") && !(--k)) return (1LL << n) - 1;
    for (int b = 0; b < 2; ++b) {
      p[1] = "01"[b];
      if (b == x && a == !x && check(x ? "01" : "10") && !(--k)) return (1LL << n) - 2;
      for (int c = 0; c < 2; ++c) {
        p[2] = "01"[c];
        if (c == x && b == !x && check(x ? "001" : "110") && a == !x && !(--k)) return (1LL << n) - 3;
        for (int d = 0; d < 2; ++d) {
          p[3] = "01"[d], p[4] = '\0';
          if (!check(p)) continue;
          LL t = c4(n, a, b, c, d);
          if (t >= k) {
            if (a != b && c != d) {
              ss[n - 1][0] = "01"[a], ss[n - 1][1] = "01"[c], ss[n - 1][2] = '\0';
              return kth(n - 1, k) * 2;
            } else {
              ss[n - 1][0] = '0' + !a, ss[n - 1][1] = "01"[b], ss[n - 1][2] = "01"[d], ss[n - 1][3] = '\0';
              return kth(n - 1, k) * 2 + 1;
            }
          } else {
            k -= t;
          }
        }
      }
    }
  }
  return -1;
}

int main() {
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
  scanf("%d%d", &n, &q);
  Init();
  ss[n][0] = '\0';
  for (int i = 0; i < q; ++i) {
    LL k; scanf("%lld", &k);
    printf("%lld ", kth(n, k));
  }
}