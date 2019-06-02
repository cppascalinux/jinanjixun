#include <cstdio>
#include <cstring>
#define maxn 1005

int n, k;
char s[maxn];
int ans;
int vis[maxn][maxn];
int c[maxn];

int main() {
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	scanf("%s%d", s+1, &k);
	n = strlen(s+1);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			if(!vis[i][j]) {
				vis[i][j] = 1;
				for(int p = 1; p <= n; ++p) c[p] = 0;
				for(int p = i; p <= j; ++p) c[p] = 1;
				for(int x = 1; x <= n; ++x)
					if(x != i) {
						int y = x+j-i;
						if(!vis[x][y]) {
							int fl = 1, len = j-i+1;
							for(int p = 0; p < len; ++p)
								if(s[i+p] != s[x+p]) {
									fl = 0; break;
								}
							if(fl) {
								vis[x][y] = 1;
								for(int p = x; p <= y; ++p) c[p] = 1;
							}
						}
					}
				int cnt = 0;
				for(int p = 1; p <= n+1; ++p)
					if(!c[p-1] && c[p]) ++cnt;
				if(cnt == k) ++ans;
			}
	printf("%d", ans);
	return 0;
}
