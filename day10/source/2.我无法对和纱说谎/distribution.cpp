#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10000 + 10;
int n;

int main(int argc, char const *argv[])
{
  freopen("distribution.in", "r", stdin), freopen("distribution.out", "r", stdout);

  srand(20021230), scanf("%d", &n);
  for(int i = 1; i <= n; ++i) printf("%d\n", rand() % 100 + 1);

  return 0;
}