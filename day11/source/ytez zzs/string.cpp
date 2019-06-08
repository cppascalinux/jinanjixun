#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
const int maxs = (1 << 24) | 3;
inline bool is_lms(int *typ, int p) {
  return p > 1 && typ[p - 1] == 1 && typ[p] == 0;
}
inline bool equal_lms(int *S, int a, int b, int *typ) {
  do {
    if(S[a] != S[b]) return false;
    a ++; b ++;
  } while(!is_lms(typ, a) && !is_lms(typ, b));
  return S[a] == S[b];
}
inline void ind_sort(int n, int *S, int *SA, int *typ, int *buf, int *lb, int *sb) {
  for(int i = 0; i <= n; i ++) {
    int th = SA[i] - 1;
    if(th > 0 && typ[th] == 1) {
      SA[lb[S[th]] ++] = th;
    }
  }
  for(int i = 0; i <= n; i ++) {
    sb[i] = buf[i] - 1;
  }
  for(int i = n; i >= 0; i --) {
    int th = SA[i] - 1;
    if(th > 0 && typ[th] == 0) {
      SA[sb[S[th]] --] = th;
    }
  }
}
int *SA_IS(int *S, int n) {
  int *SA = new int[n + 2];
  int *buf = new int[n + 2];
  int *lb = new int[n + 2];
  int *sb = new int[n + 2];
  std::fill(buf, buf + n + 2, 0);
  for(int i = 1; i <= n + 1; i ++) {
    buf[S[i]] ++;
  }
  for(int i = 1; i <= n; i ++) {
    buf[i] += buf[i - 1];
    lb[i] = buf[i - 1];
    sb[i] = buf[i] - 1;
  }
  sb[0] = lb[0] = 0;

  int *typ = new int[n + 2];
  typ[n + 1] = 0;
  for(int i = n; i >= 1; i --) {
    if(S[i] > S[i + 1]) {
      typ[i] = 1;
    } else if(S[i] < S[i + 1]) {
      typ[i] = 0;
    } else {
      typ[i] = typ[i + 1];
    }
  }

  std::fill(SA, SA + n + 2, -1);
  for(int i = 1; i <= n + 1; i ++) {
    if(is_lms(typ, i)) {
      SA[sb[S[i]] --] = i;
    }
  }
  ind_sort(n, S, SA, typ, buf, lb, sb);
  int *nm = new int[n + 2];
  int *pos = new int[n + 2]; int lms_cnt = 0;
  for(int i = 1; i <= n; i ++) {
    if(is_lms(typ, i)) {
      pos[++ lms_cnt] = i;
    }
  }
  pos[lms_cnt + 1] = n + 1;
  bool unique = true;
  int las = -1, nm_cnt = 0;
  for(int i = 0; i <= n; i ++) {
    int th = SA[i];
    if(!is_lms(typ, th)) continue;
    if(las >= 0 && !equal_lms(S, las, th, typ)) {
      ++ nm_cnt;
    }
    if(las >= 0 && nm_cnt == nm[las]) {
      unique = false;
    }
    nm[las = th] = nm_cnt;
  }

  int *S1 = new int[n + 2];
  int *SA1;
  for(int i = 1; i <= lms_cnt + 1; i ++) S1[i] = nm[pos[i]];
  if(unique) {
    SA1 = new int[n + 2];
    for(int i = 1; i <= lms_cnt + 1; i ++) {
      SA1[S1[i]] = i;
    }
  } else {
    SA1 = SA_IS(S1, lms_cnt);
  }

  lb[0] = sb[0] = 0;
  for(int i = 1; i <= n; i ++) {
    lb[i] = buf[i - 1];
    sb[i] = buf[i] - 1;
  }
  std::fill(SA, SA + n + 2, -1);
  for(int i = lms_cnt; i >= 0; i --) {
    int th = pos[SA1[i]];
    SA[sb[S[th]] --] = th;
  }
  ind_sort(n, S, SA, typ, buf, lb, sb);
  return SA;
}

int pcnt[maxs], S[maxs];
int main() {
#ifndef WOEE
  freopen("string.in", "r", stdin);
  freopen("string.out", "w", stdout);
#endif
  int k, q; scanf("%d%d", &k, &q);
  const int n = 1 << k;
  pcnt[0] = 0; S[1] = 1;
  for(int i = 1; i < n; i ++) {
    pcnt[i] = pcnt[(i - 1) & i] + 1;
    S[i + 1] = 1 + (pcnt[i] & 1);
  }
  int *SA = SA_IS(S, n);
  while(q --) {
    int p; scanf("%d", &p);
    printf("%d ", SA[p] - 1);
  }
  puts("");
  return 0;
}
