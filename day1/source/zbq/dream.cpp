#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<iostream>
#define M 62
#define ll long long
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
const int mod = 998244353;
void add(int &x, int y) {
	x += y;
	x -= x >= mod ? mod : 0;
}
int mul(int a, int b) {
	return 1ll * a * b % mod;
}
int poww(int a, int b) {
	int ans = 1, tmp = a;
	for(; b; b >>= 1, tmp = mul(tmp, tmp)) if(b & 1) ans = mul(ans, tmp);
	return ans;
}
int a[M][M][M], v[M][M][M], c[M][M][M], d[M][M][M], n, m, k, w;

int main() {
//	freopen("2.in", "r", stdin);
	//freopen("dream.out", "w", stdout);

	freopen("dream.in", "r", stdin); freopen("dream.out", "w", stdout);
	n = read(), m = read(), k = read(), w = read() % mod;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int l = 1; l <= k; l++)
				a[l][i][j] = read();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int l = 1; l <= k; l++)
				v[l][i][j] = read();
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= n; j++) {
			for(int l = 1; l <= m; l++) {
				c[i][j][l] = c[i][j - 1][l] + c[i][j][l - 1] - c[i][j - 1][l - 1] + (a[i][j][l] == 0);
			}
		}
	}
	int tot = 0, tod = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			for(int l = i; l <= n; l++) {
				for(int e = j; e <= m; e++) {
					int cnt = 0, ln = 0, rn;
					for(int now = 1; now <= k + 1; now++) {
						if(c[now][l][e] - c[now][i - 1][e] - c[now][l][j - 1] + c[now][i - 1][j - 1] == 0 && now <= k) {
							cnt++;
							if(cnt == 1) ln = now;
						} else {
							if(ln == 0) continue;
							add(tod, 1ll * cnt * (cnt + 1) / 2);
							rn = now - 1;
							//	cerr << rn - ln << "&&";
							for(int z = ln; z <= rn; z++) {
								int x = (z - ln + 1) * (rn - z + 1);
								add(d[z][i][j], x);
								add(d[z][i][e + 1], mod - x);
								add(d[z][l + 1][j], mod - x);
								add(d[z][l + 1][e + 1], x);
							}
							ln = 0;
							cnt = 0;
						}
					}
				}
			}
		}
	}
	
	tot = 1ll * n * m * k * (n + 1) * (m + 1) * (k + 1) / 8 % mod;
	int gen = mul(tod, poww(tot, mod - 2));
	int p1 = poww(gen, w);
	int ans = 0;
	for(int now = 1; now <= k; now++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				add(d[now][i][j], d[now][i - 1][j]);
				add(d[now][i][j], d[now][i][j - 1]);
				add(d[now][i][j], mod - d[now][i - 1][j - 1]);
			//	cerr << d[now][i][j] << "!!!";
				if(!a[now][i][j]) continue;
				int other = (tod - d[now][i][j] + mod) % mod;
				other = mul(other, poww(tot, mod - 2));
				other = poww(other, w);
				add(ans, mul(v[now][i][j], (p1 - other + mod) % mod));	
			}
		}
		//	cerr << "\n";
	}
	cout << ans << "\n";
	return 0;
}
/*
1 2 3

2 2 2 5
0 0 
0 0
0 0
0 0



*/
