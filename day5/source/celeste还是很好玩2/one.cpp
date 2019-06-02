#include <cstdio>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <bitset>
#include <iostream>
#include <queue>

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
#define per(i, x, y) for(int i = (x); i >= (y); -- i)
#define por(i, x, y) for(int i = (x); i > (y); -- i)

const int mod = 1e9 + 7;

int jc[100];

int ksm(int x, int p) {
	int ans = 1;
	while(p) {
		if(p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

int cantor(int *a, int n) {
	int ans = 0;
	rep(i, 1, n) {
		int x = 0;
		rep(j, i + 1, n) x += (a[j] < a[i]);
		ans += x * jc[n - i];
	}
	return ans + 1;
}

int p[10];
int f[1050][1050];
int ans[1050];
int pos[1050];

int guass(int n) {
	rep(i, 1, n) {
		int flag = -1;
		rep(j, i, n) if(f[j][i] != 0) { flag = j; break; }
		if(flag == -1) return -1;
		if(flag != i) rep(j, 1, n + 1) swap(f[i][j], f[flag][j]);
		int inv = ksm(f[i][i], mod - 2);
		rep(j, i + 1, n) {
			int div = f[j][i] * 1ll * inv % mod;
			if(div == 0) continue;
			rep(k, i, n + 1) {
				f[j][k] = (f[j][k] - f[i][k] * 1ll * div % mod + mod) % mod;
			}
		}
	}
	
	per(i, n, 1) {
		ans[i] = f[i][n + 1] * 1ll * ksm(f[i][i], mod - 2) % mod;
		rop(j, 1, i) f[j][n + 1] = (f[j][n + 1] - 1ll * ans[i] * f[j][i] % mod + mod) % mod;
	}
	return 1;
}
		

int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	jc[0] = 1;
	rep(i, 1, 10) jc[i] = jc[i - 1] * i;
	int n; scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &p[i]);
	int now = cantor(p, n);
	f[1][1] = 1;
	rep(i, 1, n) p[i] = i;
	int totrev = n * (n - 1) / 2;
	do {
		int now = cantor(p, n);
		if(now == 1) continue;
		rep(i, 1, n) {
			rep(j, i + 1, n) {
				swap(p[i], p[j]);
				int to = cantor(p, n);
				f[now][to] = mod - ksm(totrev, mod - 2);
				swap(p[i], p[j]);
			}
		}
		f[now][jc[n] + 1] = 1;
		f[now][now] = 1;
	} while(next_permutation(p + 1, p + 1 + n));
	
	guass(jc[n]);
	
	printf("%d\n", ans[now]);
	
}
	
