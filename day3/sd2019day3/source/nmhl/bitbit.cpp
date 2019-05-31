#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define x first
#define y second

const int maxn = 500 + 10;
int n, m, a[maxn][maxn]; char str[maxn][maxn];

class Subtask_1 {
private:
  int cnt_0, cnt_1, vis[maxn][maxn];

public:
  inline void Colored(int sx, int sy) {
    queue<pair<int, int> > q;
    q.push(make_pair(sx, sy)), vis[sx][sy] = 1, a[sx][sy] ? ++cnt_1 : ++cnt_0;
    while( !q.empty() ) {
      pair<int, int> p = q.front(); q.pop();
      if( p.x + 1 <= n && !vis[p.x + 1][p.y] && a[p.x + 1][p.y] == a[sx][sy] ) q.push(make_pair(p.x + 1, p.y)), vis[p.x + 1][p.y] = 1;
      if( p.x - 1 >= 1 && !vis[p.x - 1][p.y] && a[p.x - 1][p.y] == a[sx][sy] ) q.push(make_pair(p.x - 1, p.y)), vis[p.x - 1][p.y] = 1;
      if( p.y + 1 <= m && !vis[p.x][p.y + 1] && a[p.x][p.y + 1] == a[sx][sy] ) q.push(make_pair(p.x, p.y + 1)), vis[p.x][p.y + 1] = 1;
      if( p.y - 1 >= 1 && !vis[p.x][p.y - 1] && a[p.x][p.y - 1] == a[sx][sy] ) q.push(make_pair(p.x, p.y - 1)), vis[p.x][p.y - 1] = 1;
    }
  }

  inline void Breath_fs(int sx, int sy, int c) {
    queue<pair<int, int> > q;
    q.push(make_pair(sx, sy)), vis[sx][sy] = c;
    while( !q.empty() ) {
      pair<int, int> p = q.front(); q.pop();
      if( p.x + 1 <= n && vis[p.x + 1][p.y] == 0 && a[p.x + 1][p.y] == a[sx][sy] ) q.push(make_pair(p.x + 1, p.y)), vis[p.x + 1][p.y] = c;
      if( p.x - 1 >= 1 && vis[p.x - 1][p.y] == 0 && a[p.x - 1][p.y] == a[sx][sy] ) q.push(make_pair(p.x - 1, p.y)), vis[p.x - 1][p.y] = c;
      if( p.y + 1 <= m && vis[p.x][p.y + 1] == 0 && a[p.x][p.y + 1] == a[sx][sy] ) q.push(make_pair(p.x, p.y + 1)), vis[p.x][p.y + 1] = c;
      if( p.y - 1 >= 1 && vis[p.x][p.y - 1] == 0 && a[p.x][p.y - 1] == a[sx][sy] ) q.push(make_pair(p.x, p.y - 1)), vis[p.x][p.y - 1] = c;
    }
  }

  inline void Getans_0() {
    memset(vis, 0, sizeof vis);
    printf("+\n");
    for(int tx = 1; tx <= n; printf("\n"), ++tx) for(int ty = 1; ty <= m; ++ty) printf("1");
    for(int tims = 0, i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) if( a[i][j] == 0 && vis[i][j] == 0 ) {
      Breath_fs(i, j, ++tims);
      printf("-\n");
      for(int tx = 1; tx <= n; printf("\n"), ++tx)
        for(int ty = 1; ty <= m; ++ty) printf("%d", vis[tx][ty] == tims ? 1 : 0);
    }
  }

  inline void Getans_1() {
    memset(vis, 0, sizeof vis);
    for(int tims = 0, i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) if( a[i][j] == 1 && vis[i][j] == 0 ) {
      Breath_fs(i, j, ++tims);
      printf("+\n");
      for(int tx = 1; tx <= n; printf("\n"), ++tx)
        for(int ty = 1; ty <= m; ++ty) printf("%d", vis[tx][ty] == tims ? 1 : 0);
    }
  }

  inline void Main() {
    memset(vis, 0, sizeof vis), cnt_0 = 0, cnt_1 = 0;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) if( vis[i][j] == 0 ) Colored(i, j);
    printf("%d\n", min(cnt_0 + 1, cnt_1));
    cnt_0 < cnt_1 ? Getans_0() : Getans_1();
  }
} subtask_1;

class Subtask_2 {
public:
  inline void Main() {
    int cnt = 0;
    for(int i = 1; i <= m + 1; ++i) if( a[1][i - 1] == 1 && a[1][i] == 0 ) ++cnt;
    printf("%d\n", cnt);
    for(int i = 1; i <= m + 1; ++i) if( a[1][i - 1] == 1 && a[1][i] == 0 ) {
      printf("+\n");
      for(int j = 1; j < i; ++j) printf("%d", a[1][j]), a[1][j] = 0;
      for(int j = i; j <= m; ++j) printf("0");
      printf("\n");
    }
  }
} subtask_2;

int main(int argc, char const *argv[])
{
  freopen("bitbit.in", "r", stdin), freopen("bitbit.out", "w", stdout);

  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) scanf("%s", str[i] + 1);
  for(int i = 1; i <= n; ++i) for(int j = 1; j <= m; ++j) a[i][j] = str[i][j] ^ 48;
  n == 1 ? subtask_2.Main() : subtask_1.Main();

  return 0;
}