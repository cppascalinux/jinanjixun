#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <ctime>

const int T = 10000000;
inline char getChar() {
  static char s[T], *end = s, *p = s;
  if (p == end) {
    if (feof(stdin)) return EOF;
    end = s + fread(p = s, 1, T, stdin);
  }
  return *(p++);
}

int read() {
  int ans = 0, c;
  while (!isdigit(c = getChar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getChar()));
  return ans;
}

char s[T], *p = s, *end = s + T;
inline void putChar(char c) {
  if (p == end) fwrite(p = s, 1, T, stdout);
  *(p++) = c;
}

const int N = 1000050;

struct Query {
  int l, r, id;
  bool operator<(const Query &t) const {
    return l > t.l;
  }
} Q[N];

int n, m, A[N], las[N], ans[N][20];
std::pair<int, int> P[100];
bool L[20], R[20];
int S[20][N];

void add(int *S, int x, int v) { for (; x <= n; x += x & -x) S[x] += v; }
int get(int *S, int x) { int v = 0; for (; x; x &= x - 1) v += S[x]; return v; }

int main() {
  freopen("shinku.in", "r", stdin);
  freopen("shinku.out", "w", stdout);
  n = read(); m = read();
  for (int i = 1; i <= n; ++i) A[i] = read();
  for (int i = 0; i < m; ++i) Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
  memset(las, 0x3f, sizeof las);
  std::sort(Q, Q + m);
  for (int i = n, k = 0; i >= 1; --i) {
    int t = 0;
    for (int j = std::max(A[i] - 11, 0); j <= A[i] + 11; ++j)
      P[t++] = std::make_pair(las[j], j);
    P[t++] = std::make_pair(0x3f3f3f3f, 0);
    std::sort(P, P + t);
    memset(L, 0, sizeof L);
    memset(R, 0, sizeof R);
    int l = 0, r = 0;
    add(S[1], i, 1);
    for (int j = 0; j < t; ++j) {
      int x = P[j].first, b = P[j].second;
      int tt = l + r + 1;
      if (b == A[i] || x > n) {
        if (l <= 10) add(S[l], x, 1);
        if (r <= 10) add(S[r], x, 1);
        if (tt <= 10) add(S[tt], x, -1);
        break;
      } else if (b < A[i]) L[A[i] - b] = true;
      else R[b - A[i]] = true;
      if (L[l + 1]) {
        if (l <= 10) add(S[l], x, 1);
        while (L[l + 1]) ++l;
        if (l <= 10) add(S[l], x, -1);
      }
      if (R[r + 1]) {
        if (r <= 10) add(S[r], x, 1);
        while (R[r + 1]) ++r;
        if (r <= 10) add(S[r], x, -1);
      }
      int tt2 = l + r + 1;
      if (tt != tt2) {
        if (tt <= 10) add(S[tt], x, -1);
        if (tt2 <= 10) add(S[tt2], x, 1);
      }
    }
    while (Q[k].l == i) {
      for (int t = 1; t <= 10; ++t)
        ans[Q[k].id][t] = get(S[t], Q[k].r);
      ++k;
    }
    las[A[i]] = i;
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= 10; ++j)
      putChar('0' + ans[i][j] % 10);
    putChar('\n');
  }
  fwrite(s, 1, p - s, stdout);
  //fprintf(stderr, "%lu\n", clock());
  return 0;
}