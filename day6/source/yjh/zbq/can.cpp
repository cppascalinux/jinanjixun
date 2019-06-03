
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M  9
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n, m, k, ans;
char s[M][M], zz[M][M];

bool fk() {
	for(int i = 2; i <= n; i++) {
		for(int j = 2; j <= m; j++) {
			if(zz[i][j] == '?') return true;
			if((zz[i][j] == zz[i - 1][j]) && (zz[i][j] == zz[i - 1][j - 1]) && (zz[i][j] == zz[i][j - 1])) return false;
		}
	}
	return true;
}
ll vis[M][M], cor;
const int xx[4] = {0, 0, 1, -1}, yy[4] = {-1, 1, 0, 0};

void dfss(int i, int j, int v) {
	vis[i][j] = v;
	for(int now = 0; now < 4; now++) {
		int x = i + xx[now], y = j + yy[now];
		if(x < 1 || y < 1 || x > n || y > m || (zz[x][y] != zz[i][j]) || vis[x][y] == v) continue;
		dfss(x, y, v);
	}
}

int work() {
	cor++;
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(zz[i][j] == '?')	return tot;
			if(vis[i][j] == cor) continue;
			dfss(i, j, cor);
			tot++;
		}
	}
	return tot;
}

int ab(int x) {
	return x > 0 ? x : -x;
}

int check() {
	if(!fk()) return 0;
	int zd = work();
	if(zd > 2) return 0;
	return 1;
}

void dfs(int h, int l, int cha, int tot) {
	if(h > n) {
		if(cha > k || cha < -k) return;
		ans += check();
		return;
	}

	if(l > m) {
		dfs(h + 1, 1, cha, tot);
		return;
	}
	if(!fk()) return;
	int zd = work();
	if(zd > tot + 2) {
		//cerr << "!";
		return;
	}
	if(ab(cha) - k > tot) return;
	if(s[h][l] == 'A') {
		zz[h][l] = 'A';
		dfs(h, l + 1, cha + 1, tot - 1);
	} else if(s[h][l] == 'B') {
		zz[h][l] = 'B';
		dfs(h, l + 1, cha - 1, tot - 1);
	} else {
		zz[h][l] = 'A';
		dfs(h, l + 1, cha + 1, tot - 1);
		zz[h][l] = 'B';
		dfs(h, l + 1, cha - 1, tot - 1);
	}
	zz[h][l] = '?';
}

int main() {
	freopen("can.in", "r", stdin); freopen("can.out", "w", stdout);
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) zz[i][j] = '?';
	dfs(1, 1, 0, n * m);
	cout << ans << "\n";
	return 0;
}
/*
2 2 1
CC
CC
8 8 20
5 4 20
CCCC
CCCC
CCCC
CCCC
CCCC

4 5 20
CCCCC
CCCCC
CCCCC
CCCCC
5 6 20
CCCCCC
CCCCCC
CCCCCC
CCCCCC
CCCCCC
CCCCCC

8 8 11
AAACCCAC
AAAACCCC
BBAACACC
CCCCCACC
ACCCCAAA
CCCCCCCC
CCCCCCCC
AAAAAAAA
*/

