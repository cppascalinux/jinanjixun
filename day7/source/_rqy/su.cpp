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

void write(int x, char c) {
  if (x >= 10) write(x / 10, EOF);
  putChar(x % 10 + '0');
  if (c != EOF) putChar(c);
}

const int N = 100050;

int n, m, pre[N], to[N * 2], nxt[N * 2], cnt;
int dep[N], color[N];

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}

void dfs0(int x, int f) {
  dep[x] = dep[f] + 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f)
      dfs0(to[i], x);
}

void change(int x, int f, int c) {
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f && color[x] == color[to[i]])
      change(to[i], x, c);
  color[x] = c;
}

void query(int x, int f, int &mx, int &mn, int &sz) {
  mx = std::max(mx, dep[x]);
  mn = std::min(mn, dep[x]);
  sz = sz + 1;
  for (int i = pre[x]; i != -1; i = nxt[i])
    if (to[i] != f && color[x] == color[to[i]])
      query(to[i], x, mx, mn, sz);
}

int main() {
  freopen("su.in", "r", stdin);
  freopen("su.out", "w", stdout);
  n = read(); read();
  memset(pre, -1, sizeof pre);
  for (int i = 2; i <= n; ++i) addEdge(i, read());
  for (int i = 1; i <= n; ++i) color[i] = read();
  dep[0] = -1; dfs0(1, 0);
  m = read();

  while (m--) {
    int op = read(), x = read();
    if (op == 1) color[x] = read();
    else if (op == 2) change(x, 0, read());
    else {
      int mx = 0, mn = n + 1, sz = 0;
      query(x, 0, mx, mn, sz);
      write(color[x], ' ');
      write(sz, ' ');
      write(mx - mn + 1, '\n');
    }
  }
  fwrite(s, 1, p - s, stdout);
  fprintf(stderr, "%lu\n", clock());
  return 0;
}