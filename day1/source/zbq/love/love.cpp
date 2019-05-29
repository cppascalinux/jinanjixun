#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<iostream>
#define M 100100
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
int n, m, a[M];
vector<pair<int, int> > to[M];

int f[11][11][1 << 10];
int ans[11];
int fa[M];
void dfs1(int now, int f) {
	fa[now] = f;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i].first;
		if(vj == f) continue;
		dfs1(vj, now);
	}
}
void dfs(int now, int up, int hv, int cost) {
	if(cost >= f[now][up][hv]) return;
	f[now][up][hv] = cost;
	if(now == 0 && hv == ((1 << n) - 1)) {
		ans[up] = min(ans[up], cost);
		return;
	}
	if(up < m) {
		dfs(now, up + 1, hv, cost);
		for(int i = 0; i < n; i++) {
			if(hv & (1 << i)) continue;
			dfs(i, up + 1, hv, cost + a[up + 1]);
		}
	}
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i].first, v = to[now][i].second;
		if(vj == fa[now]) dfs(vj, up, hv | (1 << now), cost + v);
		else dfs(vj, up, hv | (1 << vj), cost + v);
	}
}

void work1() {
	dfs1(0, -1);
	memset(f, 0x3e, sizeof(f));
	memset(ans, 0x3e, sizeof(ans));
	dfs(0, 0, 1, 0);
	for(int i = 0; i <= m; i++) cout << ans[i] << " ";
}




int main() {
	freopen("love.in", "r", stdin); freopen("love.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i < n; i++) {
		int vi = read() - 1, vj = read() - 1, w = read();
		to[vi].push_back(mmp(vj, w));
		to[vj].push_back(mmp(vi, w));
	}
	for(int i = 1; i <= m; i++) a[i] = read();
	if(n <= 10 && m <= 10) work1();
	else {
		return 0 * puts("GG");
	}
	return 0;
}
