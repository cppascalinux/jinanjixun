#include <cstdio>
#include <cctype>
inline int gc() {
	char ch = getchar(); while(isspace(ch)) ch = getchar();
	return 'C' - ch;
}

int n, m, k;
int mp[9][9];
int ans;
int qx[105], qy[105], he, ta;
int vis[9][9];

bool check() {
	static const int dr[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	int suma = 0, sumb = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(mp[i][j] == 1) ++suma; else ++sumb;
	if(suma - sumb > k || sumb - suma > k) return 0;
	for(int i = 1; i < n; ++i)
		for(int j = 1; j < n; ++j)
			if(mp[i][j] == mp[i+1][j] && mp[i][j] == mp[i][j+1] && mp[i][j] == mp[i+1][j+1])
				return 0;
	he = ta = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			vis[i][j] = 0;
	qx[ta] = 1, qy[ta] = 1, vis[1][1] = 1;
	while(he <= ta) {
		for(int p = 0; p < 4; ++p) {
			int nx = qx[he] + dr[p][0], ny = qy[he] + dr[p][1];
			if(nx >= 1 && ny >= 1 && nx <= n && ny <= m && !vis[nx][ny] && mp[nx][ny] == mp[1][1])
				vis[nx][ny] = 1, qx[++ta] = nx, qy[ta] = ny;
		}
		++he;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(mp[i][j] == mp[1][1] && !vis[i][j])
				return 0;
	int flf = 1;
	for(int i = 1; i <= n && flf; ++i)
		for(int j = 1; j <= m; ++j)
			if(mp[i][j] != mp[1][1]) {
				flf = 0;
				qx[he = ta = 0] = i, qy[ta] = j, vis[i][j] = 1;
				break;
			}
	while(he <= ta) {
		for(int p = 0; p < 4; ++p) {
			int nx = qx[he] + dr[p][0], ny = qy[he] + dr[p][1];
			if(nx >= 1 && ny >= 1 && nx <= n && ny <= m && !vis[nx][ny] && mp[nx][ny] != mp[1][1])
				vis[nx][ny] = 1, qx[++ta] = nx, qy[ta] = ny;
		}
		++he;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(mp[i][j] != mp[1][1] && !vis[i][j])
				return 0;
	return 1;
}

void dfs(int x, int y) {
	if(x > n) {
		if(check()) ++ans;
		return;
	}
	if(y > m) return dfs(x+1, 1);
	if(mp[x][y]) {
		if(x == 1 || y == 1 || !(mp[x][y] == mp[x-1][y] && mp[x][y] == mp[x][y-1] && mp[x][y] == mp[x-1][y-1])) dfs(x, y+1);
		return;
	}
	if(x == 1 || y == 1 || !(mp[x-1][y] == 1 && mp[x][y-1] == 1 && mp[x-1][y-1] == 1)) mp[x][y] = 1, dfs(x, y+1);
	if(x == 1 || y == 1 || !(mp[x-1][y] == 2 && mp[x][y-1] == 2 && mp[x-1][y-1] == 2)) mp[x][y] = 2, dfs(x, y+1);
	mp[x][y] = 0;
}

int main() {
	freopen("can.in", "r", stdin);
	freopen("can.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			mp[i][j] = gc();
	dfs(1, 1);
	printf("%d", ans);
	return 0;
}
