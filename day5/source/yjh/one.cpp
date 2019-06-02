#include <cstdio>
#include <algorithm>
#define M 1000000007

inline int ksm(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y&1) ans = 1ll*ans*x%M;
		x = 1ll*x*x%M;
	}
	return ans;
}

inline int inv(int x) {
	return ksm(x, M-2);
}

int n;
int a[25];
int ch[10005][6], tots = 1;
int sz[10005];
int dvis[25];

void dfs(int x, int stp) {
	if(stp == n) {
		sz[x] = 1;
		return;
	}
	sz[x] = 0;
	for(int i = 1; i <= n; ++i)
		if(!dvis[i]) {
			ch[x][i] = ++tots;
			dvis[i] = 1;
			dfs(ch[x][i], stp+1);
			dvis[i] = 0;
			sz[x] += sz[ch[x][i]];
		}
}

int getrk(int* a) {
	int now = 1, ans = 1;
	for(int i = 1; i < n; ++i) {
		for(int j = 1; j < a[i]; ++j)
			ans += sz[ch[now][j]];
		now = ch[now][a[i]];
	}
	return ans;
}

int f[125][125];
int g[25];

int main() {
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	if(n == 1) {
		printf("0");
		return 0;
	}
	else if(n == 2) {
		if(a[0] == 1) printf("0");
		else printf("1");
		return 0;
	}
	dfs(1, 1);
	int mx = 1;
	for(int i = 1; i <= n; ++i) g[i] = i, mx *= i;
	f[1][1] = 1, f[1][mx+1] = 0;
	int invn = inv((1ll*n*(n-1)/2)%M);
	for(int i = 2; std::next_permutation(g+1, g+n+1); ++i) {
		f[i][i] = 1, f[i][mx+1] = 1;
		for(int p = 1; p < n; ++p)
			for(int q = p+1; q <= n; ++q) {
				std::swap(g[p], g[q]);
				int l = getrk(g);
				f[i][l] = 1ll*(M-1)*invn%M;
				std::swap(g[p], g[q]);
			}
	}
	for(int i = 1; i <= mx; ++i) {
		int div = inv(f[i][i]);
		for(int j = i; j <= mx+1; ++j)
			f[i][j] = 1ll*f[i][j]*div%M;
		for(int j = 1; j <= mx; ++j)
			if(i != j) {
				div = f[j][i];
				for(int k = i; k <= mx+1; ++k)
					f[j][k] = (f[j][k]-1ll*f[i][k]*div%M+M)%M;
			}
	}
	int l = getrk(a);
	printf("%d", f[l][mx+1]);
	return 0;
}
