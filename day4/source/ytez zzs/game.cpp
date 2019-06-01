#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
const int maxn = 100005;
int n, m, A[maxn];
int bg;
namespace BF_1 {
  int f[21][1 << 20];
  bool dp(int las, int s) {
    if(las == 1) {
      return (s == bg);
    }
    int &ans = f[las][s];
    if(ans != -1) return ans;
    ans = 0;
    for(int i = 1; i < las; i ++) {
      bool x = ((1 << (i - 1)) & s);
      bool y = ((1 << i) & s);
      int bs = (1 << (i - 1)) - 1; bs &= s;
      bs += (s - (((1 << (i + 1)) - 1) & s)) >> 1;
      int s1 = (x & y) ? (bs + (1 << (i - 1))) : bs;
      int s2 = (x ^ y) ? (bs + (1 << (i - 1))) : bs;
      ans |= !dp(las - 1, s1);
      ans |= !dp(las - 1, s2);
    }
    return ans;
  }
  
  bool solve() {
    for(int i = 1; i <= n; i ++) {
      for(int j = 0; j < (1 << i); j ++) {
        f[i][j] = -1;
      }
    }
    if(1 & n) {
      bg = 0;
    } else {
      bg = 1;
    }
    if(m == 1) bg ^= 1;
    int s = 0;
    for(int i = n; i >= 1; i --) {
      s = (s << 1) + (1 & A[i]);
    }
    if(dp(n, s)) {
      if(m)  {
        puts("B"); return false;
      } else {
        puts("A"); return true;
      }
    } else {
      if(m)  {
        puts("A"); return true;
      } else {
        puts("B"); return false;
      }
    }
  }
  
  void gen_table() {
    n = 6; m = 1;
    for(int s = 0; s < (1 << n); s ++) {
      for(int i = 1; i <= n; i ++) {
        if((1 << (i - 1)) & s) A[i] = 1;
        else A[i] = 0;
      }
      printf("New case :");
      for(int i = 1; i <= n; i ++) {
        printf(" %d", A[i]);
      }
      puts("");
      solve();
    }
  }
};

namespace CT_2 {
  bool solve() {
    if(!(n & 1)) {
      puts("A"); return true;
    }
    bool ok = true;
    for(int i = 1; i <= n; i += 2) {
      ok = ok && (A[i] % 2 == 1);
    }
    if(ok) {
      puts("B"); return false;
    } else {
      puts("A"); return true;
    }
  }
};

namespace CT_3 {
  int pre[maxn][2], suf[maxn][2];
  bool solve() {
    if(n & 1) {
      puts("A"); return true;
    }
    pre[0][0] = pre[0][1] = 1;
    for(int i = 1; i <= n; i ++) {
      memcpy(pre[i], pre[i - 1], sizeof(pre[i]));
      if(i & 1) {
        pre[i][1] &= (A[i] & 1);
      } else {
        pre[i][0] &= (A[i] & 1);
      }
    }
    suf[n + 1][0] = suf[n + 1][1] = 1;
    for(int i = n; i >= 1; i --) {
      memcpy(suf[i], suf[i + 1], sizeof(suf[i]));
      if(i & 1) {
        suf[i][1] &= (A[i] & 1);
      } else {
        suf[i][0] &= (A[i] & 1);
      }
    }
    for(int i = 1; i < n; i ++) {
      bool ok = (A[i] | A[i + 1]) & 1;
      if((i & 1) && !ok) continue;
      if(!pre[i - 1][1]) continue;
      if(!suf[i + 2][0]) continue;
      puts("B");
#ifdef LOCAL
      puts("Boom!");
#endif
      return false;
    }
    puts("A"); return true;
  }
};

void check_once(int s) {
  n = rand() % 20 + 1;
  if(n <= 2) n = 3;
  m = rand() & 1;
  for(int i = 1; i <= n; i ++) {
    A[i] = rand() & 1;
  }
  printf("New case :");
  for(int i = 1; i <= n; i ++) printf(" %d", A[i] & 1);
  puts("");
  if(m) {
    assert(CT_3::solve() == BF_1::solve());
  } else {
    assert(CT_2::solve() == BF_1::solve());
  }
}
void unit_check() {
  srand(time(0));
  while(true) check_once(0);
}

int main() {
#ifndef LOCAL
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
#endif
  // unit_check(); return 0;
  int T; scanf("%d", &T);
  while(T --) {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++) scanf("%d", &A[i]);
    if(n <= 20) {
      BF_1::solve();
    } if(m == 0) {
      CT_2::solve();
    } else {
      CT_3::solve();
    }
  }
  return 0;
}
