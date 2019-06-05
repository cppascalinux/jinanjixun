
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 100010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int a[M], n, m;
struct T {
#define ls now << 1
#define rs now << 1 | 1

#define lson l, mid, now << 1

#define rson mid + 1, r, now << 1 | 1
	int t[M << 2], laz[M << 2], len[M << 2];
	void add(int now, int v) {
		laz[now] ^= v;
		t[now] ^= v * (len[now] & 1);
		//	cerr << (len[now] & 1);
	}
	void pushdown(int now) {
		add(ls, laz[now]);
		add(rs, laz[now]);
		laz[now] = 0;
	}
	void build(int l, int r, int now) {
		len[now] = r - l + 1;
		if(l == r) {
			t[now] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(lson), build(rson);
		t[now] = t[ls] ^ t[rs];
	}
	void modify(int l, int r, int now, int ln, int rn, int v) {
		if(l > rn || r < ln) return;
		if(l >= ln && r <= rn) {
			add(now, v);
			return;
		}
		pushdown(now);
		int mid = (l + r) >> 1;
		modify(lson, ln, rn, v), modify(rson, ln, rn, v);
		t[now] = t[ls] ^ t[rs];
	}

	int query(int l, int r, int now, int ln, int rn) {
		if(l > rn || r < ln) return 0;
		if(l >= ln && r <= rn) return t[now];
		pushdown(now);
		int mid = (l + r) >> 1;
		return query(lson, ln, rn) ^ query(rson, ln, rn);
	}
} t;
int a1[M], a2[M], a3[M];

void work(int l, int r) {
	sort(a + l, a + r + 1);
}

int main() {
//	freopen("3.in", "r", stdin);
	freopen("save.in", "r", stdin); freopen("save.out", "w", stdout);

	n = read(), m = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	if(n <= 10000) {
		while(m--) {
			int op = read(), l = read(), r = read(), x;
			if(op == 1) {
				x = read();
				for(int i = l; i <= r; i++) a[i] ^= x;
			} else if(op == 2) {
				work(l, r);
			} else {
				int ans = 0;
				for(int i = l; i <= r; i++) ans ^= a[i];
				cout << ans << "\n";
			}
		}
	} else {
		t.build(1, n, 1);
		while(m--) {
			int op = read(), l = read(), r = read(), x;
			if(op == 1) {
				x = read();
				t.modify(1, n, 1, l, r, x);
			} else if(op == 2) {
			} else {
				cout << t.query(1, n, 1, l, r) << "\n";
			}
		}
	}
	return 0;
}


