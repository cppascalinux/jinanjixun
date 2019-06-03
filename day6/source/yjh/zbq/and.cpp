
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 11
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
const int mod = 1000000007;
void add(int &x, int y) {
	x += y;
	x -= x >= mod ? mod : 0;
}
int mul(int a, int b) {
	return 1ll * a * b % mod;
}

int f[31][1 << 9][1 << 9];
int b[M], note[31][M], n, m, c[M];

int work1(int step, int now, int get) {
	int x = 0;
	for(int i = 0; i < (n - 1); i++) {
		if(now & (1 << i)) {
			x |= (1 << i);
		} else {
			if(c[i] && c[i + 1]) {
				int p = get & (1 << i), q = get & (1 << (i + 1));
				if(p && !q) return -1;
				if(!p && q) x |= (1 << i);
			} else if(!c[i] && c[i + 1]) {
				if(get & (1 << (i + 1))) {
					x |= (1 << i);
				}
			} else if(c[i] && !c[i + 1]) {
				if(get & (1 << i)) return -1;
			}
		}
	}
	return x;
}
int work2(int step, int now, int get) {
	int x = 0;
	for(int i = 0; i < (n - 1); i++) {
		if(now & (1 << i)) {
			x |= (1 << i);
		} else {
			if(c[i] && c[i + 1]) {

			} else if(!c[i] && c[i + 1]) {
				if(!(get & (1 << i))) return -1;
			} else if(c[i] && !c[i + 1]) {
				if(!(get & (1 << (i + 1)))) x |= (1 << i);
			} else {
				int p = get & (1 << i), q = get & (1 << (i + 1));
				if(p && !q) x |= (1 << i);
				if(!p && q) return -1;
			}
		}
	}
	return x;
}
int cor[M];

void dfs(int to, int step, int up, int v, int bei, int x, int y) {
	if(step == n - 1) {
		add(f[to][x][y], mul(v, (1 << bei)));
		return;
	}
	int p = (x & (1 << step)), q = (y & (1 <<step));
	if(step == 0) {
		if(up & 1) {
			cor[step + 1] = 1;
			dfs(to, step + 1, up, v, bei + 1, x | 1, y | 1);
			cor[step + 1] = 0;
			dfs(to, step + 1, up, v, bei + 1, x | 1, y | 1);
		} else {

		}
	} else {
		if(1);
		if(cor[step] == 0) {
			if(up & (1 << step)) {
				cor[step + 1] = 1;
				
				cor[step + 1] = 0;
			} else {
			
			}
		} else {
			if(up & (1 << step)) {

			} else {
			
			}
		}
	}
}

int main() {
	freopen("and.in", "r", stdin); freopen("and.out", "w", stdout);
	n = read(), m = read();
	f[m][0][0] = 1;
	for(int i = 0; i < n; i++) b[i] = read();

	for(int now = m; now >= 1; now--) {
		for(int i = 0; i < n; i++) c[i] = b[i] & (1 << (now - 1));
		for(int i = 0; i < (1 << (n - 1) ); i++) {
			for(int j = 0; j < (1 << (n - 1) ); j++) {
				if(!f[now][i][j]) continue;
				int x = (i & j);
			//	dfs(now - 1, 0, x, f[now][i][j], 1, i, j);
				for(int get = 0; get < (1 << n); get++) {
					int x = work1(now, i, get), y = work2(now, j, get);
					if(x == -1 || y == -1) continue;
					add(f[now - 1][x][y], f[now][i][j]);
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < (1 << (n - 1) ); i++) {
		for(int j = 0; j < (1 << (n - 1) ); j++) {
			add(ans, f[0][i][j]);
			//	cerr << f[0][i][j] << " " << i << " " << j << "\n";
		}
	}
	cout << ans << "\n";
	return 0;
}

/*
5 1
0 0 1 1 1

2 1
0 1

2 2
0 1


8 30
123456789
998244353
991608907
177744201
19491001
20190603
23333333
100000007


*/
