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
//#define gc() getchar()
#define cint const int

inline int rd() {
	int x = 0, f = 1;
	char c = gc();
	while(!isdigit(c)) { if(c == '-') f = -1; c = gc(); }
	while(isdigit(c)) x = x * 10 + c - 48, c = gc();
	return x * f;
}

const int N = 1e5 + 50;

int p[N];
int l[N], r[N], t[N];
int n, m;
int ww[55];
int ans[55];
bool check() {
	memset(ww, 0, sizeof ww);
	rep(i, 1, m) {
		if(ans[i] == 1) rep(j, l[i], r[i]) ++ ww[j];
		else rep(j, l[i], r[i]) -- ww[j];
	}
	rep(i, 1, p[0]) {
		if(ww[i] < -1 || ww[i] > 1) return 0;
	}
	return 1;
}

void dfs(int now) {
	if(now == m + 1) {
		if(check()) {
			rep(i, 1, m) printf("%d ", ans[i]);
			exit(0);
		}
		return;
	}
	if(t[now] == -1) {
		ans[now] = 0; dfs(now + 1);
		ans[now] = 1; dfs(now + 1);
	}
	else if(t[now] == 1) {
		ans[now] = 1; dfs(now + 1);
	}
	else if(t[now] == 0) {
		ans[now] = 0; dfs(now + 1);
	}
}

int main() {
	freopen("wait.in", "r", stdin);
	freopen("wait.out", "w", stdout);
	m = rd(), n = rd();
	rep(i, 1, m) l[i] = rd(), r[i] = rd(), t[i] = rd(), p[++ p[0]] = l[i], p[++ p[0]] = r[i];
	sort(p + 1, p + 1 + p[0]);
	int tot = p[0];
	tot = unique(p + 1, p + 1 + tot) - p;
	p[0] = tot;
	rep(i, 1, m) l[i] = lower_bound(p + 1, p + 1 + p[0], l[i]) - p, r[i] = lower_bound(p + 1, p + 1 + p[0], r[i]) - p;
	dfs(1);
	printf("%d\n", -1);
}

