#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <queue>
#include <set>
const int maxn = 505;
using F_2 = std::function<bool(int, int)>;
using pii = std::pair<int, int>;
int n, m; char A[maxn][maxn];
bool vis[maxn][maxn];
void access(int x, int y, const F_2 &f, std::queue<pii> &Q) {
  if(x <= 0 || y <= 0 || x > n || y > m || !f(x, y) || vis[x][y]) return;
  Q.push({x, y}); vis[x][y] = true;
}
void bfs(int x, int y, const F_2 &f) {
  std::queue<pii> Q;
  Q.push({x, y}); vis[x][y] = true;
  while(!Q.empty()) {
    const int x = Q.front().first;
    const int y = Q.front().second; Q.pop();
    access(x - 1, y, f, Q);
    access(x + 1, y, f, Q);
    access(x, y - 1, f, Q);
    access(x, y + 1, f, Q);
  }
}
void bfs(int x, int y, const F_2 &f, std::vector<pii> &V) {
  std::queue<pii> Q;
  Q.push({x, y}); vis[x][y] = true;
  while(!Q.empty()) {
    const int x = Q.front().first;
    const int y = Q.front().second; Q.pop();
    V.push_back({x, y});
    access(x - 1, y, f, Q);
    access(x + 1, y, f, Q);
    access(x, y - 1, f, Q);
    access(x, y + 1, f, Q);
  }
}

std::vector<char*> add_ans, del_ans;
void gen_seg(int L, int R) {
  if(L == -1) return;
  char *S = (char*)malloc(m + 2);
  for(int i = 1; i <= m; i ++) {
    if(L <= i && i <= R) {
      S[i - 1] = '1';
    } else {
      S[i - 1] = '0';
    }
  }
  S[m] = '\n'; S[m + 1] = 0;
  add_ans.push_back(S);
}
void case_n_1() {
  int L = -1, R = -1;
  for(int i = 1; ; i ++) {
    if(i <= m && A[1][i] == '1') {
      R = i;
      if(L == -1) L = i;
    } else {
      gen_seg(L, R);
      if(i <= m) L = R = -1;
    }
    if(i > m) break;
  }
}

auto check_0 = [&](int x, int y) -> bool {
  return A[x][y] == '0';
};
auto check_1 = [&](int x, int y) -> bool {
  return A[x][y] == '1';
};

namespace NMSL {
  inline int get_id(int x, int y) {
    return (x - 1) * m + y;
  }
  inline int get_id(const pii &pr) {
    const int x = pr.first, y = pr.second;
    return (x - 1) * m + y;
  }
  
  int bel[maxn][maxn];
  void acc(int id, int x, int y, std::set<int> &V) {
    if(x <= 0 || y <= 0 || x > n || y > m || check_0(x, y)) return;
    V.insert(bel[x][y]);
  }
  bool solve() {
    memset(vis, 0, sizeof(vis));
    int ob_cnt = 0;
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(check_0(i, j) || vis[i][j]) continue;
#ifdef LOCAL
        printf("New one block : %d, %d\n", i, j);
#endif
        std::vector<pii> V;
        bfs(i, j, check_1, V);
        ob_cnt ++;
        for(pii pr : V) {
#ifdef LOCAL
          printf("Point : (%x, %d)\n", pr.first, pr.second);
#endif
          bel[pr.first][pr.second] = ob_cnt;
        }
      }
    }
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(vis[i][j]) continue;
#ifdef LOCAL
        printf("New zero block : %d, %d\n", i, j);
#endif
        std::vector<pii> V;
        std::set<int> tmp;
        bfs(i, j, check_0, V);
        for(pii pr : V) {
#ifdef LOCAL
          printf("Point : (%x, %d)\n", pr.first, pr.second);
#endif
          const int x = pr.first, y = pr.second, th = get_id(pr);
          acc(th, x - 1, y, tmp);
          acc(th, x + 1, y, tmp);
          acc(th, x, y - 1, tmp);
          acc(th, x, y + 1, tmp);
        }
        if(tmp.size() == ob_cnt) {
          static char S[maxn][maxn];
          for(pii pr : V) {
            S[pr.first][pr.second] = '1';
          }
          for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++) {
              if(!S[i][j]) S[i][j] = '0';
            }
          }
          puts("2");
          puts("+");
          for(int i = 1; i <= n; i ++) {
            for(int j = 1; j <= m; j ++) {
              if(A[i][j] == '1' || S[i][j] == '1') {
                putchar('1');
              } else {
                putchar('0');
              }
            }
            puts("");
          }
          puts("-");
          for(int i = 1; i <= n; i ++) {
            puts(S[i] + 1);
          }
          return true;
        }
      }
    }
    return false;
  }
};

