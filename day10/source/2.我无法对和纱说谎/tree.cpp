#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10000 + 10;
const int mod = 1000000000 + 7;
int n, m, head[maxn], dis[maxn][maxn], ans, edge_num;

struct Edge { int v, w, nxt; } edge[maxn << 1];

inline int read() {
  register char ch = 0; register int x = 0;
  for( ; !isdigit(ch); ch = getchar()) ;
  for( ; isdigit(ch); x = (x * 10) + (ch ^ 48), ch = getchar()) ;
  return x;
}

inline void Add_edge(int u, int v, int w) {
  edge[++edge_num].v = v, edge[edge_num].w = w, edge[edge_num].nxt = head[u], head[u] = edge_num;
}

inline void Deep_fs(int s, int x, int p) {
  for(int i = head[x]; i; i = edge[i].nxt) {
    if( edge[i].v != p ) dis[s][edge[i].v] = dis[s][x] + edge[i].w, Deep_fs(s, edge[i].v, x);
  }
}

int main(int argc, char const *argv[])
{
  freopen("tree.in", "r", stdin), freopen("tree.out", "r", stdout);

  scanf("%d", &n);
  for(int u, v, w, i = 1; i < n; ++i) u = read(), v = read(), w = read(), Add_edge(u, v, w), Add_edge(v, u, w);
  for(int u, v, w, i = 1; i < n; ++i) u = n + read(), v = n + read(), w = read(), Add_edge(u, v, w), Add_edge(v, u, w);
  for(int i = 1; i <= n; ++i) Deep_fs(i, i, 0);
  for(int i = 1; i <= n; ++i) Deep_fs(n + i, n + i, 0);
  for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) ans = (ans + 1ll * dis[i][j] * dis[n + i][n + j]) % mod;
  printf("%d\n", ans);

  return 0;
}