#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
const int maxn = 1000005;
const int maxt = 12;
int C[maxt][maxn];
int n;
inline int lowbit(int x) {
  return x & (-x);
}
void add(int t, int p, int v) {
  int *A = C[t];
  while(p <= n) {
    A[p] += v;
    p += lowbit(p);
  }
}
int sum(int t, int p) {
  int *A = C[t];
  int ans = 0;
  while(p > 0) {
    ans += A[p];
    p -= lowbit(p);
  }
  return ans;
}
inline void add_seg(int t, int l, int r, int v) {
  if(l > r) return;
#ifdef DEBUG
  fprintf(stderr, "New modify : (%d, %d, %d, %d)\n", t, l, r, v);
#endif
  add(t, l, v);
  add(t, r + 1, -v);
}

int occur[maxn][maxt];
inline void deal(int v, int typ = 1) {
  int *O = occur[v] + 1;
  if(!O[0]) return;
  int minl = O[0] + 1;
  /*
  if(O[1]) {
    if(O[1] < O[0]) {
      add_seg(1, std::max(O[-1], O[1]) + 1, O[0], typ);
      minl = O[1] + 1;
    } else {
      minl = O[0];
    }
  } else {
    add_seg(1, O[-1] + 1, O[0], typ);
    return;
  }
  */
  for(int i = 0; i <= 9; i ++) {
    const int th = O[i];
    if(th <= O[-1]) break;
    if(th >= minl) continue;
    int lp = 1, j = i;
    while(j <= 9) {
      if(O[j + 1] < th) {
        lp = O[j + 1] + 1; break;
      }
      j ++;
    }
    add_seg(j + 1, std::max(O[-1] + 1, lp), minl - 1, typ);
    minl = lp;
  }
}

namespace IO {
  char ibuf[1 << 26], *s;
	void init()	{
		fread(s = ibuf, 1, 1 << 26, stdin);
	}
	inline int read()
	{
		register int u = 0;
		while(*s < 48) s ++;
		while(*s > 32)
			u = u * 10 + *(s ++) - 48;
		return u;
	}
};

int A[maxn]; char ans[maxn][12];
typedef std::pair<int, int> pii;
std::vector<pii> que[maxn];
int main() {
#ifndef LOCAL
  freopen("shinku.in", "r", stdin);
  freopen("shinku.out", "w", stdout);
#endif
  IO::init();
  using IO::read;
  n = read(); int m = read();
  for(int i = 1; i <= n; i ++) A[i] = read();
  for(int i = 1; i <= m; i ++) {
    int l = read(); int r = read();
    que[r].push_back(pii(l, i));
  }
  for(int i = 1; i <= n; i ++) {
#ifdef DEBUG
    fprintf(stderr, "Stage %d\n", i);
#endif
    const int val = A[i];
    for(int j = -1; j < std::min(11, val); j ++) {
      const int nv = val - j;
      deal(nv, -1);
      occur[nv][j + 1] = i;
      deal(nv);
    }
    for(int j = 0; j < que[i].size(); j ++) {
      const int l = que[i][j].first;
      const int id = que[i][j].second;
      for(int k = 1; k <= 10; k ++) {
        ans[id][k - 1] = '0' + sum(k, l) % 10;
      }
    }
  }
  for(int i = 1; i <= m; i ++) {
    puts(ans[i]);
  }
  return 0;
}
