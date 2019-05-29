#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<iostream>
#define M 44
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
struct Note {
	int l, r, id, f;
} note[M];
int n, m;
int sta[M], tp, op[M];
int sum[M];

void check() {
	memset(sum, 0, sizeof(sum));
	for(int i = 1; i <= m; i++) {
		int v = op[i];
		if(op[i] == 0) v = -1;
		sum[note[i].l] += v;
		sum[note[i].r + 1] -= v;
	}
	for(int i = 1; i <= tp; i++) {
		sum[i] += sum[i - 1];
		if(sum[i] > 1 || sum[i] < -1) return;
	}
	for(int i = 1; i <= m; i++) cout << op[i] << " ";
	exit(0);
}

void dfs(int now) {
	if(now == m + 1) {
		check();
		return;
	}
	if(note[now].f == -1) {
		op[now] = 0;
		dfs(now + 1);
		op[now] = 1;
		dfs(now + 1);
	} else {
		op[now] = note[now].f;
		dfs(now + 1);
	}
}

int main() {
	freopen("wait.in", "r", stdin); freopen("wait.out", "w", stdout);
	m = read(), n = read();
	for(int i = 1; i <= m; i++) {
		note[i].l = read(), note[i].r = read(), note[i].id = i, note[i].f = read();
		sta[++tp] = note[i].l;
		sta[++tp] = note[i].r;
	}
	sort(sta + 1, sta + tp + 1);
	for(int i = 1; i <= m; i++) {
		note[i].l = lower_bound(sta + 1, sta + tp + 1, note[i].l) - sta;
		note[i].r = lower_bound(sta + 1, sta + tp + 1, note[i].r) - sta;
	}
	dfs(1);
	cout << "-1";

	return 0;
}
