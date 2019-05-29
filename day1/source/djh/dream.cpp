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

const int N = 65;
const int mod = 998244353;

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

int ksm(int a, int p) {
	int ans = 1;
	while(p) {
		if(p & 1) ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		p >>= 1;
	}
	return ans;
}

inline int Add(int x, int y) { int z = x + y; return z >= mod ? z - mod : z; }
inline int Del(int x, int y) { int z = x - y; return z < 0 ? z + mod : z; }

int c[N][N][N];
int sc[N][N][N];
int val[N][N][N];
int p[N][N][N];
int plu[N];

int get(int a[][N][N], int x, int y, int z, int xx, int yy, int zz) {
	return Del(Add(Add(Add(Del(Del(Del(a[xx][yy][zz], a[xx][yy][z - 1]), a[xx][y - 1][zz]), a[x - 1][yy][zz]), a[x - 1][y - 1][zz]), a[x - 1][yy][z - 1]), a[xx][y - 1][z - 1]), a[x - 1][y - 1][z - 1]);
}

inline void change(cint &x, cint &y, cint &z, cint &xx, cint &yy, cint &zz, cint &val) {
	p[x][y][z] = Add(p[x][y][z], val);
	p[xx + 1][y][z] = Del(p[xx + 1][y][z], val);
	p[x][yy + 1][z] = Del(p[x][yy + 1][z], val);
	p[x][y][zz + 1] = Del(p[x][y][zz + 1], val);
	p[xx + 1][yy + 1][z] = Add(p[xx + 1][yy + 1][z], val);
	p[xx + 1][y][zz + 1] = Add(p[xx + 1][y][zz + 1], val);
	p[x][yy + 1][zz + 1] = Add(p[x][yy + 1][zz + 1], val);
	p[xx + 1][yy + 1][zz + 1] = Del(p[xx + 1][yy + 1][zz + 1], val);
}

int main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	int n = rd(), m = rd(), k = rd(), w = rd();
	rep(i, 1, n) rep(j, 1, m) rep(l, 1, k) c[i][j][l] = rd(), c[i][j][l] ^= 1,
	sc[i][j][l] = Add(Del(Add(sc[i - 1][j][l], Add(sc[i][j - 1][l], Add(sc[i][j][l - 1], c[i][j][l]))),
	Add(sc[i - 1][j - 1][l], Add(sc[i - 1][j][l - 1], sc[i][j - 1][l - 1]))), sc[i - 1][j - 1][l - 1]);
	rep(i, 1, n) rep(j, 1, m) rep(l, 1, k) val[i][j][l] = rd();
	int cnt = 0;
	int tot = (1ll * n * (n + 1) / 2 * m * (m + 1) / 2 * k * (k + 1) / 2) % mod;
	rep(x, 1, n) rep(y, 1, m) rep(xx, x, n) rep(yy, y, m) {
		for(int l = 1, r = 1; l <= k; l = r + 1) {
			while(r <= k && get(sc, x, y, l, xx, yy, r) == 0) ++ r;
			int len = r - l;
			int mid = len >> 1;
			cnt = Add(cnt, len * (len + 1) / 2);
			rep(now, 1, mid) {
				plu[now] = now * (now + 1) / 2 + now * (mid - now);
				plu[now] <<= 1;
				if(len & 1) plu[now] += now;
				plu[len - now + 1] = plu[now];
			}
			if(len & 1) plu[mid + 1] = plu[mid] + 1;
			rop(p, l, r) {
				change(x, y, p, xx, yy, p, plu[p - l + 1]);
			}
		}
	}
	int ans = 0;
	rep(i, 1, n) rep(j, 1, m) rep(l, 1, k) {
		p[i][j][l] = Add(Del(Add(p[i - 1][j][l], Add(p[i][j - 1][l], Add(p[i][j][l - 1], p[i][j][l]))),\
		Add(p[i - 1][j - 1][l], Add(p[i - 1][j][l - 1], p[i][j - 1][l - 1]))), p[i - 1][j - 1][l - 1]);
	}
	rep(x, 1, n) rep(y, 1, m) rep(z, 1, k) {
		ans = Add(ans, 1ll * val[x][y][z] * Del(1, ksm(Del(1, (1ll * p[x][y][z] * ksm(cnt, mod - 2) % mod)), w)) % mod);
	}
	printf("%d\n", 1ll * ans * ksm(cnt, w) % mod * ksm(ksm(tot, w), mod - 2) % mod);
}
