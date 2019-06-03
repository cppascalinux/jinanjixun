#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <map>

typedef long long LL;

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f = -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

const int N = 10;
const int P = 100000;

int n, m, K;
char ss[N][N];
std::map<LL, int> M;

struct State {
  bool c[N], last;
  int s[N], u;
  LL hash() const {
    static int _s[N]; memset(_s, -1, sizeof _s);
    LL ans = last;
    int t = 0;
    for (int i = 0; i < m; ++i) {
      int si = ~_s[s[i]] ? _s[s[i]] : _s[s[i]] = t++;
      ans = (ans << 1 | c[i]) << 3 | si;
    }
    return ans;
  }
  int add(int x, bool t) {
    if (c[x] == t && x && c[x - 1] == t && last == t)
      return 1;
    last = c[x];
    bool ok = c[x] == t;
    for (int i = 0; i < m && !ok; ++i)
      if (i != x && s[i] == s[x]) ok = true;
    if (!ok) return 2;
    ++u;
    if (c[x] == t)
      for (int i = 0; i < m; ++i)
        if (i != x && s[i] == s[x]) s[i] = u;
    if (x && c[x - 1] == t) {
      for (int i = 0; i < m; ++i)
        if (i != x - 1 && s[i] == s[x - 1]) s[i] = u;
      s[x - 1] = u;
    }
    c[x] = t;
    s[x] = u;
    return 0;
  }
  int check(int l) {
    static int _s[N]; memset(_s, -1, sizeof _s);
    int t = 0;
    for (int i = 0; i < m; ++i)
      if (c[i] == l && _s[s[i]] == -1)
        _s[s[i]] = t++;
    return t;
  }
  bool check() {
    return check(0) <= 1 && check(1) <= 1;
  }
} s, p[P];

int cnt;
LL _f[2][N * N][P], (*f)[P], (*g)[P];

LL &get(LL *a, const State &s) {
  LL t = s.hash();
  if (!M.count(t)) p[M[t] = cnt++] = s;
  return a[M[t]];
}

void dfs_row0(int x, int k) {
  if (x == m) {
    int t = 0;
    s.s[0] = t++;
    for (int i = 1; i < m; ++i) s.s[i] = s.c[i] == s.c[i - 1] ? t - 1 : t++;
    s.u = t;
    ++get(f[k], s);
    return;
  }
  if (ss[0][x] != 'A') {
    s.c[x] = 1;
    dfs_row0(x + 1, k);
  }
  if (ss[0][x] != 'B') {
    s.c[x] = 0;
    dfs_row0(x + 1, k + 1);
  }
}

void debug() {
  printf("Total state number: %d\n", cnt);
  for (int i = 0; i < cnt; ++i) {
    State &t = p[i];
    printf("f[%c", "AB"[t.last]);
    for (int j = 0; j < m; ++j)
      putchar("a0"[t.c[j]] + t.s[j]);
    printf("] = {");
    for (int k = 0; k <= n * m; ++k)
      if (f[k][i]) printf(" (%d, %lld)", k, f[k][i]);
    printf(" }\n");
  }
}

inline bool checkK(int k) { return std::abs(2 * k - n * m) <= K; }

bool checkS(const State &s, int i, int j) {
  if (m <= 1) return true;
  if (i <= n - 2) return false;
  bool t = !s.c[j];
  for (int j2 = j + 1; j2 < m; ++j2)
    if (s.c[j2 - 1] == t && s.c[j2] == t) return false;
  return true;
}

int main() {
  freopen("can.in", "r", stdin);
  freopen("can.out", "w", stdout);
  n = read(); m = read(); K = read();
  int nn[3] = { 0, 0 };
  for (int i = 0; i < n; ++i) {
    scanf("%s", ss[i]);
    for (int j = 0; j < m; ++j)
      ++nn[ss[i][j] - 'A'];
  }
  f = _f[0]; g = _f[1];
  memset(f, 0, sizeof _f[0]);
  dfs_row0(0, 0);
  LL ans = 0;
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j, std::swap(f, g)) {
      printf("\n\n%d %d\n", i, j);
      debug();
      printf("\n");
      memset(g, 0, sizeof _f[0]);
      for (int k = 0; k <= m * i + j; ++k)
        for (int t = 0; t < cnt; ++t) if (f[k][t]) {
          State s;
          if (ss[i][j] != 'A') {
            int st = (s = p[t]).add(j, 1);
            if (!st)
              get(g[k], s) += f[k][t];
            else if (st == 2 && s.check(0) <= 1 && !nn[0] && checkK(k) && checkS(s, i, j))
              ans += f[k][t];
          }
          if (ss[i][j] != 'B') {
            int st = (s = p[t]).add(j, 0);
            if (!st)
              get(g[k + 1], s) += f[k][t];
            else if (st == 2 && s.check(1) <= 1 && !nn[1] && checkK(k + (n - i) * m - j) && checkS(s, i, j))
              ans += f[k][t];
          }
        }
      --nn[ss[i][j] - 'A'];
    }
  debug();
  printf("\n");
  for (int k = 0; k <= n * m; ++k) if (checkK(k))
    for (int i = 0; i < cnt; ++i) if (p[i].check()) ans += f[k][i];
  printf("%lld\n", ans);
  return 0;
}