#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned int uint;
typedef unsigned long long ULL;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair

#define rep(i, x, y) for(int i = (x); i <= (y); ++ i)
#define rop(i, x, y) for(int i = (x); i < (y); ++ i)
#define pre(i, x, y) for(int i = (x); i >= (y); -- i)
#define por(i, x, y) for(int i = (x); i > (y); -- i)

const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const db eps = 1e-8;


char buf[1 << 21], *p1 = buf, *p2 = buf;

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++)
#define cint const int

inline int rd() {
	int x = 0;
	char c = gc();
	while(!isdigit(c)) c = gc();
	while(isdigit(c)) x = x * 10 + c - 48, c = gc();
	return x;
}

const int N = 1e5 + 50;
int head[N], to[N << 1], nxt[N << 1], val[N << 1], c[N], g[N], fm, ed;
int tot = 1, prep[N], pree[N];
LL f[N], Dis, sum, p[N];
void add(int x, int y, int v) { to[++ tot] = y, nxt[tot] = head[x], head[x] = tot, val[tot] = v; }

void dfs(int now, int fa) {
	g[now] = now;
	for(int i = head[now]; i; i = nxt[i]) {
		if(to[i] == fa) continue;
		dfs(to[i], now);
		if(f[to[i]] + f[now] + val[i] > Dis) {
			Dis = f[to[i]] + f[now] + val[i];
			fm = g[to[i]];
			ed = g[now];
		}
		if(f[to[i]] + val[i] > f[now]) {
			f[now] = f[to[i]] + val[i];
			g[now] = g[to[i]];
		}
	}
}

void ch(int now, int fa) {
	for(int i = head[now]; i; i = nxt[i]) {
		if(to[i] == fa) continue;
		prep[to[i]] = now;
		pree[to[i]] = i;
		if(to[i] == ed) return ;
		ch(to[i], now);
		
	}
}

int main() {
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);
	
	int n = rd(), m = rd(), x, y, w;
	rop(i, 1, n) x = rd(), y = rd(), w = rd(), add(x, y, w), add(y, x, w), sum += w;
	rep(i, 1, m) c[i] = rd();
	rep(i, 1, m) {
		rep(j, 1, n) f[j] = 0;
		Dis = 0;
		dfs(1, 0);
		p[i] = Dis;
		p[i] += p[i - 1];
		ch(fm, 0);
		while(ed != fm) {
			val[pree[ed]] *= -1;
			val[pree[ed] ^ 1] *= -1;
			ed = prep[ed];
		}
	}
	LL Era = 0;
	rep(i, 0, m) {
		sort(c + 1, c + 1 + i);
		LL Now = 0;
		rep(j, 1, i) {
			Now += c[j];
			Era = max(Era, p[j] - Now);
		}
		printf("%lld ", 2 * sum - Era);
	}
}
