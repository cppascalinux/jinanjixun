#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#define rep(x, a, b) for(int x = (a); x <= (b); ++x)
#define per(x, a, b) for(int x = (a); x >= (b); --x)
#define rop(x, a, b) for(int x = (a); x < (b); ++x)
using namespace std;
typedef long long LL;
typedef unsigned int ui;
typedef double DB;
map <int, int> wz;
struct xxj {
	int nb[30];
	inline void push(int x) {
		per(i, 29, 0) {
			if(x >> i & 1) {
				if(nb[i] == 0) {nb[i] = x; return;}
				else x ^= nb[i];
			}
		}
	}
	inline int query() {
		int as = 0;
		rep(i, 0, 29) if(nb[i] != 0) ++as;
		return as;
	}
}XJ[105];
struct segment_tree {
	set <int> S[500005];
	void change(int nw, int l, int r, int x, int y, int z) {
		if(l >= x && r <= y) {
			S[nw].insert(z);
			return;
		}
		int md = (l + r) >> 1;
		if(x <= md) change(nw << 1, l, md, x, y, z);
		if(y > md) change(nw << 1 | 1, md + 1, r, x, y, z);
	}
	void query(int nw, int l, int r, int d) {
		set<int> :: iterator IT = S[nw].begin();
		while(IT != S[nw].end()) {
			XJ[d].push(*IT);
			++IT;
		}
		if(l == r) {
			printf("%d\n", (1 << XJ[d].query()));
			return;
		}
		int md = (l + r) >> 1;
		XJ[d + 1] = XJ[d];
		query(nw << 1, l, md, d + 1);
		XJ[d + 1] = XJ[d];
		query(nw << 1 | 1, md + 1, r, d + 1);
	}
}ST;
int m, q, op, x;
int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%d%d", &m, &q);
	rep(i, 1, q) {
		scanf("%d%d", &op, &x);
		if(op == 1) {wz[x] = i;}
		else {
			ST.change(1, 1, q, wz[x], i - 1, x);
			wz[x] = 0;
		}
	}
	map<int, int> :: iterator IT = wz.begin();
	while(IT != wz.end()) {
		if((*IT).second != 0) ST.change(1, 1, q, (*IT).second, q, (*IT).first);
		++IT;
	}
	ST.query(1, 1, q, 1);
}
