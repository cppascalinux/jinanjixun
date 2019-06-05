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
int as[300005][11];
struct segment_tree {
#define lo (nw << 1)
#define ro (nw << 1 | 1)
#define md ((l + r) >> 1)
	int sz[5000005], ll[5000005], rl[5000005], lx[5000005][11], vl[5000005];
	void upd(int nw) {
		rep(i, 1, 10) lx[nw][i] = lx[lo][i] + lx[ro][i];
		ll[nw] = ll[lo] + (ll[lo] == sz[lo] ? ll[ro] : 0);
		rl[nw] = rl[ro] + (rl[ro] == sz[ro] ? rl[lo] : 0);
		if(rl[lo] >= 1 && rl[lo] <= 10) lx[nw][rl[lo]]--;
		if(ll[ro] >= 1 && ll[ro] <= 10) lx[nw][ll[ro]]--;
		if(ll[ro] + rl[lo] <= 10 && ll[ro] + rl[lo] >= 1) lx[nw][ll[ro] + rl[lo]]++;
	}
	void build(int nw, int l, int r) {
		if(l == r) {
			sz[nw] = 1;
			return;
		}
		build(lo, l, md);
		build(ro, md + 1, r);
		sz[nw] = sz[lo] + sz[ro];
	}
	void change(int nw, int l, int r, int x, int z) {
		if(l == r) {
			vl[nw] += z;
			ll[nw] = rl[nw] = lx[nw][1] = vl[nw] ? 1 : 0;
			return;
		}
		if(x <= md) change(lo, l, md, x, z);
		else change(ro, md + 1, r, x, z);
		upd(nw);
	}
	int query(int x) {
		rep(i, 1, 10) as[x][i] = lx[1][i];
	}
}ST;
struct ques {
	int l, r, id, bl;
}q[300005];
bool operator < (const ques &a, const ques &b) {
	if(a.bl != b.bl) return a.bl < b.bl;
	return (a.bl & 1) ? a.r > b.r : a.r < b.r;
}
int mx, n, m, a[300005];
int main() {
	freopen("shinku.in", "r", stdin);
	freopen("shinku.out", "w", stdout);
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d", &a[i]), mx = max(mx, a[i]);
	int sqrn = sqrt(n);
	rep(i, 1, m) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i, q[i].bl = q[i].l / sqrn;
	sort(q + 1, q + 1 + m);
	int L = 1, R = 1;
	ST.build(1, 1, mx);
	ST.change(1, 1, mx, a[1], 1);
	rep(i, 1, m) {
		while(L > q[i].l) ST.change(1, 1, mx, a[--L], 1);
		while(R < q[i].r) ST.change(1, 1, mx, a[++R], 1);
		while(L < q[i].l) ST.change(1, 1, mx, a[L++], -1);
		while(R > q[i].r) ST.change(1, 1, mx, a[R--], -1);
		ST.query(q[i].id);
	}
	rep(i, 1, m) {rep(j, 1, 10) printf("%d", as[i][j] % 10); puts("");}
	return 0;
}
