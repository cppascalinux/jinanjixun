#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>
#include <random>
std::mt19937 gen(time(0));

int main() {
  freopen("tree.in", "w", stdout);
  const int n = 30000; printf("%d\n", n);
  std::uniform_int_distribution<int> dist_w(0, 1000000000);
  for(int i = 2; i <= n; i ++) {
    const int f = gen() % (i - 1) + 1;
    printf("%d %d %d\n", i, f, dist_w(gen));
  }
  for(int i = 2; i <= n; i ++) {
    const int f = gen() % (i - 1) + 1;
    printf("%d %d %d\n", i, f, dist_w(gen));
  }
  return 0;
}
