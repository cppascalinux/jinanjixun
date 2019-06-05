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
struct node {
	int n[8], sx;
}zt[47], I;
int n, K;
const int mod = 1000000007;
bool operator < (const node & a, const node & b) {
	rep(i, 1, 7) if(a.n[i] != b.n[i]) return a.n[i] < b.n[i];
	return a.sx < b.sx;
}
bool operator == (const node & a, const node & b) {
	rep(i, 1, 7) if(a.n[i] != b.n[i]) return 0;
	return a.sx == b.sx;
}
int ct = 1;
struct matrix {
	int nb[47][47];
	void init() {
		memset(nb, 0, sizeof(nb));
		rep(i, 0, ct) nb[i][i] = 1;
	}
}zy[2], E;
matrix operator * (const matrix &a, const matrix &b) {
	matrix c;
	memset(c.nb, 0, sizeof(c.nb));
	rep(i, 1, ct) rep(j, 1, ct) {
		if(a.nb[i][j] == 0) continue;
		rep(k, 1, ct) c.nb[i][k] = (c.nb[i][k] + 1ll * a.nb[i][j] * b.nb[j][k] % mod) % mod;
	}
	return c;
}
void dfs(int ls, int nw) {
	if(nw == 0) {
		if(ls != 0) return; 
		int x = ct;
		rep(i, 1, n) {
			if(zt[x].n[i]) {
				zt[++ct] = zt[x];
				zt[ct].sx = i;
			}
		}
		++ct;
		zt[ct] = zt[x];
		return;
	}
	for(int i = 0; i * nw <= ls; ++i) {
		zt[ct].n[nw] = i;
		dfs(ls - i * nw, nw - 1);
	}
}
void dfs20(node x, node y, int z, int wz, int op) {
	node w = x, p = y;;
	w.sx = 0;
	if(w == I) {(zy[0].nb[wz][lower_bound(zt + 1, zt + 1 + ct, y) - zt] += z * (op == 0)) %= mod; return;}
	w.sx = x.sx;
	per(i, n, 1) {
		if(x.n[i]) {
			if(x.sx == i) {
				w = x;
				w.sx = 0;
				w.n[i]--;
				p = y;
				p.n[i]++;
				p.sx = i;
				dfs20(w, p, z, wz, op);
			} else {
				rep(j, 0, i) {
					w = x;
					w.n[i]--;
					p = y;
					p.n[j]++;
					p.n[i - j]++;
					dfs20(w, p, z, wz, op ^ (j & 1));
				}
			}
			break;
		}
	}
}
void dfs21(node x, node y, int z, int wz, int op) {
	node w = x, p = y;;
	w.sx = 0;
	if(w == I) {
		(zy[1].nb[wz][lower_bound(zt + 1, zt + 1 + ct, y) - zt] += z * (op == 0)) %= mod; 
		return;
	}
	w.sx = x.sx;
	per(i, n, 1) {
		if(x.n[i]) {
			if(x.sx == i) {
				rep(j, 0, i) {
					w = x;
					w.sx = 0;
					w.n[i]--;
					p = y;
					p.n[j]++;
					p.n[i - j]++;
					p.sx = j;
					dfs21(w, p, z, wz, op ^ (j & 1));
				}
			} else {
				rep(j, 0, i) {
					w = x;
					w.n[i]--;
					p = y;
					p.n[j]++;
					p.n[i - j]++;
					dfs21(w, p, z, wz, op ^ (j & 1));
				}
			}
			break;
		}
	}
}
char S[10005];
int ls;
matrix qpow(matrix a, int b) {
	matrix c;
	c.init();
	while(b) {
		if(b & 1) c = c * a;
		a = a * a;
		b >>= 1;
	}
	return c;
} 
int main() {
	freopen("end.in", "r", stdin);
	freopen("end.out", "w", stdout);
	scanf("%d%d", &n, &K);
	dfs(n, n);
	--ct;
	sort(zt + 1, zt + 1 + ct);
	rep(i, 1, ct) {
		dfs20(zt[i], I, 1, i, 0);
		dfs21(zt[i], I, 1, i, 0);
	}
	
	E.init();
	scanf("%s", S + 1);
	ls = strlen(S + 1);
	rep(i, 1, ls) {
		if(S[i] == '0') E = E * zy[0];
		else E = E * zy[1];
	}
	matrix as;
	memset(as.nb, 0, sizeof(as.nb));
	node A;
	memset(A.n, 0, sizeof(A.n));
	A.n[n] = 1; A.sx = n;
	int wz = lower_bound(zt + 1, zt + 1 + ct, A) - zt;
	as.nb[1][wz] = 1;
	as = as * qpow(E, K - 1);
	E.init();
	per(i, ls, 1) {
		if(S[i] == '0') {S[i] = '1';}
		else {S[i] = '0'; break;}
	}
	rep(i, 1, ls) {
		if(S[i] == '0') E = E * zy[0];
		else E = E * zy[1];
	}
	as = as * E;
	memset(A.n, 0, sizeof(A.n));
	A.n[1] = n; A.sx = 1;
	wz = lower_bound(zt + 1, zt + 1 + ct, A) - zt;
	int AS = 0;
	AS = (AS + as.nb[1][wz]) % mod;
	A.n[1] = n; A.sx = 0;
	wz = lower_bound(zt + 1, zt + 1 + ct, A) - zt;
	AS = (AS + as.nb[1][wz]) % mod;
	cout << AS << endl;
	return 0;
}
