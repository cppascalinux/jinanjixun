
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 1000100
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n, m;
struct T {
#define ls now << 1
#define rs now << 1 | 1
#define lson l, mid, now << 1
#define rson mid + 1, r, now << 1 | 1
	int sum[M << 2], len[M << 2], laz[M << 2];
	void add(int now, int v) {
		laz[now] = v;
		sum[now] = v * len[now];
	}

	void pushdown(int now) {
		if(laz[now] == 2) return;
		add(ls, laz[now]);
		add(rs, laz[now]);
		laz[now] = 2;
	}
	void pushup(int now) {
		sum[now] = sum[ls] + sum[rs];
	}

	void build(int l, int r, int now) {
		len[now] = r - l + 1;
		laz[now] = 2;
		if(l == r) {
			sum[now] = read();
			return;
		}
		int mid = (l + r) >> 1;
		build(lson), build(rson);
		pushup(now);
	}

	int query(int l, int r, int now, int ln, int rn) {
		if(l > rn || r < ln) return 0;
		if(l >= ln && r <= rn) return sum[now];
		pushdown(now);
		int mid = (l + r) >> 1;
		return query(lson, ln, rn) + query(rson, ln, rn);
	}
	void modify(int l, int r, int now, int ln, int rn, int v) {
		if(l > rn || r < ln) return;
		if(l >= ln && r <= rn) {
			add(now, v);
			return;
		}
		pushdown(now);
		int mid = (l + r) >> 1;
		modify(lson, ln, rn, v);
		modify(rson, ln, rn, v);
		pushup(now);
	}




} t;
int a[M];
int main() {
	freopen("plasticmem.in", "r", stdin); freopen("plasticmem.out", "w", stdout);
//	freopen("sample1.in","r", stdin);
//	freopen("sample.out", "w", stdout);
	n = read(), m = read();
	if(n <= 1000) {
		for(int i = 1; i <= n; i++) a[i] = read();
		while(m--) {
			int op = read(), l = read(), r = read();
			if(op == 1) {
				for(int i = l; i <= r; i++) a[i] = 0;
			} else if(op == 2) {
				for(int i = l; i <= r; i++) a[i] = 1;
			} else if(op == 3) {
				for(int i = l; i < r; i++) {
					if(a[i] == 1 || a[i + 1] == 1) a[i] = 1;
					else a[i] = 0;
				}
			} else if(op == 4) {
				for(int i = r; i > l; i--) {
					if(a[i] == 1 || a[i - 1] == 1) a[i] = 1;
					else a[i] = 0;
				}
			} else if(op == 5) {
				for(int i = l; i < r; i++) {
					if(a[i] == 1 && a[i + 1] == 1) a[i] = 1;
					else a[i] = 0;
				}
			} else if(op == 6) {
				for(int i = r; i > l; i--) {
					if(a[i] == 1 && a[i - 1] == 1) a[i] = 1;
					else a[i] = 0;
				}
			} else {
				int ans = 0;
				for(int i = l; i <= r; i++) ans += a[i];
				cout << ans << "\n";
			}
		}
	} else {
		t.build(1, n, 1);
		while(m--) {
			int op = read(), l = read(), r = read();
			if(op == 1) {
				t.modify(1, n, 1, l, r, 0);
			} else if(op == 2) {
				t.modify(1, n, 1, l, r, 1);
			} else if(op == 3) {

			} else if(op == 4) {

			} else if(op == 5) {

			} else if(op == 6) {

			} else cout << t.query(1, n, 1, l, r) << "\n";
		}
	}
	return 0;
}


