#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define l first.first
#define r first.second
#define w second

const int maxn = 30000 + 10;
int n, m, t, col[maxn];

std::pair<pair<int, int>, int> p[maxn];
std::vector<int> id;

inline int read() {
  register int ch = 0; register int w = 0, x = 0;
  while( !isdigit(ch) ) w = w | (ch == '-'), ch = getchar();
  while( isdigit(ch) ) x = (x * 10) + (ch ^ 48), ch = getchar();
  return w ? -x : x;
}

class Subtask_1 {
public:
  inline bool Check(int x) { return true; }

  inline int Main() {
    for(int i = 1; i <= m; ++i) p[i].w = i;
    sort(p + 1, p + m + 1);
    for(int i = 2; i <= m; i = i + 2) {
      if( p[i - 1].l == p[i].l && p[i - 1].r == p[i].r ) col[i - 1] = 0, col[i] = 1;
      else p[++t] = p[i - 1], p[++t] = p[i];
      if( i + 1 == m ) p[++t] = p[i + 1];
    }
    m = t;
    for(int i = 0; i < (1 << n); ++i) if( Check(i) ) {
      for(int j = 1; j <= m; ++j) printf("%d ", col[i]);
      return 0;
    }
    return printf("-1\n");
  }
} subtask_1;

class Subask_2 {
public:
  inline bool Check(int x) {
    for(int j = 0; j < m; ++j) if( p[j + 1].w != -1 && ((x >> j) & 1) != p[j + 1].w ) return false;
    for(int i = 1; i <= id.size(); ++i) col[i] = 0;
    for(int j = 0; j < m; ++j) for(int i = p[j + 1].l; i <= p[j + 1].r; ++i) col[i] = col[i] + (((x >> j) & 1) ? 1 : -1);
    for(int i = id[0]; i <= id[id.size() - 1]; ++i) if( col[i] < -1 || col[i] > 1 ) return false;
    return true;
  }

  inline int Main() {
    for(int i = 1; i <= m; ++i) id.push_back(p[i].l), id.push_back(p[i].r);
    sort(id.begin(), id.end()), id.erase(unique(id.begin(), id.end()), id.end());
    for(int i = 1; i <= m; ++i) {
      p[i].l = lower_bound(id.begin(), id.end(), p[i].l) - id.begin() + 1;
      p[i].r = lower_bound(id.begin(), id.end(), p[i].r) - id.begin() + 1;
      // cerr << p[i].l << " " << p[i].r << "\n";
    }
    for(int i = 0; i < (1 << m); ++i) if( Check(i) ) {
      for(int j = 0; j < m; ++j) printf("%d ", (i >> j) & 1);
      return 0;
    }
    return printf("-1\n");
  }
} subtask_2;

int main(int argc, char const *argv[])
{
  freopen("wait.in", "r", stdin), freopen("wait.out", "w", stdout);

  scanf("%d%d", &m, &n);
  for(int i = 1; i <= m; ++i) p[i].l = read(), p[i].r = read(), p[i].w = read();
  m <= 20 ? subtask_2.Main() : subtask_1.Main();

  return 0;
}