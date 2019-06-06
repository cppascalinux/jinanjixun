
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 100100
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n, m, belong[M], biao, tp;
ll tot[M];
pair<int, int> sta[M];
struct Note {
	ll l, r, v;
	bool operator < (const Note &b) const {
		return this->v < b.v;
	}
};
vector<Note> kuai[350];
struct T {
#define ls now << 1
#define rs now << 1 | 1
#define lson l, mid, now << 1
#define rson mid + 1, r, now << 1 | 1
	ll sum[M << 2], len[M << 2], laz[M << 2];
	void add(ll now, ll v) {
		laz[now] += v;
		sum[now] += v * len[now];
	}

	void pushdown(int now) {
		if(!laz[now]) return;
		add(ls, laz[now]);
		add(rs, laz[now]);
		laz[now] = 0;
	}
	void pushup(int now) {
		sum[now] = sum[ls] + sum[rs];
	}

	void build(int l, int r, int now) {
		len[now] = r - l + 1;
		if(l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(lson), build(rson);
		pushup(now);
	}
	void work(ll l, ll r, int now) {
		if(belong[l] == belong[r]) {
			kuai[belong[l]].push_back((Note) {
				l, r, 0ll
			});
		} else {
			sta[++tp] = mmp(l, r);
		}
		if(l == r) return;
		int mid = (l + r) >> 1;
		work(lson), work(rson);
	}

	int query(int l, int r, int now, int ln, int rn, int a) {
		if(l > rn || r < ln) return 0;
		int ans = 0;
		if(l >= ln && r <= rn) ans = (sum[now] <= a);
		if(l == r) return ans;
		pushdown(now);
		int mid = (l + r) >> 1;
		return ans + query(lson, ln, rn, a) + query(rson, ln, rn, a);
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

	ll get(int l, int r, int now, int ln, int rn) {
		if(l > rn || r < ln) return 0;
		if(l >= ln && r <= rn) return sum[now];
		int mid = (l + r) >> 1;
		pushdown(now);
		return get(lson, ln, rn) + get(rson, ln, rn);
	}
} t;

void work(int k, int v) {

}

void modify(int l, int r, int v) {
	work(belong[l], v);
	if(belong[r] != belong[l]) work(belong[r], v);
	for(int i = belong[l] + 1; i < belong[r]; i++) tot[i] += v;
}

int main() {
	freopen("flipflap.in", "r", stdin); freopen("flipflap.out", "w", stdout);
//	freopen("sample4.in","r", stdin);
	// freopen("sample.out", "w", stdout);
	n = read(), m = read();

	t.build(1, n, 1);
	while(m--) {
		int op = read(), l = read(), r = read(), a = read();
		if(op == 1) {
			t.modify(1, n, 1, l, r, a);
		} else cout << t.query(1, n, 1, l, r, a) << "\n";
	}

	return 0;
}


