#include <iostream>
#include <cstdio>
#include <cstring>
#define maxn 9
#define maxm 30
using namespace std;

const int p = 1000000007;

inline int add(int a, int b) { return a + b >= p ? a + b - p : a + b; } 

int n, m, M;

int a[maxn];

int b[1 << 8], c[1 << 8]; 

int f[maxm][1 << 14]; 
int dfs(int pos, int st) {
	if (pos == -1) return 1; 
	if (~f[pos][st]) return f[pos][st]; f[pos][st] = 0; 
	for (int ST = 0; ST < M; ++ST) {
		bool F = 1; int St = st; 
		for (int i = 1; i <= n; ++i) {
			int s = ST >> i - 1 & 1;  
			b[i] = a[i] >> pos & s; 
			c[i] = (a[i] >> pos & 1) | s;    
		}
		for (int j = 1; j <= n - 1; ++j) {
			int s = st >> j - 1 & 1; 
			if (s && b[j] < b[j + 1]) St ^= 1 << j - 1;  
			if (s && b[j] > b[j + 1]) F = 0;    
		} 
		for (int j = n; j <= 2 * n - 2; ++j) {
			int k = j - n + 1, s = st >> j - 1 & 1;  
			if (s && c[k] > c[k + 1]) St ^= 1 << j - 1; 
			if (s && c[k] < c[k + 1]) F = 0;
		}
		if (F) f[pos][st] = add(f[pos][st], dfs(pos - 1, St));  
	} return f[pos][st]; 
}

int main() { memset(f, -1, sizeof f); 
	freopen("and.in", "r", stdin); 
	freopen("and.out", "w", stdout);
	cin >> n >> m; M = 1 << n; 
	for (int i = 1; i <= n; ++i) cin >> a[i];
	cout << dfs(m - 1, (1 << 2 * n - 2) - 1);  
	return 0; 
}
