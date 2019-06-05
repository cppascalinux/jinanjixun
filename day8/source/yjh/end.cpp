#include <cstdio>
#include <cctype>
#define M 1000000007
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*2+ch-48,ch=getchar();}return d;
}

inline void mpls(int& x, int y) {
	x += y; if(x >= M) x -= M;
}

int n, K, m;
int f[9][1105][1105];
int sum[1105];

int main() {
	freopen("end.in", "r", stdin);
	freopen("end.out", "w", stdout);
	scanf("%d%d", &n, &K);
	m = read();
	for(int i = 0; i < m; ++i)
		f[1][i][i] = 1;
	for(int i = 2; i <= n; ++i)
		for(int k = 0; k < 1024; ++k) {
			sum[0] = f[i-1][k][0];
			for(int j = 1; j < m; ++j) sum[j] = sum[j-1], mpls(sum[j], f[i-1][k][j]);
			for(int j = 1; j < m; ++j) mpls(f[i][k^j][j], sum[j-1]);
		}
	int ans = 0;
	for(int j = 0; j < m; ++j) mpls(ans, f[n][0][j]);
	printf("%d", ans);
	return 0;
}
