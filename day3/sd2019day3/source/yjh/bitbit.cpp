#include <cstdio>
#include <cctype>
#define maxn 7
inline int read() {
	int d = 0; char ch = getchar(); while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) {d = d*10+ch-48, ch = getchar();} return d;
}
inline int gc() {
	char ch = getchar(); while(isspace(ch)) ch = getchar();
	return ch == '1';
}

int n, m;

struct mat {
	int a[maxn][maxn];
	void print() {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j)
				printf("%d", a[i][j]);
			puts("");
		}
	}
}e;

mat operator+ (const mat& x, const mat& y) {
	mat c;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			c.a[i][j] = x.a[i][j] + y.a[i][j];
	return c;
}

mat operator- (const mat& x, const mat& y) {
	mat c;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			c.a[i][j] = x.a[i][j] - y.a[i][j];
	return c;
}

bool operator== (const mat& x, const mat& y) {
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(x.a[i][j] != y.a[i][j]) return 0;
	return 1;
}

mat tp;
mat li[1005];
int tots;

bool checki() {
	static const int dr[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	static int qx[25], qy[25];
	static int vis[maxn][maxn];
	int fl = 1, he, ta;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			vis[i][j] = 0;
	for(int i = 1; i <= n && fl; ++i)
		for(int j = 1; j <= m && fl; ++j)
			if(tp.a[i][j]) {
				qx[he = ta = 0] = i;
				qy[ta] = j;
				vis[i][j] = 1, fl = 0;
			}
	while(he <= ta) {
		for(int p = 0; p < 4; ++p) {
			int nx = qx[he] + dr[p][0], ny = qy[he] + dr[p][1];
			if(nx >= 1 && ny >= 1 && nx <= n && ny <= m && !vis[nx][ny] && tp.a[nx][ny]) {
				vis[nx][ny] = 1;
				qx[++ta] = nx;
				qy[ta] = ny;
			}
		}
		++he;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(tp.a[i][j] && !vis[i][j]) return 0;
	return 1;
}

void dfs(int x, int y) {
	if(x > n)  {
		if(checki()) li[++tots] = tp;
		return;
	}
	if(y > m) return dfs(x+1, 1);
	tp.a[x][y] = 0; dfs(x, y+1);
	tp.a[x][y] = 1; dfs(x, y+1);
}

int val1[505];

int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	n = read(), m = read();
	if(n == 1) {
		for(int i = 1; i <= m; ++i)
			val1[i] = gc();
		int ans = 0;
		for(int i = 2; i <= m+1; ++i)
			if(val1[i] && !val1[i-1]) ++ans;
		printf("%d\n", ans);
		int lst = 1;
		for(; ans; --ans) {
			for(; lst <= m; ++lst)
				if(val1[lst]) break;
			puts("+");
			for(int i = 1; i < lst; ++i) putchar('0');
			for(; lst <= m && val1[lst]; ++lst) putchar('1');
			for(int i = lst; i <= m; ++i) putchar('0');
			puts("");
		}
		return 0;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			e.a[i][j] = gc();
	int fl0 = 1;
	for(int i = 1; i <= n && fl0; ++i)
		for(int j = 1; j <= m && fl0; ++j)
			if(e.a[i][j]) fl0 = 0;
	if(fl0) {
		puts("0");
		return 0;
	}
	dfs(1, 1);
	for(int i = 1; i <= tots; ++i)
		if(e == li[i]) {
			puts("1\n+");
			e.print();
			return 0;
		}
	for(int i = 1; i <= tots; ++i)
		for(int j = 1; j <= tots; ++j) {
			tp = li[i] - li[j];
			if(e == tp) {
				puts("2\n+");
				li[i].print();
				puts("-");
				li[j].print();
				return 0;
			}
		}
	for(int i = 1; i <= tots; ++i)
		for(int j = 1; j <= tots; ++j)
			for(int k = 1; k <= tots; ++k) {
				tp = li[i] + li[k] - li[j];
				if(e == tp) {
					puts("3\n+");
					li[i].print();
					puts("+");
					li[k].print();
					puts("-");
					li[j].print();
					return 0;
				}
			}
	return 0;
}
