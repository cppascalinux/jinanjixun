#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long LL;

int read() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

const int N = 100050;
const int L = 30;

int m, q, A[N], T[N], u;

void Insert(int v, int t) {
  for (int i = m - 1; ~i; --i)
    if ((v >> i) & 1) {
      if (!A[i]) {
        A[i] = v; T[i] = t; ++u; return;
      } else {
        if (T[i] < t)
          std::swap(A[i], v), std::swap(T[i], t);
        v ^= A[i];
      }
    }
}

void Remove(int t) {
  for (int i = m - 1; ~i; --i)
    if (t == T[i]) {
      A[i] = T[i] = 0;
      --u;
      return;
    }
}

int v[N], out[N];
std::map<int, int> M;

int main() {
  freopen("xor.in", "r", stdin);
  freopen("xor.out", "w", stdout);
  m = read(); q = read();
  for (int i = 1; i <= q; ++i) {
    int op = read(), x = read();
    if (op == 1) out[M[v[i] = x] = i] = q + 1;
    else out[M[x]] = i;
  }
  for (int i = 1; i <= q; ++i) {
    if (v[i]) Insert(v[i], out[i]);
    else Remove(i);
    printf("%d\n", 1 << u);
  }
}

