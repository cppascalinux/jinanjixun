
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 10010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}

int n, cor[M];
vector<int> to[M];
int vis[M], cnt, deep[M];
void dfss(int now, int f) {
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vj == f) continue;
		deep[vj] = deep[now] + 1;
		dfss(vj, now);
	}
}

void dfs(int now, int v, int x) {
	cor[now] = x;
	vis[now] = cnt;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vis[vj] == cnt || cor[vj] != v) continue;
		dfs(vj, v, x);
	}
}
int maxx, minn, tot;

void dfsss(int now, int x) {
	maxx = max(maxx, deep[now]);
	minn = min(minn, deep[now]);
	vis[now] = cnt;
	tot++;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vis[vj] == cnt || cor[vj] != x) continue;
		dfsss(vj, x);
	}
}

void work(int x) {
	maxx = 0, minn = 0x3e3e3e3e;
	cnt++;
	tot = 0;
	dfsss(x, cor[x]);
	cout << cor[x] << " " << tot << " " << maxx - minn + 1 << "\n";
}


int main() {
	freopen("su.in", "r", stdin); freopen("su.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++) {
		int x = read();
		if(i == 1) continue;
		to[x].push_back(i);
		to[i].push_back(x);
	}
	dfss(1, 0);
	for(int i = 1; i <= n; i++) cor[i] = read();
	int m = read();
	while(m--) {
		int op = read();
		if(op == 1) {
			int x = read(), y = read();
			cor[x] = y;
		}
		if(op == 2) {
			int x = read(), y = read();
			cnt++;
			dfs(x, cor[x], y);
		}
		if(op == 3) {
			int x = read();
			work(x);
		}
	}
	return 0;
}


