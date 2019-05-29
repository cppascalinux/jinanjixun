#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
using namespace std;
typedef long long LL;
typedef double DB;
typedef unsigned int ui;
int n, m, u, v, w;
const LL INF = 1ll << 57;
namespace n1 {
	LL f[100005][10];
	LL g[100005][10];
	LL hf[10], hg[10], Z, as[10], S[10];
	int mx[100005];
	int A[10];
	struct tree {
		LL vl[200005];
		int hd[100005], vr[200005], nt[200005], tt;
		void push(int x, int y, int z) {
			vr[++tt] = y; vl[tt] = z; nt[tt] = hd[x]; hd[x] = tt;
		}
		void dfs(int nw, int en) {
			for(int i = hd[nw]; i; i = nt[i]) {
				if(vr[i] == en) continue;
				dfs(vr[i], nw);
			}
			rep(j, 0, m) f[nw][j] = g[nw][j] = -INF;
			f[nw][0] = 0;
			for(int i = hd[nw]; i; i = nt[i]) {
				if(vr[i] == en) continue;
				rep(k, 0, mx[vr[i]] + 1) {
					per(j, min(m, mx[vr[i]] + mx[nw] + 1), k) {
						hf[j] = max(hf[j], f[nw][j - k] + max(f[vr[i]][k], g[vr[i]][k]));
						if(k) hg[j] = max(hg[j], f[nw][j - k] + f[vr[i]][k - 1] + vl[i]);
						hg[j] = max(hg[j], g[nw][j - k] + f[vr[i]][k]);
						hg[j] = max(hg[j], f[nw][j - k] + g[vr[i]][k] + vl[i]);
						hf[j] = max(hf[j], g[nw][j - k] + f[vr[i]][k] + vl[i]);
						if(j) hf[j - 1] = max(hf[j - 1], g[nw][j - k] + g[vr[i]][k] + vl[i]);
					}
				}
				mx[nw] = min(m, mx[nw] + mx[vr[i]] + 1);
				rep(j, 0, mx[nw]) {
					f[nw][j] = max(f[nw][j], hf[j]); hf[j] = -INF;
					g[nw][j] = max(g[nw][j], hg[j]); hg[j] = -INF;
				}
			}
		}
	}T;
	void main() {
		rop(i, 1, n) {
			scanf("%d%d%d", &u, &v, &w);
			T.push(u, v, w);
			T.push(v, u, w);
			Z = Z + w + w;
		}
		rep(i, 1, m) scanf("%d", &A[i]);
		T.dfs(1, 0);
		as[0] = max(f[1][0], g[1][0]);
		rep(i, 1, m) as[i] = as[i - 1] + max(f[1][i - 1], g[1][i - 1]) + A[i] - max(f[1][i], g[1][i]);
		rep(i, 0, m) cout << as[i] + Z << "\n";
	}
}
namespace n2 {
	LL f[3005][3005];
	LL g[3005][3005];
	LL hf[3005], hg[3005], Z, as[3005], S[3005];
	int mx[3005];
	int A[3005];
	struct tree {
		LL vl[200005];
		int hd[100005], vr[200005], nt[200005], tt;
		void push(int x, int y, int z) {
			vr[++tt] = y; vl[tt] = z; nt[tt] = hd[x]; hd[x] = tt;
		}
		void dfs(int nw, int en) {
			for(int i = hd[nw]; i; i = nt[i]) {
				if(vr[i] == en) continue;
				dfs(vr[i], nw);
			}
			rep(j, 0, m) hf[j] = hg[j] = f[nw][j] = g[nw][j] = -INF;
			f[nw][0] = 0;
			for(int i = hd[nw]; i; i = nt[i]) {
				if(vr[i] == en) continue;
				rep(k, 0, mx[vr[i]] + 1) {
					per(j, min(m, mx[vr[i]] + mx[nw] + 1), k) {
						hf[j] = max(hf[j], f[nw][j - k] + max(f[vr[i]][k], g[vr[i]][k]));
						if(k) hg[j] = max(hg[j], f[nw][j - k] + f[vr[i]][k - 1] + vl[i]);
						hg[j] = max(hg[j], g[nw][j - k] + f[vr[i]][k]);
						hg[j] = max(hg[j], f[nw][j - k] + g[vr[i]][k] + vl[i]);
						hf[j] = max(hf[j], g[nw][j - k] + f[vr[i]][k] + vl[i]);
						if(j) hf[j - 1] = max(hf[j - 1], g[nw][j - k] + g[vr[i]][k] + vl[i]);
					}
				}
				mx[nw] = min(m, mx[nw] + mx[vr[i]] + 1);
				rep(j, 0, mx[nw]) {
					f[nw][j] = max(f[nw][j], hf[j]); hf[j] = -INF;
					g[nw][j] = max(g[nw][j], hg[j]); hg[j] = -INF;
				}
			}
		}
	}T;
	void main() {
		rop(i, 1, n) {
			scanf("%d%d%d", &u, &v, &w);
			T.push(u, v, w);
			T.push(v, u, w);
			Z = Z + w + w;
		}
		rep(i, 1, m) scanf("%d", &A[i]);
		T.dfs(1, 0);
		rep(i, 0, m) {
			sort(A + 1, A + 1 + i);
			rep(j, 1, i) S[j] = S[j - 1] + A[j];
			rep(j, 0, i) {
				as[i] = min(as[i], S[j] - max(f[1][j], g[1][j]));
			}
		}
		rep(i, 0, m) cout << as[i] + Z << " ";
	}
}
namespace n3 {
	multiset<LL> T, E, H;
	LL Z, as[100005], S[100005], ST, SE;
	int A[100005];
	void main() {
		rop(i, 1, n) {
			scanf("%d%d%d", &u, &v, &w);
			S[i] = w;
			Z += w + w;
		}
		sort(S + 1, S + n);
		reverse(S + 1, S + n);
		int y = (n - 1) / 2;
		rep(i, 1, y) E.insert(S[2 * i - 1] + S[2 * i]);
		if(2 * y < n - 1) E.insert(S[n - 1]);
		rep(i, 1, m) scanf("%d", &A[i]);
		rep(i, 1, m) {
			T.insert(A[i]); ST += A[i];
			H.insert(*--T.end()); ST -= *--T.end();
			T.erase(--T.end());
			while(E.size() && H.size()) {
				if(*H.begin() < *--E.end()) {
					T.insert(*H.begin()); ST += *H.begin();
					H.erase(H.begin()); SE -= *--E.end();
					E.erase(--E.end());
				} else break;
			}
			as[i] = ST + SE;
		}
		rep(i, 0, m) cout << as[i] + Z << " ";
	}
}
int main() {
	freopen("love.in", "r", stdin);
	freopen("love.out", "w", stdout);
	scanf("%d%d", &n, &m);
	if(n <= 3000) n2 :: main();
	else if(m <= 2) n1 :: main();
	else n3 :: main();
	return 0;
}
