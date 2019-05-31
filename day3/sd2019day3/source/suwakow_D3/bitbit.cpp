#include <queue>
#include <cstdio>
#include <cctype>
#include <utility>
#include <cstring>
#include <iostream>
#include <algorithm>
#define R register
#define ll long long
#define pii pair<int, int>
using namespace std;
const int N = 510, M = N * N;

int xj[4] = {0, 0, -1, 1}, yj[4] = {1, -1, 0, 0};
int n, m, tab[N][N], col[N][N], cnt, visCol[M], vis[N][N], listCol[M], failed[N][N], cover[N][N], fa[M];
char s[N];
pii stck[M], pre[N][N];
queue<pii> que;
struct node {
	int y, x, col;
	node (int y = 0, int x = 0, int col = 0) : y(y), x(x), col(col) {}
};

inline void swap(int &x, int &y) {
	int z = x;
	x = y, y = z;
	return;
}

inline void bfs1() {
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			if (!col[i][j] && tab[i][j]) {
				++cnt;
				while (que.size()) que.pop();
				que.push(make_pair(i, j));
				while (que.size()) {
					pii now = que.front();
					que.pop();
					int y = now.first, x = now.second, tpy, tpx;
					col[y][x] = cnt;
					for (R int k = 0; k <= 3; ++k)
						if (!col[tpy = y + yj[k]][tpx = x + xj[k]] && tab[tpy][tpx])
							que.push(make_pair(tpy, tpx));
				}
			}
	return;
}

inline bool bfs2() {
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			if (!tab[i][j] && !failed[i][j]) {
				while (que.size()) que.pop();
				int top = 0, tot = 0;
				que.push(make_pair(i, j));
				while (que.size()) {
					stck[++top] = que.front();
					que.pop();
					int y = stck[top].first, x = stck[top].second, tpy, tpx;
					vis[y][x] = 1;
					for (R int k = 0; k <= 3; ++k) {
						tpy = y + yj[k], tpx = x + xj[k];
						if (tpy < 1 || tpy > n || tpx < 1 || tpx > m)
							continue;
						if (!tab[tpy][tpx] && !vis[tpy][tpx])
							que.push(make_pair(tpy, tpx));
						if (tab[tpy][tpx]) {
							if (!visCol[col[tpy][tpx]])
								listCol[++tot] = col[tpy][tpx];
							visCol[col[tpy][tpx]] = 1;
						}
					}
				}
				if (tot == cnt)
					return 1;
				while (tot)
					visCol[listCol[tot--]] = 0;
				while (top)
					vis[stck[top].first][stck[top].second] = 0, failed[stck[top].first][stck[top].second] = 1, --top;
			}
	return 0;
}

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

inline void unity(int x, int y) {
	fa[find(x)] = find(y);
	return;
}

inline void bfs3() {
	queue<node> que;
	while (que.size()) que.pop();
	int midn = (1 + n) >> 1, midm = (1 + m) >> 1;
	for (R int i = midn; i <= n; ++i)
		for (R int j = midm; j <= m; ++j)
			if (tab[i][j])
				que.push(node(i, j, col[i][j]));
	for (R int i = midn; i <= n; ++i)
		for (R int j = midm - 1; j; --j)
			if (tab[i][j])
				que.push(node(i, j, col[i][j]));
	for (R int i = midn - 1; i; --i)
		for (R int j = midm; j <= m; ++j)
			if (tab[i][j])
				que.push(node(i, j, col[i][j]));
	for (R int i = midn - 1; i; --i)
		for (R int j = midm - 1; j; --j)
			if (tab[i][j])
				que.push(node(i, j, col[i][j]));
	while (que.size()) {
		node now = que.front();
		que.pop();
		int y = now.y, x = now.x, tpy, tpx;
		for (R int i = 0; i <= 3; ++i) {
			tpy = y + yj[i], tpx = x + xj[i];
			if (tpy < 1 || tpy > n || tpx < 1 || tpy > m || tab[tpy][tpx] || failed[tpy][tpx])
				continue;
			if (cover[tpy][tpx]) {
				if (find(cover[tpy][tpx]) != find(now.col)) {
					unity(cover[tpy][tpx], now.col);
					for (int px = x, py = y, tmp; px && py && !vis[py][px]; px = pre[py][px].second, py = pre[py][tmp].first)
						tmp = px, vis[py][px] = 1;
					for (int px = tpx, py = tpy, tmp; px && py && !vis[py][px]; px = pre[py][px].second, py = pre[py][tmp].first)
						tmp = px, vis[py][px] = 1;
				}
				continue;
			}
			cover[tpy][tpx] = now.col, pre[tpy][tpx] = make_pair(y, x);
			que.push(node(tpy, tpx, now.col));
		}
	}
	return;
}

int main() {
	freopen("bitbit.in", "r", stdin);
	freopen("bitbit.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (R int i = 1; i <= n; ++i) {
		scanf("%s", s + 1);
		for (R int j = 1; j <= m; ++j)
			tab[i][j] = s[j] - '0';
	}
	bfs1();
	if (m == 1) {
		printf("%d\n", cnt);
		for (R int i = 1; i <= cnt; ++i) {
			printf("+\n");
			for (R int j = 1; j <= n; ++j)
				printf("%d\n", col[j][1] == i);
		}
		return 0;
	}
	if (n == 1) {
		printf("%d\n", cnt);
		for (R int i = 1; i <= cnt; ++i) {
			printf("+\n");
			for (R int j = 1; j <= m; ++j)
				printf("%d", col[1][j] == i);
			printf("\n");
		}
		return 0;
	}
	if (cnt == 1) {
		printf("1\n+\n");
		for (R int i = 1; i <= n; ++i) {
			for (R int j = 1; j <= m; ++j)
				printf("%d", tab[i][j]);
			printf("\n");
		}
		return 0;
	}
	if (bfs2()) {
		printf("2\n+\n");
		for (R int i = 1; i <= n; ++i) {
			for (R int j = 1; j <= m; ++j)
				printf("%d", tab[i][j] || vis[i][j]);
			printf("\n");
		}
		printf("-\n");
		for (R int i = 1; i <= n; ++i) {
			for (R int j = 1; j <= m; ++j)
				printf("%d", vis[i][j]);
			printf("\n");
		}
		return 0;
	}
	for (R int i = 1; i <= n; ++i)
		for (R int j = 1; j <= m; ++j)
			vis[i][j] = failed[i][j] = 0;
	for (R int i = 1; i <= cnt; ++i)
		fa[i] = i;
	printf("3\n+\n");
	bfs3();
	for (R int i = 1; i <= n; ++i) {
		for (R int j = 1; j <= m; ++j) {
			printf("%d", tab[i][j] || vis[i][j]);
			if (vis[i][j]) failed[i][j] = 1;
			vis[i][j] = cover[i][j] = 0;
		}
		printf("\n");
	}
	printf("+\n");
	for (R int i = 1; i <= cnt; ++i)
		fa[i] = i;
	bfs3();
	for (R int i = 1; i <= n; ++i) {
		for (R int j = 1; j <= m; ++j) {
			printf("%d", tab[i][j] || vis[i][j]);
			if (vis[i][j]) failed[i][j] = 1;
		}
		printf("\n");
	}
	printf("-\n");
	for (R int i = 1; i <= n; ++i) {
		for (R int j = 1; j <= m; ++j)
			printf("%d", tab[i][j] || failed[i][j]);
		printf("\n");
	}
	return 0;
}
