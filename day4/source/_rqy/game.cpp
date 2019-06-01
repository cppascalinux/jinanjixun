#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef long long LL;

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
  int T = read();
  while (T--) {
    int n = read(), m = read();
    if (n == 1) {
      if (read() & 1) puts("B");
      else puts("A");
      continue;
    }
    if ((n & 1) ^ m) {
      int k = (n - 1) / 2, t = 0, s = 0;
      for (int i = 0; i < n; ++i)
        if (read() & 1) s += t ^= 1;
        else t = 0;
      puts(s <= k ? "A" : "B");
    } else {
      for (int i = 0; i < n; ++i)
        read();
      puts("A");
    }
  }
}

