#include <cstdio>
#include <cctype>
#define M 998244353
#define maxn 65
inline int read() {
	int d=0;char ch=getchar();while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){d=d*10+ch-48,ch=getchar();}return d;
}

inline int ksm(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y&1) ans = 1ll*ans*x%M;
		x = 1ll*x*x%M;
	}
	return ans;
}

inline void mpls(int& x, int y) {
	x += y; if(x >= M) x -= M;
}

int n, m, k, w;
int slt[maxn][maxn][maxn], val[maxn][maxn][maxn];

int check(int a1, int a2, int b1, int b2, int c1, int c2) {
	int sum = 0;
	for(int i = a1; i <= a2; ++i)
		for(int j = b1; j <= b2; ++j)
			for(int h = c1; h <= c2; ++h)
				if(!slt[i][j][h]) return 0;
				else mpls(sum, val[i][j][h]);
	return sum;
}

int main() {
	freopen("dream.in", "r", stdin);
	freopen("dream.out", "w", stdout);
	n = read(), m = read(), k = read(), w = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			for(int h = 1; h <= k; ++h)
				slt[i][j][h] = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			for(int h = 1; h <= k; ++h)
				val[i][j][h] = read();
	int cnt = 0;
	for(int i1 = 1; i1 <= n; ++i1)
		for(int i2 = i1; i2 <= n; ++i2)
			for(int j1 = 1; j1 <= m; ++j1)
				for(int j2 = j1; j2 <= m; ++j2)
					for(int h1 = 1; h1 <= k; ++h1)
						for(int h2 = h1; h2 <= k; ++h2)
							mpls(cnt, check(i1, i2, j1, j2, h1, h2));
	cnt = 8ll*cnt%M*ksm(n, M-2)%M*ksm(n+1, M-2)%M*ksm(m, M-2)%M*ksm(m+1, M-2)%M*ksm(k, M-2)%M*ksm(k+1, M-2)%M;
	printf("%d", cnt);
	return 0;
}
