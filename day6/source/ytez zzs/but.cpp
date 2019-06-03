#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <deque>
typedef long long ll;
struct Point {
  ll x, y; int id;
  Point(ll a = 0, ll b = 0) {
    x = a; y = b;
  }
};
typedef Point Vec;
Vec operator +(Vec a, Vec b) {
  return Vec(a.x + b.x, a.y + b.y);
}
Vec operator -(Vec a, Vec b) {
  return Vec(a.x - b.x, a.y - b.y);
}
bool operator ==(Point a, Point b) {
  return (a.x == b.x && a.y == b.y);
}
ll times(Vec a, Vec b) {
  return a.x * b.y - a.y * b.x;
}
ll dot(Vec a, Vec b) {
  return a.x * b.x + a.y * b.y; 
}
bool cmp(const Point &a, const Point &b) {
  if((a.x - b.x) == 0) {
    return a.y < b.y;
  } else {
    return a.x < b.x;
  }
}

typedef unsigned long long ull;
typedef std::vector<Point>::iterator iter_t;
const ull seed = 11451;
ull get_hash(iter_t lp, iter_t rp) {
  ull ans = 0;
  while(lp != rp) {
    ans = ans * seed + ((*lp).id);
    ++ lp;
  }
  return ans;
}

typedef std::pair<int, ull> pii;
pii andrew(Point *P, int L) {
  std::vector<Point> bot, top;
  std::sort(P + 1, P + 1 + L, cmp);
  for(int i = 1; i <= L; i ++) {
    if(i != 1 && (P[i].x - P[i - 1].x) == 0) continue;
    while(bot.size() > 1 && (times(P[i] - bot.back(), bot.back() - bot[bot.size() - 2])) >= 0) {
      bot.pop_back();
    }
    bot.push_back(P[i]);
  }
  for(int i = L; i >= 1; i --) {
    if(i != L && (P[i].x - P[i + 1].x) == 0) continue;
    while(top.size() > 1 && (times(P[i] - top.back(), top.back() - top[top.size() - 2])) >= 0) {
      top.pop_back();
    }
    top.push_back(P[i]);
  }
  for(int i = 0; i < top.size(); i ++) bot.push_back(top[i]);
  std::sort(bot.begin(), bot.end(), cmp);
  iter_t ep = std::unique(bot.begin(), bot.end());
  return pii(ep - bot.begin(), get_hash(bot.begin(), ep));
}

int pcnt[1 << 20], sumv[1 << 20];
ull hs[1 << 20]; bool ban[1 << 20];
int w[35], ans[35], n;

Point P[35], R[35];
int main() {
#ifndef LOCAL
  freopen("but.in", "r", stdin);
  freopen("but.out", "w", stdout);
#endif
  scanf("%d", &n);
  pcnt[0] = 0;
  for(int i = 1; i <= n; i ++) {
    scanf("%lld%lld%d", &R[i].x, &R[i].y, &w[i]);
    R[i].id = i;
  }
  for(int i = 1; i <= n; i ++) ans[i] = 0x7fffffff;
  for(int s = 1; s < (1 << n); s ++) {
    int L = 0;
    for(int i = 1; i <= n; i ++) {
      if((1 << (i - 1)) & s) P[++ L] = R[i];
    }
    pii pr = andrew(P, L);
    int sum = 0;
    for(int i = 1; i <= n; i ++) {
      if((1 << (i - 1)) & s) sum += w[i];
    }
    pcnt[s] = pr.first;
    hs[s] = pr.second;
    sumv[s] = sum;
  }
  for(int s = (1 << n) - 1; s > 0; s --) {
    for(int i = 0; i < n; i ++) {
      if((1 << i) & s) {
        int ns = (1 << i) ^ s;
        if(hs[ns] == hs[s]) ban[ns] = true;
      }
    }
  }
  for(int s = 3; s < (1 << n); s ++) {
    if(!ban[s]) {
      const int c = pcnt[s];
      ans[c] = std::min(ans[c], sumv[s]);
    }
  }
  for(int i = 3; i <= n; i ++) {
    if(i > 3) putchar(' ');
    if(ans[i] == 0x7fffffff) {
      ans[i] = -1;
    }
    printf("%d", ans[i]);
  }
  puts("");
  return 0;
}
