
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 100010
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
vector<int> to[M];
vector<int> zz[M];
int ln[M], rn[M], fa[M], deep[M], n, m, q;
bool vis[1010];
void dfs(int now, int f) {
	fa[now] = f;
	deep[now] = deep[f] + 1;
	for(int i = 0; i < to[now].size(); i++) {
		int vj = to[now][i];
		if(vj == f) continue;
		dfs(vj, now);
	}
}

bool del[5050];
void insert(int a, int b) {
	while(a != b) {
		if(deep[a] < deep[b]) swap(a, b);
		vis[a] = true;
		del[a] = 1;
		a = fa[a];
	}
	del[a] = 1;
}
int cor[5050], cnt;
void dfss(int now) {
	cor[now] = cnt;
	for(int i = 0; i < zz[now].size(); i++) {
		int vj = zz[now][i];
		if(cor[vj] == cnt) continue;
		dfss(vj);
	}
}

void work() {
	for(int i = 1; i <= n; i++) {
		if(vis[i]) zz[fa[i]].push_back(i), zz[i].push_back(fa[i]);
	}
	cnt++;
	int tot = 0;
	for(int i = 1; i <= n; i++) {
		if(del[i] && cor[i] != cnt) {
			dfss(i);
			tot++;
		}
	}
	cout << tot << "\n";
}

int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	n = read(), m = read(), q = read();
	for(int i = 1; i < n; i++) {
		int vi = read(), vj = read();
		to[vi].push_back(vj);
		to[vj].push_back(vi);
	}
	dfs(1, 0);
	for(int i = 1; i <= m; i++) {
		ln[i] = read(), rn[i] = read();
	}
	while(q--) {
		int l = read(), r = read();
		for(int i = l; i <= r; i++) {
			insert(ln[i], rn[i]);
		}
		work();
		for(int i = 1; i <= n; i++) vector<int>().swap(zz[i]);
		memset(vis, 0, sizeof(vis));
		memset(del, 0, sizeof(del));
	}
	return 0;
}



