#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>

const int N = 500050;
const int C = 10;
const int L = 20;

char s[N];
int n, g[C * L][N], h[C * L][N];

inline void Max(int &a, int b) { if (a < b) a = b; }
inline void Min(int &a, int b) { if (a > b) a = b; }

int main() {
  freopen("guess.in", "r", stdin);
  freopen("guess.out", "w", stdout);
  scanf("%s", s + 1); n = strlen(s + 1);
  for (int i = 1; i <= n + 1; ++i) g[0][i] = i, h[0][i] = i;
  for (int k = 1; k < C * L; ++k)
    for (int i = 0; i <= n + 1; ++i)
      g[k][i] = h[k][i] = i;
  int k;
  for (k = 0; g[k][1] <= n; ++k) {
    for (int i = 2; i <= n + 1; ++i) Max(g[k][i], g[k][i - 1]);
    for (int i = n; i >= 1; --i) Min(h[k][i], h[k][i + 1]);
    for (int i = 1; i <= n; ++i) {
      Max(g[k + s[i] - '0'][h[k][i]], g[k][i + 1]);
      Min(h[k + s[i] - '0'][g[k][i + 1]], h[k][i]);
    }
  }
  printf("%d\n", k);
  //fprintf(stderr, "%lu\n", clock());
}