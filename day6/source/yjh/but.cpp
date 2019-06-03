#include <cstdio>
#include <algorithm>
#define maxn 55

int n;

struct node {
	int x, y, w;
	bool operator< (const node& a) const {
		return w < a.w;
	}
}e[maxn];

int main() {
	freopen("but.in", "r", stdin);
	freopen("but.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
	// for(int i = 3; i <= n; ++i) work(i);
	std::sort(e+1, e+n+1);
	long long sum = e[1].w + e[2].w;
	for(int i = 3; i <= n; ++i) {
		sum += e[i].w;
		printf("%lld ", sum);
	}
	return 0;
}
