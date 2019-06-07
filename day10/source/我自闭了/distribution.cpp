#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
typedef long double R;

int main() {
#ifndef WOEE
  freopen("distribution.in", "r", stdin);
  freopen("distribution.out", "w", stdout);
#endif
  srand(time(0));
  int T; double p; scanf("%d%lf", &T, &p);
  R dv = p * (1 - p);
  while(T --) {
    int N; scanf("%d", &N);
    R v_1 = 0, v_2 = 0;
    for(int i = 1; i <= N; i ++) {
      double v; scanf("%lf", &v);
      v_1 += (R)v * (R)v;
      v_2 += v;
    }
    v_1 /= N; v_2 /= N; v_2 *= v_2;
    // v_2 = 0;
    R Var = v_1 - v_2;
#ifdef LOCAL
    printf("Var[A_i] : %.7lf\n", (double)Var);
#endif
    R delta = 1e12; int th = 0;
    for(int i = 1; i <= 100; i ++) {
      R val = 1 + (1 / (dv * i * 12));
      R th_d = fabsl(val - Var);
      if(th_d < delta) {
        delta = th_d; th = i;
      }
    }
    // if(th == 100) th = rand() % 100 + 1;
    printf("%d\n", th);
  }
  return 0;
}
