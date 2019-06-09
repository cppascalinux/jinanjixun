#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#include <queue>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
int n, _2, ct, ds[2000005];
int mod, as[2000005];
struct node {
	int nb[61];
}I;
queue<int> Q;
bool operator < (const node &a, const node &b) {
	rep(i, 1, n) if(a.nb[i] != b.nb[i]) return a.nb[i] < b.nb[i];
	return 0;
}
int qpow(int a, int b) {
	int as = 1;
	while(b) {
		if(b & 1) as = 1ll * as * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return as;
}
map<node, int> M[75];
struct graph {
	int hd[2000005], vr[20000005], vl[20000005], nt[20000005], tt;
	void push(int x, int y, int w) {
		vr[++tt] = y; vl[tt] = w; nt[tt] = hd[x]; hd[x] = tt;
	}
	int work() {
		as[ct] = 0;
		per(x, ct, 1) {
			as[x] = (1ll * (as[x] + 1) * qpow(ds[x], mod - 2)) % mod;
			for(int i = hd[x]; i; i = nt[i]) as[vr[i]] = (as[vr[i]] + 1ll * vl[i] * as[x] % mod) % mod;
		}
		return as[1];
	}
}G;
int main() {
	freopen("random.in", "r", stdin);
	freopen("random.out", "w", stdout);
	scanf("%d%d", &n, &mod);
	_2 = qpow(2, mod - 2);
	rop(i, 1, n) I.nb[i] = 0;
	I.nb[1] = n;
	M[1][I] = ++ct;
	int N = qpow(1ll * n * n % mod, mod - 2); 
	rop(k, 1, n) {
		node nw, x;
		int y, z;
		map<node, int> :: iterator IT = M[k].begin();
		while(IT != M[k].end()) {
			nw = (*IT).first;
			y = 0;
			rep(i, 1, n) y = (y + 1ll * i * i % mod * nw.nb[i] % mod) % mod;
			ds[(*IT).second] = (mod + 1 - 1ll * y * N % mod) % mod;
			rep(i, 1, n) {
				if(nw.nb[i]) rep(j, 1, i) if(nw.nb[j] > (i == j)) {
					x = nw;
					x.nb[i]--;
					x.nb[j]--;
					x.nb[i + j]++;
					z = (i == j) ? (1ll * i * nw.nb[i] % mod * i % mod * (nw.nb[i] - 1) % mod) : (1ll * i * nw.nb[i] % mod * nw.nb[j] % mod * j % mod * 2);
					z = 1ll * z * N % mod;
					if(M[k + 1][x] == 0) M[k + 1][x] = ++ct;
					G.push(M[k + 1][x], (*IT).second, z);
				}
			}
			++IT;
		}
	}
	cout << G.work() << endl;
	return 0;
}
