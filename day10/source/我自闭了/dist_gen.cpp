#include <cstdio>
#include <ctime>
#include <cassert>
#include <random>
typedef double R;

int A[35];
std::mt19937 gen_p(time(0));
std::uniform_int_distribution<int> dist_p(1, 10);
void gen_data() {
  std::mt19937 gen(time(0)), gen_mu(time(0)), gen_n(time(0));
  freopen("distribution.in", "w", stdout);
  std::uniform_real_distribution<R> dist_mu(-0.5, 0.5);
  std::uniform_int_distribution<int> dist_n(1, 100);
  int T = 30; R p = 0.05 + 0.09 * dist_p(gen_p);
  printf("%d\n%.2lf\n", T, p);
  for(int id = 1; id <= T; id ++) {
    int N = 10000; printf("%d", N);
    int n = dist_n(gen_n); A[id] = n;
    std::binomial_distribution<int> dist(n, p);
    R dv = sqrt(p * (1 - p) * n);
    R sumv = 0;
    while(N --) {
      R val = (dist(gen) + dist_mu(gen_mu) - p * n) / dv;
      sumv += val;
      printf(" %.12lf", val);
    }
    // fprintf(stderr, "sumv : %.12lf\n", sumv / 10000);
    puts("");
  }
  fclose(stdout);
}

int abs(int x) {
  if(x < 0) return -x;
  else return x;
}
int main() {
  while(true) {
    gen_data();
    system("distribution");
    freopen("distribution.out", "r", stdin);
    int delta = 0;
    for(int i = 1; i <= 30; i ++) {
      int x;
      assert(scanf("%d", &x) == 1);
      delta += abs(A[i] - x);
    }
    fprintf(stderr, "delta now : %d\n", delta);
    fclose(stdin);
  }
  return 0;
}
