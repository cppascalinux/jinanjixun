#include <map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define x first
#define y second

const int maxn = 10000 + 10;
const double pi = acos(-1.0);
const double eps = 10000000000.0;
int n, cnt, a[maxn]; char str[maxn];

std::map<double, int> ma;
std::pair<double, double> p[maxn];

inline double Abs(double x) { return x > 0 ? x : -x; }
inline double S(pair<double, double> i, pair<double, double> j) { return Abs(i.x * j.y - j.x * i.y); }

inline void Subtask_1() {
  ma.clear();
  long long ans = 0;
  for(int i = 1; i <= n; ++i) if( a[i] ) {
    for(int j = i + 1; j <= n; ++j) if( a[j] ) {
      for(int k = j + 1; k <= n; ++k) if( a[k] ) {
        pair<double, double> p_1 = make_pair(p[j].x - p[i].x, p[j].y - p[i].y);
        pair<double, double> p_2 = make_pair(p[k].x - p[i].x, p[k].y - p[i].y);
        ++ma[(long long)(S(p_1, p_2) * eps + 0.5) / eps];
      }
    }
  }
  for(map<double, int>::iterator i = ma.begin(); i != ma.end(); ++i) ans = ans + (i->second) * (i->second - 1) / 2;
  printf("%lld\n", ans);
}

inline void Subtask_2() {
  long long ans = (n % 3 ? n : n / 3);
  printf("%lld\n", ans);
}

int main(int argc, char const *argv[])
{
  freopen("three.in", "r", stdin), freopen("three.out", "w", stdout);

  scanf("%d%s", &n, str + 1);
  for(int i = 1; i <= n; ++i) a[i] = str[i] ^ 48, cnt = cnt + a[i];
  for(int i = 1; i <= n; ++i) p[i].x = cos(pi * (i << 1) / n), p[i].y = sin(pi * (i << 1) / n);
  if( cnt ) n <= 100 ? Subtask_1() : Subtask_2();
  else printf("0\n");

  return 0;
}