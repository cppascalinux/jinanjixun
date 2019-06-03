#include <cstdio>
#define M 1000000007

inline void mpls(int& x, int y) {
	x += y; if(x >= M) x -= M;
}

int n, m, mx;
int b[9], g[9][2005];

int main() {
	freopen("and.in", "r", stdin);
	freopen("and.out", "w", stdout);
	scanf("%d%d", &n, &m);
	mx = 1<<m;
	for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
	for(int j = 0; j < mx; ++j) g[1][j] = 1;
	for(int i = 2; i <= n; ++i)
		for(int j = 0; j < mx; ++j)
			for(int k = 0; k < mx; ++k)
				if((j&b[i-1]) <= (k&b[i]) && (j|b[i-1]) >= (k|b[i]))
					mpls(g[i][k], g[i-1][j]);
	int ans = 0;
	for(int j = 0; j < mx; ++j)
		mpls(ans, g[n][j]);
	printf("%d", ans);
	return 0;
}
