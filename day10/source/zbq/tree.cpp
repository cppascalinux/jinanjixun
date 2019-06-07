
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#define ll long long
#define M 10100
#define mmp make_pair
using namespace std;
int read() {
	int nm = 0, f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c); c = getchar()) nm = nm * 10 + c - '0';
	return nm * f;
}
int n;
vector<pair<int, int> > to1[M], to2[M];
int dis1[M], dis2[M];
int vis[M], cor;
const int mod = 1000000007;
void add(int &x, int y) {
	x += y;
	x -= x >= mod ? mod : 0;
}
int mul(int a, int b) {
	return 1ll * a * b % mod;
}

void dfs1(int now) {
	vis[now] = cor;
	for(int i = 0; i < to1[now].size(); i++) {
		int vj = to1[now][i].first;
		if(vis[vj] == cor) continue;
		dis1[vj] = dis1[now] + to1[now][i].second;
		dfs1(vj);
	}
}


void dfs2(int now) {
	vis[now] = cor;
	for(int i = 0; i < to2[now].size(); i++) {
		int vj = to2[now][i].first;
		if(vis[vj] == cor) continue;
		dis2[vj] = dis2[now] + to2[now][i].second;
		dfs2(vj);
	}
}

int main() {
	freopen("tree.in", "r", stdin); freopen("tree.out", "w", stdout);
	n = read();
	for(int i = 1; i < n; i++) {
		int vi = read(), vj = read(), v = read();
		to1[vi].push_back(mmp(vj, v));
		to1[vj].push_back(mmp(vi, v));
	}
	for(int i = 1; i < n; i++) {
		int vi = read(), vj = read(), v = read();
		to2[vi].push_back(mmp(vj, v));
		to2[vj].push_back(mmp(vi, v));
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		memset(dis1, 0, sizeof(dis1));
		memset(dis2, 0, sizeof(dis2));
		cor++;
		dfs1(i);
		cor++;
		dfs2(i);
		for(int j = 1; j <= n; j++) {
			add(ans, mul(dis1[j], dis2[j]));
		}
	}
	cout << ans << "\n";
	return 0;
}


