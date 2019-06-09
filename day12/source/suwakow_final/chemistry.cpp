#include <set>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
using namespace std;
const int N = 310000;

int n, k, m, fr[N], to[N], stck[N], a[N];
set<int> pos[N];

inline int lowbit(int x) {
	return x & -x;
}

int solve(int opt, int k) {
//	assert(k);
	if (pos[k].size()) {
		if (opt == 1)
			return *(pos[k].begin());
		else
			return *(--pos[k].end());
	}
	int l, r;
	if (k == lowbit(k)) {
		l = solve(opt, k >> 1), pos[k >> 1].erase(l);
		r = solve(opt, k >> 1), pos[k >> 1].erase(r);
		fr[++m] = r, to[m] = l;
		pos[k].insert(l);
		return l;
	}
	if (k & 1) {
		l = solve(opt, k + 1), pos[k + 1].erase(l);
		r = solve(opt, 1), pos[1].erase(r);
		fr[++m] = l, to[m] = r;
		pos[k].insert(l), pos[2].insert(r);
		return l;
	}
	int x = k, y = 1, w = k, ind = 0;
	while (w != lowbit(w)) w -= lowbit(w);
	while (x != w && y != w) {
		if (x & 1)
			x += (y >> 1), y >>= 1, stck[++ind] = 1;
		else
			y += (x >> 1), x >>= 1, stck[++ind] = 0;
	}
	l = solve(opt, x), pos[x].erase(l);
	r = solve(0, y), pos[y].erase(r);
	while (ind)
		fr[++m] = stck[ind] ? l : r, to[m] = stck[ind--] ? r : l;
	pos[k].insert(l), pos[1].insert(r);
	return l;
}

int main() {
	freopen("chemistry.in", "r", stdin);
	freopen("chemistry.out", "w", stdout);
	cin >> n >> k;
	if (k != lowbit(k) && n < k + (k & 1) + 1)
		return printf("-1"), 0;
	for (R int i = 1; i <= n; ++i)
		pos[1].insert(i);
	solve(1, k);
	/*assert(m <= 3 * n);
	for (R int i = 1; i <= n; ++i)
		a[i] = 1;
	for (R int i = 1; i <= m; ++i) {
		assert(a[fr[i]] >= a[to[i]]);
		a[fr[i]] -= a[to[i]], a[to[i]] <<= 1;
	}
	assert(a[1] == k);*/
	printf("%d\n", m);
	for (R int i = 1; i <= m; ++i)
		printf("%d %d\n", fr[i], to[i]);
	return 0;
}
