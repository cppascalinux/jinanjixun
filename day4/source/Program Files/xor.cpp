#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

class Subtask_1 {
private:
  static const int maxn = (1 << 10) + 10;
  int g[maxn][maxn], vis[maxn], size, ans;

  std::vector<pair<int, int> > v[maxn];

public:
  inline int Breath_fs(int s) {
    queue<int> q;
    size = 0, vis[s] = 1, q.push(s);
    while( !q.empty() ) {
      int x = q.front(); ++size, q.pop();
      for(int i = 0; i < (1 << 10); ++i) if( g[x][i] && vis[i] == 0 ) vis[i] = 1, q.push(i);
    }
    return size;
  }

  inline void Main(int n, int q) {
    for(int i = 0; i < (1 << 10); ++i) for(int j = i; j < (1 << 10); ++j) v[i ^ j].push_back(make_pair(i, j));
    for(int opt, x, i = 1; i <= q; ++i) {
      scanf("%d%d", &opt, &x);
      if( opt & 1 ) for(int j = 0; j < v[x].size(); ++j)
        g[v[x][j].first][v[x][j].second] = g[v[x][j].second][v[x][j].first] = 1;
      else for(int j = 0; j < v[x].size(); ++j)
        g[v[x][j].first][v[x][j].second] = g[v[x][j].second][v[x][j].first] = 0;
      memset(vis, 0, sizeof vis), ans = 0;
      for(int j = 0; j < (1 << 10); ++j) if( !vis[i] ) ans = max(ans, Breath_fs(i));
      printf("%d\n", ans);
    }
  }
} subtask_1;

class Subtask_2 {
private:
  static const int maxn = 100000 + 10;
  int r[maxn], a[maxn], p[35], size, top;

public:
  inline int Fast_pow(int a, int p) {
    int ans = 1;
    for( ; p; a = a * a, p = p >> 1) if( p & 1 ) ans = a * ans;
    return ans;
  }

  inline void Rebuild(int x) {
    memset(p, 0, sizeof p), size = 0;
    for(int flag = 0, i = 1; i <= top; ++i)
      if( flag == 0 && r[i] == x ) r[i] = r[i + 1], flag = 1;
      else if( flag ) r[i] = r[i + 1];
    --top;
    for(int i = 1; i <= top + 1; ++i) a[i] = r[i];
    for(int i = 1; i <= top; ++i) for(int j = 30; j >= 0; --j) {
      if( (a[i] >> j) == 0 ) continue;
      if( p[j] == 0 ) { ++size, p[j] = a[i]; break; }
      a[i] = a[i] ^ p[j];
    }
  }

  inline void Main(int n, int q) {
    for(int opt, x, i = 1; i <= q; ++i) {
      scanf("%d%d", &opt, &x);
      if( opt & 1 ) {
        a[++top] = r[top] = x;
        for(int j = 30; j >= 0; a[top] = a[top] ^ p[j], --j) {
          if( (a[top] >> j) == 0 ) continue;
          if( p[j] == 0 ) { ++size, p[j] = a[top]; break; }
        }
      } else Rebuild(x);
      printf("%d\n", Fast_pow(2, size));
    }
  }
} subtask_2;

int n, q;

int main(int argc, char const *argv[])
{
  freopen("xor.in", "r", stdin), freopen("xor.out", "w", stdout);

  scanf("%d%d", &n, &q), n <= 10 ? subtask_1.Main(n, q) : subtask_2.Main(n, q);

  return 0;
}