#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int n, m, head[maxn], dfn[maxn], idfn[maxn], deep[maxn], pre[maxn], size[maxn], dfn_num, node_num, edge_num;
long long a[maxn], cst[maxn], prev[maxn], sum, tmp, ans;

typedef pair<long long, int> pairs;
priority_queue<pairs, vector<pairs> > q;

struct Edge { int v, w, nxt; } edge[maxn << 1];

inline int read() {
  register int ch = 0; register int x = 0;
  for( ; !isdigit(ch); ch = getchar()) ;
  for( ; isdigit(ch); x = (x * 10) + (ch ^ 48), ch = getchar()) ;
  return x;
}

inline void Add_edge(int u, int v, int w) {
  edge[++edge_num].v = v, edge[edge_num].w = w, edge[edge_num].nxt = head[u], head[u] = edge_num;
}

inline void Deep_fs(int x, int p) {
  pre[x] = p, size[x] = 1, deep[x] = deep[p] + 1, dfn[x] = ++dfn_num, idfn[dfn_num] = x;
  for(int i = head[x]; i; i = edge[i].nxt) {
    if( edge[i].v == p ) continue;
    cst[edge[i].v] = cst[x] + edge[i].w, prev[edge[i].v] = edge[i].w;
    Deep_fs(edge[i].v, x), size[x] = size[x] + size[edge[i].v];
  }
}

inline int Lca(int x, int y) {
  while( x != y ) deep[x] > deep[y] ? x = pre[x] : y = pre[y];
  return x;
}

int main(int argc, char const *argv[])
{
  freopen("love.in", "r", stdin), freopen("love.out", "w", stdout);

  scanf("%d%d", &n, &m), ans = 1e18;
  for(int u, v, w, i = 1; i < n; sum = sum + 2 * w, ++i)
    u = read(), v = read(), w = read(), Add_edge(u, v, w), Add_edge(v, u, w);
  for(int i = 1; i <= m; ++i) a[i] = read();
  Deep_fs(1, 0);
  pair<long long, int> p;
  for(int i = 1; i <= n; ++i) q.push(make_pair(cst[i], i));
  int n1 = q.top().second; q.pop();
  int n2 = q.top().second; q.pop();
  int n3 = q.top().second; q.pop();
  int n4 = q.top().second; q.pop();
  printf("%lld ", sum);
  printf("%lld ", min(sum, sum - cst[n1] - cst[n2] + a[1]));
  printf("%lld ", min(sum + a[1] + a[2] - cst[n1] - cst[n2] - cst[n3] - cst[n4], min(sum, min(sum - cst[n1] - cst[n2] + a[1], sum - cst[n1] - cst[n2] + a[2]))));

  return 0;
}