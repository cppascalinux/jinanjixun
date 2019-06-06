
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<ctime>
#include<cmath>
#define ll long long
#define M 21
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
const int mod = 100000007;
inline bool add(int &x, int y) {
//	x = (x + y) % mod;
	x += y;
	x = x >= mod ? x - mod : x;
	return true;
}
int a[M][M], b[M][M], n, m;
int c[5][M][M];
int f[2][1 << 20];
int main() {
//	int tim = clock();
	freopen("scumwish.in", "r", stdin); freopen("scumwish.out", "w", stdout);
//	freopen("sample6.in","r", stdin);
	// freopen("sample.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < m; j++) {
			a[i][j] = read();
		}
	}
	for(int i = 1; i < n; i++) {
		for(int j = 1; j <= m; j++) {
			b[i][j] = read();
		}
	}
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(b[i - 1][j]) c[1][i][j] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 2; j <= m; j++) {
			if(a[i][j - 1]) c[2][i][j] = 1;
		}
	}
	for(int i = 2; i <= n; i++) {
		for(int j = 1; j < m; j++) {
			if(b[i - 1][j] && a[i - 1][j]) c[3][i][j] = 1;
		}
	}
	for(int i = 2; i <= n; i++) {
		for(int j = 2; j <= m; j++) {
			if(b[i - 1][j] && a[i][j - 1]) c[4][i][j] = 1;
		}
	}
	int now = 1, last = 0;
	const int m1 = 1 << (m - 1), m2 = 1 << (m - 2);
	f[now][(1 << m) - 1] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			swap(now, last);
			for(int s = 0; s < (1 << m); s++) {
				c[1][i][j] && add(f[now][(s >> 1) | m1], f[last][s]);
				c[3][i][j] && !(s & 2) && add(f[now][(s >> 1) | m1 | 1], f[last][s]);
				c[4][i][j] && !(s & (1 << (m - 1)))	&& add(f[now][(s >> 1) | m1 | m2], f[last][s]);
				s++;
				add(f[now][s >> 1], f[last][s]);
				add(f[now][(s >> 1) | m1], f[last][s]);
				if(s & m1) {
					f[last][s] = f[last][s ^ 1] = 0;
					continue;
				}
				c[2][i][j] && add(f[now][(s >> 1) | m1 | m2], f[last][s]);
				f[last][s] = f[last][s ^ 1] = 0;
			}
		}
	}
	cout << f[now][(1 << m) - 1] << "\n";
//	cerr << clock() - tim << "ms\n";
	return 0;
}


