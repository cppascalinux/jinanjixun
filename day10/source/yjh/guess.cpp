#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1005

int n;
char s[maxn];
int a[maxn];
int f[maxn][maxn];

int main() {
	freopen("guess.in", "r", stdin);
	freopen("guess.out", "w", stdout);
	scanf("%s", s+1);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i) a[i] = s[i] - '0';
	++n;
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; ++i) f[i][i] = 0;
	for(int l = n-1; l; --l)
		for(int r = l+1; r <= n; ++r)
			for(int k = l; k < r; ++k)
				f[l][r] = std::min(f[l][r], std::max(f[l][k], f[k+1][r])+a[k]);
	printf("%d", f[1][n]);
	return 0;
}
