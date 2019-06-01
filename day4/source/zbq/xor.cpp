
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ls now << 1
#define rs now << 1 | 1
#define lson l, mid, now << 1
#define rson mid + 1, r, now << 1 | 1
#include<map>
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
map<int, int> mp;
struct Line {
	int a[30], cnt;
	void insert(int x) {
		for(int i = 29; i >= 0; i--) {
			if(x & (1 << i)) {
				if(a[i] == 0) {
					a[i] = x;
					if(x != 0) cnt++;
					break;
				}
				x = x ^ a[i];
			}
		}
	}
} L[66];
vector<int> to[M << 2];
int sta[M], tp;
int n, q;

void modify(int l, int r, int now, int ln, int rn, int x) {
	if(l > rn || r < ln) return;
	if(l >= ln && r <= rn) {
		to[now].push_back(x);
		return;
	}
	int mid = (l + r) >> 1;
	modify(lson, ln, rn, x);
	modify(rson, ln, rn, x);
}

void dfs(int l, int r, int now, int dep) {
	L[dep] = L[dep - 1];
	for(int i = 0; i < to[now].size(); i++) {
		if(L[dep].cnt == n) break;
		int x = to[now][i];
		L[dep].insert(x);
	}
	if(l == r) {
		cout << (1 << (L[dep].cnt)) << "\n";
		return;
	}
	int mid = (l + r) >> 1;
	dfs(lson, dep + 1);
	dfs(rson, dep + 1);
}

int main() {
	freopen("xor.in", "r", stdin); freopen("xor.out", "w", stdout);
	n = read(), q = read();
	for(int i = 1; i <= q; i++) {
		read();
		int x = read();
		sta[++tp] = x;
		if(mp[x] != 0) {
			modify(1, q, 1, mp[x], i - 1, x);
			mp[x] = 0;
		} else mp[x] = i;
	}
	for(int i = 1; i <= tp; i++) {
		if(mp[sta[i]] != 0) {
			modify(1, q, 1, mp[sta[i]], q, sta[i]);
		}
	}
	dfs(1, q, 1, 1);
	return 0;
}

/*
30 10
1 1
1 2
1 3
1 1
1 4
1 4
1 8
1 16
1 2
1 17


*/

