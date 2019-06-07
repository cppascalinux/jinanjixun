#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long LL;
typedef std::pair<LL, LL> PI;
#define mp std::make_pair

const LL N = 300050;
const LL mod = 1000000007;

LL read() {
  LL ans = 0, cost, f = 1;
  while (!isdigit(cost = getchar()))
    if (cost == '-') f = -1;
  do ans = ans * 10 + cost - '0';
  while (isdigit(cost = getchar()));
  return ans * f;
}

namespace Tree1 {
LL pre[N], to[N * 2], cost[N * 2], nxt[N * 2], cnt;

void addEdge(LL x, LL y, LL z) {
  nxt[cnt] = pre[x];
  cost[cnt] = z;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  cost[cnt] = z;
  to[pre[y] = cnt++] = x;
}

LL dep[N], fa[N][20], pos[N], cnt2;
LL depc[N];
bool cmp(LL a, LL b) { return pos[a] < pos[b]; }

void dfs(LL x, LL f) {
  dep[x] = dep[fa[x][0] = f] + 1;
  pos[x] = ++cnt2;
  for (LL i = 0; fa[x][i]; ++i)
    fa[x][i + 1] = fa[fa[x][i]][i];
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) { depc[to[i]] = (depc[x] + cost[i]) % mod; dfs(to[i], x); }
}

LL LCA(LL x, LL y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  for (LL i = 19; ~i; --i) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
  for (LL i = 19; ~i; --i) if (fa[x][i] != fa[y][i]) {
    x = fa[x][i];
    y = fa[y][i];
  }
  return x == y ? x : fa[x][0];
}

LL pres[N], nxts[N], stack[N];
inline void addS(LL x, LL y) { nxts[y] = pres[x]; pres[x] = y; }

LL ans;
LL V1[N], V2[N];
LL sumV1, sumV2;

PI f(LL x, LL c) {
  for (LL y = pres[x]; y; y = nxts[y]) {
    PI t = f(y, depc[y] - depc[x]);
    V1[x] = (V1[x] + t.first) % mod;
    V2[x] = (V2[x] + t.second) % mod;
  }
  ans = (ans + ((sumV1 - V1[x]) * V2[x] + (sumV2 - V2[x]) * V1[x]) % mod * c) % mod;
  PI t = mp(V1[x], V2[x]);
  V1[x] = V2[x] = pres[x] =  0;
  return t;
}

LL p[N];

LL get(const PI *a, LL n, const PI *b, LL m) {
  LL k = 0;
  sumV1 = sumV2 = 0;
  for (LL i = 0; i < n; ++i) sumV1 += V1[p[k++] = a[i].first] = a[i].second % mod;
  for (LL i = 0; i < m; ++i) sumV2 += V2[p[k++] = b[i].first] = b[i].second % mod;
  sumV1 %= mod, sumV2 %= mod;
  std::sort(p, p + k, cmp);
  LL top = 0;
  stack[top++] = 1;
  for (LL i = 0; i < k; ++i) {
    LL x = p[i], y = LCA(stack[top - 1], x);
    while (true) {
      if (top <= 1 || dep[y] >= dep[stack[top - 2]]) {
        if (y != stack[--top]) addS(y, stack[top]);
        if (!top || stack[top - 1] != y) stack[top++] = y;
        break;
      }
      addS(stack[top - 2], stack[top - 1]); --top;
    }
    if (stack[top - 1] != x) stack[top++] = x;
  }
  while (--top) addS(stack[top - 1], stack[top]);
  ans = 0;
  f(1, 0);
  return ans;
}

void Init(LL n) {
  memset(pre, -1, sizeof pre);
  for (LL i = 1; i < n; ++i) {
    LL x = read(), y = read(), z = read();
    addEdge(x, y, z);
  }
  dfs(1, 0);
}
};

namespace Tree2 {

LL n, pre[N], to[N * 2], cost[N * 2], nxt[N * 2], cnt;

void addEdge(LL x, LL y, LL z) {
  nxt[cnt] = pre[x];
  cost[cnt] = z;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  cost[cnt] = z;
  to[pre[y] = cnt++] = x;
}

std::vector<PI> S[N];

void dfs1(LL x, LL f) {
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) {
      S[x].push_back(mp(to[i], cost[i]));
      dfs1(to[i], x);
    }
}

bool virt[N];

void build_(LL x, const std::vector<PI> &V, LL l, LL r) {
  LL len = r - l;
  if (len == 0) return;
  if (len == 1) return addEdge(x, V[l].first, V[l].second);
  if (len == 2) return (addEdge(x, V[l].first, V[l].second), addEdge(x, V[l + 1].first, V[l + 1].second));
  LL mid = (l + r + 1) / 2, a = ++n, b = ++n;
  virt[a] = virt[b] = true;
  addEdge(x, a, 0); addEdge(x, b, 0);
  build_(a, V, l, mid);
  build_(b, V, mid, r);
}

void Init(LL _n) {
  n = _n;
  memset(pre, -1, sizeof pre);
  for (LL i = 1; i < n; ++i) {
    LL x = read(), y = read(), z = read();
    addEdge(x, y, z);
  }
  dfs1(1, 0);
  memset(pre, -1, sizeof pre);
  cnt = 0;
  for (LL tn = n, x = 1; x <= tn; ++x)
    build_(x, S[x], 0, S[x].size());
}

bool vis[N];
LL siz[N];

LL dfs2(LL x, LL f) {
  siz[x] = 1;
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && !vis[to[i]])
      siz[x] += dfs2(to[i], x);
  return siz[x];
}

void dfs3(LL x, LL f, LL nn, LL &a, LL &b, LL &t) {
  LL tt = std::min(siz[x], nn - siz[x]);
  if (tt > t) a = x, b = f, t = tt;
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && !vis[to[i]])
      dfs3(to[i], x, nn, a, b, t);
}

PI A[N], B[N];

void dfs4(LL x, LL f, LL dep, PI *P, LL &k) {
  if (!virt[x]) P[k++] = mp(x, dep %= mod);
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && !vis[to[i]])
      dfs4(to[i], x, dep + cost[i], P, k);
}

void dfs5(LL x, LL f, PI *P, LL &k) {
  if (!virt[x]) P[k++] = mp(x, 1);
  for (LL i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f && !vis[to[i]])
      dfs5(to[i], x, P, k);
}

LL Divide(LL x) {
  dfs2(x, 0);
  if (siz[x] <= 1) return 0;
  LL y, t = 0;
  dfs3(x, 0, siz[x], x, y, t);
  LL kl = 0, kr = 0, c = 0;
  for (LL i = pre[x]; ~i; i = nxt[i]) if (to[i] == y) { c = cost[i]; break; }
  dfs4(x, y, 0, A, kl);
  dfs5(y, x, B, kr);
  LL ans = Tree1::get(A, kl, B, kr);
  kl = kr = 0;
  dfs4(y, x, c, A, kl);
  dfs5(x, y, B, kr);
  ans += Tree1::get(A, kl, B, kr);
  vis[y] = true;
  ans += Divide(x);
  vis[y] = false;
  vis[x] = true;
  ans += Divide(y);
  vis[x] = false;
  return ans % mod;
}
}

int main() {
  freopen("tree.in", "r", stdin);
  freopen("tree.out", "w", stdout);
  LL n = read();
  Tree1::Init(n);
  Tree2::Init(n);
  printf("%lld\n", (2 * Tree2::Divide(1) % mod + mod) % mod);
}
