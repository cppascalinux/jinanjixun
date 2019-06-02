#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <ctime>
#include <set>
#define maxn 21
#define maxm 630
#define ll long long
#define pb push_back
using namespace std;

const int p = 1000000007;

ll pow_mod(ll x, ll n) {
	ll s = 1; 
	for (; n; n >>= 1) {
		if (n & 1) s = s * x % p; 
		x = x * x % p; 
	} return s; 
}

int n, st;

map<vector<int>, int> id; 
vector<int> Id[700]; int c1; 

bool vis[maxn]; int cnt[maxn]; vector<int> v; 
int work(int *a) {
	memset(vis, 0, sizeof vis); v.clear(); memset(cnt, 0, sizeof cnt); 
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue ; 
		int x = i, s = 0; 
		do {
			vis[x] = 1; 
			x = a[x]; ++s; 
		} while (x != i); ++cnt[s]; 
	}
	for (int i = 1; i <= n; ++i) v.pb(cnt[i]); 
	if (!id.count(v)) id[v] = ++c1, Id[c1] = v;
	return id[v];
}


ll g[maxm][maxm];
void gauss(int n) {
	for (int i = 1; i <= n; ++i) 
		if (i != st) g[i][n + 1] = 1;  
	for (int i = 1; i <= n; ++i) {
		int l = i; 
		for (int j = i + 1; j <= n; ++j) 
			if (g[j][i]) l = i;
		swap(g[l], g[i]); ll inv = pow_mod(g[i][i], p - 2);
		for (int j = i; j <= n + 1; ++j) g[i][j] = g[i][j] * inv % p; 
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue ; 
			for (int k = i + 1; k <= n + 1; ++k)
				g[j][k] = (g[j][k] - g[j][i] * g[i][k]) % p; 
			g[j][i] = 0; 
		}
	}
}

int a[maxn], sum[maxm]; vector<int> b; ll inv;
void calc() {
	if (!id.count(b)) id[b] = ++c1, Id[c1] = b; 
	int to = 1; 
	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k <= b[i - 1]; ++k) {
			int now = to; 
			for (int j = 1; j < i; ++j) 
				a[now] = now + 1, ++now; 
			a[now] = to; to = now + 1;  
		}
	} 
	if (b[0] == n) return (void) (st = id[b]); memset(sum, 0, sizeof sum); 
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) {
			swap(a[i], a[j]); 
			++sum[work(a)];
			swap(a[i], a[j]);  
		}
	int _id = id[b]; 
	for (int i = 1; i <= c1; ++i) g[_id][i] = -inv * sum[i] % p; 
	g[_id][_id] = 1;  
}

void dfs(int q, int s) {
	if (q == n + 1) {
		if (!s) calc();
		return ; 
	}
	for (int i = 0; i <= s; i += q) {
		b[q - 1] = i / q; 
		dfs(q + 1, s - i); 
	}
}

int A[maxn];
int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	cin >> n; inv = pow_mod(n * (n - 1) / 2, p - 2); 
	b.resize(n); dfs(1, n); gauss(c1); 
	for (int i = 1; i <= n; ++i) cin >> A[i];
	cout << (g[work(A)][c1 + 1] + p) % p << endl;  
	return 0; 
}