int check_1_block() {
  memset(vis, 0, sizeof(vis));
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      if(check_1(i, j)) {
        bfs(i, j, check_1);
        bool ok = true;
        for(int i = 1; i <= n; i ++) {
          for(int j = 1; j <= m; j ++) {
            if(check_1(i, j) && !vis[i][j]) {
              ok = false; break;
            }
          }
          if(!ok) break;
        }
        return (int)ok;
      }
    }
  }
  return -1;
}
int get_0_block(int x, int y, int lim) {
  memset(vis, 0, sizeof(vis));
  bfs(x, y, [&](int a, int b) -> bool {
    return A[a][b] == '0' && n <= lim;
  });
  int ret = -1;
  for(int i = lim; i >= 1; i --) {
    bool ok = true;
    for(int j = 1; j <= m; j ++) {
      if(check_0(i, j) && !vis[i][j]) {
        ok = false; break;
      }
    }
    if(ok) {
      ret = i;
    } else {
      break;
    }
  }
  return ret;
}
bool check_0_block() {
  memset(vis, 0, sizeof(vis));
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      if(check_0(i, j)) {
        bfs(i, j, check_0);
        bool ok;
        for(int i = 1; i <= n; i ++) {
          for(int j = 1; j <= m; j ++) {
            if(check_0(i, j) && !vis[i][j]) {
              ok = false; break;
            }
          }
          if(!ok) break;
        }
        return ok;
      }
    }
  }
  return false;
}
bool check_no_0_line() {
  for(int i = 1; i <= n; i ++) {
    bool ok = false;
    for(int j = 1; j <= m; j ++) {
      ok |= check_1(i, j);
    }
    if(!ok) return false;
  }
  return true;
}
bool is_0_line(int i) {
  for(int j = 1; j <= m; j ++) {
    if(check_1(i, j)) return false;
  }
  return true;
}

