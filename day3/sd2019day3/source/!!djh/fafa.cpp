#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
const int mod = 998244353;
int f[5005][5005];
int n, K;
inline int MOD(LL x) {
	return x >= mod ? x - mod : x;
}
int main() {
	freopen("fafa.in", "r", stdin);
	freopen("fafa.out", "w", stdout);
	scanf("%d%d", &n, &K);
	f[1][1] = 1;
	rep(i, 1, n) {
		rep(k, 1, i) {
			f[i + 1][k] = MOD(f[i + 1][k] + 1ll * f[i][k] * (k - 1) % mod);
			f[i + 1][k + 1] = MOD(f[i + 1][k + 1] + f[i][k] * 2ll % mod);
			f[i + 1][k + 2] = MOD(f[i + 1][k + 2] + 1ll * f[i][k] * (i + 1 - (k - 1) - 2) % mod);
		}
	}
	cout << 499122177ll * (f[n][K + 1] + f[n][K]) % mod << endl;
	return 0;
}
