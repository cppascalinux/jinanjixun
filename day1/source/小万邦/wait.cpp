#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <set>
const int maxn = 30005;
int m, n;
int seg[maxn][3];

namespace BF_2 {
  const int N = 45;
  int r_seg[N][2], S[N]; int cnt = 0;
  void process() {
    std::set<int> st;
    int maxp = 0;
    for(int i = 1; i <= m; i ++) {
      int l = seg[i][0], r = seg[i][1];
      st.insert(l); st.insert(r);
      maxp = std::max(maxp, std::max(l, r));
    }
    static int np[N];
    for(int v : st) {
      np[++ cnt] = v;
      if(v < maxp && !st.count(v + 1)) {
        np[++ cnt] = v + 1;
      }
    }
    for(int i = 1; i <= m; i ++) {
      int l = seg[i][0], r = seg[i][1];
      r_seg[i][0] = std::lower_bound(np + 1, np + 1 + cnt, l) - np;
      r_seg[i][1] = std::upper_bound(np + 1, np + 1 + cnt, r) - np - 1;
    }
  }
  
  inline void add_seg(int id, int val) {
    const int l = r_seg[id][0], r = r_seg[id][1];
#ifdef LOCAL
    printf("Modify (%d, %d, %d)\n", l, r, val);
#endif
    if(val) S[l] ++, S[r + 1] --;
    else S[l] --, S[r + 1] ++;
  }
  void solve() {
    process();
    for(int s = 0; s < (1 << m); s ++) {
      memset(S, 0, sizeof(S));
      for(int i = 1; i <= m; i ++) {
        if(seg[i][2] != -1) {
          add_seg(i, seg[i][2]);
          continue;
        }
        if((1 << (i - 1)) & s) {
          add_seg(i, 1);
        } else {
          add_seg(i, 0);
        }
      }
      bool ok = true;
      for(int i = 1; i <= cnt; i ++) {
        S[i] += S[i - 1];
        if(S[i] < -1 || S[i] > 1) {
          ok = false; break;
        }
      }
      if(ok) {
        for(int i = 1; i <= m; i ++) {
          if(i > 1) putchar(' ');
          if(seg[i][2] != -1) {
            printf("%d", seg[i][2]);
          } else {
            printf("%d", ((1 << (i - 1)) & s) ? 1 : 0);
          }
        }
        return;
      }
    }
    puts("-1");
  }
};

int main() {
#ifndef LOCAL
  freopen("wait.in", "r", stdin);
  freopen("wait.out", "w", stdout);
#endif
  scanf("%d%d", &m, &n);
  for(int i = 1; i <= m; i ++) {
    int *A = seg[i];
    scanf("%d%d%d", &A[0], &A[1], &A[2]);
  }
  if(m <= 20) BF_2::solve();
  return 0;
}
