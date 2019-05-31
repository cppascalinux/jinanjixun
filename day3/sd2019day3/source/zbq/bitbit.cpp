
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M  505
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int a[M][M], n, m;
int cor[M][M], cnt, cod[M][M], cnd;
const int xx[4] = {0, 0, 1, -1}, yy[4] = {1, -1, 0, 0};


void dfs(int x, int y) {
	if(cor[x][y]) return;
	cor[x][y] = cnt;
	for(int i = 0; i < 4; i++) {
		int xxx = x + xx[i], yyy = y + yy[i];
		if(xxx > n || yyy > m || xxx < 1 || yyy < 1 || a[xxx][yyy] == 0) continue;
		dfs(xxx, yyy);
	}
}

void dfd(int x, int y) {
	if(cod[x][y]) return;
	cod[x][y] = cnd;
	for(int i = 0; i < 4; i++) {
		int xxx = x + xx[i], yyy = y + yy[i];
		if(xxx > n || yyy > m || xxx < 1 || yyy < 1 || a[xxx][yyy] == 1) continue;
		dfd(xxx, yyy);
	}
}
int note[M][M];
bool vis[M][M];

void dfss(int x, int y) {
	if(vis[x][y]) return;
	vis[x][y] = true;
	for(int i = 0; i < 4; i++) {
		int xxx = x + xx[i], yyy = y + yy[i];
		if(xxx > n || yyy > m || xxx < 1 || yyy < 1 || note[xxx][yyy] == 0) continue;
		dfss(xxx, yyy);
	}
}

bool work(int c) {

	memset(note, 0, sizeof(note));
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] || cod[i][j] == c) note[i][j] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(note[i][j]) {
				dfss(i, j);
				for(int k = 1; k <= n; k++) {
					for(int l = 1; l <= m; l++) {
						if(note[k][l] && !vis[k][l]) return false;
					}
				}
				return true;
			}
		}
	}
}

void work1() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 1 && !cor[i][j]) {
				cnt++;
				dfs(i, j);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 0 && !cod[i][j]) {
				cnd++;
				dfd(i, j);
			}
		}
	}
	if(cnt <= 2) {
		cout << cnt << "\n";
		for(int c = 1; c <= cnt; c++) {
			puts("+");
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(cor[i][j] == c) cout << "1";
					else cout << "0";
				}
				cout << "\n";
			}
		}
		return;
	}
	if(cnd == 1) {
		cout << "2\n";
		puts("+");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cout << "1";
			}
			cout << "\n";
		}
		for(int c = 1; c <= cnd; c++) {
			puts("-");
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(cod[i][j] == c) cout << "1";
					else cout << "0";
				}
				cout << "\n";
			}
		}
		return;
	}
	if(cnt == 5) {
		cout << "3\n";
		puts("+");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cout << "1";
			}
			cout << "\n";
		}
		puts("-");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if((i != 1 && i != n) || (j != 1 && j != m)) cout << "1";
				else cout << "0";
			}
			cout << "\n";
		}
		puts("+");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(i == 2 && j == 2) cout << "1";
				else cout << "0";
			}
			cout << "\n";
		}
		return;
	}
	for(int c = 1; c <= cnd; c++) {
		if(work(c)) {
			cout << "2\n";
			puts("+");
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(a[i][j] || cod[i][j] == c) cout << "1";
					else cout << "0";
				}
				cout << "\n";
			}
			puts("-");
			for(int i = 1; i <= n; i++) {
				for(int j = 1; j <= m; j++) {
					if(cod[i][j] == c) cout << "1";
					else cout << "0";
				}
				cout << "\n";
			}
			return;
		}
	}
	cout << "3\n";
	puts("+");
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] || cod[i][j] == 1 || cod[i][j] == 2) cout << "1";
			else cout << "0";
		}
		cout << "\n";
	}
	puts("-");
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(cod[i][j] == 1)  cout << "1";
			else cout << "0";
		}
		cout << "\n";
	}
	puts("-");
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(cod[i][j] == 2) cout << "1";
			else cout << "0";
		}
		cout << "\n";
	}

}


void work2() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i][j] == 1 && !cor[i][j]) {
				cnt++;
				dfs(i, j);
			}
		}
	}
	cout << cnt << "\n";
	for(int c = 1; c <= cnt; c++) {
		puts("+");
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(cor[i][j] == c) cout << "1";
				else cout << "0";
			}
			cout << "\n";
		}
	}
}
char s[M];
int main() {
	freopen("bitbit.in", "r", stdin); freopen("bitbit.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++) {
			a[i][j] = (s[j] == '1');
		}
	}
	if(n <= 3 && m <= 3) work1();
	else if(n == 1) work2();
	else
	{
		
	}
	return 0;
}