int l_typ[maxn]; bool l_sex[maxn], fk[maxn];
int lp[maxn], rp[maxn], db[maxn][2];
void solve() {
  for(int i = 1; i <= n; i ++) l_typ[i] = is_0_line(i);
  int las = 0;
  for(int i = 1; i <= n; i ++) {
    if(!l_typ[i]) las = i;
    lp[i] = las;
  }
  las = 0;
  for(int i = n; i >= 1; i --) {
    if(!l_typ[i]) las = i;
    rp[i] = las;
  }
  for(int i = 1; i <= n; i ++) {
    if(l_typ[i] == 1 && (!lp[i] || !rp[i])) l_typ[i] = -1;
  }
  for(int i = 1; i <= n; i ++) {
    if(l_typ[i] == -1) continue;
    if(l_typ[i] == 0) {
      if(!lp[i]) {
        l_sex[i] = true;
      } else if(l_typ[i - 1] == 0) {
        l_sex[i] = !l_sex[i - 1];
      }
    } else if(rp[i] == i + 1) {
      l_sex[i + 1] = !l_sex[lp[i]];
    }
#ifdef LOCAL
    if(l_typ[i] == 0) {
      printf("sex(%d) : %d\n", i, l_sex[i]);
    }
#endif
  }
  for(int i = 1; i <= n; i ++) {
    if(l_typ[i] != 1) continue;
    int nx = -1;
    for(int j = 1; j <= m; j ++) {
      if(A[lp[i]][j] == '1') {
        if(!db[i][0]) {
          db[i][0] = j;
        } else {
          nx = j; break;
        }
      }
    }
    for(int j = 1; j <= m; j ++) {
      if(A[rp[i]][j] == '1') {
        if(db[i][0] == j) {
          if(nx != -1) {
            db[i][0] = nx;
            db[i][1] = j; break;
          }
        } else {
          db[i][1] = j; break;
        }
      }
    }
    if(!db[i][1]) {
      db[i][1] = db[i][0];
      fk[i] = true;
    }
  }
  int st = 0;
  for(int i = 1; i <= n + 1; i ++) {
    if((i > n && fk[n]) || (!fk[i] && fk[i - 1])) {
      st ++;
    }
  }
  if(std::count(fk + 1, fk + 1 + n, true) == 0) {
    st = 0;
  }
  printf("%d\n", st + 3);
  puts("+");
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      if(l_typ[i] == -1) {
        putchar('0');
      } else if(l_typ[i] == 0) {
        if(l_sex[i]) {
          putchar('1');
        } else {
          putchar(A[i][j]);
        }
      } else {
        int th, qin_d;
        if(l_sex[lp[i]]) {
          th = rp[i]; qin_d = db[i][1];
        } else {
          th = lp[i]; qin_d = db[i][0];
        }
        if(qin_d == j) putchar('1');
        else putchar('0');
      }
    }
    puts("");
  }
  for(int i = 1; i <= n; i ++) l_sex[i] ^= 1;
  puts("+");
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      if(l_typ[i] == -1) {
        putchar('0');
      } else if(l_typ[i] == 0) {
        if(l_sex[i]) {
          putchar('1');
        } else {
          putchar(A[i][j]);
        }
      } else {
        int th, qin_d;
        if(l_sex[lp[i]]) {
          th = rp[i]; qin_d = db[i][1];
        } else {
          th = lp[i]; qin_d = db[i][0];
        }
        if(qin_d == j) putchar('1');
        else putchar('0');
      }
    }
    puts("");
  }
  puts("-");
  for(int i = 1; i <= n; i ++) {
    for(int j = 1; j <= m; j ++) {
      if(l_typ[i] == -1) {
        putchar('0');
      } else if(l_typ[i] == 0) {
        putchar('1');
      } else if(j == db[i][0] || j == db[i][1]) {
        putchar('1');
      } else {
        putchar('0');
      }
    }
    puts("");
  }
  int las_L = -1, las_R = -1;
  for(int i = 1; i <= n + 1; i ++) {
    if(i > n || !fk[i]) {
      if(las_L == -1) continue;
      int th = db[las_R][0];
      puts("-");
      for(int j = 1; j <= n; j ++) {
        for(int k = 1; k <= m; k ++) {
          if(las_L <= j && j <= las_R && k == th) {
            putchar('1');
          } else {
            putchar('0');
          }
        }
        puts("");
      }
      las_L = las_R = -1;
    }
    if(i > n) break;
    if(fk[i]) {
      las_R = i;
      if(las_L == -1) las_L = i;
    }
  }
}

int main() {
#ifndef LOCAL
  freopen("bitbit.in", "r", stdin);
  freopen("bitbit.out", "w", stdout);
#endif
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i ++) scanf("%s", A[i] + 1);
  const int val_1 = check_1_block();
  if(n == 1) {
    case_n_1();
  } else if(val_1 == -1) {
    puts("0"); return 0;
  } else if(val_1 == 1) {
    puts("1\n+");
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(vis[i][j]) {
          putchar('1');
        } else {
          putchar('0');
        }
      }
      puts("");
    }
    return 0;
  } else if(NMSL::solve()) {
    return 0;
  } else if(check_no_0_line()) {
    puts("3");
    puts("+");
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(check_1(i, j) || (i & 1)) {
          putchar('1');
        } else {
          putchar('0');
        }
      }
      puts("");
    }
    puts("+");
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        if(check_1(i, j) || ((i & 1) == 0)) {
          putchar('1');
        } else {
          putchar('0');
        }
      }
      puts("");
    }
    puts("-");
    for(int i = 1; i <= n; i ++) {
      for(int j = 1; j <= m; j ++) {
        putchar('1');
      }
      puts("");
    }
    return 0;
  } else {
    solve(); return 0;
  }
  printf("%d\n", add_ans.size() + del_ans.size());
  for(auto S : add_ans) {
    puts("+");
    printf("%s", S);
  }
  for(auto S : del_ans) {
    puts("-");
    printf("%s", S);
  }
  return 0;
}
