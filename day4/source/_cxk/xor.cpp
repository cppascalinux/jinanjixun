#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#define maxn 100010
#define ll long long
#define cn const node
#define pb push_back
using namespace std;

map<int, int> ma;

map<int, int>::iterator it; 

int m, n;

const int N = 30; 
struct Lb {
	int a[31]; 
	
	void insert(int x) {
		for (int i = N; ~i; --i) {
			if (!(x >> i & 1)) continue ; 
			if (a[i]) { x ^= a[i]; continue ; } 
			for (int j = 0; j < i; ++j) if (x >> j & 1) x ^= a[j]; 
			for (int j = i + 1; j <= N; ++j) if (a[j] >> i & 1) a[j] ^= x; 
			a[i] = x; break;
		}
	}	
} a;

#define lc i << 1
#define rc i << 1 | 1
vector<int> T[maxn * 4];
void update(int i, int l, int r, int L, int R, int v) {
	if (l > R || r < L) return ; 
	if (L <= l && r <= R) return T[i].pb(v);
	int m = l + r >> 1; 
	update(lc, l, m, L, R, v); update(rc, m + 1, r, L, R, v);
}

void solve(int i, int l, int r, Lb &a) {
	Lb b; for (int j = 0; j < T[i].size(); ++j) a.insert(T[i][j]); b = a; 
	if (l == r) {
		int s = 0; 
		for (int i = 0; i <= N; ++i) s += (a.a[i] > 0);
		printf("%d\n", (1 << s)); return ; 
	}  int m = l + r >> 1; 
	solve(lc, l, m, a); solve(rc, m + 1, r, b); 
}

int main() {
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%d%d", &m, &n); 
	for (int i = 1; i <= n; ++i) {
		int opt, x; scanf("%d%d", &opt, &x); 
		if (opt == 1) ma[x] = i; 
		else update(1, 1, n, ma[x], i - 1, x), ma[x] = 0; 
	}
	for (it = ma.begin(); it != ma.end(); ++it) 
		if (it -> second) update(1, 1, n, it -> second, n, it -> first);
	solve(1, 1, n, a); 
	return 0;
}
