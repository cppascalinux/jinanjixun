#include <cstdio>
#include <algorithm>
#define maxn 100005
#define M 998244353

int n, k, ans;
int g[maxn], d[maxn];

int main() {
	freopen("fafa.in", "r", stdin);
	freopen("fafa.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) g[i] = i;
	do {
		int mx = 1;
		d[1] = 1;
		for(int i = 2; i <= n; ++i) {
			d[i] = 1;
			for(int j = 1; j < i; ++j) {
				if(d[j]&1) {
					if(g[j] > g[i]) d[i] = d[j]+1;
				}
				else {
					if(g[j] < g[i]) d[i] = d[j]+1;
				}
			}
			mx = std::max(mx, d[i]);
		}
		if(mx == k) ++ans;
	}while(std::next_permutation(g+1, g+n+1));
	printf("%d", ans%M);
	return 0;
}
