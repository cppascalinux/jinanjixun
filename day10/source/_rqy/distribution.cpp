#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 105;
const int M = 10050;

double lnfac[N], X[M];

double lnC(int n, int m) { return lnfac[n] - lnfac[m] - lnfac[n - m]; }

int main() {
  freopen("distribution.in", "r", stdin);
  freopen("distribution.out", "w", stdout);
  lnfac[0] = 0;
  for (int i = 1; i < N; ++i)
    lnfac[i] = lnfac[i - 1] + log(i);
  int T;
  double p;
  scanf("%d%lf", &T, &p);
  while (T--) {
    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i)
      scanf("%lf", &X[i]);
    int ansn;
    double ans = -1e16, lp = log(p), l1p = log(1 - p);
    for (int n = 1; n <= 100; ++n) {
      double t = sqrt(n * p * (1 - p)), tn = m * log(n * p * (1 - p)) / 2;
      for (int i = 0; i < m; ++i) {
        double Y = X[i] * t + n * p;
        int y = (int)(Y + 0.5);
        if (y < 0 || y > n) {
          tn = -1e16;
          break;
        }
        tn += lnC(n, y) + y * lp + (n - y) * l1p;
        //fprintf(stderr, "%lf\n", lnC(n, y) + y * lp + (n - y) * l1p);
      }
      if (tn > ans) ans = tn, ansn = n;
        //fprintf(stderr, "%lf\n", tn);
    }
    printf("%d\n", ansn);
  }
}